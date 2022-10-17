create table emp(
    id int comment '编号',
    workno varchar(10) comment '工号',
    name varchar(10) comment '姓名',
    gender char(1) comment '性别',
    age tinyint unsigned comment '年龄',
    idcard char(18) comment '身份证号',
    workaddress varchar(50) comment '工作地址',
    entrydate date comment '入职时间'
)comment '员工表';

insert into employee(id,workno,name,gender,age,idcard,entrydate) values(1,'1','Job','m',10,'123456789012345678','2000-01-01');
insert into employee(id,workno,name,gender,age,idcard,entrydate) values(1,'1','Job','m',-1,'123456789012345678','2000-01-01');
insert into employee values(2,'2','Jason','m',18,'123456789012345670','2005-01-01');
insert into employee values(3,'3','Steve','m',38,'123456789012345670','2005-01-01'),(4,'4','Helen','w',18,'123456789012345670','2005-01-01');
