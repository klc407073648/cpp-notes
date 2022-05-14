# select 函数

[[toc]]

## 概述

该函数**允许进程指示内核**等待多个事件中的任何一个发生，并只在有一个或多个事件发生或经历一段指定时间后才唤醒它。
(主旨思想:**不再由应用程序自己监视客户端连接，取而代之由内核替应用程序监视文件。**)

## 详细解析

函数内容详解:

```cpp
#include <sys/select.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
int select(int maxfdpl, fd_set *readset, fd_set *writeset,
			fd_set *exceptset, struct timeval *timeout);

	maxfdpl: 	监控的文件描述符集里最大文件描述符加1，因为此参数会告诉内核检测前多少个文件描述符的状态
	readset: 	监控有读数据到达文件描述符集合，传入传出参数
	writeset: 	监控写数据到达文件描述符集合，传入传出参数
	exceptset: 	监控异常发生达文件描述符集合，如带外数据到达异常，传入传出参数
	timeout: 	定时阻塞监控时间，3种情况
				1.NULL，永远等下去
				2.设置timeval，等待固定时间
				3.设置timeval里时间均为0，检查描述字后立即返回，这称为轮询
	struct timeval {
		long tv_sec; /* seconds */
		long tv_usec; /* microseconds */
	};

    void FD_ZERO(fd_set *set); 			 //把文件描述符集合里所有位清0
    void FD_SET(int fd, fd_set *set); 	 //把文件描述符集合里fd位置1
	void FD_CLR(int fd, fd_set *set); 	 //把文件描述符集合里fd清0
	int  FD_ISSET(int fd, fd_set *set);  //测试文件描述符集合里fd是否置1

```

注意事项:

* select**能监听的文件描述符个数受限于FD_SETSIZE,一般为1024**，单纯改变进程打开的文件描述符个数并不能改变select监听文件个数;
* 描述符就绪条件:
    * 当某个套接字上发生错误时，它将由select标记为既可读又可写;
    * **接收低水位标记和发生低水位标记**目的在于: 允许**应用进程控制select返回可读或可写条件之前有多少数据可读或有多大空间可用于写**。
        * 例如至少存在64字节的数据准备好读时select唤醒我们，从而避免频繁打断应用进程处理其他工作。


select总结: 

优点: 
* select 遵循posix标准，跨平台移植性较好；
* select监控的超时等待时间，可以精细到微秒；

缺点: 
* select所能监控的描述符是有最大上限的，取决于宏_FD_SETSIZE，默认大小为1024；
* select的监控原理是在内核中进行轮询遍历，这种遍历会随着描述符的增多而性能下降；
* select返回的时候会移除所有的未就绪描述符，给用户返回就绪的描述符集合，但是没有直接告诉用户那个描述符就绪，需要用户自己遍历才能获知那个描述符在集合中，操作流程比较麻烦；
* select每次监控都需要重新将集合拷贝到内核中才能进行监控；
* select每次都返回都会移除所有未就绪的描述符，因此每次监控都要重新向集合中添加描述符；

