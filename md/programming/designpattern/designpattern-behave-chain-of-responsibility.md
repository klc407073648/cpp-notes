# 行为型 - 责任链(Chain Of Responsibility)

​[[toc]]

> (Chain of responsibility pattern): 通过责任链模式, 你可以为某个请求创建一个对象链. 每个对象依序检查此请求并对其进行处理或者将它传给链中的下一个对象。

# 抛砖引玉

熟悉 `VC/MFC` 的都知道，VC是“基于消息，事件驱动”，消息在VC开发中起着举足轻重的作用。在MFC中，消息是**通过一个向上递交的方式进行处理**，例如一个WM_COMMAND消息的处理流程可能为：

1. MDI主窗口（CMDIFrameWnd）收到命令消息WM_COMMAND，其ID位ID_×××；

2. MDI主窗口将消息传给当前活动的MDI子窗口（CMDIChildWnd）；

3. MDI子窗口给自己的子窗口（View）一个处理机会，将消息交给View；

4. View检查自己MessageMap；

5. 如果View没有发现处理该消息的程序，则将该消息传给其对应的Document对象；否则View处理，消息流程结束。

6. Document检查自己MessageMap，如果没有该消息的处理程序，则将该消息传给其对象的DocumentTemplate处理；否则自己处理，消息流程结束；

7. 如果在6中消息没有得到处理，则将消息返回给View；

8. View再传回给MDI子窗口；

9. MDI子窗口将该消息传给CwinApp对象，CwinApp为所有无主的消息提供了处理。

MFC提供了消息的处理的链式处理策略，处理消息的请求将**沿着预先定义好的路径依次进行处理**。消息的发送者并不知道该消息最后是由那个具体对象处理的，当然它也无须也不想知道，但是结构是该消息被某个对象处理了，或者一直到一个终极的对象进行处理了。

责任链模式描述这样一类问题将**可能处理一个请求的对象链接成一个链，并将请求在这个链上传递，直到有对象处理该请求**（可能需要提供一个默认处理所有请求的类，例如MFC中的CwinApp类）。

Chain of responsibility 模式型的结构图为：

![](_images/programming/designpattern/behave/ChainOfResponsibility.png)

Chain of Responsibility 模式中 ConcreteHandler 将自己的后继对象（向下传递消息的对象）记录在自己的后继表中，当一个请求到来时， ConcreteHandler 会先检查看自己有没有匹配的处理程序，如果有就自己处理，否则传递给它的后继。当然这里示例程序中为了简化，ConcreteHandler 只是简单的检查看自己有没有后继，有的话将请求传递给后继进行处理，没有的话就自己处理。

# 代码实现

<<< @/md/programming/designpattern/behave/ChainOfResponsibility/Handle.h

<<< @/md/programming/designpattern/behave/ChainOfResponsibility/Handle.cpp

<<< @/md/programming/designpattern/behave/ChainOfResponsibility/main.cpp

Chain of Responsibility 模式的示例代码实现很简单，这里就其测试结果给出说明：ConcreteHandleA 的对象和 h1 拥有一个后继 ConcreteHandleB 的对象 h2,当一个请求到来时候， h1 检查看自己有后继，于是 h1 直接将请求传递给其后继 h2 进行处理， h2 因为没有后继，当请求到来时候，就只有自己提供响应了。于是程序的输出为：

1. ConcreteHandleA 我把处理权给后继节点.....；
2. ConcreteHandleB 没有后继了，我必须自己处理....。

**应用**

Chain of Responsibility 模式的最大的一个有点就是给系统降低了耦合性， 请求的发送者完全不必知道该请求会被哪个应答对象处理，极大地降低了系统的耦合性。
