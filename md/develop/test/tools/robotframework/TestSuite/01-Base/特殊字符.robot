*** Settings ***
Documentation     特殊字符使用
Default Tags      Base
Library           OperatingSystem

*** Variables ***
${MESSAGE}        Hello, world!
${MESSAGE1}       Test,\ \ ${SPACE}world!

*** Test Cases ***
变量相等测试
    Should Be Equal    ${MESSAGE}    Hello, world!

转义字符测试
    Should Be Equal    ${MESSAGE1}    Test,${SPACE*3}world!

反斜杠字符测试
    Do Something    first arg    ${EMPTY}
    Do Something    \    second arg

*** Keywords ***
Do Something
    [Arguments]    ${first}    ${second}
    Log    ${first}+${second}
