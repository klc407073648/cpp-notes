# C++ 知识点 - 头文件.h 和 源文件.cpp 以及多重定义(multiple definition)

> 头文件(.h)和源文件(.cpp)以及变量或函数的多重定义问题

[[toc]]

# 概述

以案例形式讲述函数多重定义的问题：

假设项目文件目录结构为

```
.
|-- main.cpp
|-- test.cpp
`-- test.h
```

test.h

<<< @/md/c++/tips/src/multidefine/test.h

test.cpp

<<< @/md/c++/tips/src/multidefine/test.cpp

main.cpp

<<< @/md/c++/tips/src/multidefine/main.cpp

编译报错：

```
[root@VM-16-6-centos multidefine]# g++ main.cpp test.cpp -o main -I.
/tmp/ccjyvw9V.o: In function `test1()':
test.cpp:(.text+0x0): multiple definition of `test1()'
/tmp/ccdEA9Wl.o:main.cpp:(.text+0x0): first defined here
collect2: error: ld returned 1 exit status
```

## 分析

* 每个**源文件(.cpp)都会被编译**（这里的编译指的是整一个生成可执行文件的过程，包括预处理、编译、汇编、链接），最终会生成一个.obj文件，然后所有的.obj文件链接起来生成可执行程序。所以main.cpp会变成main.o，test.cpp会变成test.o。

* 每个**头文件(.h)是不能被编译的**。#include叫做编译预处理指令，可以简单理解成，在test.cpp中的 `#include "test.h"` 指令把test.h中的代码在编译前添加到了test.cpp的头部。可以简单理解为将头文件的文本插入到源文件中。

根据上面两个特点，实际上，在test.h中定义了一个test()函数，然后分别插入到test.cpp和main.cpp中。所以在将main.o和test.o链接生成可执行代码时，链接器发现他们各自都定义了test()，这就起冲突了。这就是为什么会出现**多重定义**。

## 解决方法

只在头文件test.h中保留函数test()的声明，而在源文件test.cpp 定义函数test()。这样可以保证在链接时，只有一个目标文件中拥有函数test()的定义，因此就不会出现多重定义的错误。

# 总结

最好在头文件中只放函数的声明，而在源文件中才进行函数的定义。**一个头文件会有一个对应的源文件来对头文件中的声明进行定义**，因此头文件的名字一般与实现定义的源文件的名字是相同的，这样才能显示出两者的对应关系。