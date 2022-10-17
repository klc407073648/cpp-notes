-- A. curdate：当前日期
 	select curdate();
-- B. curtime：当前时间
 	select curtime();
-- C. now：当前日期和时间
 	select now();
-- D. YEAR , MONTH , DAY：当前年、月、日
 	select YEAR(now());
 	select MONTH(now());
 	select DAY(now());
-- E. date_add：增加指定的时间间隔
	select date_add(now(), INTERVAL 70 YEAR );
-- F. datediff：获取两个日期相差的天数
 	select datediff('2021-10-01', '2021-12-01');
-- G. 查询所有员工的入职天数，并根据入职天数倒序排序。
-- 	思路： 入职天数，就是通过当前日期 - 入职日期，所以需要使用datediff函数来完成。
 	select name, datediff(curdate(), entrydate) as 'entrydays' from emp order by entrydays desc;
	
mysql> select curdate();
+------------+
| curdate()  |
+------------+
| 2022-08-27 |
+------------+
1 row in set (0.01 sec)

mysql> select curtime();
+-----------+
| curtime() |
+-----------+
| 13:27:04  |
+-----------+
1 row in set (0.00 sec)

mysql> select now();
+---------------------+
| now()               |
+---------------------+
| 2022-08-27 13:27:12 |
+---------------------+
1 row in set (0.00 sec)

mysql> select YEAR(now());
+-------------+
| YEAR(now()) |
+-------------+
|        2022 |
+-------------+
1 row in set (0.00 sec)

mysql> select MONTH(now());
+--------------+
| MONTH(now()) |
+--------------+
|            8 |
+--------------+
1 row in set (0.00 sec)

mysql> select DAY(now());
+------------+
| DAY(now()) |
+------------+
|         27 |
+------------+
1 row in set (0.00 sec)

mysql> select date_add(now(), INTERVAL 70 YEAR );
+------------------------------------+
| date_add(now(), INTERVAL 70 YEAR ) |
+------------------------------------+
| 2092-08-27 13:27:39                |
+------------------------------------+
1 row in set (0.00 sec)

mysql> select datediff('2021-10-01', '2021-12-01');
+--------------------------------------+
| datediff('2021-10-01', '2021-12-01') |
+--------------------------------------+
|                                  -61 |
+--------------------------------------+
1 row in set (0.00 sec)

mysql> select name, datediff(curdate(), entrydate) as 'entrydays' from emp order by entrydays desc;
+-----------+-----------+
| name      | entrydays |
+-----------+-----------+
| 柳岩    |    738028 |
| 常遇春 |      6782 |
| 范瑶    |      6327 |
| 韦一笑 |      6235 |
| 张无忌 |      6204 |
| 杨逍    |      6082 |
| 小昭    |      5536 |
| 赵敏    |      4652 |
| 范凉凉 |      4531 |
| 陈友谅 |      4256 |
| 周芷若 |      3739 |
| 黛绮丝 |      2675 |
| 张士诚 |      2675 |
| 胡青牛 |      1609 |
| 灭绝    |      1214 |
| 张三丰 |       664 |
+-----------+-----------+
16 rows in set (0.00 sec)
