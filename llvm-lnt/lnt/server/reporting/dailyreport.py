from future import standard_library
standard_library.install_aliases()
from lnt.server.reporting.analysis import REGRESSED, UNCHANGED_FAIL
from lnt.server.reporting.report import RunResult, RunResults, report_css_styles, pairs, OrderAndHistory
from lnt.util import multidict
import datetime
import lnt.server.reporting.analysis
import lnt.server.ui.app
import re
import sqlalchemy.sql
import urllib.parse


class DailyReport(object):
    def __init__(self, ts, year, month, day, num_prior_days_to_include=3,
                 day_start_offset_hours=16, for_mail=False,
                 filter_machine_regex=None):
        self.ts = ts
        self.hash_of_binary_field = self.ts.Sample.get_hash_of_binary_field()
        self.num_prior_days_to_include = num_prior_days_to_include
        self.year = year
        self.month = month
        self.day = day
        self.fields = list(ts.Sample.get_metric_fields())
        self.day_start_offset = datetime.timedelta(
            hours=day_start_offset_hours)
        self.for_mail = for_mail
        self.filter_machine_regex_str = filter_machine_regex
        self.filter_machine_re = None
        if self.filter_machine_regex_str:
            try:
                self.filter_machine_re = re.compile(filter_machine_regex)
            except re.error:
                pass

        # Computed values.
        self.error = None
        self.next_day = None
        self.prior_days = None
        self.machine_runs = None
        self.reporting_machines = None
        self.reporting_tests = None
        self.result_table = None
        self.nr_tests_table = None

    def get_query_parameters_string(self):
        query_params = [
            "{}={}".format(
                urllib.parse.quote_plus(query_param), urllib.parse.quote_plus(str(value)))
            for query_param, value in (
                ("day_start", self.day_start_offset.seconds // 3600),
                ("num_days", self.num_prior_days_to_include),
                ("filter-machine-regex", self.filter_machine_regex_str),)
            if value is not None]
        # Use &amp; instead of plain & to make sure legal XML is
        # produced, so that the unit tests can parse the output using
        # python's built-in XML parser.
        return "&amp;".join(query_params)

    def get_key_run(self, machine, day_index):
        """
        get_key_run(machine, day_index) -> Run or None

        Get the "key" run for the given machine and day index, or None if there
        are no runs for that machine and day.

        The key run is an arbitrarily selected run from all the available runs
        that reported for the reported run order, for that machine and day.
        """

        if self.machine_runs is None:
            raise ValueError("report not initialized")
        if day_index >= self.num_prior_days_to_include:
            raise ValueError("invalid day index")

        runs = self.machine_runs.get((machine.id, day_index))
        if runs is None:
            return None

        # Select a key run arbitrarily.
        return runs[0]

    def build(self, session):
        ts = self.ts

        # Construct datetime instances for the report range.
        day_ordinal = datetime.datetime(self.year, self.month,
                                        self.day).toordinal()

        # Adjust the dates time component.  As we typically want to do runs
        # overnight, we define "daily" to really mean "daily plus some
        # offset". The offset should generally be whenever the last run
        # finishes on today's date.

        self.next_day = (datetime.datetime.fromordinal(day_ordinal + 1) +
                         self.day_start_offset)
        self.prior_days = [(datetime.datetime.fromordinal(day_ordinal - i) +
                            self.day_start_offset)
                           for i in range(self.num_prior_days_to_include + 1)]

        # Find all the runs that occurred for each day slice.
        prior_runs = [session.query(ts.Run).
                      filter(ts.Run.start_time > prior_day).
                      filter(ts.Run.start_time <= day).all()
                      for day, prior_day in pairs(self.prior_days)]

        if self.filter_machine_re is not None:
            prior_runs = [[run for run in runs
                           if self.filter_machine_re.search(run.machine.name)]
                          for runs in prior_runs]

        # For every machine, we only want to report on the last run order that
        # was reported for that machine for the particular day range.
        #
        # Note that this *does not* mean that we will only report for one
        # particular run order for each day, because different machines may
        # report on different orders.
        #
        # However, we want to limit ourselves to a single run order for each
        # (day,machine) so that we don't obscure any details through our
        # aggregation.
        self.prior_days_machine_order_map = \
            [None] * self.num_prior_days_to_include
        historic_runs = [None] * len(prior_runs)
        for i, runs in enumerate(prior_runs):
            # Aggregate the runs by machine.
            machine_to_all_orders = multidict.multidict()
            for r in runs:
                machine_to_all_orders[r.machine] = r.order

            # Create a map from machine to max order and some history.
            self.prior_days_machine_order_map[i] = machine_order_map = dict(
                (machine, OrderAndHistory(max(orders), sorted(orders)))
                for machine, orders in machine_to_all_orders.items())

            # Update the run list to only include the runs with that order.
            def is_max_order(r):
                return r.order is machine_order_map[r.machine].max_order
            prior_runs[i] = [r for r in runs if is_max_order(r)]

            # Also keep some recent runs, so we have some extra samples.
            def is_recent_order(r):
                return r.order in machine_order_map[r.machine].recent_orders
            historic_runs[i] = [r for r in runs if is_recent_order(r)]

        # Form a list of all relevant runs.
        relevant_runs = sum(prior_runs, [])
        less_relevant_runs = sum(historic_runs, relevant_runs)

        # Find the union of all machines reporting in the relevant runs.
        self.reporting_machines = list(set(r.machine for r in relevant_runs))
        self.reporting_machines.sort(key=lambda m: m.name)

        # We aspire to present a "lossless" report, in that we don't ever hide
        # any possible change due to aggregation. In addition, we want to make
        # it easy to see the relation of results across all the reporting
        # machines. In particular:
        #
        #   (a) When a test starts failing or passing on one machine, it should
        #       be easy to see how that test behaved on other machines. This
        #       makes it easy to identify the scope of the change.
        #
        #   (b) When a performance change occurs, it should be easy to see the
        #       performance of that test on other machines. This makes it easy
        #       to see the scope of the change and to potentially apply human
        #       discretion in determining whether or not a particular result is
        #       worth considering (as opposed to noise).
        #
        # The idea is as follows, for each (machine, test, metric_field),
        # classify the result into one of REGRESSED, IMPROVED, UNCHANGED_FAIL,
        # ADDED, REMOVED, PERFORMANCE_REGRESSED, PERFORMANCE_IMPROVED.
        #
        # For now, we then just aggregate by test and present the results as
        # is. This is lossless, but not nearly as nice to read as the old style
        # per-machine reports. In the future we will want to find a way to
        # combine the per-machine report style of presenting results aggregated
        # by the kind of status change, while still managing to present the
        # overview across machines.

        # Aggregate runs by machine ID and day index.
        self.machine_runs = machine_runs = multidict.multidict()
        for day_index, day_runs in enumerate(prior_runs):
            for run in day_runs:
                machine_runs[(run.machine_id, day_index)] = run

        # Also aggregate past runs by day.
        self.machine_past_runs = multidict.multidict()
        for day_index, day_runs in enumerate(historic_runs):
            for run in day_runs:
                self.machine_past_runs[(run.machine_id, day_index)] = run

        relevant_run_ids = [r.id for r in relevant_runs]

        # If there are no relevant runs, just stop processing (the report will
        # generate an error).
        if not relevant_run_ids:
            self.error = "no runs to display in selected date range"
            return

        # Get the set all tests reported in the recent runs.
        self.reporting_tests = session.query(ts.Test).filter(
            sqlalchemy.sql.exists('*', sqlalchemy.sql.and_(
                    ts.Sample.run_id.in_(relevant_run_ids),
                    ts.Sample.test_id == ts.Test.id))).all()
        self.reporting_tests.sort(key=lambda t: t.name)

        run_ids_to_load = list(relevant_run_ids) + \
            [r.id for r in less_relevant_runs]

        # Create a run info object.
        sri = lnt.server.reporting.analysis.RunInfo(session, ts,
                                                    run_ids_to_load)

        # Build the result table of tests with interesting results.
        def compute_visible_results_priority(visible_results):
            # We just use an ad hoc priority that favors showing tests with
            # failures and large changes. We do this by computing the priority
            # as tuple of whether or not there are any failures, and then sum
            # of the mean percentage changes.
            test, results = visible_results
            had_failures = False
            sum_abs_day0_deltas = 0.
            for machine, day_results in results:
                day0_cr = day_results[0].cr

                test_status = day0_cr.get_test_status()

                if (test_status == REGRESSED or test_status == UNCHANGED_FAIL):
                    had_failures = True
                elif day0_cr.pct_delta is not None:
                    sum_abs_day0_deltas += abs(day0_cr.pct_delta)
            return (-int(had_failures), -sum_abs_day0_deltas, test.name)

        self.result_table = []
        self.nr_tests_table = []
        for field in self.fields:
            field_results = []
            for test in self.reporting_tests:
                # For each machine, compute if there is anything to display for
                # the most recent day, and if so add it to the view.
                visible_results = []
                for machine in self.reporting_machines:
                    # Get the most recent comparison result.
                    # Record which days have samples, so that we'll compare
                    # also consecutive runs that are further than a day
                    # apart if no runs happened in between.
                    day_has_samples = []
                    for i in range(0, self.num_prior_days_to_include):
                        runs = self.machine_past_runs.get((machine.id, i), ())
                        samples = sri.get_samples(runs, test.id)
                        day_has_samples.append(len(samples) > 0)

                    def find_most_recent_run_with_samples(day_nr):
                        for i in range(day_nr+1,
                                       self.num_prior_days_to_include):
                            if day_has_samples[i]:
                                return i
                        return day_nr+1

                    prev_day_index = find_most_recent_run_with_samples(0)
                    day_runs = machine_runs.get((machine.id, 0), ())
                    prev_runs = self.machine_past_runs.get(
                        (machine.id, prev_day_index), ())
                    cr = sri.get_comparison_result(
                        day_runs, prev_runs, test.id, field,
                        self.hash_of_binary_field)

                    # If the result is not "interesting", ignore this machine.
                    if not cr.is_result_interesting():
                        continue

                    # Otherwise, compute the results for all the days.
                    day_results = RunResults()
                    day_results.append(RunResult(cr))
                    for i in range(1, self.num_prior_days_to_include):
                        day_runs = machine_runs.get((machine.id, i), ())
                        if len(day_runs) == 0:
                            day_results.append(None)
                            continue

                        prev_day_index = find_most_recent_run_with_samples(i)
                        prev_runs = self.machine_past_runs.get(
                                       (machine.id, prev_day_index), ())
                        cr = sri.get_comparison_result(
                            day_runs, prev_runs, test.id, field,
                            self.hash_of_binary_field)
                        day_results.append(RunResult(cr))

                    day_results.complete()

                    # Append the result for the machine.
                    visible_results.append((machine, day_results))

                # If there are visible results for this test, append it to the
                # view.
                if visible_results:
                    field_results.append((test, visible_results))

            # Order the field results by "priority".
            field_results.sort(key=compute_visible_results_priority)
            self.result_table.append((field, field_results))

        for machine in self.reporting_machines:
            nr_tests_for_machine = []
            for i in range(0, self.num_prior_days_to_include):
                # get all runs with the same largest "order" on a given day
                day_runs = machine_runs.get((machine.id, i), ())
                nr_tests_seen = 0
                for test in self.reporting_tests:
                    samples = sri.get_samples(day_runs, test.id)
                    if len(samples) > 0:
                        nr_tests_seen += 1
                nr_tests_for_machine.append(nr_tests_seen)
            self.nr_tests_table.append((machine, nr_tests_for_machine))

    def render(self, ts_url, only_html_body=True):
        # Strip any trailing slash on the testsuite URL.
        if ts_url.endswith('/'):
            ts_url = ts_url[:-1]

        env = lnt.server.ui.app.create_jinja_environment()
        template = env.get_template('reporting/daily_report.html')

        return template.render(
            report=self, styles=report_css_styles, analysis=lnt.server.reporting.analysis,
            ts_url=ts_url, only_html_body=only_html_body)
