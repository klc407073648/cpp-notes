# poll 函数

## 概述

该函数提供的功能与select类似，不过在处理流设备时，它能够提供额外的信息。
(select的描述:该函数**允许进程指示内核**等待多个事件中的任何一个发生，并只在有一个或多个事件发生或经历一段指定时间后才唤醒它。)

## 详细解析

函数内容详解:

```c++
#include <poll.h>
int poll(struct pollfd *fdarray, unsigned long nfds, int timeout);

	struct pollfd {
		int fd; 		/* 文件描述符 */
		short events; 	/* 监控的事件 */
		short revents;  /* 监控事件中满足条件返回的事件 */
	};

	events标志以及测试revents标志的一些常量:
	—————————————处理输入—————————————————————
	POLLIN			普通或带外优先数据可读,即POLLRDNORM | POLLRDBAND
	POLLRDNORM		数据可读
	POLLRDBAND		优先级带数据可读
	POLLPRI 		高优先级可读数据
	—————————————处理输出—————————————————————
	POLLOUT			普通或带外数据可写
	POLLWRNORM		数据可写
	POLLWRBAND		优先级带数据可写
	—————————————处理错误————————————————————
	POLLERR 		发生错误
	POLLHUP 		发生挂起
	POLLNVAL 		描述字不是一个打开的文件

	nfds 			监控数组中有多少文件描述符需要被监控

	timeout 		毫秒级等待
		-1：阻塞等，#define INFTIM -1 				Linux中没有定义此宏
		0：立即返回，不阻塞进程
		>0：等待指定毫秒数，如当前系统时间精度不够毫秒，向上取值


```

注意事项:

* 如果不再监控某个文件描述符时，可以把pollfd中，fd设置为-1，poll不再监控此pollfd，下次返回时，把revents设置为0。
* pollfd结构包含了要监视的event和发生的event，不再使用select"值-结果"传递的方式。
* 同时，pollfd并没有最大数量限制（但是数量过大后性能也是会下降）。和select函数一样，poll返回后，需要轮询pollfd来获取就绪的描述符。

