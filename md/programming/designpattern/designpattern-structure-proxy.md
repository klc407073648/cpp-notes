# 结构型 - 代理(Proxy)

> 代理模式(Proxy pattern): 为另一个对象提供一个替身或占位符以控制对这个对象的访问。

​[[toc]]

# 抛砖引玉

Proxy 模式可以解决的常见问题：

1. 创建开销大的对象时候，比如显示一幅大的图片，我们将这个创建的过程交给代理去完成， GoF 称之为虚代理（ Virtual Proxy）；

2. 为网络上的对象创建一个局部的本地代理， 比如要操作一个网络上的一个对象（网络性能不好的时候，问题尤其突出），我们将这个操纵的过程交给一个代理去完成， GoF 称之为远程代理（ Remote Proxy）；

3. 对对象进行控制访问的时候， 比如在 Jive 论坛中不同权限的用户（如管理员、普通用户等） 将获得不同层次的操作权限， 我们将这个工作交给一个代理去完成， GoF 称之为保护代理（ Protection Proxy）。

4. 智能指针（Smart Pointer）

Proxy 模式典型的结构图为：

![](/_images/programming/designpattern/structure/Proxy.png)


# 代码实现

<<< @/md/programming/designpattern/structure/Proxy/Proxy.h

<<< @/md/programming/designpattern/structure/Proxy/Proxy.cpp

<<< @/md/programming/designpattern/structure/Proxy/main.cpp

```bash
[root@VM-16-6-centos Proxy]# ./ProxyTest
Proxy request....
ConcreteSubject......request....
```

## 代码说明

Proxy 模式的实现很简单，这里不做多余解释。可以看到，示例代码运行后， p 的 Request 请求实际上是交给了 sub 来实际执行。

## 讨论

Proxy 模式最大的好处就是实现了逻辑和实现的彻底解耦。