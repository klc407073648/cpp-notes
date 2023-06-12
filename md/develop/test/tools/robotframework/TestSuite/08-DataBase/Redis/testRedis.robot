*** Settings ***
Documentation     redis操作测试
Suite Setup       Create Redis Connection
Library           RedisLibrary    #Suite Teardown    Delete From Redis
Resource          ../../resource.robot

*** Variables ***
${Key1}           name
${Key2}           number
${SetKey1}        Fruit
${HashKey1}       hashname

*** Test Cases ***
添加数据
    ${redis_conn}=    Create Redis Connection
    Set To Redis    ${redis_conn}    ${Key1}    Jason
    Set To Redis    ${redis_conn}    ${Key2}    123456
    Add Set Data To Redis Set    ${redis_conn}    ${SetKey1}    Banana    Apple    Orage
    #Set To Redis Hash    ${redis_conn}    ${HashKey1}    name "redis tutorial" description "redis basic commands for caching" likes 20 visitors 23000
    Delete From Redis    ${redis_conn}    BARCODE|1234567890

查询数据
    ${redis_conn}=    Create Redis Connection
    ${Value1}=    Get From Redis    ${redis_conn}    ${Key1}
    ${Value2}=    Get From Redis    ${redis_conn}    ${Key2}
    ${SetValue1}=    Get Set From Redis Set    ${redis_conn}    ${SetKey1}
    #${HashValue1}=    Get From Redis Hash    ${redis_conn}    ${HashKey1}    BARCODE|1234567890
    Log    ${Value1}
    Log    ${Value2}
    Log    ${SetValue1}
    #Log    ${HashValue1}
    Delete From Redis    ${redis_conn}    BARCODE|1234567890

test_get_redis_value
    log    获取redis的key值
    ${redis_conn}=    Create Redis Connection
    ${value}=    Get From Redis    ${redis_conn}    ${key}
    log    value is：${value}
    log    修改value，重新获取
    Set to redis    ${redis_conn}    ${key}    123
    ${new_value}=    Get From Redis    ${redis_conn}    ${key}
    log    new value is：${new_value}
    log    对取到的value进行判断
    #Should Be Equal As Strings    ${value}    kkk
    ${str_value}=    Convert To String    ${new_value}
    Should Be Equal    ${str_value}    123
    Sleep    1
    Delete From Redis    ${redis_conn}    BARCODE|1234567890

*** Keywords ***
Create Redis Connection
    [Documentation]    Redis创建连接
    ${return}=    Connect To Redis    ${REDIS_HOST}    ${REDIS_PORT}    0    ${REDIS_PASSWORD}
    [Return]    ${return}
