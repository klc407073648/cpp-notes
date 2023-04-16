# C++ 新版本特性 - C++14

[[toc]]

# 参考资料

* [cpp14](https://en.cppreference.com/w/cpp/14)
* [C++14新特性](https://zhuanlan.zhihu.com/p/550561238)

# 特性概览

![c++14](/_images/c++/features/c++14.png)

# 变量模板

在C++14中:

* lambda表达式参数可以为auto类型，类似于函数模板;
* 可以对捕获列表的捕获变量“赋值”。

<<< @/md/c++/features/c14/src/variable_templates.cpp

# 别名模板

<<< @/md/c++/features/c14/src/alias_templates.cpp

# 泛型lambda和lambda初始化捕获

<<< @/md/c++/features/c14/src/lamdba.cpp

# 放松对constexpr函数的限制

C++11中的常量表达式函数：

* 函数体只有单一的return返回语句;
* 函数必须有返回值(不能是void函数)
* 在使用前必须有定义
* return返回语句表达式中不能使用非常量表达式的函数，全局数据，且必须是一个常量表达式

<<< @/md/c++/features/c14/src/constexpr_fun.cpp

# deprecated标记

C++14中增加了[[deprecated]]标记，可以修饰类、函数、变量等，当程序中使用了被其修饰的模块时，编译器会产生告警，提示用户该标记标记的内容将来可能会被废弃，尽量不要使用。

<<< @/md/c++/features/c14/src/deprecated.cpp

# 二进制字面量和数位分隔符

<<< @/md/c++/features/c14/src/literals_digit.cpp

# 库相关

* std::make_unique
  * C++11中没有std::make_unique，在C++14中实现了这个方法
* std::shared_timed_mutex和std::shared_lock
  * C++14中通过std::shared_timed_mutex和std::shared_lock实现读写锁，保证多个线程可以同时读，但是写线程必须独立运行，写操作不能和读操作同时进行。
* std::integer_sequence
  * 表示一个编译时的整数序列。在用作函数模板的实参时,能推导参数包Ints并将它用于包展开。
* std::exchange
  * 使用new_value 替换 obj 的值，并返回 obj 的旧值。（右边替换左边，返回左边的初值）;T 必须满足可移动构造 (MoveConstructible) 的要求。而且必须能移动赋值 U 类型对象给 T 类型对象。
  <<< @/md/c++/features/c14/src/std_exchange.cpp
* std::quoted
  * 用于给字符串添加双引号

<<< @/md/c++/features/c14/src/std_fun.cpp

执行结果：

<<< @/md/c++/features/c14/res/std_fun.txt