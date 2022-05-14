# C++ 作用域运算符::的使用

> C++的::符合代表作用域运算符，例如MyClass的成员函数myFun，会写成MyClass::myFun,表示为MyClass中的myFun函数。但是还存在另外一种情况，就是前面没有作用域名，而是只有::加函数名的情况。这表示全局作用域，即所调用的函数是全局函数。

[[toc]]

测试程序: 

::: details
#include <iostream>
using namespace std;

// 全局函数
void myFun()
{
    cout<<"global function myFun"<<endl;
}

class MyClass
{
public:
    int printFun1()
    {
    	//调用的是全局函数
        ::myFun();
    }

     int printFun2()
    {
    	//调用的是成员函数
        myFun();
    }
    void myFun()
    {
        cout<<"MyClass function myFun"<<endl;
    }
};

int main()
{
    MyClass m;
    m.printFun1();
    cout<<"————————————————————"<<endl;
    m.printFun2();
    return 0;
}
:::

[main.cpp](./src/scopeFun/main.cpp)

执行结果: 
```
global function myFun
————————————————————
MyClass function myFun

```
