# 协议 - Http

[[toc]]

# 参考资料

- [wiki百科http定义](https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol)

# HTTP概念

> The Hypertext Transfer Protocol (HTTP) is an application layer protocol in the Internet protocol suite model for **distributed, collaborative, hypermedia information** systems.

> 分布式、协作、超媒体信息系统

## 技术概览

**Technical overview**

> HTTP functions as a request–response protocol in the client–server model. 

> HTTP的功能是在客户端和服务器模型下作为请求-响应协议。

> HTTP is designed to permit intermediate network elements to improve or enable communications between clients and servers. 

> HTTP作为中间网络元素用于提高或加强客户端与服务端之间的通信。

> HTTP is an application layer protocol designed within the framework of the Internet protocol suite.

> HTTP是在Internet协议套件框架中的应用层协议。

## HTTP版本差异

**HTTP 各个版本之间的差别**

* In HTTP/1.0 a separate connection to the same server is made for every resource request.[20]

* In HTTP/1.1 instead a **TCP connection can be reused** to make multiple resource requests (i.e. of HTML pages, frames, images, scripts, stylesheets, etc.).
    * HTTP/1.1 communications therefore experience **less latency** as the establishment of TCP connections presents considerable overhead, specially under high traffic conditions.

* TCP连接可重用；更低延迟

* HTTP/2 is a revision of previous HTTP/1.1 in order to maintain the same client–server model and the same protocol methods but with these differences in order:
    * to use a **compressed binary representation of metadata (HTTP headers) instead of a textual one**, so that headers require much less space;
    * to use a single TCP/IP (usually encrypted) connection per accessed server domain instead of 2 to 8 TCP/IP connections;
    * to use one or more bidirectional streams per TCP/IP connection in which HTTP requests and responses are broken down and transmitted in small packets to almost solve the problem of the HOLB (head of line blocking). 
    * to add a push capability to allow server application to send data to clients whenever new data is available (without forcing clients to request periodically new data to server by using polling methods).
    
    * HTTP/2 communications therefore experience much less latency and, in most cases, even more speed than HTTP/1.1 communications.

