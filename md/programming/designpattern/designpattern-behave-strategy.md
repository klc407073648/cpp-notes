# 行为型 - 策略(Strategy)

> 策略模式(strategy pattern): 定义了算法族, 分别封闭起来, 让它们之间可以互相替换, 此模式让算法的变化独立于使用算法的客户。

​[[toc]]

# 抛砖引玉

Strategy 模式和 Template 模式要解决的问题是相同（类似）的，都是为了给业务逻辑（算法）具体实现和抽象接口之间的解耦。 

Strategy 模式**将逻辑（算法） 封装到一个类（ Context）里面，通过组合的方式将具体算法的实现在组合对象中实现，再通过委托的方式将抽象接口的实现委托给组合对象实现**。 State 模式也有类似的功能， 他们之间的区别将在讨论中给出。

Strategy 模式典型的结构图为：

![](/_images/programming/designpattern/behave/Strategy.png)

这里的关键就是将算法的逻辑抽象接口（ DoAction）封装到一个类中（ Context），再通过委托的方式将具体的算法实现委托给具体的 Strategy 类来实现（ ConcreteStrategeA类）。

# 代码实现

<<< @/md/programming/designpattern/behave/Strategy/Context.h

<<< @/md/programming/designpattern/behave/Strategy/Context.cpp

<<< @/md/programming/designpattern/behave/Strategy/Strategy.h

<<< @/md/programming/designpattern/behave/Strategy/Strategy.cpp

<<< @/md/programming/designpattern/behave/Strategy/main.cpp

```bash
[root@VM-16-6-centos Strategy]# ./StrategyTest
test ConcreteStrategyA.....
test ConcreteStrategyB.....
```

## 代码说明

Strategy 模式的代码很直观，关键是将算法的逻辑封装到一个类中。

## 讨论

可以看到 Strategy 模式和 Template 模式解决了类似的问题，也正如在 Template 模式中分析的， **Strategy 模式和 Template 模式实际是实现一个抽象接口的两种方式： 继承和组合之间的区别**。 

要实现一个抽象接口

* 继承：将抽象接口声明在基类中，将具体的实现放在具体子类中。 
* 组合（委托）：将接口的实现放在被组合对象中，将抽象接口放在组合类中。

这两种方式各有优缺点，先列出来：

继承：

* 优点
    1. 易于修改和扩展那些被复用的实现。
* 缺点
    1. 破坏了封装性，继承中父类的实现细节暴露给子类了；
    2. “白盒” 复用，原因在 1 中；
    3. 当父类的实现更改时，其所有子类将不得不随之改变
    4. 从父类继承而来的实现在运行期间不能改变（编译期间就已经确定了）。

组合：

* 优点
    1. “黑盒” 复用，因为被包含对象的内部细节对外是不可见的；
    2. 封装性好，原因为 1；
    3. 实现和抽象的依赖性很小（组合对象和被组合对象之间的依赖性小）；
    4. 可以在运行期间动态定义实现（ 通过一个指向相同类型的指针，典型的是抽象基类的指针）。
* 缺点
    1. 系统中对象过多。

从上面对比中我们可以看出，组合相比继承可以取得更好的效果，因此在面向对象的设计中的有一条很重要的原则就是： **优先使用（对象） 组合， 而非（ 类） 继承（ FavorComposition Over Inheritance）**。

实际上，继承是一种强制性很强的方式， 因此也使得基类和具体子类之间的耦合性很强。 例如在 Template 模式中在 ConcreteClass1 中定义的原语操作别的类是不能够直接复用（除非你继承自 AbstractClass， 具体分析请参看 Template 模式文档）。 而组合（委托）的方式则有很小的耦合性， 实现（具体实现） 和接口（抽象接口） 之间的依赖性很小， 例如在本实现中， ConcreteStrategyA 的具体实现操作很容易被别的类复用， 例如我们要定义另一个 Context 类 AnotherContext，只要组合一个指向 Strategy 的指针就可以很容易地复用 ConcreteStrategyA 的实现了。

我们在 Bridge 模式的问题和 Bridge 模式的分析中，正是说明了继承和组合之间的区别。请参看相应模式解析。

另外 Strategy 模式很 State 模式也有相似之处， 但是 State 模式注重的对象在不同的状态下不同的操作。 两者之间的区别就是 State 模式中具体实现类中有一个指向 Context的引用，而 Strategy 模式则没有。具体分析请参看相应的 State 模式分析中。