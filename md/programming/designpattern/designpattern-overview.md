# 设计模式 - Overview

> 在软件开发中，前人对软件系统的设计和开发总结了一些原则和模式，不管用什么语言做开发，都将对我们系统设计和开发提供指导意义。设计模式之于面向对象系统的设计和开发的作用就有如数据结构之于面向过程开发的作用一般，其重要性和必要性不言而喻。本文主要将对设计模式和设计原则进行总结，和具体阐述意义。

[[toc]]

::: danger
可以补充一下各个设计模式的具体应用实例。
:::

# 参考资料

* 设计模式精解－ GoF 23 种设计模式解析附 C++实现源码  作者:k_eckel
    * 总结的设计模式内容和源码均来源于上述文章

# 7大原则

1. 单一职责原则 [SINGLE RESPONSIBILITY PRINCIPLE] : 一个类负责一项职责。 
2. 里氏替换原则 [LISKOV SUBSTITUTION PRINCIPLE] : 继承与派生的规则。 
3. 依赖倒置原则 [DEPENDENCE INVERSION PRINCIPLE] : 高层模块不应该依赖低层模块，二者都应该依赖其抽象；抽象不应该依赖细节；细节应该依赖抽象。即针对接口编程，不要针对实现编程。 
4. 接口隔离原则 [INTERFACE SEGREGATION PRINCIPLE] : 建立单一接口，不要建立庞大臃肿的接口，尽量细化接口，接口中的方法尽量少。 
5. 迪米特法则 [LOW OF DEMETER] : 一个实体应当尽量少地与其他实体之间发生相互作用，使得系统功能模块相对独立。即低耦合，高内聚。 
6. 开闭原则 [OPEN CLOSE PRINCIPLE] : 一个软件实体如类、模块和函数应该对扩展开放，对修改关闭。 
7. 组合/聚合复用原则 [Composition/Aggregation Reuse Principle(CARP) ] : 尽量使用组合和聚合少使用继承的关系来达到复用的原则。

详细内容参见 `方法论` 章节

* [7大原则](/md/method/arch-principle/arch-principle-solid-detail.md)

# 设计模式

![](/_images/programming/designpattern/设计模式.png)

## 创建型模式 - Create model

* [创建型 - 单例模式(Singleton)](/md/programming/designpattern/designpattern-create-singleton.md)
    * 单例模式(Singleton): 保证一个类仅有一个实例,并提供一个访问它的全局控制点. 比如在加载配置文件时, 可使用该模式。
    
* [创建型 - 工厂模式(Factory)](/md/programming/designpattern/designpattern-create-factory.md)
    * 工厂模式(Factory): 定义一个用以创建对象的接口, 让子类决定实例化哪个类. 当遇到需要根据某个前提条件创建不同的类实现时, 会实用工厂模式。
    
* [创建型 - 抽象工厂(Abstract Factory)](/md/programming/designpattern/designpattern-create-abstract-factory.md)
    * 抽象工厂(Abstract Factory) : 抽象工厂模式创建的是对象家族，也就是很多对象而不是一个对象，并且这些对象是相关的，也就是说必须一起创建出来。而工厂方法模式只是用于创建一个对象，这和抽象工厂模式有很大不同。

* [创建型 - 生成器(Builder)](/md/programming/designpattern/designpattern-create-builder.md)
    * 生成器(Builder)，封装一个对象的构造过程，并允许按步骤构造。 

* [创建型 - 原型模式(Prototype)](/md/programming/designpattern/designpattern-create-prototype.md)
    * 原型模式(Prototype)，使用原型实例指定要创建对象的类型，通过复制这个原型来创建新对象。 
    
## 结构型模式 - Structural model

* [结构型 - 外观(Facade)](/md/programming/designpattern/designpattern-structure-facade.md)
    * 外观模式(Facade): 它提供了一个统一的接口，用来访问子系统中的一群接口，从而让子系统更容易使用。

* [结构型 - 适配器(Adapter)](/md/programming/designpattern/designpattern-structure-adapter.md)
    * 适配器模式(Adapter): 将一个类的接口, 转换成客户期望的另一个接口。 适配器让原本接口不兼容的类可以合作无间。对象适配器使用组合, 类适配器使用多重继承。
    * 应用：STL中，stack以双端队列deque修改接口而实现;queue也是由deque修改接口而实现。
    
