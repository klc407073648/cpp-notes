# 行为型 - 访问者(Visitor)

> 访问者模式(visitor pattern): 当你想要为一个对象的组合增加新的能力, 且封装并不重要时, 就使用访问者模式。

​[[toc]]

# 抛砖引玉

在面向对象系统的开发和设计过程，经常会遇到一种情况就是需求变更（Requirement Changing），经常我们做好的一个设计、实现了一个系统原型，咱们的客户又会有了新的需求。我们又因此不得不去修改已有的设计，最常见就是解决方案就是给**已经设计、实现好的类添加新的方法去实现客户新的需求**，这样就陷入了设计变更的梦魇：不停地打补丁，其带来的**后果就是设计根本就不可能封闭、编译永远都是整个系统代码**。

Visitor 模式则提供了一种解决方案：将更新（变更）封装到一个类中（访问操作），并由待更改类提供一个接收接口，则可达到效果

Visitor 模式的结构图为：

![](/_images/programming/designpattern/behave/Visitor.png)

Visitor 模式在不破坏类的前提下， 为类提供增加新的新操作。 Visitor 模式的关键是双分派（ Double-Dispatch） 的技术【注释 1】。 C++语言支持的是单分派。

在 Visitor 模式中 Accept（）操作是一个双分派的操作。具体调用哪一个具体的 Accept（）操作，有两个决定因素：

1. Element 的类型。因为 Accept（）是多态的操作，需要具体的 Element 类型的子类才可以决定到底调用哪一个 Accept（）实现； 
2. Visitor 的类型。Accept（）操作有一个参数（ Visitor* vis），要决定了实际传进来的 Visitor 的实际类别才可以决定具体是调用哪个 VisitConcrete（）实现

# 代码实现

<<< @/md/programming/designpattern/behave/Visitor/Element.h

<<< @/md/programming/designpattern/behave/Visitor/Element.cpp

<<< @/md/programming/designpattern/behave/Visitor/Visitor.h

<<< @/md/programming/designpattern/behave/Visitor/Visitor.cpp

<<< @/md/programming/designpattern/behave/Visitor/main.cpp

代码说明：

* Visitor 类中的 Visit（）操作的实现。

	* 这里我们可以向 Element 类仅仅提供一个接口 Visit（），而在 Accept（）实现中具体调用哪一个 Visit（） 操作则通过函数重载（ overload） 的方式实现： 我们提供 Visit（） 的两个重载版本 a） Visi（t ConcreteElementA* elmA）， b） Visi（t ConcreteElementB*elmB）。
	* 在 C++中我们还可以通过 RTTI（运行时类型识别： Runtime type identification）来实现， 即我们只提供一个 Visit（） 函数体， 传入的参数为 Element*型别参数 ，然后用 RTTI 决定具体是哪一类的 ConcreteElement 参数，再决定具体要对哪个具体类施加什么样的具体操作。【注释 2】 RTTI 给接口带来了简单一致性， 但是付出的代价是时间（ RTTI 的实现）和代码的 Hard 编码（要进行强制转换）。

* 讨论

有时候我们需要为 Element 提供更多的修改，这样我们就可以通过为 Element 提供一系列的Visitor 模式可以使得 Element 在不修改自己的同时增加新的操作， 但是这也带来了至少以下的两个显著问题：

1. 破坏了封装性。 
	* Visitor 模式要求 Visitor 可以从外部修改 Element 对象的状态， 这一般通过两个方式来实现： a） Element 提供足够的 public 接口， 使得 Visitor 可以通过调用这些接口达到修改 Element 状态的目的； b） Element 暴露更多的细节给 Visitor，或者让 Element 提供 public 的实现给 Visitor（当然也给了系统中其他的对象），或者将 Visitor 声明为 Element 的 friend 类， 仅将细节暴露给 Visitor。 但是无论那种情况，特别是后者都将是破坏了封装性原则（实际上就是 C++的 friend 机制得到了很多的面向对象专家的诟病）。
2. ConcreteElement 的扩展很困难：
	* 每增加一个 Element 的子类， 就要修改 Visitor 的接口，使得可以提供给这个新增加的子类的访问机制。从上面我们可以看到，或者增加一个用于处理新增类的 Visit（） 接口， 或者重载一个处理新增类的 Visit（） 操作， 或者要修改 RTTI 方式实现的 Visit（）  实现。 无论那种方式都给扩展新的 Element子类带来了困难。