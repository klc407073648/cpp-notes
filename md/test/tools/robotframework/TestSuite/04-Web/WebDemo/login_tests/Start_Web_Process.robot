*** Settings ***
Documentation     A test suite with a single test for valid login.
...
...               This test has a workflow that is created using keywords in
...               the imported resource file.
Library           Process
Resource          resource.robot

*** Test Cases ***
Run Web Process
    Start Process    python    ${CURDIR}/../demoapp/server.py
