-- A. 修改id为1的数据，将name修改为Jack
    update employee set name = 'Jack' where id = 1;
-- B. 修改id为1的数据, 将name修改为Lucky, gender修改为 w
    update employee set name = 'Lucky' , gender = 'w' where id = 1;
-- C. 将所有的员工入职日期修改为 2008-01-01
    update employee set entrydate = '2008-01-01';
	
mysql> update employee set name = 'Jack' where id = 1;
Query OK, 1 row affected (0.00 sec)
Rows matched: 1  Changed: 1  Warnings: 0

mysql> select * from employee;
+------+--------+-------+--------+------+--------------------+------------+
| id   | workno | name  | gender | age  | idcard             | entrydate  |
+------+--------+-------+--------+------+--------------------+------------+
|    1 | 1      | Jack  | m      |   10 | 123456789012345678 | 2000-01-01 |
|    2 | 2      | Jason | m      |   18 | 123456789012345670 | 2005-01-01 |
|    3 | 3      | Steve | m      |   38 | 123456789012345670 | 2005-01-01 |
|    4 | 4      | Helen | w      |   18 | 123456789012345670 | 2005-01-01 |
+------+--------+-------+--------+------+--------------------+------------+
4 rows in set (0.00 sec)

mysql> update employee set name = 'Lucky' , gender = 'w' where id = 1;
Query OK, 1 row affected (0.01 sec)
Rows matched: 1  Changed: 1  Warnings: 0

mysql> select * from employee;
+------+--------+-------+--------+------+--------------------+------------+
| id   | workno | name  | gender | age  | idcard             | entrydate  |
+------+--------+-------+--------+------+--------------------+------------+
|    1 | 1      | Lucky | w      |   10 | 123456789012345678 | 2000-01-01 |
|    2 | 2      | Jason | m      |   18 | 123456789012345670 | 2005-01-01 |
|    3 | 3      | Steve | m      |   38 | 123456789012345670 | 2005-01-01 |
|    4 | 4      | Helen | w      |   18 | 123456789012345670 | 2005-01-01 |
+------+--------+-------+--------+------+--------------------+------------+
4 rows in set (0.00 sec)

mysql> update employee set entrydate = '2008-01-01';
Query OK, 4 rows affected (0.00 sec)
Rows matched: 4  Changed: 4  Warnings: 0

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

