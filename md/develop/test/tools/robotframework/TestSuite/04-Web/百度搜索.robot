*** Settings ***
Library           SeleniumLibrary
Library           Screenshot
Library           DateTime
Resource          ../resource.robot

*** Test Cases ***
Baidu search case
    Open Browser    http://www.baidu.com    chrome
    Input text    id=kw    robot framework
    Sleep    1
    Click button    id=su
    Screenshot.Set Screenshot Directory    ${IMAGE PATH}
    Take Screenshot
    Sleep    1
    Close Browser
