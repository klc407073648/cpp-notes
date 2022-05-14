# 第五章：实现（一）

[[toc]]

# 尽可能延后变量定义式的出现时间

只要你定义了一个变量而其类型带有一个构造函数或析构函数，那么当程序控制流到达这个变量定义式时，你便得承受构造成本；**当这个变量离开其作用域时，你便得承受析构成本。即使这个变量最终并未被使用，仍需耗费这些成本，所以你一个尽可能避免这种情形。**

V1:
```cpp
std::string encryptPasswd(const std::string& password)
{
    using namespace std;
    string encrypted;
    
    if(password.length() < MinmumPasswordLength)
    {
        throw logic_error("Password is too short");
    }
    ... //必要动作，能将一个加密后的密码置入变量encrypted内
    
    return encrypted;
}
```

如果encryptPasswd在检查密码长度时，抛出异常，就不会走到后续加密动作，应该延迟encrypted的定义。

V2:
```cpp
std::string encryptPasswd(const std::string& password)
{
    using namespace std;
    
    if(password.length() < MinmumPasswordLength)
    {
        throw logic_error("Password is too short");
    }
    string encrypted;
    ... //必要动作，能将一个加密后的密码置入变量encrypted内
    
    return encrypted;
}
```
encrypted虽获定义却无任何实参作为初值，因此会调用default构造函数。

* "通过default构造函数构造出一个对象然后对它赋值"比"直接在构造时指定初值"效率差。

V3:
```cpp
std::string encryptPasswd(const std::string& password)
{
    
    ... //检查length，如前
    std::string encrypted(password); //通过copy构造函数，定义并初始化
    encrypt(encrypted);  //加密函数
    return encrypted;
}
```

如果变量在循环内使用：

```cpp
//方法A:定义于循环外
Widget w;
for(int i=0;i<n;i++)
{
    w = 取决于i的某个值;
    ...
}

//方法B:定义于循环内
Widget w;
for(int i=0;i<n;i++)
{
    Widget w(取决于i的某个值);
    ...
}
```

* 做法A:1个构造函数+1个析构函数+n个赋值操作
* 做法B:n个构造函数+n个析构函数

1. 知道赋值成本比“构造和析构”成本低；
2. 正在处理代码中效率高敏感的部分。

满足以上两点，可以选择做法A，否则选择做法B

# 尽量少做转型动作

C++提供四种新式转型：

```cpp
const_cast<T>(expression)
dynamic_cast<T>(expression)
reinterpret_cast<T>(expression)
static_cast<T>(expression)
```

```cpp
class Window
{
public:
    virtual void onResize() {...}
    ...
};

class SpecicalWindow:public Window
{
public:
    virtual void onResize() 
    {
        static_cast<Window>(*this).onResize();//调用的是*this对象之base class成分的暂时副本身上的onResize函数。
    }
    ...
};
```

应该这样写：

```cpp
class SpecicalWindow:public Window
{
public:
    virtual void onResize() 
    {
        Window::onResize();//调用Window::onResize作用于*this身上
        ...
    }
    ...
};
```

# 避免返回handles指向对象内部成分

reference、指针和迭代器都是所谓的handles(号码牌，用来取得某个对象)，而返回一个“代表对象内部的数据”的handle，随之而来的便是“降低对象封装性”的风险。

```cpp
Method& getMethod() const
{
    return method;
}
```

//getMethod()返回的Method可以修改，从而导致封装性被破坏。

进一步改进:

```cpp
const Method& getMethod() const
{
    return method;
}
```

有可能存在dangling handles(空悬的号码牌)：这种handles所指东西不复存在。

```cpp
const Rectangle boundingBox(const GUIobject& obj);
...
GUIobject* pgo;
const Ponit* pUpperLeft = &(boundingBox(*pgo).upperLeft());
//reference指向了一个临时变量temp的内部成分，但是temp在boundingBox函数返回时被销毁，导致pUpperLeft指向对象不存在
```