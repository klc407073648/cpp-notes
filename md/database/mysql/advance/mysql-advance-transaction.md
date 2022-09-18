# MySQL进阶 - 事务

> 事务是一组操作的集合，事务会把所有操作作为一个整体一起向系统提交或撤销操作请求，即这些操作**要么同时成功，要么同时失败**。

## 控制方式

**控制事务一：**

查看/设置事务提交方式
`SELECT @@autocommit ;`
`SET @@autocommit = 0 ;`
提交事务
`COMMIT;`
回滚事务
`ROLLBACK;`

**控制事务二：**

开启事务：
`START TRANSACTION 或 BEGIN TRANSACTION;`
提交事务：
`COMMIT;`
回滚事务：
`ROLLBACK;`

操作实例：

<<< @/md/database/mysql/src/事务基本操作.sql

## 四大特性ACID

- 原子性(Atomicity)：事务是不可分割的最小操作但愿，要么全部成功，要么全部失败
- 一致性(Consistency)：事务完成时，必须使所有数据都保持一致状态
- 隔离性(Isolation)：数据库系统提供的隔离机制，保证事务在不受外部并发操作影响的独立环境下运行
- 持久性(Durability)：事务一旦提交或回滚，它对数据库中的数据的改变就是永久的

## 并发事务问题

| 问题       | 描述                                                         |
| ---------- | ------------------------------------------------------------ |
| 脏读       | 一个事务读到另一个事务还没提交的数据                         |
| 不可重复读 | 一个事务先后读取同一条记录，但两次读取的数据不同             |
| 幻读       | 一个事务按照条件查询数据时，没有对应的数据行，但是再插入数据时，又发现这行数据已经存在 |

## 并发事务隔离级别

| 隔离级别              | 脏读 | 不可重复读 | 幻读 |
| --------------------- | ---- | ---------- | ---- |
| Read uncommitted (未提交读)     | √    | √          | √    |
| Read committed   (提交读)      | ×    | √          | √    |
| Repeatable Read(可重复读，默认方式) | ×    | ×          | √    |
| Serializable    (串行化)       | ×    | ×          | ×    |

- √表示在当前隔离级别下该问题会出现
- Serializable 性能最低；Read uncommitted 性能最高，数据安全性最差

查看事务隔离级别：
`SELECT @@TRANSACTION_ISOLATION;`
设置事务隔离级别：
`SET [ SESSION | GLOBAL ] TRANSACTION ISOLATION LEVEL {READ UNCOMMITTED | READ COMMITTED | REPEATABLE READ | SERIALIZABLE };`
SESSION 是会话级别，表示只针对当前会话有效，GLOBAL 表示对所有会话有效

## 事务的实现原理

实现事务功能的三个技术如下：

1. 日志文件(redo log 和 undo log)
2. MySQL锁技术
3. 多版本并发控制MVCC(MultiVersion Concurrency Control)
    * 概念: InnoDB的 MVCC ，是通过在每行记录的后面保存两个隐藏的列来实现的。这两个列，一个保存了行的创建时间，一个保存了行的过期时间，当然存储的并不是实际的时间值，而是系统版本号。
    * 思想: 通过数据多版本来做到读写分离。从而实现不加锁读进而做到读写并行。

**实现事务采取了哪些技术以及思想？**

* 原子性：使用 undo log ，从而达到回滚；
* 持久性：使用 redo log，从而达到故障后恢复；
* 隔离性：使用锁以及MVCC，运用的优化思想有读写分离，读读并行，读写并行；
* 一致性：通过回滚，以及恢复，和在并发环境下的隔离做到一致性。
