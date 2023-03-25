# C++ 基础 - 常用宏定义

[[toc]]

# 概述

https://www.techiedelight.com/zh/find-name-of-the-calling-function-in-cpp/

编译器内置宏：

ANSI C标准中有几个标准预定义宏（也是常用的）：

* __LINE__：在源代码中插入当前源代码行号；
* __FILE__：在源文件中插入当前源文件名；    
* __DATE__：在源文件中插入当前的编译日期
* __TIME__：在源文件中插入当前编译时间；
* __STDC__：当要求程序严格遵循ANSI C标准时该标识被赋值为1；
* __cplusplus：当编写C++程序时该标识符被定义，例如__cplusplus199711，__cplusplus201103。
* __FUNCTION__：调用函数的名称


编译器在进行源码编译的时候，会自动将这些宏替换为相应内容。

标识符__LINE__和__FILE__通常用来调试程序；   
   
标识符__DATE__和__TIME__通常用来在编译后的程序中加入一个时间标志，以区分程序的不同版本；
   
这四个都是预编译宏，不是包含在头文件中的：

   * __FILE__是当前编译的文件的文件名 是一个字符串
   * __TIME__是当前编译的文件的编译时间 格式是hh:mm:ss 是字符串
   * __DATE__是当前编译的文件的编译日期 格式是Mmm:dd:yyyy 是字符串
   * __LINE__是调用该宏语句所在的行数，是个十进制数

**应用场景**：在后台程序运行出问题时，详尽的日志是必不可少的，这里提供一个能自动记录日志触发点文件名、行号、函数名的方法，通常在**日志系统**中使用。

## 示例

示例：

<<< @/md/c++/basic/src/c++_marco_define.cpp

执行结果：

```
[root@VM-16-6-centos multidefine]# g++ test1.cpp -o test1
[root@VM-16-6-centos multidefine]# ./test1
__LINE__: 6
__FILE__: test1.cpp
__DATE__: Feb 20 2023
__TIME__: 14:23:31
__STDC__: 1
__cplusplus: 201402
__FUNCTION__: main

[root@VM-16-6-centos multidefine]# g++ test1.cpp -o test1 --std=c++11
[root@VM-16-6-centos multidefine]# ./test1
__LINE__: 6
__FILE__: test1.cpp
__DATE__: Feb 20 2023
__TIME__: 22:19:39
__STDC__: 1
__cplusplus: 201103
__FUNCTION__: main
```