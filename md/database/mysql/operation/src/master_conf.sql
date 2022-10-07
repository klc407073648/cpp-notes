-- A. 修改配置文件 /etc/my.cnf
#mysql 服务ID，保证整个集群环境中唯一，取值范围：1 – 2^32-1，默认为1
server-id=1
#指定同步的数据库
binlog-do-db=db01
binlog-do-db=db02
binlog-do-db=db03
# 在作为从数据库的时候，有写入操作也要更新二进制日志文件
log-slave-updates

-- B. 重启MySQL服务器
systemctl restart mysqld

-- C. 创建账户并授权
-- 创建testuser用户，并设置密码，该用户可在任意主机连接该MySQL服务
CREATE USER 'testuser'@'%' IDENTIFIED WITH mysql_native_password BY 'Root@123456'; 
-- 为 'testuser'@'%' 用户分配主从复制权限
GRANT REPLICATION SLAVE ON *.* TO 'testuser'@'%';

-- D. 通过指令，查看两台主库的二进制日志坐标
show master status;