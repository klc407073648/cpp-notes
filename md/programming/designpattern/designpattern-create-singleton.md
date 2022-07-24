# 创建型 - 单例模式(Singleton pattern)

> 单例模式(Singleton): 保证一个类仅有一个实例,并提供一个访问它的全局控制点. 比如在加载配置文件时, 可使用该模式。

​[[toc]]

# 概念

Singleton 模式典型的结构图为：

![](/_images/programming/designpattern/create/Singleton.png)

# 最基础的实现

注意单例模式从概念上就是维持一个唯一的实例对象，但是该对象不能直接创建，只能通过静态方法getInstance实现。同时，构造函数要声明为protected 或 private，避免被显示调用。

## 代码实现

<<< @/md/programming/designpattern/create/Singleton/base_use/Singleton.h

<<< @/md/programming/designpattern/create/Singleton/base_use/Singleton.cpp

<<< @/md/programming/designpattern/create/Singleton/base_use/main.cpp

```bash
[root@VM-16-6-centos base_use]# ./Singleton
Singleton()
```

# 线程安全

考虑到线程安全和内存泄漏，进一步改进：

1. 单例模式对象是禁止拷贝构造和赋值的

2. 利用智能指针shared_ptr来自动释放申请的内存

3. 为了避免多个线程同时调用getInstance函数引起错误，加入互斥锁，确保仅创建一个实例。

## 代码实现

<<< @/md/programming/designpattern/create/Singleton/safe_use/Singleton.h

<<< @/md/programming/designpattern/create/Singleton/safe_use/Singleton.cpp

<<< @/md/programming/designpattern/create/Singleton/safe_use/main.cpp

```bash
[root@VM-16-6-centos safe_use]# ./Singleton
Singleton()
~Singleton()
```

# 智能指针封装

考虑封装单例智能指针类，通过typedef SingletonPtr<worker> workerPtr;定义一个指向特定对象worker的智能指针workerPtr，然后调用getInstance获取指针对象，进一步调用成员函数myWorkFun：

## 代码实现

<<< @/md/programming/designpattern/create/Singleton/share_ptr_use/Singleton.h

<<< @/md/programming/designpattern/create/Singleton/share_ptr_use/main.cpp

```bash
[root@VM-16-6-centos share_ptr_use]# ./Singleton
worker()
I'm working
~worker()
```