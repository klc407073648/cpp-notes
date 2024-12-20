# 架构设计原则 - SOLID 原则


[[toc]]

> SOLID 是面向对象设计5大重要原则的首字母缩写，当我们设计类和模块时，遵守 SOLID 原则可以让软件更加健壮和稳定。

::: danger
待补充 SOLID 原则 的具体样例。
:::

# 参考资料

* [SOLID 原则](https://blog.csdn.net/qq_37964379/article/details/113484915)

# SOLID 原则

SOLID 原则的对应五种设计原则，每个首字母对应一种

1. S：单一职责原则
2. O：开闭原则
3. L：里氏替换原则
4. I：接口隔离原则
5. D：依赖反转原则

## SRP 单一职责原则

> 单一职责原则(Single Responsibility Principle)：一个类或者模块只负责完成一个职责（或者功能）

> A class or module should have a single responsibility

对类和模块的理解：

* 第一种理解是：把模块看做比类更抽象的概念，类也可以看做模块
* 第二种理解是：把模块看做比类更加粗粒度的代码块，模块中包含了多个类，多个类组成一个模块。

除了类和模块，在编写方法的时候，也应该考虑单一职责原则，因为函数才是功能执行的最小单元，细微处做好单一职责。

在写代码的过程中，需要注意：

* 一个类只负责完成一个职责或者功能
* 不要设计大而全的类，要设计粒度小、功能单一的类
* 作用是为了实现代码高内聚、低耦合，提高代码的复用性、可读性、可维护。

如何判断类的职责是否足够单一？

不同的应用场景、不同阶段的需求背景、不同的业务层面，对同一个类的职责是否单一，可能会有不同的判定结果。实际上，一些侧面的判断指标更具有指导意义和可执行性，比如，出现下面这些情况就有可能说明这类的设计不满足单一职责原则：

* 类中的代码行数、函数或者属性过多。(该考虑做拆分）
* 类依赖的其他类过多。或者依赖类的其他类过多；（耦合度过高）
* 私有方法过多
* 比较难给类起一个合适的名字；（类可能大而杂）
* 类中大量方法都是集中操作类中的某几个属性；
* 类的职责也不是越单一越好

单一职责原则通过避免设计大而全的类，避免将不相关的功能耦合在一起，来提高类的内聚性。同时，类职责单一，类依赖的和被依赖的其他类也会变少，减少了代码的耦合性，以此来实现代码的高内聚、低耦合。但是，如果拆分得过细，实际上会适得其反，反倒会降低内聚性，也会影响代码的可维护性。

举例:

```
Rectangle类，该类包含两个方法，一个用于把矩形绘制在屏幕上，一个方法用于计算矩形的面积。
```

## OCP 开闭原则

> 开闭原则（Open Closed Principle）：软件实体（模块、类、方法等）应该“对扩展开放、对修改关闭”

> software entities (modules, classes, functions, etc.) should be open for extension , but closed for modification.

在后期维护代码或者实现新需求的时候，尽可能在原有的基础上添加代码，而不是去修改已有代码来实现需求。因为这样不会影响之前的程序的正确性，可在最小改动下完成需求。

**目的**：对拓展开放是为了应对变化(需求)，对修改关闭是为了保证已有代码的稳定性；最终结果是为了让系统更有弹性！最终提高代码的可维护性、可扩展性。

**注意**：修改代码并不意味着违背开闭原则

开闭原则的初衷：只要它没有破坏原有的代码的正常运行，没有破坏原有的单元测试，就是一个合格的代码改动。

软件实体（模块、类、方法等）应该“对扩展开放、对修改关闭”。从定义中，可以看出开闭原则可以应用在不同粒度的代码中，可以是模块，也可以类，还可以是方法（及其属性）。同样一个代码改动，在粗代码粒度下，被认定为“修改”，在细代码粒度下，又可以被认定为“扩展”。

如何做到对扩展开放、对修改关闭？

* 时刻具备扩展意识、抽象意识、封装意识。在写代码的时候，多花点时间思考一下，这段代码未来可能有哪些需求，如何设计代码结构，实现留好扩展点，以便在未来需求变更的时候，在不改动代码整体结构、做到最小代码改动的情况下，将新的代码灵活地插入到扩展点上。

很多设计原则、设计思想、设计模式，都是以提高代码的扩展性为最终目的的。特别是 23 种经典设计模式，大部分都是为了解决代码的扩展性问题而总结出来的，都是以开闭原则为指导原则的。最常用来提高代码扩展性的方法有：多态、依赖注入、基于接口而非实现编程，以及大部分的设计模式（比如，装饰、策略、模板、职责链、状态）。

举例：

```
//计算航运的费用
Shipping的getCost(order)
可以通过Ground和Air
各自的类都可以继承Shipping —— getCost(order)，有各自的计算方式
```

## LSP 里式替换原则

> 里式替换原则（Liskov Substitution Principle）**：子类对象（object of subtype/derived class）能够替换程序（program）中父类对象（object of base/parent class）出现的任何地方，并且保证原来程序的逻辑行为（behavior）不变（正确性不被破坏）**。

> If S is a subtype of T, then objects of type T may be replaced with objects of type S, without breaking the program。

里式替换原则是用来指导，继承关系中子类该如何设计的一个原则。

理解里式替换原则，最核心的就是理解“design by contract，按照契约来设计”这几个字。

父类定义了函数的“约定”（或者叫协议），那子类可以改变函数的内部实现逻辑，但不能改变函数原有的“约定”,因为如果违反父类的约点，在用子类替换父类的时候程序可能会出错。

拿父类的单元测试来测试子类

这里的约定包括：

* 函数声明要实现的功能；
* 对输入、输出、异常的约定；
* 甚至包括注释中所罗列的任何特殊说明。

## ISP 接口隔离原则

> 接口隔离原则(Interface Segregation Principle)：客户端不应该强迫依赖它不需要的接口。客户端可以理解为接口的调用者。

> Clients should not be forced to depend upon interfaces that they do not use。

对于“接口”，可以理解为三种东西：

* 一组 API 接口集合
* 单个 API 接口或函数
* OOP 中接口的概念

如果把接口理解为 一组 API 接口集合：ISP 代表，我们在设计微服务接口或 类库时，如果部分接口只被部分调用者使用，那就需要将这部分接口隔离出来，单独给对应的调用者使用，而不是强迫其他调用者也依赖这部分不会被使用的接口。

把接口理解为 单个 API 接口或函数：ISP 代表 函数的设计功能要单一，不要将多个不同的功能逻辑在一个一函数中实现。

把接口理解OOP 中的接口：ISP 则也可以理解为面向对象编程语言中的接口语法。那接口的设计要尽量单一，不要让接口的实现类和调用者，依赖不需要的接口函数。

## DIP 依赖反转原则

> 依赖反转原则(Dependency Inversion Principle)：高层模块（high-level modules）不要依赖低层模块（low-level）。高层模块和低层模块应该通过抽象（abstractions）来互相依赖。除此之外，抽象（abstractions）不要依赖具体实现细节（details），具体实现细节（details）依赖抽象（abstractions）。

> High-level modules shouldn’t depend on low-level modules. Both modules should depend on abstractions. In addition, abstractions shouldn’t depend on details. Details depend on abstractions.

所谓高层模块和底层模块是指**：在调用链上，调用者属于高层，被调用者属于底层。**
