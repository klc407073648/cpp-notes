-- A. 根据性别分组，统计男性和女性数量
   	select gender, count(*) from emp group by gender;
-- B. 根据性别分组，统计男性和女性的平均年龄
   	select gender, avg(age) from emp group by gender;
-- C. 年龄小于45，并根据工作地址分组，获取员工数量大于等于3的工作地址
   	select workaddress, count(*) address_count from emp where age < 45 group by workaddress having address_count >= 3;
-- D. 统计各个工作地址上班的男性及女性员工的数量
   	select workaddress, gender, count(*) '数量' from emp group by gender , workaddress


mysql> select gender, count(*) from emp group by gender;
+--------+----------+
| gender | count(*) |
+--------+----------+
| 女    |        7 |
| 男    |        9 |
+--------+----------+
2 rows in set (0.00 sec)

mysql> select gender, avg(age) from emp group by gender;
+--------+----------+
| gender | avg(age) |
+--------+----------+
| 女    |  31.4286 |
| 男    |  46.8889 |
+--------+----------+
2 rows in set (0.00 sec)

mysql> select workaddress, count(*) address_count from emp where age < 45 group by workaddress having address_count >= 3;
+-------------+---------------+
| workaddress | address_count |
+-------------+---------------+
| 北京      |             7 |
+-------------+---------------+
1 row in set (0.01 sec)

mysql> select workaddress, gender, count(*) '数量' from emp group by gender , workaddress
    -> ;
+-------------+--------+-------+
| workaddress | gender | 数量 |
+-------------+--------+-------+
| 上海      | 女    |     1 |
| 北京      | 女    |     4 |
| 天津      | 女    |     1 |
| 西安      | 女    |     1 |
| 上海      | 男    |     2 |
| 北京      | 男    |     4 |
| 江苏      | 男    |     2 |
| 西安      | 男    |     1 |
+-------------+--------+-------+
8 rows in set (0.00 sec)
