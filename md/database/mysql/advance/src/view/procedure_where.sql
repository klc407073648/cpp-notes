-- while   计算从1累加到n的值，n为传入的参数值。

-- A. 定义局部变量, 记录累加之后的值;
-- B. 每循环一次, 就会对n进行减1 , 如果n减到0, 则退出循环
create procedure p7(in n int)
begin
    declare total int default 0;

    while n>0 do
         set total := total + n;
         set n := n - 1;
    end while;

    select total;
end;

call p7(100);