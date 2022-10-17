-- A. 统计该企业员工数量
   	select count(*) from emp; -- 统计的是总记录数
  	select count(idcard) from emp; -- 统计的是idcard字段不为null的记录数

-- 对于count聚合函数，统计符合条件的总记录数，还可以通过 count(数字/字符串)的形式进行统计
-- 查询，比如：
 	select count(1) from emp;
	
-- 对于count(*) 、count(字段)、 count(1) 的具体原理，我们在进阶篇中SQL优化部分会详细讲解，此处大家只需要知道如何使用即可。

-- B. 统计该企业员工的平均年龄
 	select avg(age) from emp;
-- C. 统计该企业员工的最大年龄
 	select max(age) from emp;
-- D. 统计该企业员工的最小年龄
  	select min(age) from emp;
-- E. 统计西安地区员工的年龄之和
  	select sum(age) from emp where workaddress = '西安';

mysql> select count(*) from emp;
+----------+
| count(*) |
+----------+
|       16 |
+----------+
1 row in set (0.00 sec)

mysql> select count(1) from emp;
+----------+
| count(1) |
+----------+
|       16 |
+----------+
1 row in set (0.00 sec)

mysql> select avg(age) from emp;
+----------+
| avg(age) |
+----------+
|  40.1250 |
+----------+
1 row in set (0.00 sec)

mysql> select max(age) from emp;
+----------+
| max(age) |
+----------+
|       88 |
+----------+
1 row in set (0.00 sec)

mysql> select min(age) from emp;
+----------+
| min(age) |
+----------+
|       16 |
+----------+
1 row in set (0.00 sec)

mysql> select sum(age) from emp where workaddress = '西安';
+----------+
| sum(age) |
+----------+
|       135|
+----------+
