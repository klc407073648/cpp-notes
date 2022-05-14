# 第七章：模板与泛型编程

[[toc]]

# 了解隐式接口和编译期多态

```cpp
class Widget
{
public:
    Widget();
    virtual ~Widget();
    virtual std::size_t size() const;
    virtual void normalize();
    void swap(Widget& other)
}

class doProcessing(Widget& w)
{
    if(w.size() > 10 && w != someNastyWidget)
    {
        Widget temp(w);
        temp.normalize();
        temp.swap(w);
    }
}
```

上述doProcessing函数体现了显示接口和运行期多态。

```cpp
template<typename T>
class doProcessing(T& w)
{
    if(w.size() > 10 && w != someNastyWidget)
    {
        T temp(w);
        temp.normalize();
        temp.swap(w);
    }
}
```

T必须支持一组隐式接口，且以不同的template参数具体化会导致调用不同的函数，这就是编译期多态。
“哪一个重载函数被调用”（编译期）和“哪一个virtual函数被绑定”（运行期）

注意事项：

1. classes和templates都支持接口和多态。
2. 对class而言接口是显示的，以函数签名为中心。多态则是通过virtual函数发生在运行期。
3. 对template参数而言，接口是隐式的，奠基于有效表达式。多态则是通过template具体化和函数重载解析发生于编译期。

# 了解typename的双重意义

```cpp
template<typename C>
void print2nd(const C& container)
{
    if(container.size()>=2)
    {
        C::const_iterator iter(container.begin());
        iter++;
        int value = *iter;
        std::cout << value;
    }

}
```
C::const_iterator 是嵌套从属名称；
int 是谓非从属名称。
C++默认规则是，若解析器在template中遇到嵌套从属名称，它便假设这个名称不是个类型。
需要用户添加typename，表示它是个类型。例如

```cpp
typename C::const_iterator iter(container.begin());

template<typename T>
class Derived: public Base<T>::Nested
{
public:
    explicit Derived(int x)
    :Base<T>::Nested(x)
    if(container.size()>=2)
    {
        typename Base<T>::Nested temp;
        ...
    }
}
```

基类列和成员初值列不能加typename 关键字

注意事项：

1. 声明template参数时，前缀关键字class和typename可互换；
2. 请使用关键字typename标识嵌套从属类型名称；但不得在base class lists（基类列）或member initialization list(成员初值列)内以它作为base class 修饰符。

# 将与参数无关的代码抽离template
​