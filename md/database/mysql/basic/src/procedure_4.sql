-- 变量: 局部变量
-- 声明 - declare
-- 赋值 -
create procedure p2()
begin
    declare stu_count int default 0;
    select count(*) into stu_count from student;
    select stu_count;
end;

call p2();