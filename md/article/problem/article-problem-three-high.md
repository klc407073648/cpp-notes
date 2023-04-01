# 问题 - 如何解决三高

> 更新缓存的的Design Pattern有四种：Cache aside, Read through, Write through, Write behind caching。

[[toc]]

![](/_images/article/problem/如何解决三高.png)

## 缓存

在计算机中，缓存是存储数据的硬件或软件组件，以便可以更快地满足将来对该数据的请求。存储在缓存中的数据可能是之前计算结果，也可能是存储在其他位置的数据副本。

### 缓存分类

- 本地缓存

  使用进程内成员变量或者静态变量，适合简单的场景，不需要考虑缓存一致性、过期时间、清空策略等问题。

  可以直接使用语言标准库内的容器来做存储，例如map。

- 分布式缓存

  当缓存的数据量增大以后，单机不足以承载缓存服务时，就要考虑对缓存服务做水平扩展，引入缓存集群。

  将数据分片后分散存储在不同机器中，如何决定每个数据分片存放在哪台机器呢？一般是采用一致性 Hash 算法，它能够保证在缓存集群动态调整，不断增加或者减少机器后，客户端访问时依然能够根据 key 访问到数据。

  一致性 Hash 算法也是值得用一篇文章来讲的，如果暂时还不懂的话可以去搜一下。


  常用的组件有 Memcache、 Redis Cluster 等，第二个是在高性能内存存储 Redis 的基础上，提供分布式存储的解决方案。

### 使用指南

- 适合缓存的场景

	- 读多写少
	- 计算耗时大，且实时性不高

- 不适合缓存的场景

	- 写多读少，频繁更新
	- 对数据一致性要求严格
	- 数据访问完全随机

### 更新策略

- Cache-Aside

	- 获取数据时先从缓存读，如果 cache hit 则直接返回，没命中就从数据源获取，然后更新缓存。
	- 写数据的时候则先更新数据源，然后设置缓存失效，下一次获取数据的时候必然 cache miss，然后触发回源。

- Cache-As-SoR

	- Read Through:直读式

	  这种方式和 Cache-Aside 非常相似，都是在查询时发生 cache miss 去更新缓存，但是区别在于 Cache-Aside 需要调用方手动更新缓存，而 Cache-As-SoR 则是由缓存内部实现自己负责，对应用层透明。

	- Write Through：直写式

	  Write Through：直写式，就是在将数据写入缓存的同时，缓存也去更新后面的数据源，并且必须等到数据源被更新成功后才可返回。这样保证了缓存和数据库里的数据一致性

	- Write Back：回写式

	  Write Back：回写式，数据写入缓存即可返回，缓存内部会异步的去更新数据源，这样好处是写操作特别快，因为只需要更新缓存。并且缓存内部可以合并对相同数据项的多次更新，但是带来的问题就是数据不一致，可能发生写丢失。

### 缓存有效原理

## 池化

内存、线程、连接这些都是资源，创建线程、分配内存、数据库连接这些操作都有一个特征， 那就是创建和销毁过程都会涉及到很多系统调用或者网络 IO。
每次都在请求中去申请创建这些资源，就会增加请求处理耗时，但是如果我们用一个 容器（池） 把它们保存起来，下次需要的时候，直接拿出来使用，避免重复创建和销毁浪费的时间。
池化实际上是预处理和延后处理的一种应用场景，通过池子将各类资源的创建提前和销毁延后。

### 内存池

在 C/C++ 中，经常使用 malloc、new 等 API 动态申请内存。由于申请的内存块大小不一，如果频繁的申请、释放会导致大量的内存碎片，并且这些  API 底层依赖系统调用，会有额外的开销。
内存池就是在使用内存前，先向系统申请一块空间留做备用，使用者需要内池时向内存池申请，用完后还回来。
内存池的思想非常简单，实现却不简单，难点在于以下几点:
1.如何快速分配内存
2.降低内存碎片率
3.维护内存池所需的额外空间尽量少
如果不考虑效率，我们完全可以将内存分为不同大小的块，然后用链表连接起来，分配的时候找到大小最合适的返回，释放的时候直接添加进链表。

