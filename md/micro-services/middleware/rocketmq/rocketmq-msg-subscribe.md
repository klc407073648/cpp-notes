# RocketMQ - 订阅关系

[[toc]]

# 概述

在RocketMQ中，订阅关系是按照消费组和主题+tag粒度设计的，也就是说**一个订阅关系=某消费组+某主题+某tag**。

举个例子，比如现在有一个Topic-A，两个ConsumerGroup1和2。

* ConsumerGroup-1订阅了Topic-A、Tag-1，这是一个订阅关系。
* ConsumerGroup-2订阅了Topic-A、Tag-2，这是一个订阅关系。

![](/_images/micro-services/middleware/rocketmq/订阅关系1.png)

再举个例子，比如现在有一个Topic-A、Topic-B,一个ConsumerGroup1。

* ConsumerGroup-1订阅了Topic-A、Tag-1，这是一个订阅关系。
* ConsumerGroup-1也订阅了Topic-B、Tag-2，这是一个订阅关系。

![](/_images/micro-services/middleware/rocketmq/订阅关系2.png)

# 订阅关系一致性

一致性：同一个消费组内不同消费者对同一个订阅关系的一致性问题。

两个常见的订阅关系不一致错误：

比如现在有一个Topic-A、Topic-B,一个ConsumerGroup-1，里面有consumer-1、consumer-2两个消费者。

* consumer-l订阅了Topic-A。
* consumer-2订阅了Topic-B。

![](/_images/micro-services/middleware/rocketmq/订阅关系不一致.png)

这就发生了**一个消费组内不同消费者订阅了不同Topic的问题**。

从定义上的理解就感觉这样不对，因为订阅关系是**以消费组和主题+tag为粒度的**，而不是以某个消费者为粒度的。组里面不同消费者的订阅都不一致，如何对外提供服务。

除了不同Topic的问题，Tag过滤不一致的问题也经常见。

比如现在有一个Topic-A,分别有Tags-1、Tags-2，一个ConsumerGroup-1，里面有consumer-1、consumer-2两个消费者。

* consumer-1订阅了Topic-A,Tags-1。
* consumer-2订阅了Topic-A,Tags-2。

![](/_images/micro-services/middleware/rocketmq/订阅Tag不一致.png)

一个消费组内不同消费者虽然订阅了同样的Topic,但是Tag不一样，这也发生了订阅关系不一致！

所以，订阅关系一致性指的是同一个消费者组下所有消费者实例所订阅的Topic、Tag必须完全一致。

> 如果发生订阅关系不一致会怎样？

可能会**导致报错、消息不被消费甚至消息的丢失**。

> 如何理解订阅消息不一致产生的问题？

![](/_images/micro-services/middleware/rocketmq/消费不同主题.png)

假设Topic-A每天百万消息量，Topic-B每天10条消息，这样来看消息组内能算互帮互助吗？显然consumer-1会过载，consumer-2却很轻松。

所以RocketMQ的设计需要尽可能地满足负载均衡，而不是简单的用Topic来划分负责的工作。

> 心跳机制

消费者会定时上报自己的订阅关系给Broker, 而Broker是以消费组为单位保存这个订阅关系。

如果消费组里的不同消费者订阅不同Topic，则会在定时上报时覆盖其他消费者上报的Topic，产生报错。

> 消息拉取

消费者会根据自己的订阅关系，定时地构建拉取请求，去拉取对应的消息。

如果消费组里的不同消费者订阅不同Topic，拉取消息时，发现不是自己订阅的主题，导致消息不被消费。

> 重平衡机制

消费者会定时重平衡，即客户端负载均衡，即瓜分整个消费组负责的Topic对应的队列。

重平衡后，不同消费者因为订阅的Tag不同，将消息选择性丢失。