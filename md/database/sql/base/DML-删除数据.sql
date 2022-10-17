-- A. 删除gender为女的员工
      delete from employee where gender = 'w';
-- B. 删除所有员工
      delete from employee;
	
mysql> select * from employee;
+------+--------+-------+--------+------+--------------------+------------+
| id   | workno | name  | gender | age  | idcard             | entrydate  |
+------+--------+-------+--------+------+--------------------+------------+
|    1 | 1      | Lucky | w      |   10 | 123456789012345678 | 2008-01-01 |
|    2 | 2      | Jason | m      |   18 | 123456789012345670 | 2008-01-01 |
|    3 | 3      | Steve | m      |   38 | 123456789012345670 | 2008-01-01 |
|    4 | 4      | Helen | w      |   18 | 123456789012345670 | 2008-01-01 |
+------+--------+-------+--------+------+--------------------+------------+
4 rows in set (0.00 sec)

mysql> delete from employee where gender = 'w';
Query OK, 2 rows affected (0.01 sec)

mysql> select * from employee;
+------+--------+-------+--------+------+--------------------+------------+
| id   | workno | name  | gender | age  | idcard             | entrydate  |
+------+--------+-------+--------+------+--------------------+------------+
|    2 | 2      | Jason | m      |   18 | 123456789012345670 | 2008-01-01 |
|    3 | 3      | Steve | m      |   38 | 123456789012345670 | 2008-01-01 |
+------+--------+-------+--------+------+--------------------+------------+
2 rows in set (0.00 sec)

mysql> delete from employee;
Query OK, 2 rows affected (0.01 sec)

mysql> select * from employee;
Empty set (0.00 sec)