### 线程池

线程池常常和队列一起使用来实现任务调度，主线程收到请求后将创建对应的任务，然后放到队列里，线程池中的工作线程等待队列里的任务。

线程池实现上一般有四个核心组成部分:

1.管理器（Manager）: 用于创建并管理线程池。

2.工作线程（Worker）: 执行任务的线程。

3.任务接口（Task）: 每个具体的任务必须实现任务接口，工作线程将调用该接口来完成具体的任务。

4.任务队列（TaskQueue）: 存放还未执行的任务。

### 连接池

一次 SQL 查询请求会经过哪些步骤:

1.和 MySQL server 建立 TCP 连接:

   三次握手

2.MySQL 权限认证：

	Server 向 Client 发送 密钥

	Client 使用密钥加密用户名、密码等信息，将加密 后的报文发送给 Server

    Server 根据 Client 请求包，验证是否是合法用户，然后给 Client 发送认证结果

3.Client 发送 SQL 语句

4.Server 返回语句执行结果

5.MySQL 关闭

6.TCP 连接断开

   四次挥手

### 对象池

一定数量的已经创建好的对象(Object)的集合。

一般来说，对象池有下面几个特征：

1.对象池中有一定数量已经创建好的对象

2.对象池向用户提供获取对象的接口，当用户需要新的对象时，便可通过调用此接口获取新的对象。如果对象池中有事先创建好的对象时，就直接返回给用户；如果没有了，对象池还可以创建新的对象加入其中，然后返回给用户

3.对象池向用户提供归还对象的接口，当用户不再使用某对象时，便可通过此接口把该对象归还给对象池

## 消息队列

消息队列的核心思想就是把同步的操作变成异步处理。

好处：

1. 服务解耦
2. 提高系统的并发度，将非核心操作异步处理，不会阻塞住主流程

坏处：

1. 降低了数据一致性，从强一致性变为最终一致性
2. 有消息丢失的风险，比如宕机，需要有容灾机制

### 服务解耦

### 异步处理

### 流量削峰

## 三高问题

### 高并发

高并发指的就是高 TPS 和高 QPS  

TPS (Transactions Per Second)每秒事务数 QPS（Query Per Second）每秒查询数等。

- 多进程
- 多线程
- 协程

  协程 Coroutines 是一种比线程更加轻量级的微线程。类比一个进程可以拥有多个线程，一个线程也可以拥有多个协程，因此协程又称微线程和纤程。可以粗略的把协程理解成子程序调用，每个子程序都可以在一个单独的协程内执行。

- 异步回调

  所谓异步回调就是，服务端发起 IO 请求的线程不等网络 IO 线程操作完成，就继续执行随后的代码，一般请求线程需要先注册一个回调函数，当IO 完成之后网络IO线程通过调用之前注册的回调函数来通知发起 IO 请求的线程，这样发起请求的线程就不会阻塞住等待结果，提高了服务处理性能。

- 容量评估

### 高性能

提高服务本身的处理能力

- 池化技术

	- 避免频繁的资源分配与回收

- 集群化

	- 横向扩展服务能力

- 缓存技术

	- 热点数据加入缓存，减少对数据库的访问

- CDN网格

  Content Delivery Network 内容分发网格

	- 存储和分发使用户就近获取内容，缩短响应时间

### 高可用

保证服务的稳定性，不出现重大问题或宕机。

- 高可用的框架

	- 目标

		- 保证服务软硬件出现故障时，数据依然可以被访问与处理

	- 主要手段

		- 数据和服务的冗余备份
		- 失效转移机制

- 高可用的应用

	- 无状态服务的失效转移

		- 负载均衡技术

	- 应用服务器集群的session管理

