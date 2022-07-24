# 创建型 - 抽象工厂(Abstract Factory)

> 抽象工厂(Abstract Factory) : 抽象工厂模式创建的是对象家族，也就是很多对象而不是一个对象，并且这些对象是相关的，也就是说必须一起创建出来。而工厂方法模式只是用于创建一个对象，这和抽象工厂模式有很大不同。

​[[toc]]

# 抛砖引玉

假设需要开发一款游戏， 为了吸引更多人玩，游戏难度不能太大（让大家都没有信心了，估计游戏也就没有前途了），但是也不能太简单（没有挑战性也不符合玩家的心理）。

于是我们就可以采用这样一种处理策略： 为游戏设立等级，初级、中级、高级甚至有BT级。 

假设也是过关的游戏，每个关卡都有一些怪物（monster）守着， 玩家要把这些怪物干掉才可以过关。 作为开发者， 我们就不得不创建怪物的类，然后初级怪物、中级怪物等都继承自怪物类（当然不同种类的则需要另创建类，但是模式相同）。在每个关卡， 都要创建怪物的实例，例如初级就创建初级怪物（有很多种类）、中级创建中级怪物等。可以想象在这个系统中， 将会有成千上万的怪物实例要创建，问题是还要保证创建的时候不会出错：初级不能创建 BT 级的怪物（玩家就郁闷了，玩家一郁闷，游戏也就挂挂了），反之也不可以。

AbstractFactory 模式就是用来解决这类问题的：要创建一组相关或者相互依赖的对象。

AbstractFactory 模式典型的结构图为：

![](/_images/programming/designpattern/create/AbstractFactory.png)

## 代码实现

<<< @/md/programming/designpattern/create/AbstractFactory/Product.h

<<< @/md/programming/designpattern/create/AbstractFactory/Product.cpp

<<< @/md/programming/designpattern/create/AbstractFactory/AbstractFactory.h

<<< @/md/programming/designpattern/create/AbstractFactory/AbstractFactory.cpp

<<< @/md/programming/designpattern/create/AbstractFactory/main.cpp


```bash
[root@VM-16-6-centos AbstractFactory]# ./AbstractFactory
ProductA1...
ProductB1...
ProductA2...
ProductB2...
```

## 代码说明

AbstractFactory 模式的实现代码很简单，在测试程序中可以看到，当我们要创建一组对象（ ProductA1， ProductA2）的时候我们只用维护一个创建对象（ConcreteFactory1），大大简化了维护的成本和工作。

## 讨论

AbstractFactory 模式和 Factory 模式的区别是初学（使用）设计模式时候的一个容易引起困惑的地方。 实际上， AbstractFactory 模式是为创建一组（ 有多类） 相关或依赖的对象提供创建接口， 而 Factory 模式正如我在相应的文档中分析的是为一类对象提供创建接口或延迟对象的创建到子类中实现。并且可以看到， AbstractFactory 模式通常都是使用 Factory 模式实现（ ConcreteFactory1）。