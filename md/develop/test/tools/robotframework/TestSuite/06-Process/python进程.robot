*** Settings ***
Suite Teardown    Terminate All Processes    kill=True
Library           OperatingSystem
Library           Process

*** Test Cases ***
shell执行结果内容测试
    ${result} =    Run Process    sh    ${CURDIR}/test.sh
    Print Result Detail    ${result}
    Should Be Equal    ${result.rc}    ${0}
    Should Match    ${result.stdout}    test.sh
    Should Be Empty    ${result.stderr}
    Should Be Equal As Strings    ${result.stdout_path}    None
    Should Be Equal As Strings    ${result.stderr_path}    None

*** Keywords ***
Print Result Detail
    [Arguments]    ${result}
    [Documentation]    打印Process的结果信息内容
    Log    rc:${result.rc}
    Log    stdout:${result.stdout}
    Log    stderr:${result.stderr}
    Log    stdout_path:${result.stdout_path}
    Log    stderr_path:${result.stderr_path}
