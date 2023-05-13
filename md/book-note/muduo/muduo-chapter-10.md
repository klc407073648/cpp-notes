# muduo - 学习总结

[[toc]]

# 概述

> muduo是基于非阻塞的IO和事件驱动的网络库（Reactor模式），其核心是一个事件循环EventLoop，用于响应计时器和IO事件。muduo采用**基于对象（object-based）而非面向对象（object-oriented）的设计风格，其事件回调接口多以boost::function+boost::bind表达**，用户在使用muduo的时候不需要继承其中的class，其总体结构是 one loop per thread+threadpool，

描述如下：

![线程模型](/_images/book-note/muduo/线程模型.JPG)

其中，mainReactor和subReactor都是EventLoop，在mainReactor中接收连接，然后把建立后的连接分发到subReactor中。

muduo源代码的目录结构主要分为两大块：muduo/base 和muduo/net。在muduo/base中封装了和网络无关的基础类，例如日志、时间、队列、相互排斥量、条件变量、线程、线程池等。为后续网络库（muduo/net）的设计带来了极大便利。

在muduo/net中封装了和网络相关的操作，muduo是基于Reactor模式的设计的，结构如下：

![类结构](/_images/book-note/muduo/类结构.JPG)

UML关系介绍：

* 聚合关系表示用带空心菱形和箭头的直线。聚合关系强调是“整体”包含“部分”，但是“部分”可以脱离“整体”而单独存在。
* 组合关系表示用带实心菱形和箭头的直线。组合关系与聚合关系见得最大不同在于：这里的“部分”脱离了“整体”便不复存在。
* 继承关系表示用带空心三角形和箭头的直线。由派生类指向基类。

# 核心类分析

1. EventLoop是整个模式的核心，它来管理全部事件。one loop per thread说明一个线程仅仅能有一个EventLoop。它封装了eventfd和timerfd，用来唤醒等待在poll上的线程；eventfd是在其它线程唤醒当前线程时使用的，把任务加入到EventLoop的任务队列后，假设不是EventLoop的owner线程，则要唤醒它来运行任务。timerfd用来实现定时。
2. Poller是个虚基类，真正调用的时PollPoller或EPollPoller，用来实现IO的复用。事件都注册到Poller中，且Poller是EventLoop的成员，生命期由后者控制。
3. Channel 是 selectable IO channel，负责注册与响应 IO 事件，它不拥有 file descriptor。它是 Acceptor、Connector、EventLoop、TimerQueue、TcpConnection 的成员，生命期由后者控制。它和fd是一一对应的关系。尽管Channel不拥有fd，fd须要响应哪些事件都保存在Channel中。且有相应的回调函数。
4. Acceptor主要负责Tcp连接的建立。用在server。当建立连接后。它会把连接的控制权转交给TcpConnection。
5. Connector是负责发起Tcp连接的一方，用在client。发起连接比接收连接要难。非阻塞发起连接更难，要处理各种错误，还要考虑连接失败后怎样处理。当连接成功后它会把控制权交给TcpConnection。
6. TcpConnection是保存已经建立的连接。它的生命周期模式，因此采用shared_ptr来管理。它负责数据的发送和接收。负责socket fd的关闭。
7. TcpServer是服务端，有Acceptor，用Map保存了当前已经连接的TcpConnection，**一个TcpServer 对应一个TcpConnection 列表 和 一个 Acceptor**。
5. TcpClient是客户端，封装了Connector，**一个TcpClient 对应一个TcpConnection 和一个 Connector**。
9. TimerQueue 用 timerfd 实现定时，这有别于传统的设置 poll/epoll_wait 的等待时长的办法。为了简单起见，目前用链表来管理 Timer，如果有必要可改为优先队列，这样复杂度可从 O(n) 降为O(ln n) （某些操作甚至是 O(1)）。它是 EventLoop 的成员，生命期由后者控制。
10. EventLoopThreadPool 用于创建 IO 线程池，也就是说把 TcpConnection 分派到一组运行 EventLoop 的线程上。它是 TcpServer 的成员，生命期由后者控制。

# 技术要点

* muduo头文件使用**前向声明（forward declaration），简化了头文件之间的依赖**。（C++中的前向声明）
* muduo采用**基于对象（object-based）而非面向对象（object-oriented）的设计风格，其事件回调接口多以boost::function+boost::bind表达**，采用绑定回调函数的手法，实现了事件和特定函数的绑定，更加易于理解和使用。
* 对象生命周期的管理使用了shared_ptr。多线程中，对象的声明周期难以管理，一个线程难以推断对象是否已经析构。作者shared_ptr来管理对象声明周期。
* 使用weak_ptr防止对象间相互引用。造成内存永久不释放。对于类内部的一些对象，使用scoped_ptr来管理。
* 非阻塞网络库应用层为什么须要缓冲区，怎么设计缓冲区。发送过快，缓冲区增长太大怎么办。
​