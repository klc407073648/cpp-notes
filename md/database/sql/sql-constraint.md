# SQL语言 - 约束

> 约束是作用于表中字段上的规则，用于限制存储在表中的数据。目的是保证数据库中数据的正确、有效性和完整性。

[[toc]]

## 概述

分类：

| 约束  | 描述  | 关键字  |
| ------------ | ------------ | ------------ |
| 非空约束  | 限制该字段的数据不能为null  | NOT NULL  |
| 唯一约束  | 保证该字段的所有数据都是唯一、不重复的  | UNIQUE  |
| 主键约束  | 主键是一行数据的唯一标识，要求非空且唯一  | PRIMARY KEY  |
| 默认约束  | 保存数据时，如果未指定该字段的值，则采用默认值  | DEFAULT  |
| 检查约束（8.0.1版本后）  | 保证字段值满足某一个条件  | CHECK  |
| 外键约束  | 用来让两张图的数据之间建立连接，保证数据的一致性和完整性  | FOREIGN KEY  |

注意：约束是作用于表中字段上的，可以再创建表/修改表的时候添加约束。

## 约束演示

字段名 字段含义 字段类型 约束条件 约束关键字
| 字段名  | 字段含义  | 字段类型  |约束条件  |约束关键字  |
| ------------ | ------------ | ------------ | ------------ | ------------ |
| id	 | ID唯一标识   | int  | 主键，并且自动增长  | PRIMARY KEY,AUTO_INCREMENT | 
| name  | 姓名  | varchar(10)  | 不为空，并且唯一  | NOT NULL , UNIQUE | 
| age  | 年龄  | int	 | 大于0，并且小于等于120	 | CHECK | 
| status |  状态  | char(1)	 | 如果没有指定该值，默认为1 | DEFAULT | 
| gender  | 性别  | char(1)  | 无 |   | 

注意：约束是作用于表中字段上的，可以在创建表/修改表的时候添加约束。

<<< @/md/database/sql/constraint/约束演示.sql

## 外键约束

> 外键：用来让两张表的数据之间建立连接，**从而保证数据的一致性和完整性**。

例子：

![](/_images/database/sql/constraint/外键约束例子.png)

左侧的emp表是员工表，里面存储员工的基本信息，包含员工的ID、姓名、年龄、职位、薪资、入职日期、上级主管ID、部门ID，在员工的信息中存储的是部门的ID dept_id，而这个部门的ID是关联的部门表dept的主键id，那emp表的dept_id就是外键,关联的是另一张表的主键。

外键关联的是父表，本身是子表

接下来，可以做一个测试，删除id为1的部门信息。

![](/_images/database/sql/constraint/删除ID为1的记录.png)

结果，我们看到删除成功，而删除成功之后，部门表不存在id为1的部门，而在emp表中还有很多的员工，关联的为id为1的部门，此时就出现了数据的不完整性。 而要想解决这个问题就得通过数据库的外键约束。

### 语法

```mysql
CREATE TABLE 表名(
	字段名 字段类型,
	...
	[CONSTRAINT] [外键名称] FOREIGN KEY(外键字段名) REFERENCES 主表(主表列名)
);

# 添加外键
ALTER TABLE 表名 ADD CONSTRAINT 外键名称 FOREIGN KEY (外键字段名) REFERENCES 主表(主表列名);

# 删除外键
ALTER TABLE 表名 DROP FOREIGN KEY 外键名称;
```

例子:

alter table emp add constraint fk_emp_dept_id foreign key(dept_id) references dept(id);

添加了外键约束之后，我们再到dept表(父表)删除id为1的记录，然后看一下会发生什么现象。 此时将会报错，不能删除或更新父表记录，因为存在外键约束

![](/_images/database/sql/constraint/删除记录报错.png)

删除emp表的外键fk_emp_dept_id。

alter table emp drop foreign key fk_emp_dept_id;

删除外键约束后，可以删除dept表(父表)id为1的记录

### 删除/更新行为

| 行为  | 说明  |
| ------------ | ------------ |
| NO ACTION  | 当在父表中删除/更新对应记录时，首先检查该记录是否有对应外键，如果有则不允许删除/更新（与RESTRICT一致）  |
| RESTRICT  | 当在父表中删除/更新对应记录时，首先检查该记录是否有对应外键，如果有则不允许删除/更新（与NO ACTION一致）  |
| CASCADE  | 当在父表中删除/更新对应记录时，首先检查该记录是否有对应外键，如果有则也删除/更新外键在子表中的记录  |
| SET NULL  | 当在父表中删除/更新对应记录时，首先检查该记录是否有对应外键，如果有则设置子表中该外键值为null（要求该外键允许为null）  |
| SET DEFAULT  | 父表有变更时，子表将外键设为一个默认值（Innodb不支持）  |

更改删除/更新行为：

`ALTER TABLE 表名 ADD CONSTRAINT 外键名称 FOREIGN KEY (外键字段) REFERENCES 主表名(主表字段名) ON UPDATE 行为 ON DELETE 行为;`

1. CASCADE

alter table emp add constraint fk_emp_dept_id foreign key (dept_id) references dept(id) on update cascade on delete cascade ;

A. 修改父表id为1的记录，将id修改为6

发现原来在子表中dept_id值为1的记录，现在也变为6了，这就是cascade级联的效果。

B. 删除父表id为6的记录

发现父表的数据删除成功，同时子表中关联的记录也被级联删除了

2. SET NULL

alter table emp add constraint fk_emp_dept_id foreign key (dept_id) references dept(id) on update set null on delete set null ;

A. 删除父表id为1的数据，看看会发生什么样的现象。

发现子表emp的dept_id字段，原来dept_id为1的数据，现在都被置为NULL了。

这就是SET NULL这种删除/更新行为的效果。