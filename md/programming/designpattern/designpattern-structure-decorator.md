# 结构型 - 装饰(Decorator)

> 装饰者模式(Decorator pattern): 动态地将责任附加到对象上, 若要扩展功能, 装饰者提供了比继承更有弹性的替代方案。

​[[toc]]

# 抛砖引玉

在 OO 设计和开发过程，可能会经常遇到以下的情况：需要为一个已经定义好的类添加新的职责（操作），通常的情况，我们会给定义一个新类继承自定义好的类，这样会带来一个问题（将在本模式的讨论中给出）。通过继承的方式解决这样的情况还带来了系统的复杂性，因为继承的深度会变得很深。

而 Decorator 提供了一种给类增加职责的方法，不是通过继承实现的，而是通过组合。有关这些内容在讨论中进一步阐述。

Decorator 模式典型的结构图为：

![](/_images/programming/designpattern/structure/Decorator.png)

在结构图中 ， ConcreteComponent 和 Decorator 需要有同样的接口 ，因此ConcreteComponent 和 Decorator 有着一个共同的父类。

这里有人会问，让 Decorator 直接维护一个指向 ConcreteComponent 引用（指针）不就可以达到同样的效果，答案是肯定并且是否定的。 肯定的是你可以通过这种方式实现，否定的是你不要用这种方式实现， 因为通过这种方式你就只能为这个特定的 ConcreteComponent 提供修饰操作了，当有了一个新的
ConcreteComponent 你又要去新建一个 Decorator 来实现 。

但是，通过结构图中的ConcreteComponent 和 Decorator 有一个公共基类，就可以利用 OO 中多态的思想来实现只要是 Component 型别的对象都可以提供修饰操作的类，这种情况下你就算新建了 100 个Component 型别的类 ConcreteComponent，也都可以由 Decorator 一个类搞定。这也正是Decorator 模式的关键和威力所在了。

当然如果你只用给 Component 型别类添加一种修饰， 则 Decorator 这个基类就不是很必要了。

# 代码实现

<<< @/md/programming/designpattern/structure/Decorator/Decorator.h

<<< @/md/programming/designpattern/structure/Decorator/Decorator.cpp

<<< @/md/programming/designpattern/structure/Decorator/main.cpp

```bash
[root@VM-16-6-centos Decorator]# ./DecoratorTest
ConcreteComponent operation...
ConcreteDecorator::AddedBehacior....
```

## 代码说明

Decorator 模式很简单， 代码本身没有什么好说明的。运行示例代码可以看到，ConcreteDecorator 给 ConcreteComponent 类添加了动作 AddedBehavior。

## 讨论

Decorator 模式和 Composite 模式有相似的结构图。

Decorator 模式和 Proxy 模式的相似的地方在于它们都拥有一个指向其他对象的引用（指针），即**通过组合的方式来为对象提供更多操作（或者 Decorator 模式） 间接性（ Proxy 模式）**。但是他们的区别是， Proxy 模式会提供使用其作为代理的对象一样接口， 使用代理类将其操作都委托给 Proxy 直接进行。这里可以简单理解为组合和委托之间的微妙的区别了。

Decorator 模式除了采用组合的方式取得了比采用继承方式更好的效果， Decorator 模式还给设计带来一种“即用即付” 的方式来添加职责。 在 OO 设计和分析经常有这样一种情况：为了多态， 通过父类指针指向其具体子类，但是这就带来另外一个问题， 当具体子类要添加新的职责， 就必须向其父类添加一个这个职责的抽象接口，否则是通过父类指针是调用不到这个方法了。这样处于高层的父类就承载了太多的特征（ 方法），并且继承自这个父类的所
有子类都不可避免继承了父类的这些接口，但是可能这并不是这个具体子类所需要的。 

而在Decorator 模式提供了一种较好的解决方法，当需要添加一个操作的时候就可以通过Decorator 模式来解决，可以一步步添加新的职责。