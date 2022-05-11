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