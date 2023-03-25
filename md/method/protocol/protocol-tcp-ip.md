# 协议 - TCP/IP

[[toc]]

# 参考资料

* [TCP 协议有哪些缺陷？](https://blog.csdn.net/AuroraFaye/article/details/124668798)
* [TCP/IP协议详解](https://blog.csdn.net/weixin_44198965/article/details/90083126)
* [TCP/IP协议族介绍](https://blog.csdn.net/qq_44830792/article/details/121478747)

# 概念

TCP/IP（Transmission Control Protocol/Internet Protocol，传输控制协议/网际协议）是指**能够在多个不同网络间实现信息传输的协议簇**。TCP/IP协议不仅仅指的是TCP 和IP两个协议，而是指一个由FTP、SMTP、TCP、UDP、IP等协议构成的协议簇， 只是因为在TCP/IP协议中TCP协议和IP协议最具代表性，所以被称为TCP/IP协议。

TCP/IP 四层模型，从上到下依次是应用层，传输层，网络层，网络接口层（数据链路层）

![](/_images/method/protocol/tcpip/tcpip协议簇.png)

## 应用层协议

DNS(Domain Name System,域名系统)是互联网的一项服务,可以简单的将用“.” 分隔的一般会有意义的域名转换成不易记忆的 IP 地址。一般使用 UDP 协议传输, 也可以使用 TCP,默认服务端口号 53。

FTP(FileTransferProtocol,文件传输协议)是用来进行文件传输的标准协议。FTP 基于 TCP 使用端口号 20 来传输数据,21 来传输控制信息。

TFTP(Trivial File Transfer Protocol,简单文件传输协议)是一个简化的文件传输协议,其设计非常简单,通过少量存储器就能轻松实现,所以一般被用来通过网络引导计算机过程中传输引导文件等小文件;

Telnet服务是用户远程登录服务，使用23端口，使用明码传送，保密性差、简单方便。

SSH(SecureShell,安全Shell),因为传统的网络服务程序比如TELNET本质上都极不安全,明文传输数据和用户信息包括密码,SSH 被开发出来避免这些问题, 它其实是一个协议框架,有大量的扩展冗余能力,并且提供供了加密压缩的通道可以为其他协议使用。

POP(PostOfficeProtocol,邮局协议)是支持通过客户端访问电子邮件的服务, 现在版本是 POP3,也有加密的版本 POP3S。协议使用 TCP,端口 110。

SMTP(Simple Mail Transfer Protocol,简单邮件传输协议)是简单邮件传输协议，用来控制信件的发送、中转，使用端口25。

HTTP(HyperText Transfer Protocol,超文本传输协议)是现在广为流行的WEB 网络的基础,HTTPS 是 HTTP 的加密安全版本。协议通过 TCP 传输,HTTP 默认使用端口 80,HTTPS 使用 443。

DHCP(Dynamic Host Configration Protocol,动态主机配置协议)是用于局域网自动分配 IP 地址和主机配置的协议。可以使局域网的部署更加简单。

SNMP（Simple Network Management Protocol）收集信息进行网络管理。它是一款基于UDP/IP的协议。在网络管理终端和路由器交换机之间工作。用于定时的记录网络拥堵传输情况，以及检查设备异常；并能够进行网络地址管理。

# 传输层

TCP(Transmission Control Protocol,传输控制协议)是一种面向连接的,可靠的, 基于字节流传输的通信协议。TCP 具有端口号的概念,用来标识同一个地址上的不同应用。

UDP（User Datagram Protocol）UDP主要用于那些对高速传输和实时性有较高要求的通信或广播通信。如IP电话进行通话的例子。如果使用TCP，数据在传送途中如果丢失会被重发，但这样无法流畅地传输通话人的声音，会导致无法进行正常交流。而采用UDP，它不会进行重发处理。从而也就不会有声音大幅度延迟到达的问题。

## 网络层

IP(Internet Protocol,网际协议)是网间层的主要协议,任务是在源地址和和目的地址之间传输数据。IP 协议只是尽最大努力来传输数据包,并不保证所有的包都可以传输 到目的地,也不保证数据包的顺序和唯一。

* ICMP(Internet Control Message Protocol,网络控制消息协议)是 TCP/IP 的 核心协议之一,用于在 IP 网络中发送控制消息,提供通信过程中的各种问题反馈。ICMP 直接使用 IP 数据包传输,但 ICMP 并不被视为 IP 协议的子协议。常见的联网状态诊断工具比如依赖于 ICMP 协议;

   * ICMP是网络层的补充，可以回送报文。用来检测网络是否通畅。
      * Ping命令就是发送ICMP的echo包，通过回送的echo relay进行网络测试。

* ARP(Address Resolution Protocol,地址解析协议)，能够将已知IP地址转换为MAC地址

* RARP(Reverse Address Resolution Protocol,逆地址解析协议)，能够将MAC地址转换为IP地址

