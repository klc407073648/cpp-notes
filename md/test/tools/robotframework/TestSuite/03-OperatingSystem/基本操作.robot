*** Settings ***
Documentation     Example using the space separated format.
Library           OperatingSystem
Library           Process
Library           BuiltIn

*** Variables ***
${TESTPATH}       ${CURDIR}/test

*** Test Cases ***
文件操作测试
    Create Directory    ${TESTPATH}
    Create Directory    ${TESTPATH}/tmp
    Create File    ${TESTPATH}/test1.txt
    Create File    ${TESTPATH}/test2.txt
    Directory Should Be Empty    ${TESTPATH}/tmp
    Copy Files    ${TESTPATH}/test1.txt    ${TESTPATH}/test2.txt    ${TESTPATH}/tmp
    Directory Should Exist    ${TESTPATH}/tmp    test1.txt
    Remove Files    ${TESTPATH}/tmp/test1.txt
    Remove Directory    ${TESTPATH}    recursive=True
