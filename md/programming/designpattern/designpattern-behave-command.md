# 行为型 - 命令模式(Command)

​[[toc]]

> Command 模式通过将请求封装到一个对象（ Command） 中，并将请求的接受者存放到具体的 ConcreteCommand 类中（ Receiver） 中， 从而实现调用操作的对象和操作的具体实现者之间的解耦。

Command 模式典型的结构图为：

![](_images/programming/designpattern/behave/Command.png)

Command 模式结构图中，**将请求的接收者（处理者）放到 Command 的具体子类ConcreteCommand 中，当请求到来时（ Invoker 发出 Invoke 消息激活 Command 对象），ConcreteCommand 将处理请求交给 Receiver 对象进行处理**。

备注：这里的Invoke 消息就是下面Notify()来处理的。

# 代码实现

## 模型代码实现

<<< @/md/programming/designpattern/behave/Command/Reciever.h

<<< @/md/programming/designpattern/behave/Command/Reciever.cpp

<<< @/md/programming/designpattern/behave/Command/Command.h

<<< @/md/programming/designpattern/behave/Command/Command.cpp

<<< @/md/programming/designpattern/behave/Command/Invoke.h

<<< @/md/programming/designpattern/behave/Command/Invoke.cpp

<<< @/md/programming/designpattern/behave/Command/main.cpp

上述例子中

```cpp
void Add(Command *cmd);//添加命令
void Remove(Command *cmd);//删除命令
void RemoveAll();//删除全部命令
void Notify();//通知执行所有命令
```

```bash
[root@VM-16-6-centos Command]# ./CommandTest
ConcreteCommandA Excute
Reciever action.......
ConcreteCommandA Excute
Reciever action.......
ConcreteCommandB Excute
Reciever action.......
------------------
ConcreteCommandB Excute
Reciever action.......
------------------

```