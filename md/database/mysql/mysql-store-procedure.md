# MySQL - 存储过程和函数

[[toc]]

# 存储过程和函数概念

> 创建存储过程和函数是指将经常使用的一组SQL语句的组合在一起，并将这些SQL语句当作一个整体存储在MySQL服务器中。存储过程和函数的区别在于函数必须有返回值，而存储过程没有；存储过程的参数可以使用in,out,inout类型，而函数的参数只有in类型的。

存储过程和函数的原始表和数据：

```sql
-- ----------------------------
-- Table structure for student
-- ----------------------------
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

# 存储过程

存储过程示例，根据输入id号返回对应student的人数：

```sql
DROP PROCEDURE IF EXISTS num_from_student;
DELIMITER &&
CREATE PROCEDURE num_from_student(IN stu_id INT,OUT count_num INT)
		READS SQL DATA
		BEGIN
			SELECT COUNT(*) INTO count_num FROM student  
			WHERE id=stu_id;
		END &&
DELIMITER ;	
CALL num_from_student(1002,@n);
SELECT @n;
DROP PROCEDURE IF EXISTS num_from_student;
```

执行结果：

![存储过程结果1](/_images/database/mysql/存储过程结果1.png)

# 存储函数

存储函数示例，根据输入id号返回对应student的名字：

```sql
DROP FUNCTION IF EXISTS name_from_student;
DELIMITER &&
CREATE FUNCTION name_from_student(stu_id INT)
		RETURNS VARCHAR(30)
		BEGIN
			RETURN (SELECT name from student 
			WHERE id=stu_id);
		END &&

DELIMITER ;	
SELECT name_from_student(1003);
DROP FUNCTION IF EXISTS name_from_student;
```

执行结果： 

![存储过程结果2](/_images/database/mysql/存储过程结果2.png)

