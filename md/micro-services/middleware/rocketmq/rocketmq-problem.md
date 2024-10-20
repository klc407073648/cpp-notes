# RocketMQ - 常见问题

[[toc]]

# 如何保证消息不丢失？

![](/_images/micro-services/middleware/rocketmq/消息流转链路.png)

如果要保证消息不丢失，那么从整个链路来看需要保证三大流程中消息都不丢失，缺一不可。

1. 发送 ———— 生产者需要保证消息一定被完整的发送并存储至Broker中。
2. 存储 ———— Broker需要保证已经存储的消息不会丢失，比如Broker重启、宕机后还在。
3. 消息 ———— 消费者需要保证拉取的消息一定被消费，比如消费一半重启了，需要确保还耒消费的消息后续也能被消费。

## 生产且发送消息流程

**生产者与Broker之间通过ack交互确认消息被成功的接收**。

![](/_images/micro-services/middleware/rocketmq/消息被接收.png)

## 存储流程

当Broker返回ack给生产者之后，生产者认为消息已经被成功存储至Broker，因此后续不会再发送这条消息。

因此Broker返回ack给生产者之前需要确保消息真的已经被成功存储了。

RocketMQ的消息默认是异步刷盘，也就是消息先写入到pageCache中，即文件系统的缓存，然后等待操作系统或者定时刷盘任务再将消息刷到磁盘上。

也就是默认情况下，**当消息写入到缓存中，Broker就给生产者返回ack了**。

如果Broker正常运行肯定是没问题的，但突然断个电，那么pageCache中还未刷盘的消息就都没了，此时消息就真的都丢了！

如果一定要确保消息不被丢失，那么需要**将Broker的刷盘配罟改成同步刷盘**，flushDiskType配置为SYNC_FLUSH。

![](/_images/micro-services/middleware/rocketmq/同步刷盘操作.png)

## 消费流程

消息是有点位提交的，consumer需要上报给Broker已经消费到的位置，这样假设consumer重启后，也可以从Broker获取之前的消费位置然后往后消费消息。

因此我们需要保证，上报给Broker的点位必须是一定已经被消费过的消息。

![](/_images/micro-services/middleware/rocketmq/提交点位.png)

所以需要确保：只有在对应消息的业务流程处理完毕后，再给Broker返回消费确认，提交点位。

## 总结

总体流程：

![](/_images/micro-services/middleware/rocketmq/保证消息不丢失.png)

# 保证消息不重复

## 消息一定会重复

从发送流程来看，无法避免消息不重复发送（重试机制），如果网络抖动Broker很可能会存储多条一模一样的消息。

从消费的流程来看，即使Broker实现了消息去重功能，也无法保证同一条消息一定只被消费者消费一次。

消费者是通过提交消费点位来跟Broker同步已经消费到位置。在集群模式下，消费点位是存储在Broker上的，并且是消费者在拉取消息的时把此时的消费点位提交给Broker。

假设消费者在消费完消息后，立马挂了？此时消息点位就没有提交到Broker，然后发生队列重平衡后，另一个消费者顶上了这个队列的消费，就产生了消息的重复消费。

所以不论从生产、存储、还是消费三个方向来看，都无法去保证消息的不重复。

## 消息幂等消费

无法保证消息不重复，但是可以利用幂等来避免重复消费产生的影响。

* 改造业务符合天然幂等写法
* 数据库唯一索引
* redis唯一判断

# 处理消息堆积问题

本质：消息生产的速度大于消息消费的速度。

常见的消息堆积原因其实不多，无非就是以下几种：

1. 瞬时流是
    * 考虑流控，降低消息生产的频率，避免把业务冲垮
2. 消费性能问题
    * 生产者批量发送；消费者批量消费
3. 机器不够
    * 水平扩容，需要考虑Topic下的队列数（消费者大于队列时，对消息堆积没作用）
4. BUG导致
5. 其它功能影响


