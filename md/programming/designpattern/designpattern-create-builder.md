# 创建型 - 生成器(Builder)

> 生成器模式(Builder pattern) : 封装一个对象的构造过程，并允许按步骤构造。

​[[toc]]

# 抛砖引玉

生活中有着很多的 Builder 的例子， 大学生活就是一个 Builder 模式的最好体验：要完成大学教育， 一般将大学教育过程分成 4 个学期进行， 因此没有学习可以看作是构建完整大学教育的一个部分构建过程， 每个人经过这 4 年的（ 4 个阶段） 构建过程得到的最后的结果不一样， 因为可能在**四个阶段的构建中引入了很多的参数（每个人的机会和际遇不完全相同）**。

Builder 模式要解决的也正是这样的问题：当我们要创建的对象很复杂的时候（通常是由很多其他的对象组合而成），我们要将复杂对象的创建过程和这个对象的表示（ 展示）分离开来， 这样做的好处就是通过一步步的进行复杂对象的构建， 由于在每一步的构造过程中可以引入参数，使得经过相同的步骤创建最后得到的对象的展示不一样。

Builder 模式典型的结构图为：

![](/_images/programming/designpattern/create/Builder.png)

Builder 模式的关键是其中的 Director 对象并不直接返回对象，而是通过一步步（ BuildPartA， BuildPartB， BuildPartC）来一步步进行对象的创建。当然这里 Director 可以提供一个默认的返回对象的接口（即返回通用的复杂对象的创建， 即不指定或者特定唯一指定 BuildPart 中的参数）。

# 代码实现

<<< @/md/programming/designpattern/create/Builder/Builder.h

<<< @/md/programming/designpattern/create/Builder/Builder.cpp

<<< @/md/programming/designpattern/create/Builder/Director.h

<<< @/md/programming/designpattern/create/Builder/Director.cpp

<<< @/md/programming/designpattern/create/Builder/Product.h

<<< @/md/programming/designpattern/create/Builder/Product.cpp

<<< @/md/programming/designpattern/create/Builder/main.cpp

```bash
[root@VM-16-6-centos Builder]# ./BuilderTest
Step1:Build PartA... user-defined
Step1:Build PartB... user-defined
Step1:Build PartC... user-defined
```

## 代码说明

Builder 模式的示例代码中， BuildPart 的参数是通过客户程序员传入的，这里为了简单说明问题，使用“ user-defined”代替，实际的可能是在 Construct 方法中传入这 3 个参数，这样就可以得到不同的细微差别的复杂对象了。

## 讨论

Builder 模式和 AbstractFactory 模式在功能上很相似，因为都是用来创建大的复杂的对象，它们的区别是： Builder 模式强调的是一步步创建对象，并通过相同的创建过程可以获得不同的结果对象，一般来说 Builder 模式中对象不是直接返回的。而在 AbstractFactory 模式中对象是直接返回的， AbstractFactory 模式强调的是为创建多个相互依赖的对象提供一个同一的接口。