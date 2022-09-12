-- 查询权限
show grants for 'docker'@'%';

-- 授予权限
grant all on docker_mysql.* to 'docker'@'%';

-- 撤销权限
revoke all on docker_mysql.* from 'docker'@'%';