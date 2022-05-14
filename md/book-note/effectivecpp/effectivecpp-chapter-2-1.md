# 第二章：构造/析构/赋值运算（一）

[[toc]]

# 确认对象被使用前已先被初始化

```cpp
class Point
{
    public:
        Point(int x,int y);
        ~Point();
		void printPoint();
    private:
        int m_x,m_y;
};

//成员初值列方式（member initialization list）
Point::Point(int x,int y)
:m_x(x),
 m_y(y)
{
	cout<<"Point()"<<endl;
}

//成员变量赋值
Point::Point(int x,int y)
{
    m_x=x;
    m_y=y;
	cout<<"Point()"<<endl;
}
```

注意事项：

1. 为内置型对象进行手工初始化（例如int，double）,string类型或自定义类等使用对应的构造函数。

```cpp
MyClass::MyClass()
:num(0), //内置型对象（int）
 m_str(), //string类型调用default构造函数
 m_class() //自定义类对象用default构造函数
{}
```

2. 构造函数最好使用成员初值列，而不要在构造函数中使用赋值操作。初始列列出的成员变量，其排列次序应该和它们在类中的声明次序相同。

3. 为了避免“跨编译单元之初始化次序”的问题，请用local static 对象替换non-local static对象。

# 了解C++默默编写并调用哪些函数

如果写下 class Empty {  };   如同写下这样的代码：

```cpp
class Empty
{
    Empty()    //default构造函数
	Empty(const Empty& rhs) //copy构造函数
    ~Empty(); 	//析构函数
	Empty& operator=(const Empty& rhs); //copy assignment操作符
};
```

注意事项：

* 编译器会暗自为class创建default构造函数、copy构造函数、copy assignment操作符，以及析构函数。

# 若不想使用编译器自动生成的函数，就该明确拒绝

以房产为例，每间房子都是独一无二的，不能被copy,因此私有化copy和copy assignment操作。

```cpp
class HomeForSale
{
public:
    ...
private:
    HomeForSale(const HomeForSale&);   //只有声明
    HomeForSale& operator=(const HomeForSale&);
};
```

进一步，可以使用noncopyable的基类方法来实现：

```cpp
class noncopyable
{
protected:
    noncopyable() {}
    ~noncopyable() {}
private:
    noncopyable(const noncopyable&);
    const noncopyable& operator=(const noncopyable&);
};

class HomeForSale :private（或public） noncopyable   //参考下面各种继承的区别
{
...
}
```

注意事项：

* 将成员函数声明为private而且故意不实现它们，以达到阻止copy的行为。

C++中公有继承、保护继承、私有继承的区别:

| 公有继承                 | 对象访问 | 成员访问 |
| ------------------------ | -------- | -------- |
| public    -->  public    | Y        | Y        |
| protected -->  protected | N        | Y        |
| private   -->  private   | N        | N        |
| 保护继承                 |          |          |
| public    -->  protected | N        | Y        |
| protected -->  protected | N        | Y        |
| private   -->  protected | N        | N        |
| 私有继承                 |          |          |
| public    -->  private   | N        | Y        |
| protected -->  private   | N        | Y        |
| private   -->  private   | N        | N        |

