# C++ 知识点 - 模板特化与偏特化

[[toc]]

# 模板特化

> 模板特化（template specialization）不同于模板的实例化，模板参数在某种特定类型下的具体实现称为模板特化。模板特化有时也称之为模板的具体化，分别有函数模板特化和类模板特化。

## 函数模板特化

函数模板特化指函数模板在模板参数为特定类型下的特定实现。

```cpp
#include <iostream>
#include <string.h>
using namespace std;

template<typename T> 
T compareMax(T t1,T t2) {
	return (t1>t2)?t1:t2;
}

template<> 
const char* compareMax<const char*>(const char* s1,const char* s2) {
	return (strcmp(s1,s2)>0)?s1:s2;
}

int main() {
	// 隐式调用实例：int max<int>(int,int)
	int i=compareMax(10,5);
	
	// 显式调用特化版本：const char* max<const char*>(const char*,const char*)
	const char* p=compareMax<const char*>("abc","bcd");
	cout<<"i:"<<i<<endl;
	cout<<"p:"<<p<<endl;
}
```

运行结果：

```
[root@VM-16-6-centos test]# ./fun_temp
i:10
p:bcd
```

在函数模板显示**特化定义（Explicit Specialization Definition）**中，显示关键字 template 和一对尖括号 <>，然后是函数模板特化的定义。该定义指出了模板名、被用来特化模板的模板实参，以及函数参数表和函数体。

在上面的程序中，如果不给出函数模板compareMax<T>在T为const char*时的特化版本，那么在比较两个字符串的大小时，**比较的是字符串的起始地址的大小，而不是字符串的内容在字典序中的先后次序**。

除了定义函数模板特化版本外，还可以直接给出模板函数在特定类型下的重载形式（普通函数）。**使用函数重载可以实现函数模板特化的功能，也可以避免函数模板的特定实例的失效**。

例如，把上面的模板特化可以改成如下重载函数:

```cpp
const char* compareMax<const char*>(const char* s1,const char* s2) {
	return (strcmp(s1,s2)>0)?s1:s2;
}
```

程序运行结果和使用函数模板特化相同。但是，使用普通函数重载和使用模板特化还是有不同之处，主要表现在如下两个方面：

1. 如果使用普通重载函数，那么不管是否发生实际的函数调用，都会在目标文件中生成该函数的二进制代码。而如果使用模板的特化版本，除非发生函数调用，否则不会在目标文件中包含特化模板函数的二进制代码。这符合**函数模板的“惰性实例化”准则**。

2. 如果使用普通重载函数，那么在分离编译模式下，需要在各个源文件中包含重载函数的申明，否则在某些源文件中就会使用模板函数，而不是重载函数。

## 类模板特化

> 类模板特化类似于函数模板的特化，即类模板参数在某种特定类型下的具体实现。

```cpp
#include <iostream>
using namespace std;

template<class T>
class A {
	T num;
public:
	A(){
		num=T(0);
	}
	void print(){
		cout<<"A'num:"<<num<<endl;
	}
};

template<> 
class A<char*> 
{
	char* str;
public:
	A() {
		str="A' special definition: char*";
	}
	void print() {
		cout<<str<<endl;
	}
};

int main() {
	A<int> a1;      //显示模板实参的隐式实例化
	a1.print();
	A<char*> a2;    //使用特化的类模板
	a2.print();
	
	return 0;
}
```

运行结果：
```
[root@VM-16-6-centos test]# ./class_temp
A'num:0
A' special definition: char*
```

# 模板偏特化

> 模板偏特化（Template Partitial Specialization）是模板特化的一种特殊情况，指显示指定部分模板参数而非全部模板参数，或者指定模板参数的部分特性分而非全部特性，也称为模板部分特化。与模板偏特化相对的是模板全特化，指对所有模板参数进行特化。模板全特化与模板偏特化共同组成模板特化。

模板偏特化主要分为两种:

1. 对部分模板参数进行全特化;
2. 对模板参数特性进行特化，包括将模板参数特化为指针、引用或是另外一个模板类。

##  函数模板偏特化

 compare 函数模板，在比较数值大小时没有问题，但是如果传入的是数值的地址，需要比较两个数值的大小，而非比较传入的地址大小。此时需要对compare函数模板进行偏特化。考察如下代码：

