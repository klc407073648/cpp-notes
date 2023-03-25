# 概念 - 脑裂

[[toc]]

# 参考资料

* [wiki百科概念](https://en.wikipedia.org/wiki/Split-brain_(computing))


# wiki百科概念

> Split-brain is a computer term, based on an analogy with the medical Split-brain syndrome. It indicates **data or availability inconsistencies** originating from the maintenance of **two separate data sets** with overlap in scope, either because of servers in a network design, or a failure condition based on servers not **communicating and synchronizing** their data to each other. This last case is also commonly referred to as a network partition.

> High-availability clusters usually use a heartbeat private network connection which is used to **monitor the health and status** of each node in the cluster. 

Approaches for dealing with split-brain：

1. The optimistic approaches simply let the partitioned nodes work as usual; this provides a greater level of availability, at the cost of sacrificing correctness. Once the problem has ended, automatic or manual reconciliation might be required in order to have the cluster in a consistent state. One current implementation for this approach is Hazelcast, which does automatic reconciliation of its key-value store.[3]

2. The pessimistic approaches sacrifice availability in exchange for consistency. Once a network partitioning has been detected, access to the sub-partitions is limited in order to guarantee consistency. A typical approach, as described by Coulouris et al.,[4] is to use a quorum-consensus approach. This allows the sub-partition with a majority of the votes to remain available, while the remaining sub-partitions should fall down to an auto-fencing mode. One current implementation for this approach is the one used by MongoDB replica sets.[5] And another such implementation is Galera replication for MariaDB and MySQL.[6]

3. Modern commercial general-purpose HA clusters typically use a combination of heartbeat network connections between cluster hosts, and quorum witness storage. The challenge with two-node clusters is that adding a witness device adds cost and complexity (even if implemented in the cloud), but without it, if heartbeat fails, cluster members cannot determine which should be active. In such clusters (without quorum), if a member fails, even if the members normally assign primary and secondary statuses to the hosts, there is at least a 50% probability that a 2-node HA cluster will totally fail until human intervention is provided, to prevent multiple members becoming active independently and either directly conflicting or corrupting data.

## 产生条件

* 分区数据因通信或同步原因，产生双主或多主的场景。

## 解决方法

1. 乐观的方法：
    * 以牺牲正确性为代价，让分区节点照常工作，即提供了更高级别的可用性。等到分区恢复后，可能需要自动或手动调节，以使集群处于一致状态。（Hazelcast就是采用该方法，它对其键值存储进行自动调节）
2. 悲观的方法：
    * 以牺牲可用性换取一致性。一旦检测到网络分区，就限制对子分区的访问，以保证一致性。可以采用投票选举方式(quorum-consensus approach)。这允许具有多数投票权的分区保持可用，而剩余的子分区应降至自动隔离模式(auto-fencing mode)。(MongoDB副本集使用;MariaDB和MySQL的Galera复制)

3. 现代商用HA集群：
    * 使用集群主机之间的心跳网络连接和仲裁见证存储。
    * 添加仲裁节点，增加额外成本和复杂性
    * 没有仲裁，当心跳网络中断，集群无法确定应该存活。
    
补充：

仲裁（Quorum）：法定数量，预先规定具有投票权的节点或见证（Witness）的数量；
