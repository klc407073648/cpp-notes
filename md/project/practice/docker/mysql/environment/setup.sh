#!/bin/bash
set -e
 
#查看mysql服务的状态，方便调试，这条语句可以删除
echo `service mysql status`
 
echo '1.启动mysql....'
#启动mysql
service mysql start
sleep 3
echo `service mysql status`
 
echo '2.开始导入数据....'
#导入数据
mysql < /mysql/sql/docker_mysql/create_table.sql 
mysql < /mysql/sql/docker_mysql/init_data.sql 
mysql < /mysql/sql/docker_mysql/update_data.sql

mysql < /mysql/sql/student/create_table.sql 
mysql < /mysql/sql/student/init_data.sql 
mysql < /mysql/sql/student/update_data.sql

mysql < /mysql/sql/apollo/apolloconfigdb.sql  
mysql < /mysql/sql/apollo/apolloportaldb.sql

mysql < /mysql/sql/usercenter/create_table.sql 
mysql < /mysql/sql/usercenter/init_data.sql

echo '3.导入数据完毕....'
 
sleep 3
echo `service mysql status`
 
#重新设置mysql密码
echo '4.开始修改密码....'
mysql < /mysql/sql/privileges/privileges.sql
echo '5.修改密码完毕....'
 
#sleep 3
echo `service mysql status`
echo `mysql容器启动完毕,且数据导入成功`
 
tail -f /dev/null