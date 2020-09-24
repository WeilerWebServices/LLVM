import smtplib
import lnt.server.reporting.runs


def emailReport(result, session, run, baseurl, email_config, to,
                was_added=True):
    import email.mime.multipart
    import email.mime.text

    subject, report, html_report = _getReport(result, session, run, baseurl,
                                              was_added)

    # Ignore if no to address was given, we do things this way because of the
    # awkward way we collect result information as part of generating the email
    # report.
    if email_config is None or to is None:
        return

    # Generate a plain text message if we have no html report.
    if not html_report:
        msg = email.mime.text.MIMEText(report.encode('utf-8'), 'plain', 'utf-8')
        msg['Subject'] = subject
        msg['From'] = email_config.from_address
        msg['To'] = to
    else:
        msg = email.mime.multipart.MIMEMultipart('alternative')
        msg['Subject'] = subject
        msg['From'] = email_config.from_address
        msg['To'] = to

        # Attach parts into message container, according to RFC 2046, the last
        # part of a multipart message, in this case the HTML message, is best
        # and preferred.
        msg.attach(email.mime.text.MIMEText(report.encode('utf-8'), 'plain', 'utf-8'))
        msg.attach(email.mime.text.MIMEText(html_report.encode('utf-8'), 'html', 'utf-8'))

    s = smtplib.SMTP(email_config.host)
    s.sendmail(email_config.from_address, [to], msg.as_string())
    s.quit()


def _getReport(result, session, run, baseurl, was_added, compare_to=None):
    data = lnt.server.reporting.runs.generate_run_data(
        session, run, baseurl=baseurl, result=result, compare_to=compare_to,
        num_comparison_runs=10)

    env = lnt.server.ui.app.create_jinja_environment()
    text_template = env.get_template('reporting/run_report.txt')
    text_report = text_template.render(data)
    html_template = env.get_template('reporting/run_report.html')
    html_report = html_template.render(data)
    return data['subject'], text_report, html_report
