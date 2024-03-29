# C++ IO框架 - I/O 复用

[[toc]]

## 概述

当TCP客户端同时处理两个输入:标准输入和TCP套接字，会遇到以下问题: 
* 在客户端阻塞于标准输入上的fgets调用时，突然服务器进程被干掉。服务器TCP虽然正确地给客户端发送了一个FIN，但是客户端正阻塞于从标准输入读入的过程，看不到这个EOF，直至从标准输入读到数据才能看到EOF，这时黄花菜已经凉凉了。
* 这样的进程就需要一种预先告知内核的能力，使得内核一旦发现进程指定的一个或多个I/O条件就绪，就通知进程。这种能力就叫I/O复用（multiplexing）。

## I/O 模型

5种I/O模型:
* 阻塞式I/O
* 非阻塞式I/O
* I/O 复用
* 信号驱动式I/O
* 异步I/O

一个输入操作通常包括两个不同的阶段:
1. 等待数据准备好;
2. 从内核向进程复制数据。


![1](/_images/c++/io/五种IO模型.png)
