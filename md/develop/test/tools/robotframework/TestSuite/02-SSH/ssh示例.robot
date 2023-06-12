*** Settings ***
Documentation     ssh示例
Suite Setup       Open Connection And Login In
Suite Teardown    Close All Connections
Library           SSHLibrary
Resource          ../resource.robot

*** Test Cases ***
执行命令校验返回结果
    Execute Command And Verify Output    echo Hello SSHLibrary!    Hello SSHLibrary!

执行命令校验返回码
    Execute Command And Verify Return Code    echo Success guaranteed.    ${0}    #${0}强转为整型符号

交互式执行命令
    Executing Commands In An Interactive Session    path=/home/jenkins/test    cmd=test.sh    util=SSH    expect=TEST SSH

*** Keywords ***
Open Connection And Login In
    [Documentation]    ssh创建连接
    Open Connection    ${SSH_HOST}
    Login    ${SSH_USERNAME}    ${SSH_PASSWORD}

Execute Command And Verify Output
    [Arguments]    ${cmd}    ${result}
    [Documentation]    执行命令,校验结果
    ${output}=    Execute Command    ${cmd}
    Should Be Equal    ${output}    ${result}

Execute Command And Verify Return Code
    [Arguments]    ${cmd}    ${retcode}
    [Documentation]    执行命令,校验返回码
    ${rc}=    Execute Command    ${cmd}    return_stdout=False    return_rc=True
    Should Be Equal    ${rc}    ${retcode}

Executing Commands In An Interactive Session
    [Arguments]    ${path}    ${cmd}    ${util}    ${expect}
    [Documentation]    交互式会话下执行命令
    Write    cd ${path}
    Write    ./${cmd}
    ${output}=    Read Until    ${util}
    Should End With    ${output}    ${expect}
