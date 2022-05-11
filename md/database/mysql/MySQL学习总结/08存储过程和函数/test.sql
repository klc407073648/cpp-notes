-- 存储过程创建
DELIMITER &&
CREATE PROCEDURE num_from_student(IN stu_id INT,OUT count_num INT)
		READS SQL DATA
		BEGIN
			SELECT COUNT(*) INTO count_num FROM student  
			WHERE id=stu_id;
		END &&

DELIMITER ;	

-- 存储过程使用
CALL num_from_student(1002,@n);
SELECT @n;

-- 存储过程删除
DROP PROCEDURE IF EXISTS num_from_student;

-- 存储过程调用结果
mysql> CALL num_from_student(1002,@n);
Query OK, 1 row affected

mysql> SELECT @n;
+----+
| @n |
+----+
|  1 |
+----+
1 row in set

-- 存储函数创建
DELIMITER &&
CREATE FUNCTION name_from_student(stu_id INT)
		RETURNS VARCHAR(30)
		BEGIN
			RETURN (SELECT name from student 
			WHERE id=stu_id);
		END &&

DELIMITER ;	

-- 存储函数使用
SELECT name_from_student(1003);

-- 存储函数删除
DROP FUNCTION IF EXISTS name_from_student;

-- 存储函数调用结果
mysql> SELECT name_from_student(1003);
+-------------------------+
| name_from_student(1003) |
+-------------------------+
| Steve                   |
+-------------------------+
1 row in set

-- 生成建表脚本
DROP FUNCTION IF EXISTS genTable;
DELIMITER $$
CREATE FUNCTION genTable(name varchar(20)) RETURNS varchar(50)
BEGIN
  DECLARE str VARCHAR(50) DEFAULT '';
  SET @tableName=name;
  SET str=CONCAT('create table ', @tableName,'(id int, name varchar(20));');
  return str;
END $$
DELIMITER ;
select genTable('student');
DROP FUNCTION IF EXISTS genTable;


-- 更新学生id,返回空
DROP FUNCTION IF EXISTS update_student_id;
DELIMITER $$
CREATE FUNCTION update_student_id() RETURNS varchar(2)
BEGIN
    DECLARE cnt int;
	SELECT COUNT(*) FROM student WHERE id=1004 INTO cnt;
	IF cnt>2 THEN
	   UPDATE student SET name="hello"  WHERE id=1004;
	ELSE
	   UPDATE student SET name="world"  WHERE id=1004;
	END IF;
    return '';
END $$
DELIMITER ;
SELECT update_student_id();
DROP FUNCTION IF EXISTS update_student_id;

-- 更新学生id,返回对应执行逻辑
DROP FUNCTION IF EXISTS update_student_id;
DELIMITER $$
CREATE FUNCTION update_student_id() RETURNS varchar(2)
BEGIN
    DECLARE cnt int;
	DECLARE str VARCHAR(2) DEFAULT '';
	SELECT COUNT(*) FROM student WHERE id=1004 INTO cnt;
	IF cnt>2 THEN
	   UPDATE student SET name="hello"  WHERE id=1004;
	   SET str='1';
	ELSE
	   UPDATE student SET name="world"  WHERE id=1004;
	   SET str='2';
	END IF;
    return str;
END $$
DELIMITER ;
SELECT update_student_id();
DROP FUNCTION IF EXISTS update_student_id;

-- 光标使用，返回id的奇数和偶数和
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

            OPEN cur_student;
            REPEAT
                FETCH cur_student INTO stu_id,stu_name;
                IF stu_id%2=1 THEN
                   SET  @id_ji = @id_ji + stu_id;
                ELSE
                   SET  @id_ou = @id_ou + stu_id;
                END IF;
            UNTIL 0 END REPEAT;
            CLOSE cur_student;
		END &&
DELIMITER ;	
CALL student_info();
SELECT @id_ji,@id_ou;

-- 光标使用，返回id的奇数和偶数和，以及对应name。
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
