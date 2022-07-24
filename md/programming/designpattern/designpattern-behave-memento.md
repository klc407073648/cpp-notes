# 行为型 - 备忘录(Memento)

​[[toc]]

> 备忘录模式(Memento pattern): 要在不破坏封装行的前提下，捕获并保存一个类的内部状态，这样就可以利用该保存的状态实施恢复操作。

Memento 模式典型的结构图为：

![](_images/programming/designpattern/behave/Memento.png)


# 代码实现

<<< @/md/programming/designpattern/behave/Memento/Memento.h

<<< @/md/programming/designpattern/behave/Memento/Memento.cpp

<<< @/md/programming/designpattern/behave/Memento/main.cpp

```bash
[root@VM-16-6-centos Memento]# ./MementoTest
old.....
new.....
old.....
```

## 代码说明

Memento 模式的关键就是 friend class Originator;可以看到 Memento 的接口都声明为 private，而将 Originator 声明为 Memento 的友元类。我们将 Originator 的状态保存在 Memento 类中，而将 Memento 接口 private 起来， 也就达到了封装的功效。在 Originator 类中我们提供了方法让用户后悔： RestoreToMemento(Memento* mt)；我们可以通过这个接口让用户后悔。在测试程序中，我们演示了这一点： Originator 的状态由 old 变为 new 最后又回到了 old。

## 讨论

在 Command 模式中， **Memento 模式经常被用来维护可以撤销（ Undo） 操作的状态**。 这一点将在 Command 模式具体说明。