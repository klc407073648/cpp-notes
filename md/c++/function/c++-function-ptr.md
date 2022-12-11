# C++ 函数指针及其应用

> 介绍C++函数指针的概念及其应用

[[toc]]

## 为何存在函数指针

与数据项相似的是函数也有地址，一般情况下对用户来说没什么用，但是对于程序来说，用处比较大。

函数指针，其本质是一个指针变量，该指针指向这个函数。总结来说，函数指针就是指向函数的指针。

* 例如：将另一个函数的地址作为一个函数的参数，这样第一个函数就能找到第二个函数并且运行它。虽然这种方式比起直接调用的方式比更加的笨拙，但是其允许在不同的时间传递不同函数的地址，这意味着可以在不同的时间使用不同的函数。

补充：

指针函数和函数指针的区别

定义不同

* 指针函数本质是一个函数，其返回值为指针。
* 函数指针本质是一个指针，其指向一个函数。

写法不同

* 指针函数：int* fun(int x,int y);
* 函数指针：int (*fun)(int x,int y);

可以简单粗暴的理解为，指针函数的*是属于数据类型的，而函数指针的星号是属于函数名的。

再简单一点，可以这样辨别两者：函数名带括号的就是函数指针，否则就是指针函数。

指针函数示例：

```cpp
#include<iostream>
#include<cstdio>
#include <cstring>

using namespace std;

/* 
 * 指针函数的定义 
 * 返回值是指针类型int * 
 */  
int *f(int a, int b) {  
    int *p = (int *)malloc(sizeof(int));  
    memset(p, 0, sizeof(int));  
    *p = a + b;    
    return p;  
} 

int main(){
	int *p = NULL;  
    p = f(1, 2);  
	cout<< p<<endl;//0x2166e70
	cout<< *p<<endl;//3
	return 0;
}
```

## 函数地址

函数的地址就是函数名，要将函数作为参数进行传递，必须传递函数名。

## 声明函数指针

声明格式：类型说明符 (*函数名) (参数)

函数指针的声明：表明指定的函数返回类型、表明函数的特征标（参数列表）

注意：只有当一个函数的返回类型和参数列表和声明的函数指针的返回类型和参数列表一致的时候才可以进行传递，编译器拒绝这种赋值。

```cpp
int sum(int a, int b);
 
int (*ptr)(int, int); // 声明函数指针ptr

ptr p1 = sum;    // 指针赋值
```

将指针作为函数的参数传递：

```cpp
void result(int a, int b, int (*ptr)(int, int))
```

## 使用指针来调用函数

```cpp
// 第一种方式
(*ptr)(4, 5);
// 第二种方式C++可用
ptr(4, 5);
```

## 使用typedef进行简化

定义一个函数指针，然后调用，输出结果:

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

int sum(int a, int b)
{
	return a+b;
}
 
int multiply(int a, int b)
{
	return a*b;
}
 
int main()
{
	typedef int (*ptr)(int, int);
	ptr p1 = sum;
	cout<< p1(4, 5)<< endl;
	p1 = multiply;
	cout<< p1(4, 5)<< endl;	
	
	return 0;		
}
```

将函数指针作为一个函数的形参然后输出，并且说明两种输出方式表达的结果一致:

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

int sum(int a, int b)
{
	return a+b;
}
 
int multiply(int a, int b)
{
	return a*b;
}
 
void result(int a, int b, int (*ptr)(int, int))
{
	cout<< ptr(a, b)<< endl;
	cout<< (*ptr)(a, b)<< endl;
}
 
int main()
{
	result(4, 5, sum);
	result(4, 5, multiply);
		
	return 0;		
}
```
