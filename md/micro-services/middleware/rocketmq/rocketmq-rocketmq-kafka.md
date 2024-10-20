# RocketMQ - RocketMQ和Kafka消息存储差异对比

[[toc]]

# RocketMQ消息存储

RocketMQ采用**多Topic混合存储一个文件的方式来保存消息**，即一个CommitLog文件中会包含分给此Broker的所有消息，不论消息属于哪个Topic的哪个Queue。

![](/_images/micro-services/middleware/rocketmq/RocketMQ消息存储.png)

也就是说RcoketMQ是以Broker为单位，将此Broker收到的所有消息放到一个文件中（当commitlog超过IG，新起一个commitlog)

然后再以 Topic+队列维度，存储ConsumeQueue，消费者通过ConsumeQueue得到消息的真实物理地址再去访问CommitLog获取消息的，所有ConsumeQueue可理解为消息的索引。

每条消息存储至commitlog，都会在对应的ConsumeQueue生成一条记录因此这个索引也叫**稠密案引**。

# Kafka消息存储

Kafka和RocketMQ一样，Topic下也分了多个队列提高消费的并发度，但是在Kafka中不以队列，叫分区(Partition）

Kafka对消息存储和RocketMQ不一样，它是以Partition为单位来存储消息的：

![](/_images/micro-services/middleware/rocketmq/Kafka消息存储.png)

从图中可以看到，每个Topic的每个分区都会有自已的消息文件，且对应会有索引文件，它们的文件名一样（后缀不同）。

都以文件存储的第一条消息的offset作为文件，当一个文件写满会新起一个文件（和RocketMQ的一样）。

不同分区的消息是顺序写入到对应的文件中的，也就是在存储上，相同Topic且相同分区的消息被存储到一个文件中，这跟RocketMQ的混台存槠是完全不一样的。

并且索引文件的设计也不一样，Kafka不会为每条消息都对应生成一个索引，而是每隔几条消息再
创建一条索引，这样能节省存储空间，能在内存中保存更多的索引，这样的索引叫**稀疏索引**。

> 稠密索引的查找逻辑很清晰，那稀疏索引是如何查找到对应的消息的呢？

首先通过offset找到对应的索引文件，再通过二分法遍历索引文件找到离目标消息最近的索引，再利用这个索引内容从消息文件找到最近这条消息的位置，再从这个位置开始顺序历消息文件找到目标消息。

这样一次寻址的时间复杂度为O(log2n) + O(m)，其中n为索引文件中的索引个数，m为索引的稀疏程度。

相比之下，RocketMQ的消息寻址则是根据消息的offset，直接计算消息在索引中的实际位置，然得到消息在commitlog中的物理位置以及消息长度，直接从commitlog获取消息，一次寻址的时间杂度为O(1)。

这其实就是时间和空间的权衡了。Kafka用更少的空间就需要花些更多的时间，而RocketMQ用的时间更少却花了更多的空间。

其实这个Kafka索引的二分查找也很有讲究，不是朴素的二分查找，而是**经过工程优化冷热分区的二分查找**。

如果按照正常的二分查找，那么需要读取索引的头和尾内容，尾的内容是最新写入的，很有可能已经在page Cache，而头的内容可能是很久之前的，很大概率不在page Cache中，因此需要从磁盘加载渎取到page Cache.

而内存的资源是有限的，操作系统会通过类LRU机制淘汰内存，当内存不足，很有可能因为加载这些很久以前的数据，导致内存中一些最近的pageCache被置到磁盘中，而最近的pageCache的消息正常而言是近会被消些者读取消费的，但这些消息又被挤出了内存，这样一来对性能就不好了。

且按照一般的逻辑，消些者要拉取的消息肯早在索引文件的尾部，也就是最近写入的，而不是时间久远的头部，从头部找意义不大。

![](/_images/micro-services/middleware/rocketmq/Kafka消息拉取.png)

因此Kafka给索引文件做了冷热分区，修改过的二分是先查热区的二分，如果查不到再从冷区开始，由于热区的数据身都已经在pageCache中，因此对缓存友好，不会污染缓存，且很大可能性能找到对应的消息。

![](/_images/micro-services/middleware/rocketmq/冷热区.png)

## 不同点

不同点在于RocketMQ是**将不同Topic消息都混合存储到一个文件中，而Kafka则是以分区为单位存储文件**。

相比之下Kafka的存储结构在**数据复制和迁移更加灵活**，迁移一个分区直接拷贝文件就行了，而RocketMQ由于一个文件混合存储了所有的Topic的消息，因此很不灵活。

> 那从性能来看，它们之间这样的设计有什么显著的区别吗？

之前的文章我们提到顺序读写的问题，像RocketMQ将所有消息都追加顺序写入到commitlog这个文件中，因此它是顺序写，且消费者按序获取最新的消息，虽然不同消费者并发消费时拉取消息不是完全按照顺序读取的，但是从整体来看也近似于顺序读。

![](/_images/micro-services/middleware/rocketmq/顺序写顺序读.png)

Kafka其实也遵循这个规律，对每个Partition文件来说，消息都是顺序追加写入，遵循顺序写，对消费而言，每个分区都是顺序读，但这一切都得在少量Topic和少量Partition的前提下。

想象一下，如果一个Broker中有海量的Topic或者Partition，那么对于Kafka而言就需要增加海量的消息文件，那么不同Partition消息的写入意味看需要频繁切焕不同文件来写入，对每个文件而言确实是顺序写，但是**从全局来看这是随机写**。

不同文件之前的存储不能保证连续，磁盘需要各种寻道，这样一来性能就会显著下降，同理对消息的读取也是一样的，全局来看就是随机读，因为需要切很多文件来读取消息。

因此海量Topic或者Partition场景下，Kafka的性能会显著下降，而RocketMQ没有这个烦恼，这是混合存储的好处。
