# 新增表
# MYISAM存储引擎不产生事物，插入速度极快
create table if not exists big_data (
    id int primary key not null auto_increment,
    name varchar(20) not null,
    age int(11),
    email varchar(64) default null
)engine=MYISAM default charset=utf8;

# 定义存储过程
DELIMITER $$
CREATE 
    PROCEDURE insert_data()
        BEGIN
            DECLARE i INT;
            SET i = 0;
            WHILE i >= 0 && i <=10000000 DO
                INSERT INTO big_data (name,age,email) VALUES(concat('test',i), rand()*50, concat('test', i, '@163.com'));
                SET i = i + 1;
            END WHILE;
        END$$

DELIMITER ;

#执行存储过程
call insert_data();
# 插入1000万条数据，用时：20.74 sec

#删除存储过程
drop PROCEDURE insert_data;

# 修改数据表引擎
alter table big_data engine=InnoDB;
# 修改引擎，数据加锁，用时：4.41 sec
