# 行为型 - 迭代器(Iterator)

​[[toc]]

> Iterator 模式也正是用来**解决对一个聚合对象的遍历问题**，将对聚合的遍历封装到一个类中进行，这样就避免了暴露这个聚合对象的内部表示的可能。

Iterator 模式典型的结构图为：

![](_images/programming/designpattern/behave/Iterator.png)

Iterator 模式中定义的对外接口可以视客户成员的便捷定义，但是基本的接口在图中的Iterator 中已经给出了（参考 STL 的 Iterator 就知道了）。———— 迭代器可以用于对统一类型的处理，Java 使用Iterable<T>来作入参类型，可以忽略到底是数组还是链表。

# 代码实现

<<< @/md/programming/designpattern/behave/Iterator/Aggregate.h

<<< @/md/programming/designpattern/behave/Iterator/Aggregate.cpp

<<< @/md/programming/designpattern/behave/Iterator/Iterator.h

<<< @/md/programming/designpattern/behave/Iterator/Iterator.cpp

<<< @/md/programming/designpattern/behave/Iterator/main.cpp

Iterator 模式的实现代码很简单，实际上为了更好地保护 Aggregate 的状态，我们可以尽量减小 Aggregate 的 public 接口，而通过将 Iterator 对象声明位 Aggregate 的友元来给予 Iterator一些特权，获得访问 Aggregate 私有数据和方法的机会。

**应用**

Iterator 模式的应用很常见，在开发中就经常会用到 STL 中预定义好的 Iterator 来对 STL 类进行遍历（ Vector、 Set 等）。
