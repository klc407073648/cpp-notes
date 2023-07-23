# 分布式系统 - 通信方式

[[toc]]

# 同步

## RPC

**实现考虑**

- 通讯方式，IO选择(同步阻塞的BIO、同步非阻塞的NIO、异步非阻塞的AIO), 长连接还是短连接
- 序列化与反序列化，hessian、protobuf、json、kryo等
- 服务注册与发现
- 负载均衡及容错
- 结果缓存
- 接口多版本控制

**现有案例**

- motan
  * 新浪微博出的rpc框架
- gRPC
  * GRPC尚未提供连接池，需要自行实现 
  * 尚未提供“服务发现”、“负载均衡”机制 
  * 因为基于HTTP2，绝大部多数HTTP Server、Nginx都尚不支持，即Nginx不能将GRPC请求作为HTTP请求来负载均衡，而是作为普通的TCP请求。（nginx1.9版本已支持） 
  * Protobuf二进制可读性差（貌似提供了Text_Fromat功能） 
- Apache Thrift
- Dubbo
  - rpcx go语言版本
  - dubbox
- HTTP - 特殊的RPC

```
HTTP1.0 协议时，HTTP 调用还只能是短链接调用，一个请求来回之后连接就会关闭。HTTP1.1 在 HTTP1.0 协议的基础上进行了改进，引入了 KeepAlive 特性可以保持 HTTP 连接长时间不断开，以便在同一个连接之上进行多次连续的请求，进一步拉近了 HTTP 和 RPC 之间的距离。

当 HTTP 协议进化到 2.0 之后，Google 开源了一个建立在 HTTP2.0 协议之上的通信框架直接取名为 gRPC，也就是 Google RPC，这时 HTTP 和 RPC 之间已经没有非常明显的界限了

- Http 1.0 短连接
- Http 1.1 Keep-Alive 保持长连接
- Http 2.0
```

# 异步

消息队列

* ActiveMQ
* RabbitMQ
* Kafka
* ZeroMQ

![](/_images/micro-services/arch/distributedsystem/mq.png)