* [结构型 - 桥接(Bridge)](/md/programming/designpattern/designpattern-structure-bridge.md)
    * 桥接模式(Bridge): 通过将实现和抽象放在两个不同的类层次中而使它们可以独立改变。
    
* [结构型 - 组合(Composite)](/md/programming/designpattern/designpattern-structure-composite.md)
    * 组合模式(Composite): 允许你将对象组合成树形结构来表现"整体/部分"层次结构. 组合能让客户以一致的方式处理个别对象以及对象组合。 

* [结构型 - 装饰(Decorator)](/md/programming/designpattern/designpattern-structure-decorator.md)
    * 装饰者模式(Decorator): 动态地将责任附加到对象上, 若要扩展功能, 装饰者提供了比继承更有弹性的替代方案。
    
* [结构型 - 享元(Flyweight)](/md/programming/designpattern/designpattern-structure-flyweight.md)
    * 享元模式(Flyweight): 利用共享的方式来支持大量细粒度的对象，这些对象一部分内部状态是相同的。它让某个类的一个实例能用来提供许多"虚拟实例"。 
    
* [结构型 - 代理(Proxy)](/md/programming/designpattern/designpattern-structure-proxy.md)
    * 代理模式(Proxy): 为另一个对象提供一个替身或占位符以控制对这个对象的访问。 
    
## 行为型模式 - Behavioral model

* [行为型 - 责任链(Chain Of Responsibility)](/md/programming/designpattern/designpattern-behave-chain-of-responsibility.md)
    * 责任链模式(Chain of Responsibility): 通过责任链模式, 你可以为某个请求创建一个对象链. 每个对象依序检查此请求并对其进行处理或者将它传给链中的下一个对象。 

* [行为型 - 策略(Strategy)](/md/programming/designpattern/designpattern-behave-strategy.md)
    * 策略模式(Strategy): 定义了算法族, 分别封闭起来, 让它们之间可以互相替换, 此模式让算法的变化独立于使用算法的客户。
    
* [行为型 - 模板模式(Template)](/md/programming/designpattern/designpattern-behave-template.md)
    * 模板模式(Template): 在一个方法中定义一个算法的骨架, 而将一些步骤延迟到子类中. 模板方法使得子类可以在不改变算法结构的情况下, 重新定义算法中的某些步骤。 
    
* [行为型 - 命令模式(Command)](/md/programming/designpattern/designpattern-behave-command.md)
    * 命令模式(Command): 将请求封装到一个对象（ Command） 中，并将请求的接受者存放到具体的 ConcreteCommand 类中（ Receiver） 中， 从而实现调用操作的对象和操作的具体实现者之间的解耦。
    
* [行为型 - 观察者(Observer)](/md/programming/designpattern/designpattern-behave-observer.md)
    * 观察者模式(Observer): 定义了一种一对多的依赖关系,让多个观察者对象同时监听某一主题对象,在它的状态发生变化时,会通知所有的观察者。
    
* [行为型 - 访问者(Visitor)](/md/programming/designpattern/designpattern-behave-visitor.md)
    * 访问者模式(Visitor): 当你想要为一个对象的组合增加新的能力, 且封装并不重要时, 就使用访问者模式。 
    
* [行为型 - 状态(State)](/md/programming/designpattern/designpattern-behave-state.md)
    * 状态模式(State): 允许对象在内部状态改变时改变它的行为, 对象看起来好象改了它的类。 
    
* [行为型 - 解释器(Interpreter)](/md/programming/designpattern/designpattern-behave-interpreter.md)
    * 解释器模式(Interpreter): 使用一个解释器为用户提供一个一门定义语言的语法表示的解释器，然后通过这个解释器来解释语言中的句子。 
    
* [行为型 - 迭代器(Iterator)](/md/programming/designpattern/designpattern-behave-iterator.md)
    * 迭代器模式(Iterator): 解决对一个聚合对象的遍历问题，将对聚合的遍历封装到一个类中进行，这样就避免了暴露这个聚合对象的内部表示的可能。 
    
* [行为型 - 中介者(Mediator)](/md/programming/designpattern/designpattern-behave-mediator.md)
    * 中介者模式(Mediator) : 使用中介者模式来集中相关对象之间复杂的沟通和控制方式。 
    
* [行为型 - 备忘录(Memento)](/md/programming/designpattern/designpattern-behave-memento.md)
    * 备忘录模式(Memento): 要在不破坏封装行的前提下，捕获并保存一个类的内部状态，这样就可以利用该保存的状态实施恢复操作。