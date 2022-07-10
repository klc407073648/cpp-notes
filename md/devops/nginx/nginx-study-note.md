# Nginx应用 - nginx反向代理服务器

[[toc]]

## nginx进程间的关系

nginx一般通过一个master进程来管理多个worker进程(个数一般等于CPU核数)。master只负责监控管理worker进程，具体互联网服务都是由worker进程提供。worker进程之间通过共享内存、原子操作等一些进程间通信机制来实现负载均衡等功能

![部署后nginx的进程间关系](/_images/devops/nginx/部署后nginx的进程间关系.png)


## 仅对指定的客户端输出debug级别的日志

events {
    debug_connection 10.224.66.14
    debug_connection 10.224.57.0/24
}

## 超时keeplive_timeout配置详解

Nginx 处理的每个请求均有相应的超时设置。如果做好这些超时时间的限定，判定超时后资源被释放，用来处理其他的请求，以此提升 Nginx 的性能。

**keepalive_timeout**

* HTTP是一种无状态协议，客户端向服务器发送一个 TCP 请求，服务端响应完毕后断开连接。

* 如果客户端向服务器发送多个请求，每个请求都要建立各自独立的连接以传输数据。

* HTTP 有一个 KeepAlive 模式，它告诉 webserver 在处理完一个请求后保持这个 TCP 连接的打开状态。若接收到来自客户端的其它请求，服务端会利用这个未被关闭的连接，而不需要再建立一个连接。

* KeepAlive 在一段时间内保持打开状态，它们会在这段时间内占用资源。占用过多就会影响性能。

* Nginx 使用 keepalive_timeout 来指定 KeepAlive 的超时时间（timeout）。指定每个 TCP 连接最多可以保持多长时间。Nginx 的默认值是 75 秒，有些浏览器最多只保持 60 秒，所以可以设定为 60 秒。若将它设置为 0，就禁止了 keepalive 连接。

## 每个worker的最大连接数

worker_connections  1024;

## 用HTTP核心模块配置一个静态Web服务器

Nginx为配置一个完整的静态Web服务器提供了非常多的功能，主要有以下8类：

1. 虚拟主机与请求的分发
2. 文件路径的定义
3. 内存及磁盘资源的分配
4. 网络连接的设置
5. MIME类型的设置
6. 对客户端请求的限制
7. 文件操作的优化
8. 对客户端请求的特殊处理


### 虚拟主机与请求的分发

配置块 server

1. 监听端口
2. 主机名称
3. location

```
1. =表示把URI作为字符串，以便于参数中的uri做完全匹配
location = / {
    #只有用户请求是/时，才会使用该location下的配置
}
2. ~表示匹配URI时是字母大小写敏感的。
3. ~*表示匹配URI时忽略字母大小写问题。
4. ^~表示匹配URI时只需要前半部分与uri参数匹配即可。
5. @表示仅用于Nginx服务内部请求之间的重定向，带有@的location不直接处理用户请求
    当然，在uri参数里是可以用正则表达式：
    location ~* \. (gif|jpg|jpeg) $ {
        #匹配以.gif、.jpg、.jpeg结尾的请求
    }
6. 可以用/作为参数，来匹配所有HTTP请求
    location  / {
        #可以匹配所有HTTP请求
    }
```

### 文件路径的定义

```
location /download/ {
    root /opt/web/html/
}

将请求的URI  /download/index/test.html  转换成web服务器上的 /opt/web/html/download/index/test.html 

location /conf {
    alias /usr/local/nginxc/conf/
}

将 /conf/nginx.conf 转换成 /usr/local/nginxc/conf/nginx.conf，即会去掉/conf/nginx.conf中原始的conf前缀
```

