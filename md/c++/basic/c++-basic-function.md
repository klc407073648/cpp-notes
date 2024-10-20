# C++ 基础 - 宏函数、内联函数、普通函数

[[toc]]

> 普通函数调用有时间和空间的开销：入栈和出栈。

> 内联函数会进行参数类型的检查，可以使用调试器调试，但会导致程序存在多份相同的函数拷贝，且每次修改需要重新编译。（编译阶段展开到生成指令中的）编译器会对inline 声明的函数做判断，决定是否将对应代码直接替换到实际调用点。

> 宏定函数书写上简洁美观，但不会对参数类型进行检查，也不符合函数调用的一些规则。（预编译阶段展开到代码中）

# 概述

函数是一个可以重复使用的代码块，CPU 会一条一条地挨着执行其中的代码。CPU 在执行主调函数代码时如果遇到了被调函数，主调函数就会暂停，CPU 转而执行被调函数的代码；被调函数执行完毕后再返回到主调函数，主调函数根据刚才的状态继续往下执行。

一个 C/C++程序的执行过程可以认为是多个函数之间的相互调用过程，它们形成了一个或简单或复杂的调用链条，这个链条的起点是 main()，终点也是 main()。当 main() 调用完了所有的函数，它会返回一个值（例如return 0;）来结束自己的生命，从而结束整个程序。

如果函数体代码比较多，需要较长的执行时间，那么**函数调用机制占用的时间可以忽略**；如果函数只有一两条语句，那么**大部分的时间都会花费在函数调用机制上，这种时间开销就就不容忽视**。

## 普通函数

函数调用是有时间和空间开销的。程序在执行一个函数之前需要做一些准备工作，要将实参、局部变量、返回地址以及若干寄存器都**压入栈中**，然后才能执行函数体中的代码；函数体中的代码执行完毕后还要清理现场，将之前压入栈中的数据都**出栈**，才能接着执行函数调用位置以后的代码。

## 内联函数

内联函数是在 C++ 中增加的一个功能，可以提高程序执行效率。如果函数是内联的，编译器在编译时，会把内联函数的实现替换到每个调用内联函数的地方，可以与宏函数作类比，但宏函数不会进行类型检查。可以将普通函数或者类的成员函数声明为内联。

当内联函数具有外部的定义，其他文件只需要采用普通的函数声明，就可以调用它。然而，从别的文件调用函数，将不会被编译成内联函数。

**内联函数一般要求如下**：

1. 函数简短，通常3-5行；
2. 函数内没有复杂的实现，比如：包含while、for 循环，递归等；
3. 通常在多处有调用；

注意：对函数作 inline 声明只是程序员对编译器提出的一个建议，而不是强制性的，并非一经指定为 inline 编译器就必须这样做。编译器有自己的判断能力，它会根据具体情况决定是否这样做。

### 内联函数和宏函数的异同 

相同点：

* 内联函数和宏函数一样，它会在代码书写处直接拷贝一份指令，不会像普通函数一样单独生成指令然后调用，这使得其相对普通函数而言其仍然是高效的。

不同点：

* 但与宏函数不同，内联函数是在**编译阶段展开到生成指令中的**，而不是**预编译阶段展开到代码中**，什么时候调用内联函数，就会将展开后的指令插入进去。
* 内联函数也会**进行参数类型的检查**，符合函数的一般直觉，由于经常需要进行调用，其每次调用都会被重定义，所以经常在头文件中定义内联函数。宏函数**不会对参数类型进行检查**。
* 内联函数是可以使用调试器调试的，而宏函数不行。

### 为什么要使用内联函数

解决一些**频繁调用的小函数消耗大量空间**的问题。

通常情况下，在调用函数时，程序会将控制权从调用程序处转移到被调用函数处，在这个过程中，传递参数、寄存器操作、返回值等会消耗额外的时间和内存，如果调用的函数代码量很少，也许转移到调用函数的时间比函数执行的时间更长。而如果使用内联函数，内联函数会在调用处将代码展开，从而节省了调用函数的开销。

### 哪些函数不能是内联函数？

1. 递归调用本身的函数；
2. 包含复杂语句的函数，例如：for、while、switch 等；
3. 函数包含静态变量；

### 使用内联函数的缺点

1. 编译后的程序会存在多份相同的函数拷贝，如果被声明为内联函数的函数体非常大，那么编译后的程序体积也将会变得很大
2. 编译的时间会增加，因为每次内联函数有修改，就需要重新编译代码。

## 宏定义函数

宏定函数在书写上要比普通函数简洁美观的多。

但宏展开的一大弊端是它**不会对参数类型进行检查，也不符合函数调用的一些规则**，而且在定义时要格外小心其展开的结果是否是我们想要的结果，往往需要加上 {} 或 () 加以限制。

使用宏代码最大的缺点是容易出错，预处理在拷贝宏代码时常常产生意想不到的边际效应。

例如以下的代码：

```
#define MAX(a,b) (a)>(b)?(a):(b)

result = MAX(i,j)+2;
//被预处理器扩展为 
result = (i)>(j)?(i):(j)+2;
```

### 宏定义函数与普通函数不同

**编译过程上不同**

在编译时，对于宏定义函数而言，预编译时会将这些宏定义函数按展开的规则直接展开成语句，并且宏定义函数在代码中书写多少次，便**展开多少次**，拷贝相应的代码插入，生成相应的指令，而对于普通函数而言其**只会生成一份相应的指令**，调用处会生成传参指令和调用指令实现对函数的调用。

**执行过程上不同**

在实际执行过程中，宏定义式函数所有的语句都是**普通语句执行**，而普通函数由于需要调用的缘故，需要进行**开辟栈空间、压栈、出栈等操作**。

基于以上两点不同使得宏函数和普通函数在使用和设计上有很大差异。

**宏的另一个缺点是不可调试**

内联机制既具备宏代码的效率，又增加了安全性，而且可以自由操作的类的数据成员，所以应该尽量使用内联函数来取代宏代码。
