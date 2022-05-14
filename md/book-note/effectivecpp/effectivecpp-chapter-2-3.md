#  第二章：构造/析构/赋值运算（三）

[[toc]]

# 区分接口继承和实现继承

```cpp
class Shape
{
public:
    virtual void draw() const = 0;
    virtual void error(const std::string& msg);
    int objectID() const;
    ...
};

class Rectangle : public Shape {...};
class Ellipse: public Shape {...};


class Airport {...};
class Airplane
{
public:
    virtual void fly(const Airport& destination);
};
void Airplane::fly(const Airport& destination)
{
    //缺省代码，将飞机飞至指定的目的地
}

class ModelA:public Airplane {...};
class ModelB:public Airplane {...};

Airplane::fly的缺省方法，可能被ModelA和ModelB同时使用，因此采用virtual方式进行抽象处理
void  ModelA::fly(const Airport& destination)
{
    Airplane::fly(destination); //也可以不用缺省代码
}

void  ModelB::fly(const Airport& destination)
{
    Airplane::fly(destination);//也可以不用缺省代码
}
```

如果继续定义ModelC，但是没有重新定义fly函数，将导致以ModelA或ModelB的飞行方式来飞ModelC,因此导致错误。

改进：

```cpp
class Airplane
{
public:
    virtual void fly(const Airport& destination)=0;
};

void Airplane::fly(const Airport& destination) //pure virtual函数实现
{
    //缺省代码，将飞机飞至指定的目的地
}

class ModelA:public Airplane 
{
public:
    virtual void fly(const Airport& destination)
    {
        Airplane::fly(destination);
    }
    ...
};

class ModelB:public Airplane 
{
public:
    virtual void fly(const Airport& destination)
    {
        Airplane::fly(destination);
    }
    ...
};

class ModelC:public Airplane 
{
public:
    virtual void fly(const Airport& destination)
    {
        //重写实现，将C飞机飞至指定的目的地
    }
    ...
};
```

## pure virtual

1. pure virtual函数draw使得Shape成为一个抽象class,因此不能直接创建Shape Class的实体，只能创建其derived classes的实体。

2. 声明pure virtual函数的目的是为了让derived classes只继承函数接口。此外特殊情况下，可以为Shape::draw提供一份实现代码，但调用的唯一途径是“调用时明确指出其class名称”，例如ps->Shape::draw(); 。（**pure virtual + 缺省实现的方式，用于derived classes必须重新实现该函数，避免导致不确定行为**）

## impure virtual

1. 声明简朴的impure virtual函数的目的，是为了让derived classes继承函数接口和缺省实现。

## non-virtual

1. 声明non-virtual函数的目的是为了令derived classes继承函数的接口及一份强制性实现。即任何derived classes都不应该尝试去改写non-virtual函数。

三者差异：只继承接口，或是继承接口和一份缺省实现，或是继承接口和一份强制实现。

# 复制对象时勿忘其每一个成分

如果自己定义copying函数（copy构造函数和copy assignment 操作符），需要注意每一次新增成员变量时，需要改动copy函数的实现以保证每个成员变量都得到复制。

注意事项：

1. Copying函数应该确保复制“对象内的所有成员变量”及“所有base class成分”；

2. 不要尝试以某个copying函数实现另外一个copying函数。应该把共同机能放到第三个函数中，并由两个copying函数共同调用。

​