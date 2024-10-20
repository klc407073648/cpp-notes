# RocketMQ - 基础

[[toc]]

> 学习任何东西需要先有一个整体的认识，然后再深入学习，钻研细节，最后再抓住核心脉络，总结整理消化在自己脑海中形成体系。

# 什么是消息队列

从消息的传递入手，这就是我们开发经常会遇到的：

![](/_images/micro-services/middleware/rocketmq/消息1.png)

随着消息越来越大，避免消息的丢失，引入了中转站的概念，和微信的未读消息一致会有一种方式提醒消息的消费者：

![](/_images/micro-services/middleware/rocketmq/消息2.png)

但是，一个中转站也可能存不下这么多消息，因此想到了扩展中转站：

![](/_images/micro-services/middleware/rocketmq/消息3.png)

但是随着中转站变多，发送者和消费者如何知道消息应该发到哪个中转站或者从哪个中转站读取消息呢？

引出今天的主人公：RocketMQ

# RocketMQ总览

首先看一下RocketMQ的相关组件和角色：

![](/_images/micro-services/middleware/rocketmq/RocketMQ总览.png)

* producer就类似上面的开发小A和Leader王
* producer group-A组进一步可以理解成开发同事的集合
* namesrvl、2类似于看板。
* BrokerA、B类似于中转站1、2
* Broker Cluster就是中转站们
* consumer就类似于上面的产品经理、测试同事和开发小B
* consumer group-A就类似于测试同事的集合。

## 各个组件

* producer：生产者，就是消息的发送者。它会将消息发送给Broker。
* producergroup：顾名思义，生产者组，它用于标识一类生产者。比如发送事务消息时，当一个生产者挂了后，broker可以找同一个生产组里的另一个生产者来确认事务的情况。
* nameSrv：名字服务，类比为一个看板，实际上它就是一个路由注册中心。Broker会定时上传自身信息给nameSrv。这样生产者和消费者就可以从nameSrv上获取这些信息，从而能够顺利的发送和接收消息。
* Broker：代理服务器，也就是消息中转站，它主要负责消息的存储、投递、查询。
* Broker Cluster：代理服务器集群，都知道一个服务是脆弱的，假设就一个broker,万一宕机了僦无法正常处理消息。
* consumer：消费者，用来消费消息。可以从Broker拉取自己想要的消息。
* consumergroup：消费者组，同个消息是能够被不同的消费者进行消费的，对于同一个组而言，消费模式有集群消费（组内负载均衡地消费消息）和广播消费（组内所有成员都消费从消费组接到的消息）两种。

Topic：主题，理解成消费的分类。例如体育、音乐、新闻等，生产者往指定主题发送消息，消费者可以选择对应主题进行消费。通过主题可以过滤不需要的消息，避免无关消息的打扰。

Tag：属于二级分类，例如体育主题中的足球主题感兴趣，就可以在体育主题的消息上带上tag标记这个消息是来自足球的。
