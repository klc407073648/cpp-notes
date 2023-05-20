*** Settings ***
Documentation     Template示例

*** Variables ***
@{ITEMS}          this    list    is    quite    long
@{NUMS}           7    6    1    2    3

*** Test Cases ***
Normal test case
    Example keyword    first argument    second argument

Templated test case
    [Template]    Example keyword
    first argument    second argument

Normal test case with embedded arguments
    The result of 1 + 1 should be 2
    The result of 1 + 2 should be 3

Template with embedded arguments
    [Template]    The result of ${calculation} should be ${expected}
    1 + 1    2
    1 + 2    3

Template with for loop
    [Template]    Example keyword
    FOR    ${item}    IN    @{ITEMS}
        ${item}    2nd arg
    END
    FOR    ${index}    IN RANGE    5
        1st arg    ${index}
    END

Template with for and if
    [Template]    Example keyword
    FOR    ${item}    IN    @{NUMS}
        IF    ${item} < 5
        ${item}    2nd arg
    END
    END

*** Keywords ***
Example keyword
    [Arguments]    ${first}    ${second}
    Log    ${first}+${second}

The result of ${calculation} should be ${expected}
    ${result} =    Evaluate    ${calculation}    #Calculate    Evaluate
    Should Be Equal    ${result}    ${expected}
