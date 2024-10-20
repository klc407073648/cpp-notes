# RocketMQ - 消息过滤

[[toc]]

# 概述

消费者去拉取消息的时候，Broker只给消费者想要的消息，自动把不需要的那部分过滤。这样一来才能高效地减轻消费者的负担，降低消费压力。

# Tag 和 SQL

官方提供了两种方式，分别是：

1. Tag标签过滤
2. SQL属性过滤

## Tag标签过滤

使用方法：

* 在生产者构造消息时，给消息打个标记 message.setTags("TagHello")
* 消费者在订阅主题时，指定自己想要接受的tag即可 consumer.subscribe("TopicA","TagHello")。
* 然后这个订阅关系会随着心跳发送给Broker，这样Broker就知晓消费者们想要过滤的Tag。当对应消费者去Broker拉取消息的时候，就可以过滤掉不要消息。

在官网上有一副以电商交易场景为例来展示过滤效果的图：

![](/_images/micro-services/middleware/rocketmq/Tag过滤.png)

交易相关的消息都发往Trader-Topic这个主题，其中分别有order（订单消息）、pay（支付消息）、logistics（物流消息）这三类消息。

然后物流、支付、交易成功率分析、实时计算这四个系统都订阅了Trader-Topic这个主题，但并不是所有的消息都需要。比如物流系统仅关注物流消息，支付系统仅关注支付消息，交易成功率分析则是关注订单和支付两个消息，实时计算系统则是想要处理所有的消息。

这个时候就可以利用Tag来给不同的消息打标，区分这三类消息，让对应的系统仅处理对应的子消息即可。

消费者订阅Tag有多个规则，从上图可以看到：

1. 单Tag匹配，物流和支付两个系统的订阅，consumer.subscribe("Trader—Topic"，"logistics")、consumer.subscribe("Trader_Topic",'pay")
2. 多Tag匹配，交易成功率分析系统的订阅，consumer.subscribe("Trader—Topic"，"order || pay")，不同Tag间使用两个竖线（||）隔开，多个Tag之间为或的关系，任意一个Tag命中都会被消费者拉取到。
3. 全匹配，实时计算系统的订阅，使用星号（*）作为全匹配表达式，表示都要。

## SQL标签过滤

RocketMQ提供了一种更高级的过滤方式：SQL属性过滤。

在发送消息时，生产者可以给消息设置属性，属性是一个键值对(Key/Value)，然后消费者在订阅时可以设置SQL过滤表达式来过滤多个属性。

以下代码就是生产者在发送消息时给消息设置了一个属性，同时也设置了Tag。

```
message.setTags("TagHello");
message.putUserProperty("a","1");
```

然后消费者在订阅时，可以指定SQL过滤的条件：

```
consumer.subscribe("TopicA", MessageSelector.bySql("(TAGS is not null and TAGS in ('TagA','TagHello'))" +
    "and (a is not null and a between 0 and 3)"));
```

可以看到，SQL过滤条件比较灵活，不仅可以通过是否有值来过滤，还可以根据值的内容且能结合多个条件（消息可以设置多属性）一起判断。

SQL里面利用TAGS这个属性就能用来判断tag的值，所以SQL属性过滤的功能其实是包含了Tag过滤的。

## Tag 过滤原理

生产者发送消息到Broker，遵循正常消息的存储逻辑，写到commitlog里，且分发到ConsumeQueue,每条消息映射到ConsumeQueue的内容都是commilog0ffset、size、taghash code。

![](/_images/micro-services/middleware/rocketmq/消息映射到ConsumeQueue.png)

而利用taghash code就能快速地判断当前要取的消息打了哪个tag，不需要去commitlog拉取真正的消息内容再解析，这样就比较高效的完成了tag的过滤。

> Broker是如何得知当前来拉消息的消费者要订阅的是哪个tag?

从消费者定时给Broker的心跳包里面知晓的，消费者启动后就会定时上报自己的订阅信息给Broker，订阅信息结构如下：

![](/_images/micro-services/middleware/rocketmq/订阅信息.png)

其中的tags set存储的就是订阅的tag，而code set就是tag对应的hash值，即ConsumeQueue里的taghash code。

所以Broker在消费者来拉消息的时候，利用请求的offset的从ConsumerQueue能直接得到消息的taghash code，且本地已经存储了当前消费者的订阅消息，因此无需解析消息体也无需去哪索要消费者的订阅值，直接利用hashcode对比当前消息是否应该被该消费者拉取。

如果hashcode不一致，则跳过这条消息以达到过滤的作用。

> 为什么要利用taghash code来判断，不能直接利用tag字符来判断吗？

因为ConsumerQueue的设计就是定长的，而tag字符的长度不能控制，但是hash的长度是可以控制的，所以采用哈希。

> 不同的tag可能产生一样的hash值怎么处理？

RocketMQ也考虑到了这点，当消费者拉取到经过Broker过滤的消息后，它还会自己通过tag字符判断一遍，以确保过滤那些因为哈希碰撞导致的消息。这样双重过滤下，就能保证消息被正确过滤了。

## SQL 过滤原理

其实本质上和tag过滤是一样的，差别就在于SQL属性过滤需要从commitlog获取消息，然后解析其中的属性，紧接着再做SQL匹配，不匹配的消息被过滤，校验通过的消息被消费者拉取到本地。

因为不会存在hash碰撞的情况，所以消费者本地不需要再进行二次校验。

从实现上可以确定的是：SQL属性过滤的性能比tag过滤差。

首先SQL解析比tag直接equals对比慢，其次SQL属性过滤还需要从commitlog获取消息体，解析里面的属性再比对，而tag过滤直接拿ConsumerQueue里的内容就能判断，这里又慢了一波。