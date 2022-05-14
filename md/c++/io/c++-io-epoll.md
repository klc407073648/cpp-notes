# epoll 函数

[[toc]]

## 概述

1. epoll是Linux下多路复用I/O接口select/poll的增强版本，它能显著提高程序**在大量并发连接中只有少量活跃的情况下的系统CPU利用率**。因为它会**复用文件描述符集合来传递结果而不用迫使开发者每次等待事件之前都必须重新准备要被侦听的文件描述符集合**。
2. 获取事件的时候，它**无须遍历整个被侦听的描述符集，只要遍历那些被内核IO事件异步唤醒而加入Ready队列的描述符集合**就行了。
3. 目前epell是linux大规模并发网络程序中的热门首选模型。epoll除了提供select/poll那种IO事件的电平触发（Level Triggered）外，还提供了边沿触发（Edge Triggered），这就使得用户空间程序有可能缓存IO状态，减少epoll_wait/epoll_pwait的调用，提高应用程序效率。

## 基础API

1. 创建一个epoll句柄，参数size用来告诉内核监听的文件描述符的个数，跟内存大小有关。

```cpp
#include <sys/epoll.h>
int epoll_create(int size)		size: 监听数目
```

2. 控制某个epoll监控的文件描述符上的事件: 注册、修改、删除。

```cpp
#include <sys/epoll.h>
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
		epfd: epoll_creat的句柄
		op: 表示动作，用3个宏来表示: 
			EPOLL_CTL_ADD (注册新的fd到epfd)，
			EPOLL_CTL_MOD (修改已经注册的fd的监听事件)，
			EPOLL_CTL_DEL (从epfd删除一个fd)；
		event: 	告诉内核需要监听的事件

		struct epoll_event {
			__uint32_t events; /* Epoll events */
			epoll_data_t data; /* User data variable */
		};
		typedef union epoll_data {
			void *ptr;
			int fd;
			uint32_t u32;
			uint64_t u64;
		} epoll_data_t;

		EPOLLIN : 	表示对应的文件描述符可以读（包括对端SOCKET正常关闭）
		EPOLLPRI: 	表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）
		EPOLLOUT: 	表示对应的文件描述符可以写
		EPOLLERR: 	表示对应的文件描述符发生错误
		EPOLLHUP: 	表示对应的文件描述符被挂断；
		EPOLLET:  	将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)而言的
		EPOLLONESHOT: 只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里

```

3. 等待所监控文件描述符上有事件的产生，类似于select()调用。

```cpp
#include <sys/epoll.h>
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout)
	events: 	用来存内核得到事件的集合，
	maxevents: 	告之内核这个events有多大，这个maxevents的值不能大于创建epoll_create()时的size，
	timeout: 	是超时时间
				-1: 	阻塞
				0: 	立即返回，非阻塞
				>0: 	指定毫秒
	返回值: 	成功返回有多少文件描述符就绪，时间到时返回0，出错返回-1

```


注意事项:

* epoll除了提供select/poll那种IO事件的水平触发（Level Triggered）外，还提供了边缘触发（Edge Triggered），这就使得用户空间程序有可能缓存IO状态，减少epoll_wait/epoll_pwait的调用，提高应用程序效率。

* 水平触发（LT）: 默认工作模式，即当epoll_wait检测到某描述符事件就绪并通知应用程序时，应用程序可以不立即处理该事件；下次调用epoll_wait时，会再次通知此事件。

* 边缘触发（ET）:  当epoll_wait检测到某描述符事件就绪并通知应用程序时，应用程序必须立即处理该事件。如果不处理，下次调用epoll_wait时，不会再次通知此事件。（直到你做了某些操作导致该描述符变成未就绪状态了，也就是说边缘触发只在状态由未就绪变为就绪时只通知一次）。

* LT和ET原本应该是用于脉冲信号的，可能用它来解释更加形象。Level和Edge指的就是触发点，Level为只要处于水平，那么就一直触发，而Edge则为上升沿和下降沿的时候触发。比如: 0->1 就是Edge，1->1 就是Level。

* `ET模式`很大程度上减少了`epoll事件的触发次数`，因此效率比LT模式下高。


总结一下select,poll,epoll的区别: 

选择方式 |select | poll | epoll
---|---|---|---
操作方式|	遍历|	遍历|	回调
底层实现|	数组|	链表|	红黑树
IO效率|	每次调用都进行线性遍历，时间复杂度为O(n)|	每次调用都进行线性遍历，时间复杂度为O(n)|	事件通知方式，每当fd就绪，系统注册的回调函数就会被调用，将就绪fd放到readyList里面，时间复杂度O(1)
最大连接数|	1024（x86）或2048（x64）|	无上限|	无上限
fd拷贝|	每次调用select，都需要把fd集合从用户态拷贝到内核态|	每次调用poll，都需要把fd集合从用户态拷贝到内核态|	调用epoll_ctl时拷贝进内核并保存，之后每次epoll_wait不拷贝

