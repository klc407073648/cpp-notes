*** Settings ***
Documentation     http请求Demo
Library           Collections
Library           RequestsLibrary

*** Variables ***
${host}           http://httpbin.org

*** Test Cases ***
Post 请求Demo
    [Tags]    Post    main
    ${data}    Create Dictionary    name=Detector    age=18
    create session    httpbin    ${host}
    ${response}    post request    httpbin    /post    params=${data}
    should be equal as integers    ${response.status_code}    200
    ${resp}    to json    ${response.content}
    should not be empty    ${resp["args"]}
    dictionary should contain key    ${resp["headers"]}    Host
    dictionary should contain value    ${resp["headers"]}    httpbin.org

Get 请求Demo
    [Tags]    Get
    ${data}    Create Dictionary    name=Detector    age=18
    create session    httpbin    ${host}
    ${response}    get request    httpbin    /get    params=${data}
    should be equal as integers    ${response.status_code}    200
    ${resp}    to json    ${response.content}
    should not be empty    ${resp["args"]}
    dictionary should contain key    ${resp["headers"]}    Host
    dictionary should contain value    ${resp["headers"]}    httpbin.org
