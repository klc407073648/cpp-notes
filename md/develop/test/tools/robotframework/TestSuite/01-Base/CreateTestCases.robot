*** Settings ***
Documentation     Example using the space separated format.
Library           OperatingSystem
Library           Process
Library           BuiltIn

*** Variables ***
${MESSAGE}        Hello,world!

*** Test Cases ***
Test With Settings
    [Documentation]    学习Settings的内容
    [Tags]    Test    Settings
    [Setup]    Log    begin Test With Settings
    [Timeout]    3
    #Sleep    5    #会超时
    Log    ${MESSAGE}
    [Teardown]    Log    end Test With Settings

Example
    [Documentation]    运行python程序，待解决:FAIL : OSError: [WinError 193] %1 不是有效的 Win32 应用程序
    Log    ${CURDIR}
    Import Library    D:/CODE/klc/autoTest/studyTest/testPython.py
    Run Process    D:/CODE/klc/autoTest/studyTest/testPython.py

Copy Example
    [Documentation]    创建文件夹以及拷贝文件
    Create Directory    ${CURDIR}/stuff
    Copy File    ${CURDIR}/testPython.py    ${CURDIR}/stuff

*** Keywords ***
Run Program
    [Arguments]    @{args}
    Run Process    program.py    @{args}    # Named arguments are not recognized from inside @{args}

My Keyword
    [Arguments]    ${path}
    Directory Should Exist    ${path}
