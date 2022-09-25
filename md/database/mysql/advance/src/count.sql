mysql> select count(*) from big_data;
+----------+
| count(*) |
+----------+
| 10000000 |
+----------+
1 row in set (1.89 sec)

mysql> select count(1) from big_data;
+----------+
| count(1) |
+----------+
| 10000000 |
+----------+
1 row in set (1.91 sec)

mysql> select count(id) from big_data;
+-----------+
| count(id) |
+-----------+
|  10000000 |
+-----------+
1 row in set (2.15 sec)

mysql> select count(name) from big_data;
+-------------+
| count(name) |
+-------------+
|    10000000 |
+-------------+
1 row in set (3.32 sec)