# 关于 - 网站问题修正

[[toc]]

# C++ 全栈知识体系 首页 快速开始链接不对

* 时间： 2022-06-10
* 反馈人：euyy
* 来源： gitub issues
* [C++ 全栈知识体系](https://stibel.icu/)

![](/_images/about/problem/1.png)


# 设计模式 - Overview 页面 7大原则描述不正确

* 时间： 2023-03-25
* 反馈人：[%ĀĀ␇Ö]0&#92;o%O。1〇.ō)°•|
* 来源： QQ群
* [设计模式 - Overview](https://stibel.icu/md/programming/designpattern/designpattern-overview.html)
* 修正前后对比:

![](/_images/about/problem/2.png)

# C++ 知识点 - 模板特化与偏特化 理解修正，函数偏特化是不支持这样做

* 时间： 2023-05-31
* 反馈人：小生
* 来源： QQ群
* [C++ 知识点 - 模板特化与偏特化](https://stibel.icu/md/c++/tips/c++-tips-spec-template.html)
* 修正前后对比:

![](/_images/about/problem/3.png)

# C++ 知识点 - return 局部变量   上下文描述不清晰

* 时间： 2023-06-07
* 反馈人：長安乱
* 来源： QQ群
* [C++ 知识点 - return 局部变量](https://stibel.icu/md/c++/tips/c++-tips-return-temp-var.html)
* 修正前后对比:

> 在主函数调用子函数时，首先程序会跳转到子函数的地址处，在子函数执行到最后return返回值时，系统会把需要返回的值存入寄存器中，然后经过“}”，子函数正式结束，在这个过程中，如果子函数有形参和局部变量，系统会为它们分配栈内存空间，等到函数运行完毕后，系统将会自动释放在栈内存中给局部变量分配的内存中的数据。

> 在主函数调用子函数时，首先程序会跳转到子函数的地址处，在子函数执行到最后return返回值时，系统会把需要返回的值存入寄存器中，**然后经过函数体结尾的“}”后**，子函数正式结束，在这个过程中，如果子函数有形参和局部变量，系统会为它们分配栈内存空间，等到函数运行完毕后，系统将会自动释放在栈内存中给局部变量分配的内存中的数据。
