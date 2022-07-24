# 行为型 - 中介者(Mediator)

> 中介者模式(Mediator pattern) : 使用中介者模式来集中相关对象之间复杂的沟通和控制方式。

​[[toc]]

# 概念

Mediator 模式典型的结构图为：

![](/_images/programming/designpattern/behave/Mediator.png)

Mediator 模式中，每个 Colleague 维护一个 Mediator，当要进行交互，例如图中ConcreteColleagueA 和 ConcreteColleagueB 之间的交互就可以通过 ConcreteMediator 提供的DoActionFromAtoB 来处理， ConcreteColleagueA 和 ConcreteColleagueB 不必维护对各自的引用，甚至它们也不知道各个的存在。 **Mediator 通过这种方式将多对多的通信简化为了一（ Mediator） 对多（ Colleague）的通信**。

# 代码实现

<<< @/md/programming/designpattern/behave/Mediator/Colleage.h

<<< @/md/programming/designpattern/behave/Mediator/Colleage.cpp

<<< @/md/programming/designpattern/behave/Mediator/Mediator.h

<<< @/md/programming/designpattern/behave/Mediator/Mediator.cpp

<<< @/md/programming/designpattern/behave/Mediator/main.cpp

```bash
[root@VM-16-6-centos Mediator]# ./MediatorTest
State of ConcreteColleageA: old
State of ConcreteColleageB: old

State of ConcreteColleageA: new
State of ConcreteColleageB: new

State of ConcreteColleageB: old
State of ConcreteColleageA: old
```

## 代码说明

Mediator 模式的实现关键就是将**对象 Colleague 之间的通信封装到一个类种单独处理**，为了模拟 Mediator 模式的功能，这里给每个 Colleague 对象一个 string 型别以记录其状态，并通过状态改变来演示对象之间的交互和通信。这里主要就 Mediator 的示例运行结果给出

分析：
1. 将 ConcreteColleageA 对象设置状态“ old”， ConcreteColleageB 也设置状态“ old”；
2. ConcreteColleageA 对象改变状态，并在 Action 中和 ConcreteColleageB 对象进行通信，并改变ConcreteColleageB 对象的状态为“ new”；
3. ConcreteColleageB 对象改变状态，并在 Action 中和 ConcreteColleageA 对象进行通信，并改变ConcreteColleageA 对象的状态为“ old”；

注意到，两个 Colleague 对象并不知道它交互的对象，并且也不是显示地处理交互过程，这一切都是通过 Mediator 对象完成的，示例程序运行的结果也正是证明了这一点。

## 讨论

Mediator 模式是一种很有用并且很常用的模式，它通过将对象间的通信封装到一个类中，**将多对多的通信转化为一对多的通信， 降低了系统的复杂性（有点类似消息队列）**。 Mediator 还获得系统解耦的特性，通过 Mediator，各个 Colleague 就不必维护各自通信的对象和通信协议，降低了系统的耦合性， Mediator 和各个 Colleague 就可以相互独立地修改了。Mediator 模式还有一个很显著额特点就是将控制集中，集中的优点就是便于管理，也正式符合了 OO 设计中的每个类的职责要单一和集中的原则