# 第二章：构造/析构/赋值运算（二）

[[toc]]

# 为多态基类声明virtual析构函数

例如工程模式，创建一个base class指针，指向生成的derived class对象。

```cpp
class TimeKeeper
{
    public:
        TimeKeeper();
        ~TimeKeeper();
    private:
        int time;
};

class AtomicClock: public  TimeKeeper
{
    public:
        AtomicClock();
        ~AtomicClock();
};

TimeKeeper::TimeKeeper()
{
	cout<<"TimeKeeper()"<<endl;
}

TimeKeeper::~TimeKeeper()
{
	cout<<"~TimeKeeper()"<<endl;		
}

AtomicClock::AtomicClock()
{
	cout<<"AtomicClock()"<<endl;	
}

AtomicClock::~AtomicClock()
{
	cout<<"~AtomicClock()"<<endl;	
}

//main
#include"Time.h"

int main()
{
	TimeKeeper* m = new  AtomicClock();
	delete m;
	return 0;
}
```

执行结果：

```bash
[root@192 07]# ./main
TimeKeeper()
AtomicClock()
~TimeKeeper()
```

修改 ~TimeKeeper(); 为 virtual ~TimeKeeper();
virtual函数的目的是**允许derived class的实现得以客制化。**（见34条款）

```bash
[root@192 07]# ./main
TimeKeeper()
AtomicClock()
~AtomicClock()
~TimeKeeper()
```

注意事项：

1. 带有多态性质的base class应该声明一个virtual析构函数。且如果class带有任务virtual函数，它就应该拥有一个virtual析构函数。

2. class的设计目的如果不是作为base class使用，或不是为了具有多态性，就不该声明virtual析构函数。

# 别让异常逃离析构函数

```cpp
class DBConn
{
public:
    ...
    void close()
    {
        db.close();
        closed = true;
    }
    ~DBConn()
    {
        if(!closed)
        {
            try {
            db.close();
            }
            catch (...){ //如果关闭动作失败，记录下来并结束程序或吞下异常
             制造运转记录，记下对close的调用失败
             ...
            }
        }
    }
}
```

注意事项：

1. 析构函数如果可能抛出异常，应该捕捉任何异常，然后吞下它们或结束程序。 

2. 最好提供一个函数供客户使用，能够使得客户对运行期间抛出的异常做出反应。（例如上述的close函数）

# 绝不在构造和析构过程中调用virtual函数 

由于base class构造函数执行更早于derived class构造函数，当base class构造函数执行时derived class的成员变量尚未初始化。如果此期间调用的virtual函数下降至derived class 阶层，要知道derived class的函数几乎必然取用local成员变量，而那些成员变量尚未初始化。

注意事项**：在构造和析构期间不要调用virtual函数，因为这类调用从不下降至derived class。**

# 令operator= 返回一个reference to *this

```cpp
Widget& operator=(const Widget& rhs)
{
    ...
    return *this;
}
```

# 在operator=中处理"自我赋值"

```cpp
class Bitmap {...};
class Widget
{
    ...
private:
    Bitmap * pb;
}

Widget& Widget::opeator=(const Widget& rhs) // 一份不安全的opeator=实现版本
{
    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
}

Widget& Widget::opeator=(const Widget& rhs) 
{
    if(this = &rhs)  return *this; //证同测试（identity test）
    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
}

Widget& Widget::opeator=(const Widget& rhs) 
{
    Bitmap* pOrig = pb;
    pb = new Bitmap(*rhs.pb);
    delete pOrig;
    return *this;
}

Widget& Widget::opeator=(const Widget& rhs) 
{
    Widget trmp(rhs);
    swap(temp); //将*this和temp数据交换
    return *this;
}
```

注意事项：

1.确保当对象自我赋值时 operator= 有良好行为。其中技术包括比较“来源对象”和“目标对象”的地址、精心周到的语句顺序、以及copy and swap。

2.确认任何函数如果操作一个以上的对象，而其中多个对象是同一个对象时，其行为仍然正确。

​