* 采用二进制替代文本方式，压缩head空间
* 采用单个连接替代多个TCP连接(使用更少的TCP/IP连接数)
* 允许在单个或多个 双向流 TCP 连接上通过交错排列块来多路传输多个资源。同时解决了第一个资源缓慢时的队头阻塞问题
    * [队头阻塞](https://zhuanlan.zhihu.com/p/330300133)
* 可以让服务端应用给客户端发送新数据，而不需要客户端定期来请求

* HTTP/3 is a revision of previous HTTP/2 in order to use QUIC + UDP transport protocols instead of TCP/IP connections also to slightly improve the average speed of communications and to avoid the occasional (very rare) problem of TCP/IP connection congestion that can temporarily block or slow down the data flow of all its streams (another form of "head of line blocking").

* 使用QUIC+UDP传输协议而不是TCP/IP连接
* 略微提高通信的平均速度，并避免偶尔（非常罕见）出现的TCP/IP连接拥塞问题，该问题可能会暂时阻塞或减缓其所有流的数据流（另一种形式的“队头阻塞”）。

* HTTP/2 使用了多路复用，一般来说同一域名下只需要使用一个 TCP 连接。当这个连接中出现了丢包的情况，那就会导致 HTTP/2 的表现情况反倒不如 HTTP/1 了。因为在出现丢包的情况下，整个 TCP 都要开始等待重传，也就导致了后面的所有数据都被阻塞了。

* HTTP/3 基于UDP协议，所以如果数据包丢失，只会中断一个数据流，而不会中断所有流。
    * QUIC 原生就实现了多路复用，并且传输的单个数据流可以保证有序交付且不会影响其他的数据流，这样的技术就解决了之前 TCP 存在的问题。
    * QUIC 在移动端的表现也会比 TCP 好。因为 TCP 是基于 IP 和端口去识别连接的，这种方式在多变的移动端网络环境下是很脆弱的。但是QUIC 是通过 ID 的方式去识别一个连接，不管你网络环境如何变化，只要 ID 不变，就能迅速重连上。

**Summary of HTTP milestone versions**

![](/_images/method/protocol/http/http_version.png)

## HTTP数据交互

> HTTP is a stateless application-level protocol and it requires a reliable network transport connection to exchange data between client and server. In HTTP implementations, TCP/IP connections are used using well known ports (typically port 80 if the connection is unencrypted or port 443 if the connection is encrypted, see also List of TCP and UDP port numbers). In HTTP/2, a TCP/IP connection plus multiple protocol channels are used. In HTTP/3, the application transport protocol QUIC over UDP is used.

**Request and response messages through connections**

> Data is exchanged through a sequence of request–response messages which are exchanged by a session layer transport connection. An HTTP client initially tries to connect to a server establishing a connection (real or virtual). An HTTP(S) server listening on that port accepts the connection and then waits for a client's request message. The client sends its request to the server. Upon receiving the request, the server sends back an HTTP response message (header plus a body if it is required). The body of this message is typically the requested resource, although an error message or other information may also be returned. At any time (for many reasons) client or server can close the connection. Closing a connection is usually advertised in advance by using one or more HTTP headers in the last request/response message sent to server or client.

**Persistent connections**

* In HTTP/0.9, the TCP/IP connection is **always closed after server response has been sent**, so it is never persistent.

* In HTTP/1.0, as stated in RFC 1945, the TCP/IP connection should **always be closed by server after a response has been sent**.

* In HTTP/1.1 a **keep-alive-mechanism** was officially introduced so that a connection could be reused for more than one request/response. Such persistent connections reduce request latency perceptibly because the client does not need to re-negotiate the TCP 3-Way-Handshake connection after the first request has been sent. Another positive side effect is that, in general, the connection becomes faster with time due to TCP's **slow-start-mechanism**.

* HTTP/1.1 added also HTTP pipelining in order to further reduce lag time when using persistent connections by allowing clients to send multiple requests before waiting for each response. This optimization was never considered really safe because a few web servers and many proxy servers, specially transparent proxy servers placed in Internet / Intranets between clients and servers, did not handle pipelined requests properly (they served only the first request discarding the others, they closed the connection because they saw more data after the first request or some proxies even returned responses out of order etc.). Besides this only HEAD and some GET requests (i.e. limited to real file requests and so with URLs without query string used as a command, etc.) could be pipelined in a safe and idempotent mode. After many years of struggling with the problems introduced by enabling pipelining, this feature was first disabled and then removed from most browsers also because of the announced adoption of HTTP/2.

* HTTP/2 extended the usage of persistent connections by  **multiplexing many concurrent requests/responses through a single TCP/IP connection**.

* HTTP/3 does not use TCP/IP connections but  **QUIC + UDP**

**Content retrieval optimizations**

## HTTP鉴权

> HTTP provides multiple authentication schemes such as **basic access authentication and digest access authentication** which operate via a challenge–response mechanism whereby the server identifies and issues a challenge before serving the requested content

## HTTP应用会话

HTTP is a stateless protocol. A stateless protocol does not require the web server to retain information or status about each user for the duration of multiple requests.

Some web applications need to manage user sessions, so they implement states, or server side sessions, using for instance HTTP cookies[45] or hidden variables within web forms.

To start an application user session, an interactive authentication via web application login must be performed. To stop a user session a logout operation must be requested by user. These kind of operations do not use HTTP authentication but a custom managed web application authentication.

## HTTP/1.1 请求和响应消息

### 请求方法

![](/_images/method/protocol/http/request_method.png)

### 响应状态码

```
1XX (informational)
The request was received, continuing process.
2XX (successful)
The request was successfully received, understood, and accepted.
3XX (redirection)
Further action needs to be taken in order to complete the request.
4XX (client error)
The request contains bad syntax or cannot be fulfilled.
5XX (server error)
The server failed to fulfill an apparently valid request.
```

* 1xx：表示临时响应并需要请求者继续执行操作的状态代码
* 2xx：表示成功处理了请求的状态代码
* 3xx：要完成请求，需要进一步操作（通常这些代码用来重定向）
* 4xx：表示请求可能出错，妨碍了服务器的处理
* 5xx：表示服务器在尝试处理请求时，发生内部错误

### 例子

客户端请求
```
GET / HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: en-GB,en;q=0.5
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
```

服务端响应
```
HTTP/1.1 200 OK
Date: Mon, 23 May 2005 22:38:34 GMT
Content-Type: text/html; charset=UTF-8
Content-Length: 155
Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT
Server: Apache/1.3.3.7 (Unix) (Red-Hat/Linux)
ETag: "3f80f-1b6-3e1cb03b"
Accept-Ranges: bytes
Connection: close

<html>
  <head>
    <title>An Example Page</title>
  </head>
  <body>
    <p>Hello World, this is a very simple HTML document.</p>
  </body>
</html>
```
