*** Settings ***
Documentation     变量使用
Default Tags      Base

*** Variables ***
${STRING}         This is a long string. It has multiple sentences. It does not have newlines.
${MULTILINE}      This is a long multiline string.    This is the second line.    This is the third and the last line.
@{LIST}           this    list    is    quite    long    and    items in it can also be long
&{DICT}           first=This value is pretty long.    second=This value is even longer. It has two sentences.

*** Test Cases ***
不同类型变量使用
    Log    ${STRING}
    Log    ${MULTILINE}
    Log    ${LIST}
    Log    ${DICT}
