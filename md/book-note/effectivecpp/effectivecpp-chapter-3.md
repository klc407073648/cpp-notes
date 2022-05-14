#  第三章：资源管理

[[toc]]

# 以对象管理资源

中心思想：把资源放进对象内，便可以依赖C++的析构函数自动调用机制确保资源被释放。

关键点：

1. 获得资源后立刻放进管理对象。（**Resource Acquisition Is Initialization,RAII**）

2. 管理对象运用析构函数确保资源被释放。

```cpp
class Lock
{
public:
    explict Lock(Mutex* pm)
    : mutexPtr(pm)
    {
        lock(mutexPtr);
    }
    ~Lock()
    {
        unlock(mutexPtr);
    }
private:
    Mutex *mutexPtr;
}
```

注意事项：

1. **为防止资源泄漏，请使用RAII对象**，它们在**构造函数中获取资源并在析构函数中释放资源**。

2. 两个常被使用的RAII classes分别是share_ptr和auto_ptr，前者通常是较佳选择。

# 在管理资源类中小心copying行为

如果RAII对象被复制，会发生什么情况？

## 禁止复制

通常允许RAII对象被复制不合理，如果需要禁止copy RAII对象，可以通过将copying操作声明为private（继承Uncopyable类）来禁止copy；

## 对底层资源使用引用计数法（reference-count）

如果需要保留资源直到资源的最后一个使用者被销毁，可实现引用计数法（shared_ptr）。

```cpp
class Lock
{
public:
    explict Lock(Mutex* pm)
    : mutexPtr(pm , unlock)
    {
        lock(mutexPtr.get());
    }
    ~Lock()
    {
        unlock(mutexPtr);
    }
private:
    std::tr1::shared_ptr<Mutex> mutexPtr;
}
```

std::tr1::shared_ptr允许指定删除器，当引用次数为0时调用。

# 在资源管理类中提供对原始资源的访问

```cpp
#include <iostream>
#include <memory>

using namespace std;

class MyTest
{
public:
	MyTest()
	:n(0)
	{
		cout<<"MyTest()"<<endl;
	}
	~MyTest()
	{
		cout<<"~MyTest()"<<endl;
	}
	MyTest(const MyTest& m)
	{
		cout<<"copying MyTest"<<endl;
		this->n = m.n;
	}
	void printMyTest(MyTest* m)
	{
		cout<<"printMyTest "<<m->n<<endl;
	}
private:
	int n;
};

int main()
{
	//std::shared_ptr<MyTest> m_test = new MyTest();
	//error: conversion from ‘MyTest*’ to non-scalar type ‘std::shared_ptr<MyTest>’ requested

	std::shared_ptr<MyTest> m_test(new MyTest());
	m_test->printMyTest(m_test.get());
	
    //m_test->printMyTest(m_test);
	//error: cannot convert ‘std::shared_ptr<MyTest>’ to ‘MyTest*’ ,通过get方法获取raw指针
	return 0;
}
```

执行结果：

```bash
[root@192 15]# ./main
MyTest()
printMyTest 0
~MyTest()
```

# 成对使用new和delete时要采用相同形式

被删除的指针对象，是单一对象或是对象数组，处理方式不同，对象数据内存布局里会多存储一个记录n，表示数组的大小。

（备注：不要对数组形式做typedef操作，容易产生误操作）

```cpp
std::string* mystr = new std::string();
std::string* mystrArr = new std::string[100];

delete mystr;
delete [] mystrArr;


typedef std::string strArr[10];
std::string* str = new strArr;

delete str;//出错
delete [] str;//正确
```

# 以独立语句将newd对象置入智能指针

```cpp
processWidget(std::shared_ptr<Widget>(new Widget), priority());
```

调用processWidget需要经历以下三个步骤：

1. 调用priority()函数；
2. 执行 new Widget
3. 调用std::shared_ptr构造函数

C++编译器以什么样的次序完成上述三个步骤存在弹性。如果执行顺序是213，然后在调用priority的过程中出现异常，那new Widget返回的指针将会遗失，不会存入std::shared_ptr内。
即资源创建和资源被转换为资源管理对象过程中，可能发生异常干扰。因此建议将上述函数调用改为：

```cpp
std::shared_ptr<Widget> pw(new Widget)
processWidget(pw,priority());
```

​