# 结构型 - 桥接(Bridge)

​[[toc]]

> 桥接模式(Bridge pattern): 通过将**实现和抽象放在两个不同的类层次中**而使它们可以独立改变。

# 抛砖引玉

总结面向对象实际上就两句话：一是松耦合（ Coupling），二是高内聚（ Cohesion）。

面向对象系统追求的目标就是尽可能地提高系统模块内部的内聚（Cohesion）、尽可能降低模块间的耦合（ Coupling）。然而这也是面向对象设计过程中最为难把握的部分，大家肯定在OO 系统的开发过程中遇到这样的问题：

1. 客户给了你一个需求，于是使用一个类来实现（A）；
2. 客户需求变化，有两个算法实现功能，于是改变设计，通过一个抽象的基类，再定义两个具体类实现两个不同的算法（A1 和 A2）；
3. 客户又告诉我们说对于不同的操作系统，于是再抽象一个层次，作为一个抽象基类A0，在分别为每个操作系统派生具体类（ A00 和 A01，其中 A00 表示原来的类 A）实现不同操作系统上的客户需求，这样我们就有了一共 4 个类。
4. 可能用户的需求又有变化，比如说又有了一种新的算法……..
5. 我们陷入了一个需求变化的郁闷当中，也因此带来了类的迅速膨胀。

Bridge 模式则正是解决了这类问题。

Bridge 模式典型的结构图为：

![](_images/programming/designpattern/structure/Bridge.png)

在 Bridge 模式的结构图中可以看到，系统被分为两个相对独立的部分，左边是抽象部分，右边是实现部分，这两个部分可以互相独立地进行修改：例如上面问题中的客户需求变化，当用户需求需要从 Abstraction 派生一个具体子类时候，并不需要像上面通过继承方式实现时候需要添加子类 A1 和 A2 了。另外当上面问题中由于算法添加也只用改变右边实现（添加一个具体化子类），而右边不用在变化，也不用添加具体子类了。

# 代码实现

<<< @/md/programming/designpattern/structure/Bridge/Abstraction.h

<<< @/md/programming/designpattern/structure/Bridge/Abstraction.cpp

<<< @/md/programming/designpattern/structure/Bridge/AbstractionImp.h

<<< @/md/programming/designpattern/structure/Bridge/AbstractionImp.cpp

<<< @/md/programming/designpattern/structure/Bridge/main.cpp

```bash
[root@VM-16-6-centos Bridge]# ./BridgeTest
ConcreteAbstractionImpA....
ConcreteAbstractionImpB....
```

## 代码说明

Bridge 模式将抽象和实现分别独立实现， 在代码中就是 Abstraction 类和 AbstractionImp类。

## 讨论

Bridge 是设计模式中比较复杂和难理解的模式之一， 也是 OO 开发与设计中经常会用到的模式之一。 使用组合（委托）的方式将抽象和实现彻底地解耦， 这样的好处是抽象和实现可以分别独立地变化，系统的耦合性也得到了很好的降低。

上面使用 Bridge 模式和使用带来问题方式的解决方案的根本区别在于是通过继承还是通过组合的方式去实现一个功能需求。因此面向对象分析和设计中有一个原则就是：**Favor Composition Over Inheritance**。 其原因也正在这里。