-- 创建用户 test , 只能够在当前主机localhost访问, 密码123456;
create user 'test'@'localhost' identified by '123456';

-- 创建用户 myuser , 可以在任意主机访问该数据库, 密码123456 ;
create user 'myuser'@'%' identified by '123456';

-- 修改用户 myuser 的访问密码为 1234 ;
alter user 'myuser'@'%' identified with mysql_native_password by '1234';

-- 删除test@localhost用户
drop user 'test'@'localhost';