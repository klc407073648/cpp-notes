-- A. 修改配置文件 /etc/my.cnf
-- mysql 服务ID，保证整个集群环境中唯一，取值范围：1 – 232-1，默认为1
server-id=2


-- B. 重启MySQL服务器
systemctl restart mysqld