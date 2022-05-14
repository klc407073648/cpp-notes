# 第四章：设计与声明（二）

[[toc]]

# 必须返回对象时，别妄想返回其reference

```cpp
class Rational
{
public:
    Rational(int numerator=0,int deominator = 1);
    ...
private:
    int n,d;
    friend const Rational operator*(const Rational& lhs,const Rational& rhs);
}
```

函数创建新对象可以在stack空间或heap空间创建。

stack空间:

```cpp
const Rational operator*(const Rational& lhs,const Rational& rhs)
{
    Rational  result(lhs.n*rhs.n, lhs.d*rhs.d); 
    return result;
}
```

注意：**任何函数如果返回一个reference指向某个local对象，而local对象回在函数退出前被销毁，因此返回值无效。**（返回一个指针指向某个local对象也是同理）

heap空间:

```cpp
const Rational& operator*(const Rational& lhs,const Rational& rhs)
{
    Rational*  result = new Rational(lhs.n*rhs.n, lhs.d*rhs.d); 
    return *result;
}
```

注意：何时调用delete函数释放申请的heap空间？

正确写法：

```cpp
inline const Rational operator*(const Rational& lhs,const Rational& rhs)
{
    return Rational(lhs.n*rhs.n, lhs.d*rhs.d); 
}
```

# 将成员变量声明为private

注意事项：

1. 将成员变量声明为private。这可赋予客户访问数据的一致性、可细微划分访问控制、允许约束条件获得保证，并提供clss作者以充分的弹性。（将成员变量隐藏在函数接口的背后，可以为“所有可能的实现”提供弹性；只读访问、读写访问函数；class约束条件获得维护，因为只有成员函数可以影响它们；）

2. protected并不比public更具封装性。

3. 其实只有两种访问权限：private(提高封装)和其他（不提供封装）。

# 宁以non-member、non-friend替换member函数

声明成员变量为private能保证只有class的member函数加上friend函数可以访问它们。因此，在一个member和一个non-member，non-friend函数都能提供相同函数功能的情况下，**应该优先选用non-member，non-friend函数，因为它并不增加“能够访问class内之private成分”的函数数量，所以较好的维持了class的封装性。**

例如，WebBrowser类中已经实现了清理缓存，历史记录以及cookies的操作，可以创建一个non-member,no-friend函数并且位于WebBrowser所在的同一个namespace内，即实现了用户可以扩展自定义的函数。

```cpp
//WebBrowser.h
namespace  WebBrowserStuff{

class WebBrowser
{
    public:
        WebBrowser();
        ~WebBrowser();
		
		void clearCache();
		void clearHistory();
		void removeCookies();
    private:
        
};

} 
```

```cpp
//WebBrowserClear.h
namespace  WebBrowserStuff{

class WebBrowser;

void clearBrowser(WebBrowser& wb)
{
	wb.clearCache();
	wb.clearHistory();
	wb.removeCookies();
}


} //WebBrowserStuffs
```