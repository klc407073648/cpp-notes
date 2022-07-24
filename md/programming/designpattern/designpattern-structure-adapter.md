# 结构型 - 适配器(Adapter)

​[[toc]]

> 适配器模式(Adapter pattern): 将一个类的接口, 转换成客户期望的另一个接口。 适配器让原本接口不兼容的类可以合作无间。 对象适配器使用组合, 类适配器使用多重继承。

# 抛砖引玉

Adapter 模式解决的问题在生活中经常会遇到：

比如我们有一个 Team 为外界提供 S 类服务，但是我们 Team 里面没有能够完成此项人物的 member，然后我们得知有 A 可以完成这项服务（他把这项人物重新取了个名字叫 S’，并且他不对外公布他的具体实现）。为了保证我们对外的服务类别的一致性（提供 S 服务），我们有以下两种方式解决这个问题：

1. 把 B 君直接招安到我们 Team 为我们工作，提供 S 服务的时候让 B 君去办就是了；
2. B 君可能在别的地方有工作，并且不准备接受我们的招安，于是我们 Team 可以想这样一种方式解决问题：我们安排 C 君去完成这项任务，并做好工作（Money：））让 A 君工作的时候可以向 B 君请教，因此 C 君就是一个复合体（提供 S 服务，但是是 B 君的继承弟子）。

实际上在软件系统设计和开发中，这种问题也会经常遇到：我们为了完成某项工作购买了一个第三方的库来加快开发。这就带来了一个问题：我们在应用程序中已经设计好了接口，与这个第三方提供的接口不一致，为了使得这些接口不兼容的类（不能在一起工作）可以在一起工作了，Adapter 模式提供了将一个类（第三方库）的接口转化为客户（购买使用者）希望的接口。

在上面生活中问题的解决方式也就正好对应了 Adapter 模式的两种类别：类模式和对象模式。

Adapter 类模式结构图为：

![](_images/programming/designpattern/structure/Adapter_class.png)

Adapter 对象模式结构图为：

![](_images/programming/designpattern/structure/Adapter_object.png)

在 Adapter 模式的结构图中可以看到，**类模式的 Adapter 采用继承的方式复用 Adaptee的接口，而在对象模式的 Adapter 中我们则采用组合的方式实现 Adaptee 的复用**。

# 代码实现

<<< @/md/programming/designpattern/structure/Adapter/Adapter.h

<<< @/md/programming/designpattern/structure/Adapter/Adapter.cpp

<<< @/md/programming/designpattern/structure/Adapter/AdapterObject.h

<<< @/md/programming/designpattern/structure/Adapter/AdapterObject.cpp

<<< @/md/programming/designpattern/structure/Adapter/main.cpp

```bash
[root@VM-16-6-centos Adapter]# ./AdapterTest
Adaptee::SpecificRequest
Adaptee::SpecificRequest
```

## 代码说明

Adapter 模式实现上比较简单，要说明的是在类模式 Adapter 中，我们通过 private 继承Adaptee 获得实现继承的效果， 而通过 public 继承 Target 获得接口继承的效果。

## 讨论

在 Adapter 模式的两种模式中，重点是接口继承和实现继承的区别和联系。

**接口继承和实现继承**是面向对象领域的两个重要的概念：

接口继承指的是通过继承，子类获得了父类的接口，而实现继承指的是通过继承子类获得了父类的实现（并不统共接口）。

在 C++中的 public 继承既是接口继承又是实现继承，因为子类在继承了父类后既可以对外提供父类中的接口操作，又可以获得父类的接口实现。当然我们可以通过一定的方式和技术模拟单独的接口继承和实现继承，例如我们可以通过 `private 继承`获得实现继承的效果（private 继承后，父类中的接口都变为 private，当然只能是实现继承了。），通过纯抽象基类模拟接口继承的效果， 但是在 C++中 pure virtual function 也可以提供默认实现， 因此这是不纯正的接口继承，但是在 Java 中我们可以 interface 来获得真正的接口继承了。
