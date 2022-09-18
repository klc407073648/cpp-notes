mysql> show variables like 'slow_query_log';
+----------------+-------+
| Variable_name  | Value |
+----------------+-------+
| slow_query_log | OFF   |
+----------------+-------+
1 row in set (0.00 sec)

mysql> set global slow_query_log = ON;
Query OK, 0 rows affected (0.00 sec)

mysql> set global long_query_time = 2;
Query OK, 0 rows affected (0.00 sec)

mysql> show variables like 'slow%';
+---------------------+--------------------------------------+
| Variable_name       | Value                                |
+---------------------+--------------------------------------+
| slow_launch_time    | 2                                    |
| slow_query_log      | ON                                   |
| slow_query_log_file | /var/lib/mysql/1a11b56b97f7-slow.log |
+---------------------+--------------------------------------+
3 rows in set (0.00 sec)