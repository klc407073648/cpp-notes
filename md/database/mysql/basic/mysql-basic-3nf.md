# MySQL基础 - 三范式

[[toc]]

# 概述

> 范式: 对设计数据库提出的一些规范，目前有迹可寻的共有8种范式，一般遵守3范式即可。

* 第一范式（1NF）: 强调的是**列的原子性**，即列不能够再分成其他几列。
* 第二范式（2NF）: 满足 1NF，另外包含两部分内容，**一是表必须有一个主键；二是非主键字段必须完全依赖于主键，而不能只依赖于主键的一部分**。
* 第三范式（3NF）: 满足 2NF，另外**非主键列必须直接依赖于主键，不能存在传递依赖**。即不能存在：非主键列 A 依赖于非主键列 B，非主键列 B 依赖于主键的情况。

## 第一范式

如图所示的表结构:

| contact         |      | name  | id   | age  |
| --------------- | ---- | ----- | ---- | ---- |
| Jason、1001、25 |      | Jason | 1001 | 25   |

说明: 

* 这种表结构设计就没有达到 1NF，要符合 1NF 我们只需把列拆分，即：把 contact 字段拆分成 name 、id、age 等字段。

## 第二范式

如图所示的表结构:

| OrderDetail表 |           |             |          |          |             |
| ------------- | --------- | ----------- | -------- | -------- | ----------- |
| OrderID       | ProductID | UnitPrice   | Discount | Quantity | ProductName |
| 1001758       | 7055      | 20.5        | 2.2      | 4        | Mike        |
| OrderDetail表 |           |             |          |          |             |
| OrderID       | ProductID | Discount    | Quantity |          |             |
| 1001758       | 7055      | 2.2         | 4        |          |             |
| Product表     |           |             |          |          |             |
| ProductID     | UnitPrice | ProductName |          |          |             |
| 7055          | 20.5      | Mike        |          |          |             |


说明:

* 这种表结构设计就没有达到 2NF，因为 Discount（折扣），Quantity（数量）完全依赖于主键（OrderID），而 UnitPrice单价，ProductName产品名称 只依赖于 ProductID, 所以 OrderDetail 表不符合 2NF。
* 我们可以把【OrderDetail】表拆分为【OrderDetail】（OrderID，ProductID，Discount，Quantity）和【Product】（ProductID，UnitPrice，ProductName）这样就符合第二范式了。

## 第三范式

如图所示的表结构:

| Order表 |                  |            |              |              |              |              |              |
| ------- | ---------------- | ---------- | ------------ | ------------ | ------------ | ------------ | ------------ |
| OrderID | OrderDate        | CustomerID | CustomerName | CustomerAddr | CustomerCity |              |              |
| 1001758 | 2020/10/20 12:30 | 13500      | Jason        | nanjing      | jiangsu      |              |              |
| Order表 |                  |            |              | Customer表   |              |              |              |
| OrderID | OrderDate        | CustomerID |              | CustomerID   | CustomerName | CustomerAddr | CustomerCity |
| 1001758 | 2020/10/20 12:30 | 13500      |              | 13500        | Jason        | nanjing      | jiangsu      |


说明:

* 这种表结构设计就没有达到 3NF，因为 OrderDate，CustomerID，CustomerName，CustomerAddr，CustomerCity 等非主键列都完全依赖于主键（OrderID），所以符合 2NF。不过问题是 CustomerName，CustomerAddr，CustomerCity 直接依赖的是 CustomerID（非主键列），而不是直接依赖于主键，它是通过传递才依赖于主键，所以不符合 3NF。
* 我们可以把【Order】表拆分为【Order】（OrderID，OrderDate，CustomerID）和【Customer】（CustomerID，CustomerName，CustomerAddr，CustomerCity）从而达到 3NF。

# E-R模型

> E-R模型即实体-关系模型，E-R模型就是描述数据库存储数据的结构模型。

E-R模型的使用场景:

1. 对于大型公司开发项目，我们需要根据产品经理的设计，我们先使用建模工具, 如:power designer，db desinger等这些软件来画出实体-关系模型(E-R模型)
2. 然后根据三范式设计数据库表结构。

E-R模型的效果图：

![E-R模型图](/_images/database/mysql/basic/E-R模型图.png)

说明:

* 实体: 用矩形表示，并标注实体名称
* 属性: 用椭圆表示，并标注属性名称，
* 关系: 用菱形表示，并标注关系名称
    * 一对一
    * 一对多
    * 多对多

一对一的关系:

![一对一](/_images/database/mysql/basic/一对一.png)

说明:

* 关系也是一种数据，需要通过一个字段存储在表中
* 1对1关系，在表A或表B中创建一个字段，存储另一个表的主键值

一对多的关系:

![一对多](/_images/database/mysql/basic/一对多.png)

说明:

* 1对多关系，在多的一方表(学生表)中创建一个字段，存储班级表的主键值

多对多的关系:

![多对多](/_images/database/mysql/basic/多对多.png)

说明:

* 多对多关系，新建一张表C，这个表只有两个字段，一个用于存储A的主键值，一个用于存储B的主键值。

# 总结

* 范式就是设计数据库的一些通用规范。
    * 1NF强调字段是最小单元，不可再分
    * 2NF强调在1NF基础上必须要有主键和非主键字段必须完全依赖于主键，也就是说 不能部分依赖
    * 3NF强调在2NF基础上 非主键字段必须直接依赖于主键，也就是说不能传递依赖(间接依赖)。
* E-R模型由 实体、属性、实体之间的关系构成，主要用来描述数据库中表结构。
* 开发流程是先画出E-R模型，然后根据三范式设计数据库中的表结构
​