import contextlib
import logging
import pprint
import sys

import click

import lnt.formats
from lnt.lnttool.common import submit_options, init_logger
from lnt.server.db.rules_manager import register_hooks


@click.command("import")
@click.argument("instance_path", type=click.UNPROCESSED)
@click.argument("files", nargs=-1, type=click.Path(exists=True), required=True)
@click.option("--database", default="default", show_default=True,
              help="database to modify")
@click.option("--format", "output_format", show_default=True,
              type=click.Choice(lnt.formats.format_names + ['<auto>']),
              default='<auto>', help="input format")
@click.option("--show-sql", is_flag=True, help="show SQL statements")
@click.option("--show-sample-count", is_flag=True)
@click.option("--show-raw-result", is_flag=True)
@click.option("--testsuite", "-s", default='nts')
@click.option("--verbose", "-v", is_flag=True,
              help="show verbose test results")
@click.option("--quiet", "-q", is_flag=True, help="don't show test results")
@click.option("--no-email", is_flag=True, help="don't send e-mail")
@click.option("--no-report", is_flag=True, help="don't generate report")
@submit_options
def action_import(instance_path, files, database, output_format, show_sql,
                  show_sample_count, show_raw_result, testsuite, verbose,
                  quiet, no_email, no_report, select_machine, merge):
    """import test data into a database"""
    import lnt.server.instance
    import lnt.util.ImportData

    init_logger(logging.INFO if verbose or show_sql else logging.WARNING,
                show_sql=show_sql)

    # Load the LNT instance.
    instance = lnt.server.instance.Instance.frompath(instance_path)
    config = instance.config

    register_hooks()

    # Get the database.
    with contextlib.closing(config.get_database(database)) as db:
        session = db.make_session()
        # Load the database.
        success = True
        for file_name in files:
            result = lnt.util.ImportData.import_and_report(
                config, database, db, session, file_name,
                output_format, testsuite, show_sample_count, no_email,
                no_report, select_machine=select_machine, merge_run=merge)

            success &= result.get('success', False)
            if quiet:
                continue

            if show_raw_result:
                pprint.pprint(result)
            else:
                lnt.util.ImportData.print_report_result(result, sys.stdout,
                                                        sys.stderr, verbose)

        if not success:
            raise SystemExit(1)
