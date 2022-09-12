mysql> use student;
Reading table information for completion of table and column names
You can turn off this feature to get a quicker startup with -A

Database changed
mysql> show tables;
+-------------------+
| Tables_in_student |
+-------------------+
| student           |
+-------------------+
1 row in set (0.00 sec)

mysql> desc student;
+-------+---------------------+------+-----+---------+-------+
| Field | Type                | Null | Key | Default | Extra |
+-------+---------------------+------+-----+---------+-------+
| id    | int(11)             | NO   | PRI | NULL    |       |
| name  | varchar(30)         | YES  |     | NULL    |       |
| age   | int(11)             | YES  |     | NULL    |       |
| sex   | enum('man','woman') | YES  |     | NULL    |       |
| class | int(10)             | YES  |     | NULL    |       |
+-------+---------------------+------+-----+---------+-------+
5 rows in set (0.00 sec)

mysql> show create table student;
+---------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Table   | Create Table                                                                                                                                                                                                                                           |
+---------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| student | CREATE TABLE `student` (
  `id` int(11) NOT NULL,
  `name` varchar(30) DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  `sex` enum('man','woman') DEFAULT NULL,
  `class` int(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 |
+---------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
1 row in set (0.00 sec)