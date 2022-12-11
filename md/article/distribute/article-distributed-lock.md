# 分布式 - Distributed Lock Manager

> 本节主要介绍分布式单元化技术架构的内容。

[[toc]]

# 参考资料

* [陈皓老师Distributed Lock Manager的分享](https://www.youtube.com/watch?v=VnbC5RG1fEo)

# 为什么需要锁  ———— > 保证一致性

比如，对于一个订单，买家取消订单、商家发货这两个动作，先后顺序不一样，走的流程也不一致。

![](/_images/article/distribute/取消订单和商家发货.png)

## 锁的类型

* 数据库锁(Database Lock)
* 应用Sharding(Shard Application)
* 中心分布式锁(Centralized Distributed Lock Manager)

### DB Lock

以MySQL InnoDB Lock举例：

1. 共享锁(Shared Lock)：我在写，别人可以读
`SELECT * LOCK IN SHARED MODE`

2. 排他锁(Exclusive Lock)：我在写，别人不可以读。
`SELECT ... FOR UPDATE`

3. 乐观锁(Versioning Optimistic Lock)：用版本控制

![](/_images/article/distribute/DB_LOCK.png)

乐观锁性能高，但是失败时可能需要不停访问数据库。

### Shard模式

![](/_images/article/distribute/Shard.png)

流程：

* 将数据分片到不同的节点。
* 数据的索引交给索引服务器(indices)，索引服务器前面是两个Gateway。
* Gateway通过数据发现，对数据(Order A)全部转向同一个节点上。
* 对同一个节点上的数据，可以使用多线程的一些方法(比如Mutex)来锁处理数据。

当前方法的问题：

* 存在热点数据
* 扩节点时需要reshard所有数据

由此，我们使用一致性哈希(Consistent Hash)。

#### Shard问题

![](/_images/article/distribute/Shard_problem.png)

* 热点数据
* 多个数据的问题(Multiple Entities Transaction): 比如从A账户转账到B账户
* 节点失效时的数据复制倒置的一致性问题：R+W>N –> CAP理论 (NRW: 读的节点与写的节点大于N节点：写过半时是强一致性的，如果写未过半，此时是AP系统，需要自己Merge)

### Distributed Lock Manager

![](/_images/article/distribute/Lock_Manager.png)

https://en.wikipedia.org/wiki/Distributed_lock_manager

> DLM：分布式锁管理器，由他统一管理锁。需要注意的是，DLM一定要能对锁进行持久化，否则容易造成数据丢失。

1. 要提供锁的租约机制：防止加锁后，持有锁的对象不释放锁。
2. Lock Manager需要高可用，没有单点故障，锁状态可持久化。
3. 死锁检测：
    * 锁过期(Lock expired)
    * 保活心跳(Keepalive heart beats)

#### DLM Lock Modes

![](/_images/article/distribute/DLM_Lock_Modes.png)

lock modes

上面是Wikipedia中的6种锁模型：

1. 无锁
2. 并发读
3. 并发写
4. 保护读
5. 保护写
6. 排他锁

前三个没什么，主要是后面三个。

### Redlock

![](/_images/article/distribute/Redlock.png)

https://redis.io/topics/distlock

算法：

1. 客户端获取当前时间（精确到毫秒）；
2. 客户端按照顺序请求N个实例的锁。对这N个实例上锁时使用相同的key名称与随机值，随机值需要是唯一的；
3. 当获得的锁节点的数量大于半数，且消耗的时间(elapsed time) < 锁有效的时间(lock validity time)；
4. 锁实际有效时间=初始有效时间 - 消耗时间(Actual lock validity time = initial validity time - elapsed time)：这是为了让锁同时失效，而不是参差不齐的时间点失效；
5. 如果获取锁失败了，尝试释放掉所有实例。

redlock存在一些问题：

![](/_images/article/distribute/Redlock_problem.png)

1. 节点C存在时间跳变导致的锁过期失效；
2. 客户端1获取节点C的锁后挂起，在对应锁失效后又恢复了；
3. 客户端1 与节点C的通信存在很大的网络延迟。

Martin Kleppmann(写DDIA的老哥) 提出上面的挑战后，给了一个非常著名的结论：

the algorithm makes dangerous assumptions about timing and system clocks(算法依据时间和系统时钟不靠谱)

![](/_images/article/distribute/unsafe_redlock.png)

同时,给出了一个如何实现分布式锁的文章：[How to do distributed locking](https://martin.kleppmann.com/2016/02/08/how-to-do-distributed-locking.html).

可以使用fencing token的方案：

![](/_images/article/distribute/fencing_token.png)

该方案需要锁服务与数据配合，锁服务提供token，数据对token进行单调性验证。本质上是一个乐观锁，而且需要数据存储侧配合，比较复杂。

于是Redis作者Antirez做出了回应：

TL;DR http://antirez.com/news/101

* 用这个方案还要分布式锁干啥，直接用乐观锁不就行了(Fencing is great, with this, no need distributed lock!)
* 时钟跳变是个大问题，Redlock搞不定(Clock jump is a big problem, Redlock cannot work correctly under this problem.)
* Redlock能搞定网络延时和客户端挂起的问题(For network delay & client hangs, they all will be fine.)

Antirez最后说，分布式锁做的最好的是Zookeeper。

### Zookeeper

https://zookeeper.apache.org/doc/r3.1.2/recipes.html

上面的连接给了几个比较厉害的Zookeeper用法，包含了分布式锁。

![](/_images/article/distribute/Zookeeper.png)

* 在_locknode/lock-下创建顺序临时节点(Create _locknode/lock- with Sequence & Ephemeral flag)
* 这些节点看是不是节点下最小的(Get children to see to check if I am the lowest sequence number)
    * Yes. Get the Lock
    * No. Set the watch
zk lock

### Google Chubby

![](/_images/article/distribute/Google——Chubby.png)

* 两个组件：Master & Client SDK
* 集群：典型的5个节点
* 副本：使用Paxos来选主与副本
* Failover：Master失败后，其他副本进行选举
* Session & Keepalive
    * 客户端请求或结束session
    * 租约间隔与租约释放
* 性能一般

除了论文，还可看这个进行了解：https://www.slideshare.net/romain_jacotin/the-google-chubby-lock-service-for-looselycoupled-distributed-systems

需要说明，为了防止脑裂，每个master使用不同的周期。每次client连接新的master时，需要协商获取周期。

# 总结

* Concurrent transaction need be synchronized
    * DB Lock is fine, but the Optimistic Lock is great.
    * Sharding the data cannot solve the all of problem
* Distributed Lock Service need the following features:
    * High Availability
        * Data Replicas - strong consistent protocol – Pasox, Raft, zab
        * Master Failover – Leader election
    * Deadlock Detection
        * Keepalive & Lease Timeout