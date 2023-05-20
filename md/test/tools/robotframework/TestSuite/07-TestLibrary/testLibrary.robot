*** Settings ***
Documentation     自定义库测试
Library           Collections
Library           ../../Library/NewLibrary

*** Variables ***
${STR1}           STRING1
${STR2}           STRING2

*** Test Cases ***
测试自定义关键字
    Print Msg    Hello,World
    Join Info    ${STR1}    ${STR2}
