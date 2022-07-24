# 行为型 - 解释器(Interpreter) 

> Interpreter 模式的目的就是使用一个解释器为用户提供一个一门定义语言的语法表示的解释器，然后通过这个解释器来解释语言中的句子。

​[[toc]]

# 概念

Interpreter 模式提供了这样的一个实现语法解释器的框架, Interpreter 模式典型的结构图为：

![](/_images/programming/designpattern/behave/Interpreter.png)

Interpreter 模式中，提供了 TerminalExpression 和 NonterminalExpression 两种表达式的解释方式，Context 类用于为解释过程提供一些附加的信息（例如全局的信息）

# 代码实现

## 模型代码实现

<<< @/md/programming/designpattern/behave/Interpreter/Context.h

<<< @/md/programming/designpattern/behave/Interpreter/Context.cpp

<<< @/md/programming/designpattern/behave/Interpreter/Interpreter.h

<<< @/md/programming/designpattern/behave/Interpreter/Interpreter.cpp

<<< @/md/programming/designpattern/behave/Interpreter/main.cpp

## 符号运算实现

<<< @/md/programming/designpattern/behave/Interpreter/SymbolOperation.cpp
