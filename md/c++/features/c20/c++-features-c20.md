# C++ 新版本特性 - C++20

[[toc]]

::: danger
C++20下面的代码未在环境上编译测试使用，仅用于理论知识补充，后期升级gcc版本再进行实测。
:::

# 参考资料

* [cpp20](https://en.cppreference.com/w/cpp/20)

# 特性概览

![c++20_1](/_images/c++/features/c++20_1.png)

![c++20_2](/_images/c++/features/c++20_2.png)

![c++20_3](/_images/c++/features/c++20_3.png)

# The Big Four

## Concepts

C++中模板编程极大地简化了代码的编写，但同时也会带来一些使用上的疑惑,例如，判断两个数是否相等，C++17提供了concept机制，用来检查模板参数类型：

<<< @/md/c++/features/c20/src/concept.cpp

## Range library

**ranges**：代表一段元素，之前版本使用begin和end标识一段元素。

ranges优点:

* 简化语法和操作；
* 防止begin，end迭代器的不配对使用；
* 使得类似管道|的串行操作成为可能。

相关概念：

* View：延迟计算，只有读权限
* Actions：即时处理，读或写
* Algorithms：操作range
* Views和Actions的串联操作

<<< @/md/c++/features/c20/src/range_library.cpp

## Coroutines

所谓协程，是一个函数，能在保持状态的时候暂停或者继续。具有关键字：

* co_await：挂起协程，等待其它计算完成
* co_return：退出协程
* co_yield：弹出一个值，挂起协程，等待下一次调用，类似于Python中的生成器

待补充内容

## Modules

关键字：import，export

新建测试文件test_module.ixx和main.cpp，注意模块文件后缀名为.ixx，如果为.cpp文件可能需要去命令行编译，使用方式和include差不多，但是说使用模块比使用include效率要高很多：

<<< @/md/c++/features/c20/src/modules.cpp

模块优势：

* 没有头文件
* 声明和实现仍然可以分离，但没有必要
* 可以显式指定导出目标对象（函数，类）
* 没有头文件重复包含风险
* 模块名称可以相同
* 模块只处理一次，编译更快（头文件每次引入都需要处理）
* 预处理宏只在模块内有效
* 模块引入顺序无关紧要

# Core Language

## 特性测试宏

通过它可以判断编译器是否支持某个功能，例如：

```cpp
// 语言特性
__has_cpp_attribute(fallthrough)
__cpp_binary_literals
__cpp_char8_t
__cpp_coroutines
// 标准库特性
__cpp_lib_concepts
__cpp_lib_ranges
__cpp_lib_scoped_lock
```

## 三路比较运算符<=>

```cpp
(x <=> y) < 0 // 如果 x < y, 返回 true
(x <=> y) > 0 // 如果 x > y, 返回 true
(x <=> y) == 0 // 如果 x == y, 返回 true
```

可以使用以下代码代替所有的比较运算符：

```cpp
auto X::operator<=>(const X&) = default;
```

## 范围for循环初始化

```cpp
class Data {
public:
  Data(){}
  Data getData() { return Data(); }
private:
  std::vector<int> values;
};

int main() {
  for (auto data = getData(); auto &value : data.values) {
    cout << value << " ";
  }

  return 0;
}

```

# 待补充