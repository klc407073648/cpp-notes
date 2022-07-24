# 行为型 - 模板(Template Method)

​[[toc]]

> 模板模式(Template pattern) : 将逻辑（算法）框架放在抽象基类中，并定义好细节的接口，子类中实现细节。

# 抛砖引玉

在面向对象系统的分析与设计过程中经常会遇到这样一种情况：对于某一个业务逻辑（算法实现）在不同的对象中有不同的细节实现， 但是逻辑（算法） 的框架（或通用的应用算法）是相同的。 

Template 提供了这种情况的一个实现框架。Template 模式是采用继承的方式实现这一点：将逻辑（算法）框架放在抽象基类中，并定义好细节的接口，子类中实现细节。

Strategy 模式解决的是和 Template 模式类似的问题， 但是 Strategy 模式是将逻辑（算法）封装到一个类中，并采取组合（委托）的方式解决这个问题。

Template 模式典型的结构图为：

![](_images/programming/designpattern/behave/Template.png)

Template 模式实际上就是利用面向对象中`多态`的概念实现算法实现细节和高层接口的`松耦合`。可以看到 Template 模式采取的是继承方式实现这一点的，由于继承是一种强约束性的条件，因此也给 Template 模式带来一些许多不方便的地方。

# 代码实现

<<< @/md/programming/designpattern/behave/Template/Template.h

<<< @/md/programming/designpattern/behave/Template/Template.cpp

<<< @/md/programming/designpattern/behave/Template/main.cpp

```bash
[root@VM-16-6-centos Template]# ./TemplateTest
ConcreteClass1...PrimitiveOperation1
ConcreteClass1...PrimitiveOperation2
ConcreteClass2...PrimitiveOperation1
ConcreteClass2...PrimitiveOperation2
```

## 代码说明

由于 Template 模式的实现代码很简单，其关键是将通用算法（逻辑）封装起来，而将算法细节让子类实现（多态）。

唯一注意的是我们将原语操作（细节算法）定义未保护（ Protected） 成员，只供模板方法调用（子类可以）。

## 讨论

Template 模式获得一种反向控制结构效果，即（依赖倒置： Dependency Inversion Principles）。其含义就是父类调用子类的操作（高层模块调用低层模块的操作），低层模块实现高层模块声明的接口。这样控制权在父类（高层模块），低层模块反而要依赖高层模块。

继承的强制性约束关系也让Template模式有不足的地方，可以看到对于ConcreteClass 类中的实现的原语方法 Primitive1()，是不能被别的类复用。假设我们要创建一个 AbstractClass 的变体 AnotherAbstractClass，并且两者只是通用算法不一样，其原语操作想复用 AbstractClass 的子类的实现。但是这是不可能实现的，因为 ConcreteClass 继承自AbstractClass，也就继承了 AbstractClass 的通用算法， AnotherAbstractClass 是复用不了ConcreteClass 的实现，因为后者不是继承自前者。

Template 模式暴露的问题**也正是继承所固有的问题**，Strategy 模式则通过组合（委托）来达到和 Template 模式类似的效果， 其代价就是空间和时间上的代价， 关于 Strategy 模式的详细讨论请参考 Strategy 模式解析。