```cpp
#include <vector>
#include <iostream> 
using namespace std;

// 函数模板
template<class T, class N> 
void compare(T num1, N num2) {
	cout << "standard function template" << endl;
	if(num1>num2) {
		cout << "num1:" << num1 << " > num2:" << num2 <<endl;
	} else {
		cout << "num1:" << num1 << " <= num2:" << num2 << endl;
	}
}

//对部分模板参数进行特化
template<class N> 
void compare(int num1, N num2) {
	cout<< "partitial specialization" <<endl;
	if (num1>num2)
		cout << "num1:" << num1 << " > num2:" << num2 << endl;
	else
		cout << "num1:" << num1 << " <= num2:" << num2 << endl;
}

//将模板参数特化为指针(模板参数的部分特性)
template<class T, class N> 
void compare(T* num1, N* num2) {
	cout << "new partitial specialization" << endl;
	if (*num1>*num2)
		cout << "num1:" << *num1 << " > num2:" << *num2 << endl;
	else
		cout << "num1:" << *num1 << " <= num2:" << *num2 << endl;
}

// 将模板参数特化为另一个模板类
template<class T, class N> 
void compare(std::vector<T>& vecLeft, std::vector<T>& vecRight) {
	cout << "to vector partitial specialization" << endl;
	if (vecLeft.size()>vecRight.size())
		cout << "vecLeft.size()" << vecLeft.size() << " > vecRight.size():" << vecRight.size() << endl;
	else
		cout << "vecLeft.size()" << vecLeft.size() << " <= vecRight.size():" << vecRight.size() << endl;
}

int main() {
	// 调用非特化版本 compare<int,int>(int num1, int num2)
	compare<int,int>(30,31);

	// 调用偏特化版本 compare<char>(int num1, char num2)
	compare(30,'10');

	int a = 30;
	char c = '1';
	// 调用偏特化版本 compare<int,char>(int* num1, char* num2)
	compare(&a, &c);

	vector<int> vecLeft{0};
	vector<int> vecRight{1,2,3};
	// 调用偏特化版本 compare<int,char>(int* num1, char* num2)
	compare<int,int>(vecLeft,vecRight);

    return 0;
}
```

运行结果：
```
[root@VM-16-6-centos test]# ./fun_part_temp
standard function template
num1:30 <= num2:31
partitial specialization
num1:30 <= num2:12592
new partitial specialization
num1:30 <= num2:1
to vector partitial specialization
vecLeft.size()1 <= vecRight.size():3
```

## 类模板偏特化

> 类模板的偏特化与函数模板的偏特化类似。

```cpp
#include <vector>
#include <iostream> 
using namespace std;

// 类模板
template<class T, class N> 
class Test {
public:
	static bool comp(T num1, N num2) {
		cout <<"standard class template"<< endl;
		return (num1<num2) ? true : false;
	}
};

// 对部分模板参数进行特化
template<class N> 
class Test<int, N> {
public:
	static bool comp(int num1, N num2) {
		cout << "partitial specialization" << endl;
		return (num1<num2) ? true : false;
	}
};

// 将模板参数特化为指针
template<class T, class N> 
class Test<T*, N*> {
public:
	static bool comp(T* num1, N* num2) {
		cout << "new partitial specialization" << endl;
		return (*num1<*num2) ? true : false;
	}
};

// 将模板参数特化为另一个模板类
template<class T, class N> 
class Test<vector<T>,vector<N>> {
public:
	static bool comp(const vector<T>& vecLeft, const vector<N>& vecRight) {
		cout << "to vector partitial specialization" << endl;
		return (vecLeft.size()<vecRight.size()) ? true : false;
	}
};

int main() {
	// 调用非特化版本
	cout << Test<char, char>::comp('0', '1') << endl;	
	
	// 调用部分模板参数特化版本
	cout << Test<int,char>::comp(30, '10') << endl;		

	// 调用模板参数特化为指针版本
	int a = 30;
	char c = '10';
	cout << Test<int*, char*>::comp(&a, &c) << endl;		

	// 调用模板参数特化为另一个模板类版本
	vector<int> vecLeft{1,2,3,4};
	vector<int> vecRight{5,6};
	cout << Test<vector<int>, vector<int>>::comp(vecLeft,vecRight) << endl;	

    return 0;
}
```

运行结果：
```
[root@VM-16-6-centos test]# ./class_part_temp
standard class template
1
partitial specialization
1
new partitial specialization
1
to vector partitial specialization
0

```

# 模板类调用优先级

对主版本模板类、全特化类、偏特化类的调用优先级从高到低进行排序是：
    * 全特化类 > 偏特化类 > 主版本模板类。这样的优先级顺序对性能也是最好的。

但是模板特化并不只是为了性能优化，更多是为了让模板函数能够正常工作。

最典型的例子就是 STL中的 iterator_traits。algorithm 中大多数算法通过 iterator 对象来处理数据，但是同时允许以指针代替 iterator 对象，这是为了支持 C-Style Array。如果直接操作 iterator，那么为了支持指针类型，每个算法函数都需要进行重载，因为指针没有::value_type类型。为了解决这个问题，STL 使用了 iterator_traits 对 iterator 特性进行封装，并为指针类型做了偏特化处理，算法通过它来操作 iterator，不需要知道实际操作的是 iterator 对象还是指针。

```cpp
template<typename IteratorClass> class iterator_traits
...
template<typename ValueType> class iterator_traits<ValueType*>
...
template<typename ValueType> class iterator_traits<ValueType const*>
...
```