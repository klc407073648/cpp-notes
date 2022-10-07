-- 执行update命令之前的查询
mysql> select * from score;
+------+------+------+---------+---------+
| id   | name | math | english | chinese |
+------+------+------+---------+---------+
|    1 | Tom  |   67 |      88 |      95 |
|    2 | Rose |   23 |      66 |      90 |
|    3 | Jack |   56 |      98 |      76 |
+------+------+------+---------+---------+

mysql> update score set math = math +1;
Query OK, 3 rows affected (0.01 sec)

-- 查询binlog的结果
[root@VM-16-6-centos mysql]# mysqlbinlog -v binlog.000004

### UPDATE `db01`.`score`
### WHERE
###   @1=1
###   @2='Tom'
###   @3=67
###   @4=88
###   @5=95
### SET
###   @1=1
###   @2='Tom'
###   @3=68
###   @4=88
###   @5=95
### UPDATE `db01`.`score`
### WHERE
###   @1=2
###   @2='Rose'
###   @3=23
###   @4=66
###   @5=90
### SET
###   @1=2
###   @2='Rose'
###   @3=24
###   @4=66
###   @5=90
### UPDATE `db01`.`score`
### WHERE
###   @1=3
###   @2='Jack'
###   @3=56
###   @4=98
###   @5=76
### SET
###   @1=3
###   @2='Jack'
###   @3=57
###   @4=98
###   @5=76