# 创建型 - 原型模式(Prototype)

> 原型模式(Prototype pattern) : 使用原型实例指定要创建对象的类型，通过复制这个原型来创建新对象。

​[[toc]]

# 抛砖引玉

关于这个模式，类似于西游记里的孙悟空，通过自己身上的毛可以复制出来成千上万的自己， 用于应付一些小喽啰。

Prototype 模式也正是提供了自我复制的功能，就是说新对象的创建可以通过已有对象进行创建。在 C++中拷贝构造函数（ Copy Constructor） 曾经是很对程序员的噩梦，浅层拷贝和深层拷贝的魔魇也是很多程序员在面试时候的快餐和系统崩溃时候的根源之一。

Prototype 模式典型的结构图为：

![](/_images/programming/designpattern/create/Prototype.png)

Prototype 模式提供了一个通过已存在对象进行新对象创建的接口（ Clone）， Clone（）实现和具体的实现语言相关，在 C++中我们将通过拷贝构造函数实现之。

# 代码实现

<<< @/md/programming/designpattern/create/Prototype/Prototype.h

<<< @/md/programming/designpattern/create/Prototype/Prototype.cpp

<<< @/md/programming/designpattern/create/Prototype/main.cpp

```bash
[root@VM-16-6-centos Prototype]# ./PrototypeTest
ConcretePrototype copy ...
```

## 代码说明

Prototype 模式的结构和实现都很简单，其关键就是（C++中）拷贝构造函数的实现方式， 这也是 C++实现技术层面上的事情。由于在示例代码中不涉及到深层拷贝（主要指有指针、复合对象的情况），因此我们通过编译器提供的默认的拷贝构造函数（按位拷贝）的方式进行实现。 说明的是这一切只是为了实现简单起见， 也因为本文档的重点不在拷贝构造函数的实现技术，而在 Prototype 模式本身的思想。

备注：位拷贝拷贝的是地址（也叫浅拷贝），而值拷贝则拷贝的是内容（深拷贝）。深拷贝和浅拷贝可以简单理解为：如果一个类拥有资源，当这个类的对象发生复制过程的时候，资源重新分配，这个过程是深拷贝，反之，没有重新分配资源，是浅拷贝。

## 讨论

Prototype 模式通过复制原型（ Prototype）而获得新对象创建的功能，这里 Prototype 本身就是“对象工厂”（ 因为能够生产对象） ，实际上 Prototype 模式和 Builder 模式、AbstractFactory 模式都是通过一个类（对象实例） 来专门负责对象的创建工作（工厂对象），它们之间的区别是： Builder 模式重在复杂对象的一步步创建（并不直接返回对象） ，AbstractFactory 模式重在产生多个相互依赖类的对象，而 Prototype 模式重在从自身复制自己创建新类。