# 事务理论 - ACID

[[toc]]

# 事务的概念和目的

概念:

事务就是一组原子性的SQL查询，或者说是独立的工作单元。

事务的ACID概念：原子性(Atomicity),一致性(Consistency),隔离型(Isolation)以及持久性(Durability)。

![ACID原则](/_images/method/theory/ACID原则.png)

目的：

最终目的是保障数据的可靠性，一致性。

## ACID

> ACID 是数据库管理系统为了保证事务的正确性而提出来的一个理论，ACID 包含四个约束。

Atomicity（原子性）

一个事务中的所有操作，要么全部完成，要么全部不完成，不会在中间某个环节结束。事务在执行过程中发生错误，会被回滚到事务开始前的状态，就像这个事务从来没有执行过一样。

Consistency（一致性）

在事务开始之前和事务结束以后，数据库的完整性没有被破坏。

Isolation（隔离性）

数据库允许多个并发事务同时对数据进行读写和修改的能力。隔离性可以防止多个事务并发执行时由于交叉执行而导致数据的不一致。事务隔离分为不同级别，包括读未提交（Read uncommitted）、读提交（read committed）、可重复读（repeatable read）和串行化（Serializable）。

Durability（持久性）

事务处理结束后，对数据的修改就是永久的，即便系统故障也不会丢失。

可以看到，ACID 中的 A（Atomicity）和 CAP 中的 A（Availability）意义完全不同，而 ACID 中的 C 和 CAP 中的 C 名称虽然都是一致性，但含义也完全不一样。ACID 中的 C 是指数据库的数据完整性，而 CAP 中的 C 是指分布式节点中的数据一致性。再结合 ACID 的应用场景是数据库事务，CAP 关注的是分布式系统数据读写这个差异点来看。

