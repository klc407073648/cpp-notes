# 分布式一致性算法Raft

[[toc]]

## 参考资料

* [图解Raft:应该是最容易理解的分布式一致性算法](https://www.jianshu.com/p/5b25b019eebb)
* [分布式一致性算法-Paxos、Raft、ZAB、Gossip)](https://zhuanlan.zhihu.com/p/130332285)

## 为什么需要一致性

1. 数据不能存在单个节点（主机）上，否则可能出现单点故障。
2. 多个节点（主机）需要保证具有相同的数据。
3. 一致性算法就是为了解决上面两个问题。

## 一致性算法的定义

* 一致性就是数据保持一致，在分布式系统中，可以理解为多个节点中数据的值是一致的。

## 一致性的分类
* 强一致性
    * 说明:保证系统改变提交以后立即改变集群的状态。
    * 模型:
        * Paxos
        * Raft（muti-paxos）
        * ZAB（muti-paxos）
* 弱一致性
    * 说明:也叫最终一致性，系统不保证改变提交以后立即改变集群的状态，但是随着时间的推移最终状态是一致的。
    * 模型:
        * DNS系统
        * Gossip协议

## 一致性算法实现举例

* Google的Chubby分布式锁服务，采用了Paxos算法
* etcd分布式键值数据库，采用了Raft算法
* ZooKeeper分布式应用协调服务，Chubby的开源实现，采用ZAB算法

## Raft算法

基础概念:

* term: 任期，比如新的选举任期，即整个集群初始化时，或者新的Leader选举就会开始一个新的选举任期。
* 大多数: 假设一个集群由N个节点组成，那么大多数就是至少N/2+1。例如:3个节点的集群，大多数就是至少2；5个节点的集群，大多数就是至少3。
* 状态: 每个节点有三种状态，且某一时刻只能是三种状态中的一种:Follower（图左），Candidate（图中），Leader（图右）。假设三种状态不同图案如下所示:

![1](/_images/algorithm/distribute/raft/node_status.png)

* 节点特点:
    * Leader总统节点，负责发出提案
    * Follower追随者节点，负责同意Leader发出的提案
    * Candidate候选人，负责争夺Leader 
* 步骤: Raft算法将一致性问题分解为两个的子问题，**Leader选举和状态复制**

初始化状态时，三个节点都是Follower状态，并且term为0，如下图所示:

![2](/_images/algorithm/distribute/raft/init.png)

### Leader选举

Leader选举需要某个节点发起投票，在确定哪个节点向其他节点发起投票之前，每个节点会分配一个随机的选举超时时间（election timeout）。在这个时间内，节点必须等待，不能成为Candidate状态。现在假设节点a等待168ms , 节点b等待210ms , 节点c等待200ms 。由于a的等待时间最短，所以它会最先成为Candidate，并向另外两个节点发起投票请求，希望它们能选举自己为Leader:

![3](/_images/algorithm/distribute/raft/vote.png)

另外两个节点收到请求后，假设将它们的投票返回给Candidate状态节点a，节点a由于得到了大多数节点的投票，就会从Candidate变为Leader，如下图所示，这个过程就叫做Leader选举（Leader Election）。接下来，这个分布式系统所有的改变都要先经过节点a，即Leader节点:

![4](/_images/algorithm/distribute/raft/Leader_node.png)

如果某个时刻，Follower不再收到Leader的消息，它就会变成Candidate。然后请求其他节点给他投票（类似拉票一样）。其他节点就会回复它投票结果，如果它能得到大多数节点的投票，它就能成为新的Leader。

### 日志复制

假设接下来客户端发起一个SET 5的请求，这个请求会首先由leader即节点a接收到，并且节点a写入一条日志。由于这条日志还没被其他任何节点接收，所以它的状态是uncommitted。

![5](/_images/algorithm/distribute/raft/receive_request.png)

为了提交这条日志，Leader会将这条日志通过心跳消息复制给其他的Follower节点:

![6](/_images/algorithm/distribute/raft/copy_message.png)

一旦有大多数节点成功写入这条日志，那么Leader节点的这条日志状态就会更新为committed状态，并且值更新为5:
![7](/_images/algorithm/distribute/raft/Leader_update.png)


Leader节点然后通知其他Follower节点，其他节点也会将值更新为5。如下图所示，这个时候集群的状态是完全一致的，这个过程就叫做日志复制（Log Replication）:

![8](/_images/algorithm/distribute/raft/Follower_update.png)

### 两个超时

接下来介绍Raft中两个很重要的超时设置:选举超时和心跳超时。

* 选举超时

为了防止3个节点（假设集群由3个节点组成）同时发起投票，会给每个节点分配一个随机的选举超时时间（Election Timeout），即从Follower状态成为Candidate状态需要等待的时间。在这个时间内，节点必须等待，不能成为Candidate状态。如下图所示，节点C优先成为Candidate，而节点A和B还在等待中:

![9](/_images/algorithm/distribute/raft/election_timeout.png)

* 心跳超时

如下图所示，节点A和C投票给了B，所以节点B是leader节点。节点B会固定间隔时间向两个Follower节点A和C发送心跳消息，这个固定间隔时间被称为heartbeat timeout。Follower节点收到每一条日志信息都需要向Leader节点响应这条日志复制的结果:

![10](/_images/algorithm/distribute/raft/heartbeat_timeout.png)

### 重新选举和网络分区

* 重新选举: 选举过程中，如果Leader节点出现故障，就会触发重新选举。

* 网络分区

发生网络分区时，Raft仍能保持一致性。假设我们的集群由5个节点组成，且节点B是Leader节点:

![11](/_images/algorithm/distribute/raft/Five_node_cluster.png)


假设发生了网络分区:节点A和B在一个网络分区，节点C、D和E在另一个网络分区，且节点B和节点C分别是两个网络分区中的Leader节点:

![12](/_images/algorithm/distribute/raft/network_partition_occurred.png)

假设还有一个客户端，并且往节点B上发送了一个SET 3，由于网络分区的原因，这个值不能被另一个网络分区中的Leader即节点C拿到，它最多只能被两个节点（节点B和C）感知到，所以它的状态是uncomitted（红色）:

![13](/_images/algorithm/distribute/raft/network_partition_operation_1.png)

另一个客户端准备执行SET 8的操作，由于可以被同一个分区下总计三个节点（节点C、D和E）感知到，3个节点已经符合大多数节点的条件。所以，这个值的状态就是committed:

![14](/_images/algorithm/distribute/raft/network_partition_operation_2.png)

接下来，我们假设网络恢复正常，节点B就能感知到C节点这个Leader的存在，它就会从Leader状态退回到Follower状态，并且节点A和B会回滚之前没有提交的日志（SET 3产生的uncommitted日志）。同时，节点A和B会从新的Leader节点即C节点获取最新的日志（SET 8产生的日志），从而将它们的值更新为8。如此一来，整个集群的5个节点数据完全一致了:

![15](/_images/algorithm/distribute/raft/partition_network_recovery.png)