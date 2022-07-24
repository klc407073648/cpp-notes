# 行为型 - 状态(State)

> 状态模式(State pattern): 允许对象在内部状态改变时改变它的行为, 对象看起来好象改了它的类。

​[[toc]]

# 抛砖引玉

每个人、事物在不同的状态下会有不同表现（ 动作），而一个状态又会在不同的表现下转移到下一个不同的状态（ State）。最简单的一个生活中的例子就是： 地铁入口处，如果你放入正确的地铁票，门就会打开让你通过。在出口处也是验票，如果正确你就可以出站，否则就不让你通过。

有限状态自动机（FSM）也是一个典型的状态不同，对输入有不同的响应（状态转移）。通常我们在实现这类系统会使用到很多的 Switch/Case 语句， Case 某种状态， 发生什么动作，Case 另外一种状态，则发生另外一种状态。但是这种实现方式至少有以下两个问题：

1. 当状态数目不是很多的时候， Switch/Case 可能可以搞定。 但是当状态数目很多的时候（实际系统中也正是如此）， 维护一大组的 Switch/Case 语句将是一件异常困难并且容易出错的事情。

2. 状态逻辑和动作实现没有分离。 在很多的系统实现中，动作的实现代码直接写在状态的逻辑当中。这带来的后果就是系统的扩展性和维护得不到保证。

## 模式选择

State 模式就是被用来解决上面列出的两个问题的， 在 State 模式中将状态逻辑和动作实现进行分离。当一个操作中要维护大量的 case 分支语句，并且这些分支依赖于对象的状态。 State 模式将每一个分支都封装到独立的类中。 

State 模式典型的结构图为：

![](/_images/programming/designpattern/behave/State.png)


# 代码实现

<<< @/md/programming/designpattern/behave/State/Context.h

<<< @/md/programming/designpattern/behave/State/Context.cpp

<<< @/md/programming/designpattern/behave/State/State.h

<<< @/md/programming/designpattern/behave/State/State.cpp

<<< @/md/programming/designpattern/behave/State/main.cpp

```bash
[root@VM-16-6-centos State]# ./StateTest
ConcreteStateA::OperationInterface......
ConcreteStateB::OperationInterface......
ConcreteStateA::OperationInterface......
```

## 代码说明

State 模式在实现中，有两个关键点：

1. 将 State 声明为 Context 的友元类（ friend class）， 其作用是让 State 模式访问 Context的 private 接口 ChangeSate（）。
2. State 及其子类中的操作都将 Context*传入作为参数，其主要目的是 State 类可以通过这个指针调用 Context 中的方法（在本示例代码中没有体现）。 这也是 State 模式和 Strategy模式的最大区别所在。

运行了示例代码后可以获得以下的结果：连续 3 次调用了 Context 的 OperationChangState(),因为每次调用后状态都会改变（ A－ B－ A），因此该动作随着 Context 的状态的转变而获得了不同的结果。

## 讨论

State 模式的应用也非常广泛，从最高层逻辑用户接口 GUI 到最底层的通讯协议（例如利用 State 模式模拟实现一个 TCP 连接的类。 ） 都有其用武之地。

State 模式和 Strategy 模式又很大程度上的相似：它们都有一个 Context 类， 都是通过委托（组合） 给一个具有多个派生类的多态基类实现 Context 的算法逻辑。 两者最大的差别就是 State 模式中派生类持有指向 Context 对象的引用， 并通过这个引用调用 Context 中的方法，但在 Strategy 模式中就没有这种情况。因此可以说一个 State 实例同样是 Strategy 模式的一个实例，反之却不成立。

实际上 State 模式和 Strategy 模式的区别还在于它们所关注的点不尽相同： 

* State 模式主要是要适应对象对于状态改变时的不同处理策略的实现
* Strategy 则主要是具体算法和实现接口的解耦（ coupling），Strategy 模式中并没有状态的概念，并且更加不关心状态的改变了。

State 模式很好地实现了**对象的状态逻辑和动作实现的分离， 状态逻辑分布在 State 的派生类中实现，而动作实现则可以放在 Context 类中实现**（这也是为什么 State 派生类需要拥有一个指向 Context 的指针）。 这使得两者的变化相互独立， 改变 State 的状态逻辑可以很容易复用 Context 的动作， 也可以在不影响 State 派生类的前提下创建 Context 的子类来更改或替换动作实现。

State 模式问题主要是逻辑分散化，状态逻辑分布到了很多的 State 的子类中，很难看到整个的状态逻辑图，这也带来了代码的维护问题。