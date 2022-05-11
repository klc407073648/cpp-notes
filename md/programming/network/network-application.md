# 应用层

## 参考资料

* [从零开始的计网学习——应用层](https://blog.csdn.net/Nimrod__/article/details/113726975)
* [学习视频](https://www.bilibili.com/video/BV1c4411d7jb?p=29&spm_id_from=pageDriver)
* [Centos7安装搭建FTP服务器](https://www.cnblogs.com/Sungeek/p/10148656.html)
* [阿里云centos7搭建ftp服务器详细过程，&用fileZilla客户端登录](https://blog.csdn.net/MissLu99/article/details/103813271)


## 应用层概述

- 应用层解决通过应用进程的交互来实现特定网络应用的问题。

![1](/_images/programming/network/application/应用层结构.png)

- 应用层是计算机网络体系结构的**最顶层**，是**设计和建立计算机网络的最终目的**，也是计算机网络中**发展最快**的部分

应用层主要有以下应用：

![2](/_images/programming/network/application/应用层的网络应用.png)


## 客户服务器(C/S)方式和对等(P2P)方式

- 网络应用程序运行在处于网络边缘的不同段的系统上，通过彼此间的通信来完成某项任务。
- 开发一种新的网络应用给首先要考虑的问题就是**网络应用程序在各种端系统上的组织方式和他们之间的关系**。

目前流行的两种方式是：

1. 客户/服务器(Client/Server,C/S)方式
2. 对等方式（Peer-to-Peer，P2P）方式

**客户/服务器(Client/Server,C/S)方式**

- 客户和服务器指的是通信中所设计的两个应用进程。
- 客户/服务器方式所描述的是进程之间服务和被服务的关系。
- 客户是服务请求方，服务器是服务提供方。
- 服务器总是处于运行状态的，并且等待计算机的服务请求。
- 服务器有固定端口号（如HTTP服务器的默认端口是80）,而运行服务器的主机有固定的IP地址。

![3](/_images/programming/network/application/CS方式介绍.png)

C/S应用举例：

![4](/_images/programming/network/application/CS应用举例.png)

**对等方式（Peer-to-Peer，P2P）方式**

- 在P2P方式中，**没有固定的服务请求者和服务提供者**，分布在网络边缘各端**系统中的应用程序是对等的**，被称为对等方。
- **对等方之间直接通信**，每个对等即是服务的请求者，又是服务的提供者。
- 目前在因特网上流行的P2P应用主要包括P2P文件共享、即时通信，P2P流媒体、分布式存储等。
- 基于P2P应用是**服务分散型**的，因为服务不是集中在少数几个服务器计算机中，而是分散在大量对等计算机中。这些计算机不为服务提供商所有，而是个人控制的桌面计算机和笔记本电脑，通常位于住宅、校园和办公室中。
- P2P的最突出的特性之一就是他的**可扩展性**。因为系统的每增加一个对等方，不仅增加的是服务的请求者，同时也增加了服务的提供者，系统性能不会因为规模的增大而降低。

P2P应用举例：

![5](/_images/programming/network/application/P2P应用举例.png)

## 动态主机配置协议DHCP

- 互联网广泛使用的**动态主机配置协议 DHCP (Dynamic Host Configuration Protocol) 提供了即插即用连网 (plug-and-play networking) 的机制**。

- 这种机制允许一台计算机**加入新的网络和获取IP地址**，而不用手工配置。

我们进行举例说明DHCP的作用：

**没有配置DHCP服务器时：**

![6](/_images/programming/network/application/没有配置DHCP时.png)

在没有DHCP时，我们需要手动给每台主机设计IP地址、子网掩码、默认网关等数据。当网络中主机较多时，手工配置的工作量大，并且容易出错。

**当在网络中设置DHCP服务器后：**

![7](/_images/programming/network/application/配置DHCP后.png)

在引入DHCP服务器后，网络中各主机开机后自动启动DHCP程序，向DHCP服务器请求自己的网络配置信息。此时网络中各主机就可以通过DHCP自动获取网络配置信息。


**DHCP的运行过程：**

- **DHCP 使用客户 - 服务器方式。**

- **DHCP在运输层使用UDP协议，DHCP 服务器运行在 67 号端口， DHCP客户运行在 68 号端口。**

用两个服务器，一个客户端举例。

整体的时序图：

![8](/_images/programming/network/application/DHCP运行时序图.png)

1. 客户端广播DHCP发送报文：
    - 发送报文中**有事务ID和DHCP客户端的MAC地址**

2. DHCP服务器接收报文后返回DHCP提供报文：
    - DHCP提供报文中有以下信息：
        - 事务ID:DHCP客户会根据DHCP提供的事务ID,**当报文中的事务ID与客户端的发送的事务ID相等时，就表示是自己请求的报文，将其接收**。
        - 配置信息：IP地址、子网掩码、地址租期等。
            - 在使用IP地址时会使用**ARP协议来确保所选IP地址未被网络中其他主机占用**。
            - 在本例子中会受到两个服务器发来的报文，只会从中选择一个，并且一般会选择先到达的那个。并向该服务器发送DHCP请求发送报文。

3. 客户端发送选择服务器的发送请求报文：
    - 广播发送报文给各个DHCP服务器
    - DHCP请求报文中封装有以下数据：
        - **事务ID、DHCP客户端的MAC地址、接受租约中的IP地址、接收此租约DHCP服务器的IP地址**。
    - DPCH服务器根据报文中的内容，若发现其选择自己服务器，便将其接收，**并给该客户端发送DHCP确认报文**。

4. DHCP服务器发送确认报文：
    - DHCP客户经过验证收到该报文后就可以使用租用的IP地址。（在使用前还会进行ARP检测）

5. 租用期的使用：
    - 当到达租用期的一半时，会发送续约请求给服务器，根据服务器情况进行相应反馈。
    - 若没收到服务器反馈，会在0.75个续约期后再次发送并等待回应。
    - 若还是没有反应，会在续约期到达后立即放弃使用该IP地址。
    - 客户端可以随时终止使用该IP地址。


**DHCP中继代理**

首先思考一个问题：

有路由器进行隔离的网络能使用DHCP吗？

![9](/_images/programming/network/application/DHCP中继代理.png)

由于**路由器隔离广播域**，因此其DHCP请求报文不能发送到DHCP服务器中，所以其**不能使用DHCP服务**。


解决方法是给服务器配置一个DHCP服务器地址，使其称为DHCP代理中继：

![10](/_images/programming/network/application/配置DHCP中继代理.png)

这样做的原因是可以减少DHCP服务器的数量。通过中继代理进行转发来获取DHCP，而不用新增加一个DHCP服务器。

## 域名系统DNS

- 域名系统DNS的作用是将请求的**域名转换为IP地址**，给相关程序进行发送IP请求。

使用过程如下：

![11](/_images/programming/network/application/域名系统DNS的作用.png)

在浏览器中输入域名后，用户主机首先会在**自己的DNS高速缓存中查找该域名所对应的IP地址**。当在本次高速缓存查找不到后，会向网络中的**某台DNS服务器查询**。在DNS服务器中有相关的域名和IP地址数据库，收到查询请求报文后，会在**数据库中进行查寻**，之后将查询结构发送给主机。主机收到对应的IP地址后就会进行访问。

**层次树状结构的域名结构**

- 因特网采用层次树状结构的域名结构

关于域名的知识点：

![12](/_images/programming/network/application/域名的知识点.png)

顶级域名分为以下三类：

![13](/_images/programming/network/application/顶级域名的分类.png)

- 值得注意的是，**域名一样但是代表的级别不一定一样**。

因特网的域名空间举例：

![14](/_images/programming/network/application/域名空间举例.png)

域名空间的整体样子是一棵倒着的树，越往下一级越多分支。

- 域名和IP地址的映射关系必须保存在域名服务器中，供所有其他应用查询。显然不能将所有信息都存储在一台域名服务器中。
- DNS使用分布在各地的域名服务器来实现域名到IP地址的转换。

域名服务器的分类：

![15](/_images/programming/network/application/域名服务器的分类.png)

域名解析的过程：

1. 递归查询

![16](/_images/programming/network/application/域名解析递归查询.png)

与递归的思路一直，该查询是层层向上发出查询请求，查询到后在层层向下返回查询结果。

2. 迭代查询

![17](/_images/programming/network/application/域名解析迭代查询.png)

迭代查询的思路是：

每次查询先向最高级查询（根域名服务器），最高级根据查询情况返回下一级该向哪一级查询，如此重复进行，直到查询完毕。

提高域名查询效率的措施，设置高速缓存：

![18](/_images/programming/network/application/DNS高速缓存.png)

有高速缓存的查询过程为:

![19](/_images/programming/network/application/DNS高速缓存的查询过程.png)


## 文件传送协议FTP

- 文件传送是将某台计算机中的文件通过网络传送到可能相距很远的一台计算机中，是一项基本的网络应用。

- 文件传输协议FTP是因特网上**使用的最广泛的文件传送协议**。

FTP协议的要点：

- FTP提供交互式的访问，允许**客户指明文件的类型和格式**（如指明是否使用ASCII码），并允许文件具有**存取权限**（如访问文件必须经过授权，并输入有效的口令）
- **FTP屏蔽了各计算机系统的细节，因而适合于在异构网络中任意计算机之间传输文件**。
在因特网发展早期阶段，用FTP传输占整个因特网通信量的三分之一，而电子邮件和域名系统所产生的通信量还要小于FTP所产生的通信量。到了1995年，万维网的通信量才首次超过了FTP。

**FTP的应用过程**

- FTP使用C/S方式（用户/服务器方式）

**FTP客户计算机可将各种类型的文件上传到FTP服务器计算机：**

![20](/_images/programming/network/application/FTP上传.png)

**FTP客户计算机可以从FTP服务器计算机下载文件：：**

![21](/_images/programming/network/application/FTP下载.png)

根据应用需求的不同，FTP服务器可能需要一台高性能和高可靠性的服务器计算机，也可能只需要一台普通的个人计算机即可。

- FTP的常见用途是在计算机之间传输文件，尤其是用于批量传输文件。
- FTP的另外一个常见用途是让网站设计者将构成网站内容的大量文件批量上传到他们的web服务器。

**FTP的基本工作原理**

首先服务器会不断监听FTP协议的数值端口，端口号为21，等待客户端连接。

此后，FTP工作分为以下几步：

1. FTP客户端随机选择一个临时端口号发起建立TCP连接：

![22](/_images/programming/network/application/FTP客户发起TCP连接.png)

此条连接用于**传送控制命令的TCP连接**，当有**数据需要发送时，会重新发起建立传输数据的TCP连接**。

2. 有数据要传输时，客户端通过命令通道发送建立数据连接信号，此时服务器主动发起建立连接请求：

![23](/_images/programming/network/application/FTP服务器建立数据连接.png)

有数据要传输时，客户端通过命令通道发送建立数据连接信号，此时服务器就会主动发起连接建立请求报文，此时双方将会开始建立用于**发送数据的通道**。由于其是服务器主动请求建立连接，因此称为**主动连接**，接下来还有一种**被动连接**：

3. 有数据要传输时，客户端通过命令通道通知某个临时端口**被动等待TCP连接**：

![24](/_images/programming/network/application/FTP客户被动等待连接.png)

有数据要传输时，客户端通过命令通道通知某个临时端口被动等待TCP连接。此后客户端**主动会发起与服务器建立TCP连接的请求，建立数据通道**。由于此过程中**服务器是被动等待请求建立连接的**，因此称为被动连接。

需要注意的是，在两种连接中：

- 控制连接在整个会话期间一直保持打开，用于传送FTP相关的控制命令。
- 传输连接用于文件传输，每次文件传输时才建立，传输结束后就关闭。

**FTP安装与学习**
```
yum -y install vsftpd

useradd -d /home/klc/ -s /sbin/nologin admin
passwd admin


systemctl enable vsftpd.service
systemctl start vsftpd.service
systemctl status vsftpd.service

yum install -y psmisc net-tools systemd-devel libdb-devel perl-DBI

1.15.109.169
admin Build@2013
```

## 电子邮件

- 电子邮件（E-mail）是因特网上最早流行的一种应用，并且仍是当今因特网上最重要、最实用的应用之一。
- 传统的电话通信属于试试通信，具有以下两个缺点：
    - 电话通信的主叫和被叫双方必须同时在场；
    - 一些不是十分紧迫的电话也常常不必要地打断人们的工作或休息。
- 电子邮件和邮件系统的寄信相似，其工作过程如下：
    - 发件人将邮件发送到自己使用的邮件服务器；
    - 发件人的邮件服务器将收到的邮件按其目的地址转发到收件人邮件服务器中的收件人邮箱；
    - 收件人在方便的时候访问收件人邮件服务器中自己的邮箱，获取收到的电子邮件。
- 电子邮件使用方便、传播迅速并且费用低廉。不仅可以传送文字信息，而且还可以附上声音和图像。
- 随着电子邮件的广泛应用，许多国家已经正式取消了电报业务。
- 电子邮件也是使用了**客户/服务器方式**。
- 电子邮件系统的三个主要组成构件：**用户代理，邮件服务器以及电子邮件所需协议**。
    - 用户代理是用户与电子邮件系统的接口，又称为**电子邮件客户端软件**；
    - 邮件服务器是电子邮件系统的基础设施。因特网上所有的ISP都有邮件服务器，其功能是**发送和接收邮件**，同时还要负责维护用户的邮箱；
    - 协议包括邮件发送协议(例如SMTP)和邮件读取协议(例如POP3,IMAP)。

电子邮件的发送过程：

![25](/_images/programming/network/application/电子邮件的发送过程.png)

可见以上**发送邮件到服务器用到了SMTP协议，从服务器接收文件用到了POP3协议**。

**简单邮件传送协议SMTP（Simple Mail Transfer Protocol）基本工作原理**

SMTP工作原理原理概述：

- SMTP发送方的邮件服务器会**周期性对邮件进行缓存扫描，若发现有邮件**，会通过**TCP协议，端口号25**与接收方的邮件服务器建立连接。
- 建立这条连接后，SMTP客户基于这条连接给SMTP服务器发送SMTP命令，共14条。SMTP服务器会给SMTP客户端发送相应的应答，共21种。
- 双方通过**这种命令和应答的方式**最终实现客户发送邮件给SMTP服务器。

SMTP工作详细过程：

![26](/_images/programming/network/application/SMTP的工作过程.png)

电子邮件格式：

![27](/_images/programming/network/application/电子邮件格式.png)

SMTP的一些知识点：

![28](/_images/programming/network/application/SMTP的知识点.png)

MIME是一种将SMTP传递种非ASCII码值进行转换的协议，其工作流程如下：

![29](/_images/programming/network/application/MIME工作流程.png)


**常用的邮件读取协议**

邮局协议POP(Post Office Protocol)，POP3使其第三个版本，是因特网正式标准。

POP协议特点：
    - 非常简单，功能有限的邮件读取协议。用户只能以**下载并删除方式或下载并保存方式**从邮件服务器下载邮件到用户计算机。**不允许用户在邮件服务器上管理自己的邮件**。

因特网邮件访问协议IMAP(Internet Message Access Protocol),IMAP4是其第四个版本，没目前还只是因特网建议标准。

IMAP特点：
    - 功能比POP3强大的邮件读取协议。用户在自己的计算机上就可以操控邮件服务器中的邮箱，就像在本地操控一样，因此IMAP是一个联机协议。

- POP3和IMAP4都采用**基于TCP连接的客户端/服务器方式**。POP3使用熟知**端口110**，IMAP4使用熟知**端口143**。


**基于万维网的电子邮件**

- 基于万维网的电子邮件通过浏览器登陆（提供用户名和口令）邮件服务器万维网网站就可以撰写、收发、阅读和管理电子邮件。这种方式和IMAP很类似，不同的是用户计算机无需安装专门的用户代理程序，只需要使用通用的万维网浏览器。
- 邮件服务器网站通常都提供非常强大和方便的邮件管理功能，用户可以在邮件服务器网站上管理和处理自己的邮件，而不需要将邮件下载到本地进行管理。

例如：

![30](/_images/programming/network/application/万维网电子邮件传输1.png)

- 用户通过登陆HTTP请求登陆网易邮件服务器，进行邮件操作，若发送给本服务器的用户，直接通过HTTP超文本协议进行发送。

![31](/_images/programming/network/application/万维网电子邮件传输2.png)

- 若是不同的服务器，服务器之间会通过SMTP协议转发邮件给对应服务器，再发送给对应用户。

**万维网WWW**

- 万维网WWW(World Wide web)并非某种特殊的计算机网络。是一个**规模很大、联机式**的信息储藏所，是**运行在因特网上的一个分布式应用**。
- 万维网利用网页件的**超链接**将不同网站的网页链接成一张逻辑上的信息网。万维网用链接的方法能非常方便地从互联网上的一个站点访问另一个站点，从而主动地按需获取丰富的信息。
- 万维网以客户 - 服务器方式工作
- 浏览器就是在用户计算机上的万维网客户程序。万维网文档所驻留的计算机则运行服务器程序，因此这个计算机也称为万维网服务器。
- 客户程序向**服务器程序发出请求，服务器程序向客户程序送回客户所要的万维网文档**。

关于浏览器：

![32](/_images/programming/network/application/浏览器.png)

为了方便访问在世界范围的文档，万维网使用统一资源定位符URL，URL来知名因特网上任何种类资源的位置。
- URL的一般形式由以下四个部分组成：
    - <协议>://<主机>:<端口>/<路径>

万维网的文档主要有以下文件：
    - HTML、JavaScript、CSS
        - 其主要功能为:

![33](/_images/programming/network/application/万维网文件的功能.png)


**超文本传输协议HTTP(HyperText Transfer Protocol)**

HTTP定义了浏览器（万维网进行）怎样向万维网服务器请求万维网文档，以及万维网服务器怎么样把万维网文档传送给浏览器。

例如：

用户主机需要访问万维网服务器。

![34](/_images/programming/network/application/主机访问万维网服务器.png)

- HTTP/1.0采用**非持续连接**方式。该方式下，每次浏览器要请求一个文件都要与服务器建立TCP连接，当收到响应后就立即关闭连接。
- HTTP/1.1采用**持续连接**方式。该方式下，万维网服务器在**发送响应后仍然保持这条连接，使同一个客户和该服务器可以在这条连接上继续传送后续的HTTP报文**。这样子并不局限于传送同一个页面上引用的对象，而是只要这些文档都在同一个服务器上就行。
    - 进一步提高效率，HTTP/1.1的持续连接还可以使用流水线方式工作，即浏览器在收到HTTP的响应报文之前就能够连续发送多个请求报文。


HTTP报文格式:

HTTP是面向文本的。其报文的每一个字段都是一些ASCII码串，并且每个字段的长度都是不确定的。
HTTP报文分为请求报文、响应报文。

**请求报文:**

![35](/_images/programming/network/application/HTTP请求报文.png)

HTTP请求报文实例：

![36](/_images/programming/network/application/HTTP请求报文实例.png)

HTTP的首部方法字段取值可能：

![37](/_images/programming/network/application/HTTP首部方法.png)

**响应报文:**

![38](/_images/programming/network/application/HTTP响应报文.png)

响应报文常见的状态码取值：

![39](/_images/programming/network/application/HTTP响应报文状态码.png)

响应报文常见的状态行：

![40](/_images/programming/network/application/HTTP响应报文状态行.png)

万维网中的Cookie：

- Cookie是用来在服务器上记录用户信息

![41](/_images/programming/network/application/万维网的Cookie.png)

万维网中的缓存和代理服务器：

![42](/_images/programming/network/application/万维网的代理服务器.png)
