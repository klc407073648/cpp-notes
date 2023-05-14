# 常用开发库 - zeromq

**无代理的消息队列, 无代理指没有中间的缓存队列来存储消息**

## pub_sub:

* base_use:基本的PUB-SUB模式，pubServer只推送music和programing的内容，subClient可以指定订阅的内容，默认music
* better_use:  server: ip:port + 多个topic,content对;client: ip:port + 多个要接收的topic。
* syn_pubsub: syncpub中syncservice等待 SUBSCRIBERS_EXPECTED 数量的syncclient进行连接。等待连接建立后，
* publisher发送10次更新消息给subscriber。

备注：5561端口用于消息发送，5562端口用于同步，syncsub进程要启动SUBSCRIBERS_EXPECTED个。

## req_rep

* hello_world：基础的C/S架构，其中server负责发送World，接收Hello;client负责发送Hello,接收World。但是程序不包括发送和接收消息的解析都是直接写在打印语句中。
* pthread_use：在一个可执行程序中，创建多个线程，其中0线程是服务器，1线程是客户端，其他是工作线程。
* pthread_use_s：进一步完善，通过zhelps.hpp的函数s_send和s_recv，完成C++程序的消息发送和接收，并不会存在pthread_use中需要解析字符串的问题。
* req_rep_broker：request-reply broker 请求-应答代理可以客户-服务模式更容器伸缩，因为客户端看不见服务器，服务器也看不见
客户端。唯一稳定的节点是中间的代理。有代理的情况下,是rrbroker进行bind，rrserver和rrclient都是connect。
* req_rep_identity：在request-reply模型中，封装拥有应答的返回地址。例子中，有identity为空的情况，XREP会自动生成
UUID用于传输套接字；在定义identity为Hello时，应答的时候使用这个identity作为应答的地址。
