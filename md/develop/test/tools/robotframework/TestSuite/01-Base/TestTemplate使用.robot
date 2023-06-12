*** Settings ***
Documentation     Test Template示例
Test Template     Example keyword

*** Test Cases ***
Templated test case
    first round 1    first round 2
    second round 1    second round 2
    third round 1    third round 2

*** Keywords ***
Example keyword
    [Arguments]    ${first}    ${second}
    Log    ${first}+${second}
