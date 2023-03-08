# MySQL运维 - 读写分离

[[toc]]

## 概述

读写分离, 简单地说是把对数据库的读和写操作分开, 以对应不同的数据库服务器。主数据库提供写操作，从数据库提供读操作，这样能有效地减轻单台数据库的压力。

通过MyCat即可轻易实现上述功能，不仅可以支持MySQL，也可以支持Oracle和SQL Server。

![](/_images/database/mysql/operation/读写分离.png)

## 一主一从

### 原理

MySQL的主从复制，是基于二进制日志（binlog）实现的。

![](/_images/database/mysql/operation/主从复制原理.png)

### 准备

```
主机                角色        用户名      密码
192.168.200.211     master      root        1234
192.168.200.212     slave       root        1234
```

### 配置文件

MyCat控制后台数据库的读写分离和负载均衡由schema.xml文件datahost标签的balance属性控制。

**schema.xml配置**

<<< @/md/database/mysql/operation/src/schema.xml

上述配置的具体关联对应情况如下：

![](/_images/database/mysql/operation/schema配置关系.png)

参数：

* writeHost: 写操作对应的数据库
* readHost: 读操作对应的数据库。
* balance: 负责均衡参数
    * 取值有4种，具体含义如下：

| 参数值 | 含义 | 
| --------------------- | ----------- | 
| 0 | 不开启读写分离机制 , 所有读操作都发送到当前可用的writeHost上 | 
| 1 | 全部的readHost 与 备用的writeHost 都参与select 语句的负载均衡（主要针对于双主双从模式） | 
| 2 | 所有的读写操作都随机在writeHost , readHost上分发 | 
| 3 | 所有的读请求随机分发到writeHost对应的readHost上执行, writeHost不负担读压力 | 

所以，在一主一从模式的读写分离中，balance配置1或3都是可以完成读写分离的。

**server.xml配置**

配置root用户可以访问SHOPPING、testuser 以及 testuser_RW逻辑库。

<<< @/md/database/mysql/operation/src/server.xml

### 测试

配置完毕MyCat后，重新启动MyCat。

```
bin/mycat stop
bin/mycat start
```

然后观察，在执行增删改操作时，对应的主库及从库的数据变化。 在执行查询操作时，检查主库及从库对应的数据变化。

在测试中，可以发现当主节点Master宕机之后，业务系统就只能够读，而不能写入数据了。

## 双主双从

一个主机 Master1 用于处理所有写请求，它的从机 Slave1 和另一台主机 Master2 还有它的从机 Slave2 负责所有读请求。当 Master1 主机宕机后，Master2 主机负责写请求，Master1 、Master2 互为备机。

架构图如下:

![](/_images/database/mysql/operation/双主双从.png)

### 准备

需要准备5台服务器，具体的服务器及软件安装情况如下：

```
编号    IP                  预装软件        角色
1       192.168.200.210     MyCat、MySQL    MyCat中间件服务器
2       192.168.200.211     MySQL           M1
3       192.168.200.212     MySQL           S1
4       192.168.200.213     MySQL           M2
5       192.168.200.214     MySQL           S2
```

### 搭建

主从复制搭建过程，参考主从复制.md

![](/_images/database/mysql/operation/双主双从搭建.png)

1. 主库配置修改

<<< @/md/database/mysql/operation/src/master_conf.sql

2. 从库配置修改

<<< @/md/database/mysql/operation/src/slave_conf.sql

3. 从库关联主库

```sql
-- A. 在 slave1(192.168.200.212)上执行
CHANGE MASTER TO MASTER_HOST='192.168.200.211', MASTER_USER='testuser',MASTER_PASSWORD='Root@123456', MASTER_LOG_FILE='binlog.000002',MASTER_LOG_POS=663;
-- B. 在 slave2(192.168.200.214)上执行
CHANGE MASTER TO MASTER_HOST='192.168.200.213', MASTER_USER='testuser',MASTER_PASSWORD='Root@123456',MASTER_LOG_FILE='binlog.000002',MASTER_LOG_POS=663;
-- C. 启动两台从库主从复制，查看从库状态
start slave;
show slave status \G;
```

4. 两台主库相互复制

```sql
-- A. 在 Master1(192.168.200.211)上执行
CHANGE MASTER TO MASTER_HOST='192.168.200.213', MASTER_USER='testuser'MASTER_PASSWORD='Root@123456', MASTER_LOG_FILE='binlog.000002',MASTER_LOG_POS=663;
-- B. 在 Master2(192.168.200.213)上执行
CHANGE MASTER TO MASTER_HOST='192.168.200.211', MASTER_USER='testuser',MASTER_PASSWORD='Root@123456', MASTER_LOG_FILE='binlog.000002',MASTER_LOG_POS=663;
-- C. 启动两台从库主从复制，查看从库状态
start slave;
show slave status \G;
```

经过上述的四步配置之后，双主双从的复制结构就已经搭建完成了。 接下来，可以来测试验证一下。

### 测试

分别在两台主库Master1、Master2上执行DDL、DML语句，查看涉及到的数据库服务器的数据同步情况。

```sql
create database db01;
use db01;
create table tb_user(
    id int(11) not null primary key ,
    name varchar(50) not null,
    sex varchar(1)
)engine=innodb default charset=utf8mb4;

insert into tb_user(id,name,sex) values(1,'Tom','1');
insert into tb_user(id,name,sex) values(2,'Trigger','0');
insert into tb_user(id,name,sex) values(3,'Dawn','1');
insert into tb_user(id,name,sex) values(4,'Jack Ma','1');
insert into tb_user(id,name,sex) values(5,'Coco','0');
insert into tb_user(id,name,sex) values(6,'Jerry','1');
```

* 在Master1中执行DML、DDL操作，看看数据是否可以同步到另外的三台数据库中。
* 在Master2中执行DML、DDL操作，看看数据是否可以同步到另外的三台数据库中。

完成了上述双主双从的结构搭建之后，接下来，再来看看如何完成这种双主双从的读写分离。

## 双主双从读写分离

### 配置

MyCat控制后台数据库的读写分离和负载均衡由schema.xml文件datahost标签的balance属性控制，通过writeType及switchType来完成失败自动切换的。

**schema.xml配置**

<<< @/md/database/mysql/operation/src/schema_2.xml

具体的对应情况如下：

![](/_images/database/mysql/operation/schema_2配置关系.png)

属性说明：

* balance="1":
    * 代表全部的 readHost 与 stand by writeHost 参与 select 语句的负载均衡，简单的说，当双主双从模式(M1->S1，M2->S2，并且 M1 与 M2 互为主备)，正常情况下，
M2,S1,S2 都参与 select 语句的负载均衡 ;

* writeType
    * 0 : 写操作都转发到第1台writeHost, writeHost1挂了, 会切换到writeHost2上;
    * 1 : 所有的写操作都随机地发送到配置的writeHost上;

* switchType
    * -1 : 不自动切换
    * 1 : 自动切换


**user.xml**

配置root用户也可以访问到逻辑库 ITCAST_RW2。

<<< @/md/database/mysql/operation/src/user.xml

### 测试

登录MyCat，测试查询及更新操作，判定是否能够进行读写分离，以及读写分离的策略是否正确。当主库挂掉一个之后，是否能够自动切换。


