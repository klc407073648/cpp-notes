# Redis - 哨兵模式

[[toc]]

## 简介

在主从复制下，redis服务器存在一个master和多个slave同时在工作。如果这时候，主机宕机，会发生什么情况，即数据写服务没人复制，且从机的数据也无法实现同步。

针对上述场景，引入了哨兵模式的概念，`哨兵(sentinel) 是一个分布式系统`，用于对主从结构中的每台服务器进行监控，<font color='red'>**当出现故障时通过投票机制选择新的master并将所有slave连接到新的master。**</font>


![哨兵模式](/_images/database/redis/哨兵模式.png)

哨兵的作用:

1. 监控

* 不断的检查master和slave是否正常运行。
* master存活检测、 master与slave运行情况检测

2. 通知（提醒）

* 当被监控的服务器出现问题时，向其他（哨兵间，客户端） 发送通知。

3. 自动故障转移

* 断开master与slave连接，选取一个slave作为master，将其他slave连接到新的master，并告知客户端新的服务器地址

![哨兵模式](/_images/database/redis/哨兵的作用.png)

Sentinel**基于心跳机制监测服务状态**，每隔1秒向集群的每个实例发送ping命令：

* 主观下线：如果某sentinel节点发现某实例未在规定时间响应，则认为该实例**主观下线**。

* 客观下线：若超过指定数量（quorum）的sentinel都认为该实例主观下线，则该实例**客观下线**。quorum值最好超过Sentinel实例数量的一半。

![哨兵模式](/_images/database/redis/服务状态监控.png)


## 启动哨兵模式

配置哨兵:

1. 配置一拖二的主从结构
2. 配置三个哨兵
3. 启动哨兵

```bash
启动顺序，先主机，后从机，最后哨兵
 
cd /home/believe123/myproject/redis/sentinel/
 
分别开三个窗口，启动主从机
redis-server ./redis-6379.conf
redis-server ./redis-6380.conf
redis-server ./redis-6381.conf
 
分别开三个窗口，启动三个哨兵
redis-sentinel ./sentinel-26379.conf
redis-sentinel ./sentinel-26380.conf
redis-sentinel ./sentinel-26381.conf
 
当主机宕机时，例如6379下线，6381被投票选举为主机，等待6379上线的时，它就变成了6381的从机。
```

手动杀死master服务器，6381变为master:

![手动杀死master](/_images/database/redis/手动杀死master.png)

重新连接6379，6379就作为6381的从机进行数据同步:

![6379重新连接](/_images/database/redis/6379重新连接.png)

配置文件内容如下:

![哨兵配置文件](/_images/database/redis/哨兵配置文件.png)

且运行过程中sentinel*.conf文件会被重写:

![sentinel配置文件重写](/_images/database/redis/sentinel配置文件重写.png)


## 哨兵工作原理 

哨兵在进行主从切换过程中经历三个阶段:

* 监控阶段
* 通知阶段
* 故障转移阶段

### 监控阶段 

![监控阶段](/_images/database/redis/监控阶段.png)

sentinel与master之间维持着cmd连接，来通过info获取其状态信息，通过定时ping操作维护各个 sentinel的通信。


### 通知阶段 

![通知阶段](/_images/database/redis/通知阶段.png)

每个时段，挑选出一个 sentinel 来获取master和slave的info，并通过sentinel之间的pulish和subcribe操作，将信息广播给其他sentinel。

### 故障转移阶段 

![故障转移阶段](/_images/database/redis/故障转移阶段.png)

当其中一个哨兵sentinel1发现master下线时，通知其他哨兵（sentinel2、sentinel3），然后其他哨兵尝试给master发送消息，如果发现master真的下线，则将flags:SRI_S_DOWN转换为flags:SRI_O_DOWN。

```
该策略实现是配置:
sentinel monitor mymaster 127.0.0.1 6379 2
 
说明:设置哨兵监听的主服务器信息，最后的参数决定了最终参与选举的服务器数量
```

通过投票先选举出哪个ID的sentinel去选举master:

![投票选举](/_images/database/redis/投票选举.png)


选举新的master，选举规则:

服务器列表中挑选备选master:

* 在线的
* 响应快的
* 与原master断开时间短的
* 优先原则
     - 优先级
     - offset
     - runid

发送指令（ sentinel ）

* 向新的master发送slaveof no one
* 向其他slave发送slaveof 新masterIP端口


## 三个阶段总结

1. 监控阶段
     - 同步信息

2. 通知阶段
     - 保持联通

3. 故障转移阶段
     - 发现问题
     - 竞选负责人
     - 优选新master
     - 新master上任，其他slave切换master，原master作为slave故障回复后连接