use mysql;
select host, user from user;
-- 因为mysql版本是5.7，因此新建用户为如下命令：
create user $MYSQL_USER identified by '$MYSQL_PASSWORD';
-- 将docker_mysql数据库的权限授权给创建的docker用户，密码为123456：
grant all on $MYSQL_DATABASE.* to docker@'%' identified by '$MYSQL_PASSWORD' with grant option;
-- 将所有数据库的权限授权给root用户，密码为123456：
grant all privileges on *.* to root@'%' identified by "$MYSQL_ROOT_PASSWORD";
-- 这一条命令一定要有：
flush privileges;