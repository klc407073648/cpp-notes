#  第四章：设计与声明（一）

[[toc]]

# 让接口容易被正确使用，不易被误用

```cpp
class Date
{
public:
     Date(int month, int day, int year)
     ...
};
```

上述接口可能会引起客户调用的错误,即填写顺序出错：

```cpp
Date d(2, 30, 2020);
Date d(30, 2, 2020);
```

进一步，可以将month,day,year封装成struct或class

```cpp
struct Day
{
   explicit Day(int d)
	       :val(d)
			{}
   int val;
};

struct Month
{
   explicit Month(int d)
	       :val(d)
			{}
   int val;
};

struct Year
{
   explicit Year(int d)
	       :val(d)
			{}
   int val;
};

class Date
{
public:
     Date(const Month& m, const Day& d,const Year& y)
     ...
};
```

这样调用的时候会直接报类型不匹配：

```cpp
Date m_date(Month(12),Day(20),Year(2020));//正确
Date m_date1(Day(20),Month(12),Year(2020));//错误
//error: no matching function for call to ‘Date::Date(Day, Month, Year)’
```

但是构造函数内仍需要做Day、Month和Year之间的关系以及大小限制。
STL容器的接口十分一致，size函数对各个容器都适用，不像Java中数组适用length，Lists使用size。

# 设计class犹如设计type

# 宁以pass-by-reference-to -const替换pass-by-value
优点：

* 避免额外的构造和析构函数带来的消耗,因此比较高效。
* 以by-reference方式传递参数可以避免slicing(对象切割)问题。

注意事项：

以上规则**并不适用于内置类型，以及STL的迭代器和函数对象。对它们而言，pass-by-value 往往比较恰当。**

```cpp
bool validateStudent(Student s);
bool platoIsOK = validateStudent(plato);
```

上述过程：Student的copy构造函数被调用，以plato为蓝本初始化s。当validateStudent函数返回时,s会被销毁。因此，对此函数而言，参数的传递成本是“一次Student copy构造函数被调用 ，加上一次Student析构函数调用”。当Student类中存在多个成员变量的时候，构造和析构的次数会成倍增加。

采用bool validateStudent(const Student& s) 效率会高很多，因为没有任何新对象被创建，所以没有任何构造函数和析构函数被调用。

当一个derived class 对象以by value方式传递并视为一个base class对象， base class的copy构造函数会被调用，而“造成此对象的行为像个derived class对象”的那些特化性质全被切割，仅仅留下一个base class对象。

```cpp
void printNameAndDisplay(Window w)
void printNameAndDisplay(const Window& w)
```