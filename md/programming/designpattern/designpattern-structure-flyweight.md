# 结构型 - 享元(Flyweight)

> 享元模式(Flyweight Pattern): 利用共享的方式来支持大量细粒度的对象，这些对象一部分内部状态是相同的。 它让某个类的一个实例能用来提供许多"虚拟实例"。

​[[toc]]

# 抛砖引玉

在面向对象系统的设计何实现中，创建对象是最为常见的操作。

这里就有一个问题：如果一个应用程序使用了太多的对象，就会造成很大的存储开销。 

特别是对于大量轻量级（细粒度）的对象，比如在文档编辑器的设计过程中，如果为没有字母创建一个对象的话，系统可能会因为大量的对象而造成存储开销的浪费。例如一个字母“ a”在文档中出现了100000 次， 而实际上可以让这一万个字母“ a” 共享一个对象。当然因为在不同的位置可能字母“ a” 有不同的显示效果（例如字体和大小等设置不同），在这种情况下，可以为将对象的状态分为“外部状态”和“ 内部状态”， **将可以被共享（不会变化）的状态作为内部状态存储在对象中， 而外部对象（例如上面提到的字体、 大小等）**。 可以在适当的时候将外部对象作为参数传递给对象（例如，在显示的时候，将字体、大小等信息传递给对象）。

Flyweight 模式典型的结构图为：

![](/_images/programming/designpattern/structure/Flyweight.png)

从上图可以看出， Flyweight 模式中有一个类似 Factory 模式的对象构造工厂FlyweightFactory，当客户程序员（ Client）需要一个对象时候就会向 FlyweightFactory 发出请求对象的消息 GetFlyweight（）消息， FlyweightFactory 拥有一个管理、存储对象的“仓库”（或者叫对象池， vector 实现）， GetFlyweight（）消息会遍历对象池中的对象，如果已经存在则直接返回给 Client，否则创建一个新的对象返回给 Client。当然可能也有不想被共享的对象（例如结构图中的 UnshareConcreteFlyweight），但不在本模式的讲解范围，故在实现中不给出。

# 代码实现

<<< @/md/programming/designpattern/structure/Flyweight/Flyweight.h

<<< @/md/programming/designpattern/structure/Flyweight/Flyweight.cpp

<<< @/md/programming/designpattern/structure/Flyweight/FlyweightFactory.h

<<< @/md/programming/designpattern/structure/Flyweight/FlyweightFactory.cpp

<<< @/md/programming/designpattern/structure/Flyweight/main.cpp

```bash
[root@VM-16-6-centos Flyweight]# ./FlyweightTest
ConcreteFlyweight Build.....hello
ConcreteFlyweight Build.....world!
already created by users....

```

## 代码说明

Flyweight 模式在实现过程中主要是要为**共享对象提供一个存放的“仓库”（对象池）**。

这里是通过 C++ STL 中 Vector 容器， 当然就牵涉到 STL 编程的一些问题（ Iterator 使用等）。另外应该注意的就是对对象“仓库”（对象池） 的管理策略（查找、 插入等）， 这里是通过直接的顺序遍历实现的，当然我们可以使用其他更加有效的索引策略，例如 Hash 表的管理策略，当时这些细节已经不是 Flyweight 模式本身要处理的了。

## 讨论

在 State 模式和 Strategy 模式中会产生很多的对象，因此可以通过 Flyweight模式来解决这个问题。