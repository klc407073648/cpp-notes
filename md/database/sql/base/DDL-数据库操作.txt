# 查询所有数据库
mysql> show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| performance_schema |
| student            |
| sys                |
+--------------------+
4 rows in set (0.00 sec)

# 测试创建数据库,最好加上 if not exists条件，再去创建
mysql> create database test_db;
Query OK, 1 row affected (0.00 sec)

mysql> create database test_db;
ERROR 1007 (HY000): Can't create database 'test_db'; database exists

mysql> create database if not exists test_db;
Query OK, 1 row affected, 1 warning (0.00 sec)

mysql> show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| performance_schema |
| student            |
| sys                |
| test_db            |
+--------------------+
5 rows in set (0.00 sec)

# 测试删除数据库,最好加上 if exists条件，再去删除
mysql> drop database test_db;
Query OK, 0 rows affected (0.06 sec)

mysql> drop database test_db;
ERROR 1008 (HY000): Can't drop database 'test_db'; database doesn't exist

mysql> drop database if exists test_db;
Query OK, 0 rows affected, 1 warning (0.00 sec)


