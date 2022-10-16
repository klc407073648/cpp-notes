-- 变量: 系统变量
-- 查看系统变量
show session variables;
show session variables like 'auto%';
show global variables like 'auto%';

select @@global.autocommit;
select @@session.autocommit;

-- 设置系统变量
set session autocommit = 1;

insert into course(id, name) VALUES (6, 'ES');

set global autocommit = 0;

select @@global.autocommit;