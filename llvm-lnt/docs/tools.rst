.. _tools:

The ``lnt`` Tool
================

The ``lnt`` command line utility provides the following commands for client-side
use and server-side use. The following is a list of commands and the most
importat options, use ``lnt <toolname> --help`` for more information on any
particular tool.

Client-Side Tools
-----------------

  ``lnt checkformat [<file>]``
    Checks the syntax of an LNT test report file. In addition to verifying that
    LNT can read the raw format (e.g., JSON or property list), this also creates
    a temporary in-memory database instance and ensures that the test report
    file can be imported correctly.

    If run without arguments, this expects to read the input file from ``stdin``.

  ``lnt convert <input path> [<output path>]``
    Convert between LNT test report formats. By default, this will convert to
    the property list format. You can use ``-`` for either the input (to read
    from ``stdin) or the output (to write to ``stdout``).

  ``lnt importreport <input path> [<output path>]``
    Convert text based key value pairs into a LNT json report file.

  ``lnt submit <server url> <file>+``
    Submits one or more files to the given server. The ``<server url>`` should
    be the url to the actual ``submitRun`` page on the server; the database
    being submitted to is effectively a part of this URL.

  ``lnt showtests``
    List available built-in tests. See the :ref:`tests` documentation for more
    details on this tool.

  ``lnt runtest [<run options>] <test name> ... test arguments ...``
    Run a built-in test. See the :ref:`tests` documentation for more
    details on this tool.

  ``lnt check-no-errors <file>+``
    Check that the report file contains `"no_errors": true` in their run section
    otherwise end with returncode 1. This is useful for continuous integration
    scripts which want to report an error if any of the benchmarks didn't
    compile or run correctly.


Server Administration
~~~~~~~~~~~~~~~~~~~~~

The ``lnt admin`` tool allows connecting to a server through LNTs REST API and
perform data queries and modifications. Data modification is only possible with
an authentication mechanism specified in the `lntadmin.cfg` file.  See
:ref:`auth_tokens` for details.

  ``lnt admin create-config``
  Create a `lntadmin.cfg` configuration file in the current directory. The file
  describes the URL, authentication settings and default database and
  test-suite settings for an LNT server. The other admin commands read this
  file if it exists.

  ``lnt admin list-machines``
  List machines and their id numbers

  ``lnt admin machine-info <machine>``
  Display information about the specified machine.

  ``lnt admin get-machine <machine>``
  Download machine information and save data in a json file.

  ``lnt admin rm-machine <machine>``
  Removes the specified machine and related runs and samples.

  ``lnt admin rename-machine <machine> <new-name>``
  Renames the specified machine.

  ``lnt admin merge-machine-into <machine> <merge-into-machine>``
  Move all runs from one machine to another machine and delete the machine.

  ``lnt admin list-runs <machine>``
  List all runs for the specified machine.

  ``lnt admin get-run <run>+``
  Download the specified runs.

  ``lnt admin post-run <filename>+``
  Post the specified report files as a new runs to the server.

  ``lnt admin rm-run <run>+``
  Remove the specified runs and related samples.


Server-Side Tools
-----------------

The following tools are used to interact with an LNT server:

  ``lnt create <path>``
    Creates a new LNT server instance. This command has a number of parameters
    to tweak the generated server, but they can all be modified after the fact
    in the LNT configuration file.

    The default server will have a sqlite3 database named *default*. You can
    specify to use PostgreSQL using ``--db-dir postgresql://user@hostname``.

  ``lnt import <instance path> <file>+``
    Import an LNT data file into a database. You can use ``--database`` to
    select the database to write to. Note that by default this will also
    generate report emails if enabled in the configuration, you can use
    ``--no-email`` to disable this.

  ``lnt runserver <instance path>``
    Start the LNT server using a development WSGI server. Additional options can
    be used to control the server host and port, as well as useful development
    features such as automatic reloading.

  ``lnt updatedb --database <NAME> --testsuite <NAME> <instance path>``
    Modify the given database and testsuite.

    Currently the only supported commands are ``--delete-machine`` and
    ``--delete-run``.

All commands which take an instance path support passing in either the path to
the ``lnt.cfg`` file, the path to the instance directory, or the path to a
(compressed) tarball. The tarball will be automatically unpacked into a
temporary directory and removed on exit. This is useful for testing and for
passing database instances back and forth, for example when others only need to
be able to view the results.
