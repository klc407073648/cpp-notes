-- A. 数据准备，删除其他索引
mysql> show index from tb_user;
+---------+------------+----------+--------------+-------------+-----------+-------------+----------+--------+------+------------+---------+---------------+
| Table   | Non_unique | Key_name | Seq_in_index | Column_name | Collation | Cardinality | Sub_part | Packed | Null | Index_type | Comment | Index_comment |
+---------+------------+----------+--------------+-------------+-----------+-------------+----------+--------+------+------------+---------+---------------+
| tb_user |          0 | PRIMARY  |            1 | id          | A         |          24 |     NULL | NULL   |      | BTREE      |         |               |
+---------+------------+----------+--------------+-------------+-----------+-------------+----------+--------+------+------------+---------+---------------+
1 row in set (0.00 sec)

-- A. 在没有索引的情况下，执行如下SQL，查询执行计划
mysql> explain select profession , count(*) from tb_user group by profession ;
+----+-------------+---------+------------+------+---------------+------+---------+------+------+----------+---------------------------------+
| id | select_type | table   | partitions | type | possible_keys | key  | key_len | ref  | rows | filtered | Extra                           |
+----+-------------+---------+------------+------+---------------+------+---------+------+------+----------+---------------------------------+
|  1 | SIMPLE      | tb_user | NULL       | ALL  | NULL          | NULL | NULL    | NULL |   24 |   100.00 | Using temporary; Using filesort |
+----+-------------+---------+------------+------+---------------+------+---------+------+------+----------+---------------------------------+
1 row in set, 1 warning (0.00 sec)

-- B. 针对于 profession ， age， status 创建一个联合索引
mysql> create index idx_user_pro_age_sta on tb_user(profession , age , status);
Query OK, 0 rows affected (0.04 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> explain select profession , count(*) from tb_user group by profession ;
+----+-------------+---------+------------+-------+----------------------+----------------------+---------+------+------+----------+-------------+
| id | select_type | table   | partitions | type  | possible_keys        | key                  | key_len | ref  | rows | filtered | Extra       |
+----+-------------+---------+------------+-------+----------------------+----------------------+---------+------+------+----------+-------------+
|  1 | SIMPLE      | tb_user | NULL       | index | idx_user_pro_age_sta | idx_user_pro_age_sta | 42      | NULL |   24 |   100.00 | Using index |
+----+-------------+---------+------------+-------+----------------------+----------------------+---------+------+------+----------+-------------+
1 row in set, 1 warning (0.00 sec)

mysql> explain select profession , count(*) from tb_user group by profession,age;
+----+-------------+---------+------------+-------+----------------------+----------------------+---------+------+------+----------+-------------+
| id | select_type | table   | partitions | type  | possible_keys        | key                  | key_len | ref  | rows | filtered | Extra       |
+----+-------------+---------+------------+-------+----------------------+----------------------+---------+------+------+----------+-------------+
|  1 | SIMPLE      | tb_user | NULL       | index | idx_user_pro_age_sta | idx_user_pro_age_sta | 42      | NULL |   24 |   100.00 | Using index |
+----+-------------+---------+------------+-------+----------------------+----------------------+---------+------+------+----------+-------------+
1 row in set, 1 warning (0.00 sec)

mysql> explain select age , count(*) from tb_user group by age;
+----+-------------+---------+------------+-------+----------------------+----------------------+---------+------+------+----------+----------------------------------------------+
| id | select_type | table   | partitions | type  | possible_keys        | key                  | key_len | ref  | rows | filtered | Extra                                        |
+----+-------------+---------+------------+-------+----------------------+----------------------+---------+------+------+----------+----------------------------------------------+
|  1 | SIMPLE      | tb_user | NULL       | index | idx_user_pro_age_sta | idx_user_pro_age_sta | 42      | NULL |   24 |   100.00 | Using index; Using temporary; Using filesort |
+----+-------------+---------+------------+-------+----------------------+----------------------+---------+------+------+----------+----------------------------------------------+
1 row in set, 1 warning (0.00 sec)

-- 发现，如果仅仅根据age分组，就会出现 Using temporary ；而如果是 根据profession,age两个字段同时分组，则不会出现 Using temporary。原因是因为对于分组操作，
-- 在联合索引中，也是符合最左前缀法则的。