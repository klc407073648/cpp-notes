CREATE TABLE tb_user(
    id int AUTO_INCREMENT PRIMARY KEY COMMENT 'ID唯一标识',
    name varchar(10) NOT NULL UNIQUE COMMENT '姓名' ,
    age int check (age > 0 && age <= 120) COMMENT '年龄' ,
    status char(1) default '1' COMMENT '状态',
    gender char(1) COMMENT '性别'
);

insert into tb_user(name,age,status,gender) values ('Tom1',19,'1','男'),('Tom2',25,'0','男');
insert into tb_user(name,age,status,gender) values ('Tom3',19,'1','男');
insert into tb_user(name,age,status,gender) values (null,19,'1','男');//[Err] 1048 - Column 'name' cannot be null
insert into tb_user(name,age,status,gender) values ('Tom3',19,'1','男');//[Err] 1062 - Duplicate entry 'Tom3' for key 'name'
insert into tb_user(name,age,status,gender) values ('Tom4',80,'1','男');
insert into tb_user(name,age,status,gender) values ('Tom5',-1,'1','男');//[Err] 1264 - Out of range value for column 'age' at row 1
insert into tb_user(name,age,status,gender) values ('Tom5',121,'1','男');//年龄限制
insert into tb_user(name,age,gender) values ('Tom5',120,'男');
