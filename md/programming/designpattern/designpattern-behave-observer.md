# 行为型 - 观察者(Observer)

​[[toc]]

> 观察者模式(Observer): 定义了一种一对多的依赖关系,让多个观察者对象同时监听某一主题对象,在它的状态发生变化时,会通知所有的观察者。

# 抛砖引玉

Observer 模式应该可以说是应用最多、影响最广的模式之一，因为 Observer 的一个实例 Model/View/Control（ MVC） 结构在系统开发架构设计中有着很重要的地位和意义， MVC实现了业务逻辑和表示层的解耦。 

Observer 模式要解决的问题为：建立一个一（ Subject）对多（ Observer） 的依赖关系， 并且做到当“一” 变化的时候， 依赖这个“一”
的多也能够同步改变。 

最常见的一个例子就是：对同一组数据进行统计分析时候，希望能够提供多种形式的表示（例如以表格进行统计显示、 柱状图统计显示、 百分比统计显示等）。这些表示**都依赖于同一组数据，当然需要当数据改变的时候，所有的统计的显示都能够同时改变**。Observer 模式就是解决了这一个问题。

Observer 模式典型的结构图为：

![](_images/programming/designpattern/behave/Observer.png)

具体思路解析：

1. Subject 提供依赖于它的观察者 Observer 的注册（Attach）和注销（Detach）操作，并且提供了使得依赖于它的所有观察者同步的操作（Notify）。

2. Subject通过维护list<Observer* >* _obvs，Object维护Subject* _sub，使用时。先创建Subject* sub，然后将其作为变量传递给Observer* o1,o2，使得ConcreteObserver在构造时完成Attach操作，将监听对象加入Subject的监听队列_obvs。

3. Subject* sub 通过SetState函数改变状态，在调用Notify去遍历监听队列_obvs，更新Observer* o1,o2的状态。

# 代码实现

<<< @/md/programming/designpattern/behave/Observer/Subject.h

<<< @/md/programming/designpattern/behave/Observer/Subject.cpp

<<< @/md/programming/designpattern/behave/Observer/Observer.h

<<< @/md/programming/designpattern/behave/Observer/Observer.cpp

<<< @/md/programming/designpattern/behave/Observer/main.cpp

执行结果如下，因为list是头插法，后加入的ConcreteObserverB在sub广播通知list的开头，所以通知的消息先到达B：

```bash
[root@192 base_use]# ./ObserverTest
ConcreteObserverB observer....old
ConcreteObserverA observer....old
ConcreteObserverB observer....new
ConcreteObserverA observer....new
```

## 代码说明

在 Observer 模式的实现中:

1. Subject 维护一个 list 作为存储其所有观察者的容器。每当调用 Notify 操作就遍历 list 中的 Observer 对象， 并广播通知改变状态（调用 Observer 的 Update操作）。 

2. 目标的状态 state 可以由 Subject 自己改变（ 示例），也可以由 Observer 的某个操作引起 state 的改变（可调用 Subject 的 SetState 操作。 

3. Notify 操作可以由 Subject 目标主动广播（示例），也可以由 Observer 观察者来调用（因为 Observer 维护一个指向 Subject 的指针）。

4. 运行示例程序，可以看到当 Subject 处于状态“ old” 时候， 依赖于它的两个观察者都显示“ old”，当目标状态改变为“ new”的时候，依赖于它的两个观察者也都改变为“ new”。

## 讨论

Observer 是影响极为深远的模式之一，也是在大型系统开发过程中要用到的模式之一。除了 MFC、 Struts 提供了 MVC 的实现框架， 在 Java 语言中还提供了专门的接口实现 Observer模式：通过专门的类 Observable 及 Observer 接口来实现 MVC 编程模式， 其 UML 图可以表示为

![](_images/programming/designpattern/behave/MVC的UML图.png)

这里的 Observer 就是观察者， **Observable 则充当目标 Subject 的角色。Observer 模式也称为发布－订阅（ publish-subscribe），目标就是通知的发布者，观察者则是通知的订阅者（接受通知）**。
​