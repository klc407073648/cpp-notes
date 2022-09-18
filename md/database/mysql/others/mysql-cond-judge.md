# MySQL - 条件判断函数

[[toc]]

# 条件判断函数

IF(expr,v1,v2)函数:
    * 如果表达式expr成立，返回结果v1；否则，返回结果v2。

IFNULL(expr,v1,v2)函数:
    * 如果v1不为空，返回结果v1；否则，返回结果v2。

CASE函数:
    * CASE WHEN expr1 THEN v1 [WHEN expr2 THEN v2... ] [ELSE vn] END 
    * CASE表示函数开始，END表示函数结束。如果表达式expr1成立，返回结果v1。如果表达式expr2成立，返回结果v2,依次类推，最后遇到ELSE时，返回vn的值。


# 建表和插入数据

```sql
DROP TABLE IF EXISTS `student`;
CREATE TABLE `student` (
  `id` int(11) NOT NULL,
  `name` varchar(30) DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  `sex` enum('man','woman') DEFAULT NULL,
  `class` int(10) DEFAULT NULL,
  `grade` int(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of student
-- ----------------------------
INSERT INTO `student` VALUES ('1001', 'Jason', '25', 'man', '1', '90');
INSERT INTO `student` VALUES ('1002', 'Helen', '25', 'woman', '3', '50');
INSERT INTO `student` VALUES ('1003', 'Steve', '27', 'man', '5', '85');
INSERT INTO `student` VALUES ('1004', 'Hanna', '25', 'woman', '1', '100');
INSERT INTO `student` VALUES ('1005', 'Bob', '26', 'man', '3', null);
INSERT INTO `student` VALUES ('1006', 'John', '28', 'man', '7', '70');
INSERT INTO `student` VALUES ('1007', 'Walln', '25', 'woman', '8', '60');
```

执行结果：

```sql
mysql> select id,if(grade>=60,'PASS','FAIL') as if_grade_pass from student;
+------+---------------+
| id   | if_grade_pass |
+------+---------------+
| 1001 | PASS          |
| 1002 | FAIL          |
| 1003 | PASS          |
| 1004 | PASS          |
| 1005 | FAIL          |
| 1006 | PASS          |
| 1007 | PASS          |
+------+---------------+
7 rows in set

mysql> select id,ifnull(grade,'NO GRADE') as if_grade_null from student;
+------+---------------+
| id   | if_grade_null |
+------+---------------+
| 1001 | 90            |
| 1002 | 50            |
| 1003 | 85            |
| 1004 | 100           |
| 1005 | NO GRADE      |
| 1006 | 70            |
| 1007 | 60            |
+------+---------------+
7 rows in set

mysql> select id,grade, case when grade>=90 then 'Great' when grade>=70 and grade<90 then 'Good' when grade>=60 and grade<70 then 'Okay' else 'FAIL' end level from student;
+------+-------+-------+
| id   | grade | level |
+------+-------+-------+
| 1001 |    90 | Great |
| 1002 |    50 | FAIL  |
| 1003 |    85 | Good  |
| 1004 |   100 | Great |
| 1005 | NULL  | FAIL  |
| 1006 |    70 | Good  |
| 1007 |    60 | Okay  |
+------+-------+-------+
7 rows in set
```
​