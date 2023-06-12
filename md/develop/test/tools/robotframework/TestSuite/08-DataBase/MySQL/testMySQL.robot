*** Settings ***
Documentation     自定义库测试
Suite Setup       Create MySQL Connection
Suite Teardown    Disconnect From Database
Library           Collections
Library           DatabaseLibrary
Resource          ../../resource.robot

*** Test Cases ***
查询单条数据
    ${result}    query    select * from student
    log    ${result[0]}

查询多条数据
    ${result}    query    select * from student
    log    ${result}

数据库中存在
    Check If Exists In Database    select * from student where id=1001

数据库中不存在
    Check If Not Exists In Database    select * from student where id=1011

插入单条数据
    Execute Sql String    INSERT INTO `student` VALUES (1008, 'Haven', 27, 'man', 9)

返回查询结果总行数
    ${rowCount}    Row Count    select * from student
    log    ${rowCount}

*** Keywords ***
Create MySQL Connection
    [Documentation]    mysql创建连接
    Connect To Database Using Custom Params    pymysql    host='${MYSQL_HOST}', port=${MYSQL_PORT}, user='${MYSQL_USER}', passwd='${MYSQL_PASSWORD}', db='${MYSQL_DATABASE}', charset='utf8'
