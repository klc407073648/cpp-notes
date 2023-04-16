# C++函数 - 作用域运算符::的使用

> C++的::符合代表作用域运算符，例如MyClass的成员函数myFun，会写成MyClass::myFun,表示为MyClass中的myFun函数。但是还存在另外一种情况，就是前面没有作用域名，而是只有::加函数名的情况。这表示全局作用域，即所调用的函数是全局函数。

[[toc]]

# 测试以及结果

测试程序: 

::: details
<<< @/md/c++/function/src/scopeFun/main.cpp
::: 

执行结果: 
```
global function myFun
————————————————————
MyClass function myFun

```