- 高可用的服务

	- 分级管理

		- 核心应用和服务具有更高的优先级

	- 超时设置

		- 设置服务调用的超时时间，超过时间后使用服务调度策略

	- 异步调用

		- 通过消息队列等异步方式完成

	- 服务降级

		- 限流隔离降级技术

			- 拒绝服务

				- 减少服务的调用并发数

			- 关闭功能

				- 关闭不重要的服务

	- 幂等性设计

		- 保证服务重复调用和调用一次产生的结构相同

- 高可用的数据

	- CAP原理

		- Consistency 数据一致性
		- Availibility 数据可访问性
		- Patition Tolerance 分区耐受性

	- 数据备份

		- 冷备份
		- 热备份

			- 异步热备份
			- 同步热备份

	- 失效转移

		- 心跳检测与失败报告
		- 访问转移
		- 数据恢复

## 批量处理

### 请求合并

## IO、CPU

### 零拷贝

HTTP 静态服务器发送静态文件：通过read操作将数据读到buffer，再通过send发送给客户端。
常用的零拷贝技术:
mmap:
mmap通过内存映射，将文件映射到内核缓冲区，同时，用户空间可以共享内核空间的数据。这样，在进行网络传输时，就可以减少内核空间到用户空间的拷贝次数。
sendfile:
sendfile是 Linux2.1 版本提供的，数据不经过用户态，直接从页缓存拷贝到 socket 缓存，同时由于和用户态完全无关，就减少了一次上下文切换。

### IO复用

### 高度序列化

### 无锁编程

在多线程环境下，为了避免 竞态条件（race condition）， 我们通常会采用加锁来进行并发控制，锁的代价也是比较高的，锁会导致上线文切换，甚至被挂起直到锁被释放。



基于硬件提供的原子操作 CAS(Compare And Swap) 实现一些高性能无锁的数据结构，比如无锁队列，可以在保证并发安全的情况下，提供更高的性能。

### 多线程

### 缓存友好

代码在访问数据的时候，尽量使用缓存命中率高的方式。

## 数据库

### SQL调优

### 索引优化

这是因为索引一般而言是一个排序列表，排序意味着可以基于二分思想进行查找，将查询时间复杂度做到 O(log(N))，快速的支持等值查询和范围查询。
知识点：
1.主键索引和普通索引，以及它们之间的区别
2.最左前缀匹配原则
3.索引下推
4.覆盖索引、联合索引

### 读写分离

### 分库分表

- 垂直拆分

  订单表、用户表、支付表、商品表、商家表，将它们分到不同的数据库， 比如订单库、用户库、支付库、商品库、商家库。

- 水平拆分

  订单库分为订单1库、订单2库、订单3库。

  考虑对主键通过哈希算法计算放在哪个库。

## 预处理与延后处理

### 预先处理

支付宝联合杭州市政府发放消费劵：
1.提前将杭州所有常驻居民的 user_id 存到缓存中， 比如可以直接存到 Redis。
2.当请求到来的时候我们直接通过缓存可以快速判断是否来自杭州常驻居民。如果不是则直接在这里返回前端。
这里通过预先处理减少了实时链路上的 RPC 调用，既减少了系统的外部依赖，也极大的提高了系统的吞吐量。

### 延迟处理

支付宝春节集五福活动开奖当晚，「稍后到账」

1.到账即转账，A 账户给 B 账户转钱，A 减钱， B 就必须要同时加上钱，也就是说不能 A 减了钱但 B 没有加上，这就会导致资金损失。

2.这两个动作必须一起成功或是一起都不成功，不能只成功一半，这是保证数据一致性。 保证两个操作同时成功或者失败就需要用到事务。

3.如果去实时的做到账，那么大概率数据库的 TPS（每秒处理的事务数） 会是瓶颈。通过产品提示，将到账操作延后处理，解决了数据库 TPS 瓶颈。

COW（Copy On Write，写时复制）。 Linux 创建进程的系统调用 fork，fork 产生的子进程只会创建虚拟地址空间，而不会分配真正的物理内存，子进程共享父进程的物理空间，只有当某个进程需要写入的时候，才会真正分配物理页，拷贝该物理页，通过 COW 减少了很多不必要的数据拷贝。

## 空间换时间