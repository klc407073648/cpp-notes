# Tars简介

用于记录Tars框架学习的内容。

# 开发模式

无论什么语言, 服务的开发模式大体如下:

- Tars通过自定义的一套语法定义, 服务间的通信协议

- Tars各语言都提供了一套lib库, 可以快速基于以上通信协议实现服务

- 各语言服务可以相互调用, 协议是一致的

- 服务可以打包发布到Tars框架上管理

- 可以在web平台管理所有服务



```
/usr/local/tars/cpp/script/cmake_tars_server.sh [App] [Server] [Servant]
##会生成所需代码框架

采用tars2cpp工具自动生成c++文件：/usr/local/tars/cpp/tools/tars2cpp Hello.tars会生成Hello.h文件，里面包含客户端和服务端的代码( 编译时会自动处理)。

即客户端和服务器都需要Hello.h

服务端:HelloImp是Servant的接口实现类，需要用户实现Hello.tars所定义的接口
客户端：引用Hello.h头文件，调用接口的函数来测试调用是否正常。
```



# 关注概念

- 服务鉴权
  - 服务准备
    - 被调服务 TestServer
    - 主调服务 HttpServer
  - 开启鉴权
    - 修改被调用方的 endpoint，开启鉴权机制
    - 修改被调用方的配置文件添加账号密钥对
    - 修改主调方的配置文件添加账号密钥
- 自定义命令
- RPC的多种调用方式（同步、异步、单向、hash）
- 支持HTTP协议，需要自己编写代码
- 服务线程说明文档 ，主要 业务逻辑线程数量默认为5
- 使用指南，阅读

# RPC

- 养成看英文文档的习惯，例如RPC调用，查询
- 动态代理，Stub
