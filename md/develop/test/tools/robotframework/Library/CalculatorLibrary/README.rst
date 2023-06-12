====================
Robot Framework Demo
====================

`Robot Framework`_ is a generic open source test automation framework.
In addition to introducing Robot Framework test data syntax, this demo
shows how to execute test cases, how generated reports and logs
look like, and how to extend the framework with custom test libraries.

.. contents:: **Contents:**
   :depth: 1
   :local:

Downloading demo package
========================

To get the demo, you can either `download`_ and extract the latest
package from the GitHub or checkout the `source code`_ directly.
As a result you get ``RobotDemo`` directory with several files.

Example `test cases`_, `test library`_ used by them, and `generated results`_
are available also online. Therefore, you do not need to download the demo if
you are not interested in `running it`__ yourself.

__ `running demo`_

Demo application
================

The demo application is a very simple calculator implemented with Python
(`calculator.py`_). It contains only business logic and no user interface.
You cannot really run the calculator manually.

Test cases
==========

The demo contains three different test case files illustrating three different
approaches for creating test cases with Robot Framework. Click file names below
to see the latest versions online.

`keyword_driven.robot`_
    Example test cases using the *keyword-driven* testing approach.

    All tests contain a workflow constructed from keywords in
    `CalculatorLibrary.py`_. Creating new tests or editing
    existing is easy even for people without programming skills.

    The *keyword-driven* approach works well for normal test
    automation, but the *gherkin* style might be even better
    if also business people need to understand tests. If the
    same workflow needs to repeated multiple times, it is best
    to use to the *data-driven* approach.

`data_driven.robot`_
    Example test cases using the *data-driven* testing approach.

    The *data-driven* style works well when you need to repeat
    the same workflow multiple times.

    Tests use ``Calculate`` keyword created in this file, that in
    turn uses keywords in `CalculatorLibrary.py`_. An exception
    is the last test that has a custom *template keyword*.

`gherkin.robot`_
    Example test case using the *gherkin* syntax.

    This test has a workflow similar to the *keyword-driven*
    examples. The difference is that the keywords use higher
    abstraction level and their arguments are embedded into
    the keyword names.

    This kind of *gherkin* syntax has been made popular by Cucumber_.
    It works well especially when tests act as examples that need to
    be easily understood also by the business people.

As you can see, creating test cases with Robot Framework is very easy.
See `Robot Framework User Guide`_ for details about the test data syntax.

Test library
============

All test cases interact with the calculator using a custom test library named
`CalculatorLibrary.py`_. In practice the library is just a Python class
with methods that create the keywords used by the test cases.

Generated library documentation makes it easy to see what keywords the
library provides. This documentation is created with Libdoc_ tool integrated
with the framework:

- `CalculatorLibrary.html`_

As you can see, Robot Framework's test library API is very simple.
See `Robot Framework User Guide`_ for more information about creating test
libraries, using Libdoc, and so on.

Generated results
=================

After `running tests`_, you will get report and log in HTML format. Example
files are also visible online in case you are not interested in running
the demo yourself. Notice that one of the test has failed on purpose to
show how failures look like.

- `report.html`_
- `log.html`_

Running demo
============

Preconditions
-------------

A precondition for running the tests is having `Robot Framework`_ installed.
It is most commonly used on Python_ but it works also with Jython_ (JVM)
and IronPython_ (.NET). Robot Framework `installation instructions`_
cover installation procedure in detail. People already familiar with
installing Python packages and having `pip`_ package manager installed, can
simply run the following command::

    pip install robotframework

Robot Framework 3.0 and newer support Python 3 in addition to Python 2. Also
this demo project is nowadays Python 3 compatible.

Running tests
-------------

Test cases are executed with the ``robot`` command::

    robot keyword_driven.robot

.. note:: If you are using Robot Framework 2.9 or earlier, you need to
          use Python interpreter specific command ``pybot``, ``jybot`` or
          ``ipybot`` instead.

To execute all test case files in a directory recursively, just give the
directory as an argument. You can also give multiple files or directories in
one go and use various command line options supported by Robot Framework.
The results `available online`__ were created using the following command::

    robot --name Robot --loglevel DEBUG keyword_driven.robot data_driven.robot gherkin.robot

Run ``robot --help`` for more information about the command line usage and see
`Robot Framework User Guide`_ for more details about test execution in general.

__ `Generated results`_


.. _Robot Framework: http://robotframework.org
.. _download: https://github.com/robotframework/RobotDemo/archive/master.zip
.. _source code: https://github.com/robotframework/RobotDemo.git
.. _calculator.py: https://github.com/robotframework/RobotDemo/blob/master/calculator.py
.. _keyword_driven.robot: https://github.com/robotframework/RobotDemo/blob/master/keyword_driven.robot
.. _CalculatorLibrary.py: https://github.com/robotframework/RobotDemo/blob/master/CalculatorLibrary.py
.. _data_driven.robot: https://github.com/robotframework/RobotDemo/blob/master/data_driven.robot
.. _gherkin.robot: https://github.com/robotframework/RobotDemo/blob/master/gherkin.robot
.. _Cucumber: https://cucumber.io/
.. _Robot Framework User Guide: http://robotframework.org/robotframework/#user-guide
.. _Python: http://python.org
.. _Jython: http://jython.org
.. _IronPython: http://ironpython.net
.. _pip: http://pip-installer.org
.. _installation instructions: https://github.com/robotframework/robotframework/blob/master/INSTALL.rst
.. _Libdoc: http://robotframework.org/robotframework/#built-in-tools
.. _CalculatorLibrary.html: http://robotframework.org/RobotDemo/CalculatorLibrary.html
.. _report.html: http://robotframework.org/RobotDemo/report.html
.. _log.html: http://robotframework.org/RobotDemo/log.html
