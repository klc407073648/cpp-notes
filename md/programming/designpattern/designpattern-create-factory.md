# 创建型 - 工厂模式(Factory)

​[[toc]]

> 工厂模式(Factory): 定义一个用以创建对象的接口, 让子类决定实例化哪个类. 当遇到需要根据某个前提条件创建不同的类实现时, 会实用工厂模式。

# 抛砖引玉

在面向对象系统设计中经常可以遇到以下的两类问题：

1. 为了提高内聚（ Cohesion）和松耦合（ Coupling），我们经常会抽象出一些类的公共接口以形成抽象基类或者接口。 这样我们可以通过声明一个指向基类的指针来指向实际的子类实现，达到了多态的目的。这里很容易出现的一个问题 n 多的子类继承自抽象基类， 我们不得不在每次要用到子类的地方就编写诸如 new ××× ;的代码。这里带来两个问题：

	1. 客户程序员必须知道实际子类的名称（当系统复杂后，命名将是一个很不好处理的问题，为了处理可能的名字冲突，有的命名可能并不是具有很好的可读性和可记忆性， 就姑且不论不同程序员千奇百怪的个人偏好了。 

	2. 程序的扩展性和维护变得越来越困难。

2. 还有一种情况就是在父类中并不知道具体要实例化哪一个具体的子类。这里的意思为：假设我们在类 A 中要使用到类 B， B 是一个抽象父类，在 A 中并不知道具体要实例化哪一个 B 的子类， 但是在类 A 的子类 D 中是可以知道的。 在 A 中我们没有办法直接使用类似于 new × ××的语句，因为根本就不知道×××是什么。

以上两个问题也就引出了 Factory 模式的两个最重要的功能：

1. 定义创建对象的接口，封装了对象的创建；
2. 使得具体化类的工作延迟到了子类中。

## 模式选择

通常使用 Factory 模式来解决上面给出的两个问题。
* 在第一个问题中，我们经常就是声明一个创建对象的接口，并封装了对象的创建过程。Factory 这里类似于一个真正意义上的工厂（ 生产对象）。 
* 在第二个问题中，我们需要提供一个对象创建对象的接口，并在子类中提供其具体实现（因为只有在子类中可以决定到底实例化哪一个类）。

第一中情况的 Factory 的结构示意图为：

Factory 模式典型的结构图1为：

![](_images/programming/designpattern/create/Factory_1.png)

图1的Factory 模式经常在系统开发中用到，但是这并不是 Factory 模式的最大威力所在（因为这可以通过其他方式解决这个问题）。 

Factory 模式不单是提供了创建对象的接口，其最重要的是延迟了子类的实例化（第二个问题）。

以下是这种情况的一个 Factory 的结构示意图2

![](_images/programming/designpattern/create/Factory_2.png)

图 2 中关键中 Factory 模式的应用并不是只是为了封装对象的创建，而是要把对象的创建放到子类中实现： Factory 中只是提供了对象创建的接口，其实现将放在 Factory 的子类ConcreteFactory 中进行。这是图 2 和图 1 的区别所在。


## 代码实现

<<< @/md/programming/designpattern/create/Factory/Product.h

<<< @/md/programming/designpattern/create/Factory/Product.cpp

<<< @/md/programming/designpattern/create/Factory/Factory.h

<<< @/md/programming/designpattern/create/Factory/Factory.cpp

<<< @/md/programming/designpattern/create/Factory/main.cpp


```bash
[root@VM-16-6-centos Factory]# ./Factory
ConcreteFactory.....
ConcreteProduct....
```

## 代码说明

示例代码中给出的是 Factory 模式解决父类中并不知道具体要实例化哪一个具体的子类的问题，至于为创建对象提供接口问题，可以由 Factory 中附加相应的创建操作例如CreateProduct（）即可。具体请参加讨论内容。

## 讨论

Factory 模式在实际开发中应用非常广泛，面向对象的系统经常面临着对象创建问题：要创建的类实在是太多了。而 Factory 提供的创建对象的接口封装（第一个功能），以及其将类的实例化推迟到子类（第二个功能） 都部分地解决了实际问题。 

Factory 模式也带来至少以下两个问题：

1. 如果为每一个具体的 ConcreteProduct 类的实例化提供一个函数体，那么我们可能不得不在系统中添加了一个方法来处理这个新建的ConcreteProduct，这样 Factory 的接口永远就不肯能封闭（ Close）。 当然我们可以通过创建一个 Factory 的子类来通过多态实现这一点，
但是这也是以新建一个类作为代价的。

2. 在实现中我们可以通过参数化工厂方法，即给 FactoryMethod（）传递一个参数用以决定是创建具体哪一个具体的 Product。当然也可以通过模板化避免 1）中的子类创建子类，其方法就是将具体 Product 类作为模板参数，实现起来也很简单。

可以看出， Factory 模式对于对象的创建给予开发人员提供了很好的实现策略，但是Factory 模式仅仅局限于一类类（就是说 Product 是一类，有一个共同的基类），如果我们要为不同类的类提供一个对象创建的接口，那就要用 AbstractFactory 了。