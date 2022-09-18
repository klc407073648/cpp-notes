# MySQL基础 - 光标

[[toc]]

# 概念

> 查询语句时，可能查询出多条记录，在存储过程和函数中使用光标来逐条读取查询结果集中的记录。有些书上将光标称为游标。光标的使用包括声明光标、打开光标、使用光标和关闭光标。光标必须声明在处理程序之前，并且声明在变量和条件之后。光标可以类比为数组内部中的循环指针。

## 声明光标

MySQL中使用DECLARE关键字来声明光标。其语法的基本形式如下：

```sql
DECLARE cursor_name CURSOR FOR select_statement ;
```

其中，cursor_name参数表示光标的名称；select_statement参数表示SELECT语句的内容，返回一个用于创建光标的结果集。

下面声明一个名为cur_student的光标，示例如下：

```sql
DECLARE cur_student CURSOR FOR SELECT id, name FROM student;
````

上面的示例中，光标的名称为cur_student；SELECT语句部分是从student表中查询出id和name字段的值。

## 打开光标

> MySQL中使用OPEN关键字来打开光标。其语法的基本形式如下

```sql
OPEN  cursor_name;
```

其中，cursor_name参数表示光标的名称。

下面打开一个名为cur_student的光标，示例如下：

```sql
OPEN  cur_student;
```

## 使用光标

> MySQL中使用FETCH关键字来使用光标。其语法的基本形式如下：

```sql
FETCH cursor_name INTO var_name[,var_name…] ;
````

其中，cursor_name参数表示光标的名称；var_name参数表示将光标中的SELECT语句查询出来的信息存入该参数中。var_name必须在声明光标之前就定义好。

下面使用一个名为cur_student的光标。将查询出来的数据存入stu_id和stu_name这两个变量中，代码如下：

```sql
FETCH  cur_employee INTO stu_id, stu_name;
```

上面的示例中，将光标cur_student中SELECT语句查询出来的信息存入stu_id和stu_name中。stu_id和stu_name必须在前面已经定义。

## 关闭光标

> MySQL中使用CLOSE关键字来关闭光标。其语法的基本形式如下：

```sql
CLOSE  cursor_name;
```

其中，cursor_name参数表示光标的名称。

下面关闭一个名为cur_employee的光标，示例如下：

```sql
CLOSE  cur_student;
```

上面的示例中，关闭了这个名称为cur_employee的光标。关闭之后就不能使用FETCH来使用光标了。

# 光标的使用案例

数据的准备和导入：

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

数据表如下：

![光标数据表](/_images/database/mysql/光标数据表.png)

查询student表中所有奇数id和偶数id的总和，以及对应name的集合。

```sql
DROP PROCEDURE IF EXISTS student_info;
DELIMITER &&
CREATE PROCEDURE student_info()
		READS SQL DATA
		BEGIN
            DECLARE stu_id INT;
            DECLARE stu_name VARCHAR(200);

			DECLARE cur_student CURSOR FOR SELECT id,name FROM student;
            DECLARE EXIT HANDLER FOR NOT FOUND CLOSE cur_student;  

            SET @id_ji = '';
            SET @id_ou = '';
			SET @name_ji = '';
            SET @name_ou = '';

            OPEN cur_student;
            REPEAT
                FETCH cur_student INTO stu_id,stu_name;
                IF stu_id%2=1 THEN
                   SET  @id_ji = @id_ji + stu_id;
				   SET  @name_ji =CONCAT(@name_ji,' ',stu_name);
                ELSE
                   SET  @id_ou = @id_ou + stu_id;
				   SET  @name_ou =CONCAT(@name_ou,' ',stu_name);
                END IF;
            UNTIL 0 END REPEAT;
            CLOSE cur_student;
		END &&
DELIMITER ;	
CALL student_info();
SELECT @id_ji,@id_ou,@name_ji,@name_ou;
```

执行结果：

![光标执行结果](/_images/database/mysql/光标执行结果.png)

​