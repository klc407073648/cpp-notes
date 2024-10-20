# RocketMQ - NameSrv

[[toc]]

# 概述

![](/_images/micro-services/middleware/rocketmq/RocketMQ总览.png)

NameSrv的作用：类似一个看板，实际上它就是一个路由注册中心。Broker会定时上传自身信息给nameSrv。这样生产者和消费者就可以从nameSrv上获取这些信息，从而能够顺利的发送和接收消息。

## NameSrv 和 Broker

在Broker启动之前，NameSrv需要先启动。

待Broker启动后，Broker需要将自己的一些信息上报到NameSrv上，并且每过30S也会上报自身信息至NameSrv。

NameSrv每10s会扫描它记录的Broker列表，看看这些Broker是否还活着（维持心跳）。

具体判断存活的方式是看120S内该Broker是否有上报自身消息至NameSrv，如果超过120S都没有，那么NameSrv会移除这个Broker相关的信息，表示这个Broker下线了。

![](/_images/micro-services/middleware/rocketmq/NameSrv和Broker.png)

从源码角度解读相关的路由信息：

![](/_images/micro-services/middleware/rocketmq/RouteInfo.png)

* **topicQueueTable**: 主题和队列关系，每个topic可以设置不同数量队列。

![](/_images/micro-services/middleware/rocketmq/QueueData.png)

包含Broker名称，读写队列数量等。

* **brokerAddrTable**: Broker名字和具体Broker相关属性的记录，

![](/_images/micro-services/middleware/rocketmq/BrokerData.png)

每个Broker都会有对应的一个brokerld,这个broker address就是broker的地址。通过map可以利用名字找到对应broker地址。

* **clusterAddrTabIe**: Broker有集群的概念，这个map就是记录集群和对应Broker的关联关系。通过集群名就能找到所有在这个集群下的Broker。

* **brokerLiveTable**: Broker地址对应的Broker存活的相关信息。

![](/_images/micro-services/middleware/rocketmq/BrokerLivelnfo.png)

包括Broker最新上报的更新时间、版本号、读写channel通道等。前面提到的NameSrv每10S扫描的就是这个map。

**Broker会定时的把自己关于Topic的信息上报至Namesrv,Namesrv会维护记录这些信息，井且将无用的Broker剔除。**

## NameSrv 和 Producer

对于Producer来说，启动后它需要找到一台NameSrv进行关联，即进行长连接的建立。因为Producer需要知晓它将要发送的Topic应该发往哪个Broker，具体的Broker的地址是什么。

所以Producer需要从NameSrv获取有关Topic的路由信息，然后跟对应的Broker建立长连接，后面直接将消息发送给对应的Topic。

![](/_images/micro-services/middleware/rocketmq/NameSrv和Producer.png)

并且Producer每过30S会从NameSrv获取topic和broker最新的映射关系到本地，如果发现有新的Broker出现，那么就会跟新的Broker建立长连接。

![](/_images/micro-services/middleware/rocketmq/更新新的Broker连接.png)

Producer不会将路由信息缓存到本地文件，只会存储在内存中。

## NameSrv 和 Consumer

Consumer和Producer一样，在启动时需要连接NamerSrv，跟它建立长连接，并且从它获取topic和broker的映射关系，这样consumer才能知道它想要消费的消息具体在哪个Broker。然后会跟有关系的Broker建立长连接，这个和Producer是一样的，发送消息的过程和消费消息的过程是不会经过Namersrv这个中间商的。

![](/_images/micro-services/middleware/rocketmq/NameSrv和Consumer.png)

生产者和消费者会直接跟Broker进行交互，NameSrv的作用就是“看板"，来记录维护路由信息，为Consumer和Producer指路。

## NameSrv 和 NameSrv

RocketMQ实现的Namesrv非常轻量级，集群内的Namesrv是互相独立的存在，它们之间不会进行任何的信息交互。

![](/_images/micro-services/middleware/rocketmq/NameSrv和NameSrv.png)

因此Broker需要给集群内的每一台NameSrv都上报路由信息，这样每台NameSrv存储的都是完整的路由信息。

这样的设计使得NameSrv的实现非常简单，不涉及集群内多台NameSrv的数据交互，就没有类似**脑裂等信息不一致的问题**。

而对Producer和Consumer来说，因为多台NameSrv的数据都是一样的，因此它们只需要随机选择集群内的一台NameSrv进行长连接即可获取全量的路由信息。