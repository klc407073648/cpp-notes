# MySQL基础使用方法

# MySQL数据库的介绍
MySQL是一个关系型数据库管理系统，在 WEB 应用方面，MySQL是最好的 RDBMS (Relational Database Management System，关系数据库管理系统) 应用软件，它是由瑞典MySQL AB 公司开发，目前属于 Oracle 旗下产品，MySQL 是最流行的关系型数据库管理系统中的一个。

Linux下的MySQL数据库安装可以使用如下命令，此外可以借助图形化客户端软件Navicat便于对数据库进行直接操作。

安装MySQL服务端软件使用: yum install mysql-server
安装MySQL客户端软件使用: yum install mysql-client
图形化操作界面：



# 数据类型和约束
数据类型和约束保证了表中数据的准确性和完整性。

##  数据类型
数据类型是指在创建表的时候为表中字段指定数据类型，只有数据符合类型要求才能存储起来，使用数据类型的原则是:够用就行，尽量使用取值范围小的，而不用大的，这样可以更多的节省存储空间。

常用数据类型如下:

整数：int，bit
小数：decimal
字符串：varchar,char
日期时间: date, time, datetime
枚举类型(enum)

## 数据约束
约束是指数据在数据类型限定的基础上额外增加的要求。

常见的约束如下:

主键 primary key: 物理上存储的顺序. MySQL 建议所有表的主键字段都叫 id, 类型为 int unsigned.
非空 not null: 此字段不允许填写空值.
惟一 unique: 此字段的值不允许重复.
默认 default: 当不填写字段对应的值会使用默认值，如果填写时以填写为准.
外键 foreign key: 对关系字段进行约束, 当为关系字段填写值时, 会到关联的表中查询此值是否存在, 如果存在则填写成功, 如果不存在则填写失败并抛出异常.

## 数据库操作的SQL语句
在linux下命令行客户端的使用。

### 登陆和登出数据库
登录数据库:
输入  mysql -uroot -p   然后填入密码

登陆成功，执行命令查看结果：
select now();

退出数据库
exit;


### 数据库操作的SQL语句
查看所有数据库

show databases;
创建数据库

create database 数据库名 charset=utf8;
例如：
create database mytest charset=utf8;
使用数据库

use 数据库名;
查看当前使用的数据库

select database();
删除数据库-慎重

drop database 数据库名;
例如：
drop database mytest;

### 表结构操作的SQL语句
查看当前数据库中所有表

show tables;
create table 表名(
字段名称 数据类型  可选的约束条件,
column1 datatype contrai,
...
);
修改表-添加字段

alter table 表名 add 列名 类型 约束;
例如：
alter table students add birthday datetime;
修改表-修改字段类型

alter table 表名 modify 列名 类型 约束;
例如：
alter table students modify birthday date not null;
说明: modify 只能修改字段类型或者约束，不能修改字段名

修改表-修改字段名和字段类型

alter table 表名 change 原名 新名 类型及约束;
例如：
alter table students change birthday birth datetime not null;
说明: change 既能对字段重命名又能修改字段类型还能修改约束

修改表-删除字段

alter table 表名 drop 列名;
例如：
alter table students drop birthday;
查看创表SQL语句

show create table 表名;
例如：
show create table students;
查看创库SQL语句

show create database 数据库名;
例如：
show create database mytest;
删除表

drop table 表名;
例如：
drop table students;

### 表数据操作的SQL语句
查询数据

-- 1. 查询所有列
select * from 表名;
例如：
select * from students;
-- 2. 查询指定列
select 列1,列2,... from 表名;
例如：
select id,name from students;
添加数据

-- 1. 全列插入：值的顺序与表结构字段的顺序完全一一对应
insert into 表名 values (...)
例如：
insert into students values(0, 'xx', default, default, '男');
-- 2. 部分列插入：值的顺序与给出的列顺序对应
insert into 表名 (列1,...) values(值1,...)
例如：
insert into students(name, age) values('Helen', 15);
-- 3. 全列多行插入
insert into 表名 values(...),(...)...;
例如：
insert into students values(0, 'Jason', 55, 1.75, '男'),(0, 'Steve', 58, 1.85, '男');
-- 4. 部分列多行插入
insert into 表名(列1,...) values(值1,...),(值1,...)...;
例如：
insert into students(name, height) values('Jason', 1.75),('Steve', 1.6);
说明:

主键列是自动增长，但是在全列插入时需要占位，通常使用空值(0或者null或者default)
在全列插入时，如果字段列有默认值可以使用 default 来占位，插入后的数据就是之前设置的默认值
修改数据

update 表名 set 列1=值1,列2=值2... where 条件
例如：
update students set age = 18, gender = '女' where id = 6;
删除数据

delete from 表名 where 条件
例如：
delete from students where id=5;
问题:

上面的操作称之为物理删除，一旦删除就不容易恢复，我们可以使用逻辑删除的方式来解决这个问题。

-- 添加删除表示字段，0表示未删除 1表示删除
alter table students add isdelete bit default 0;
-- 逻辑删除数据
update students set isdelete = 1 where id = 8;
说明:  逻辑删除，本质就是修改操作。

# SQL语句用法总结
登录数据库: mysql -uroot -p
退出数据库: quit 或者 exit 或者 ctr + d
创建数据库: create database 数据库名 charset=utf8;
使用数据库: use 数据库名;
删除数据库: drop database 数据库名;
创建表: create table 表名(字段名 字段类型 约束, ...);
修改表-添加字段: alter table 表名 add 字段名 字段类型 约束
修改表-修改字段类型: alter table 表名 modify 字段名 字段类型 约束
修改表-修改字段名和字段类型: alter table 表名 change 原字段名 新字段名 字段类型 约束
修改表-删除字段: alter table 表名 drop 字段名;
删除表: drop table 表名;
查询数据: select * from 表名; 或者 select 列1,列2,... from 表名;
插入数据: insert into 表名 values (...) 或者 insert into 表名 (列1,...) values(值1,...)
修改数据: update 表名 set 列1=值1,列2=值2... where 条件
删除数据: delete from 表名 where 条件