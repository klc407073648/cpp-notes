# C++17特性

[[toc]]

# 参考资料

* [cpp17](https://en.cppreference.com/w/cpp/17)
* [C++17新特性总结](https://blog.csdn.net/weixin_42482896/article/details/118943564)

# 特性概览

![c++17_1](/_images/c++/features/c++17_1.png)

![c++17_2](/_images/c++/features/c++17_2.png)

![c++17_3](/_images/c++/features/c++17_3.png)

![c++17_4](/_images/c++/features/c++17_4.png)

# 折叠表达式

C++17中引入了折叠表达式，主要是方便模板编程，分为左右折叠，下图为其解包形式：

1) Unary right fold (E op ...) becomes (E1 op (... op (EN-1 op EN)))
2) Unary left fold (... op E) becomes (((E1 op E2) op ...) op EN)
3) Binary right fold (E op ... op I) becomes (E1 op (... op (EN−1 op (EN op I))))
4) Binary left fold (I op ... op E) becomes ((((I op E1) op E2) op ...) op EN)

<<< @/md/c++/features/c17/src/fold_expressions.cpp

运行结果:

<<< @/md/c++/features/c17/res/fold_expressions.txt

# 类模板参数推导

类模板实例化时，可以不必显式指定类型，前提是保证类型可以推导：

<<< @/md/c++/features/c17/src/class_template_arg_deduce.cpp

# auto占位的非类型模板形参

<<< @/md/c++/features/c17/src/auto_no_type.cpp

# 编译期constexpr if语句/constexpr的lambda表达式

lambda表达式可以在编译期进行运算，且函数体不能包含汇编语句、goto语句、label、try块、静态变量、线程局部存储、没有初始化的普通变量，不能动态分配内存，不能有new delete等，不能为虚函数。

<<< @/md/c++/features/c17/src/compile_time_if_constexpr.cpp

# 内联变量

扩展的inline用法，使得可以在头文件或者类内初始化静态成员变量:

<<< @/md/c++/features/c17/src/inline_variables.cpp

# 结构化绑定

在C++11中，如果需要获取tuple中元素，需要使用get<>()函数或者tie<>函数，这个函数可以把tuple中的元素值转换为可以绑定到tie<>()左值的集合。
C++17中的结构化绑定，大大方便了类似操作，而且使用引用捕获时，还可以修改捕获对象里面的值，代码也会简洁很多。

<<< @/md/c++/features/c17/src/structured_bindings.cpp

执行结果：

<<< @/md/c++/features/c17/res/structured_bindings.txt

# if，switch初始化

<<< @/md/c++/features/c17/src/if_switch_init.cpp

# 简化的嵌套命名空间

<<< @/md/c++/features/c17/src/simplified_nested_namespaces.cpp

# using声明语句可以声明多个名称

```cpp
using std::cout, std::endl;
```

# 新的求值顺序规则

<<< @/md/c++/features/c17/src/new_order_eva_rules.cpp

执行结果：

<<< @/md/c++/features/c17/res/new_order_eva_rules.txt

为了解决类似问题，C++17优化了求值顺序：

* 后缀表达式从左到右求值，包括函数调用和成员选择表达式；
* 赋值表达式从右向左求值，包括复合赋值；
* 从左到右计算移位操作符的操作数。

# 新增属性

https://blog.csdn.net/weixin_42482896/article/details/118943564

**还有疑问**

* [[fallthrough]]: switch语句中跳到下一条语句，不需要break，让编译器忽略告警;
* [[nodiscard]]: 所修饰的内容不可被忽略，主要用于修饰函数返回值：
* [[maybe_unused]]

<<< @/md/c++/features/c17/src/new_attributes.cpp

执行结果：

```cpp
[root@iZuf61kbf845xt6tz10abgZ c17]# ./new_attributes
result=2
result=0
5
2
```

# 库相关

* std::variant
  * C++17中提供了std::variant类型，意为多变的，可变的类型，类似于加强版的union，里面可以存放复合数据类型，且操作元素更为方便。
* std::optional
  * 该类型主要用于简化函数返回值的判断
* std::any
  * 在C++11中引入的auto自动推导类型变量大大方便了编程，但是auto变量一旦声明，该变量类型不可再改变。C++17中引入了std::any类型，该类型变量可以存储任何类型的值，也可以时刻改变它的类型，类似于python中的变量。
* tuple
  * std::apply
    * 将tuple元组解包，并作为函数的传入参数。
  * std::make_from_tuple
    * 解包tuple作为构造函数参数构造对象。
  * std::apply
    * 将tuple元组解包，并作为函数的传入参数。
* std::as_const
  * 将左值转化为const类型
* std::shared_mutex
  * 读写锁相关

<<< @/md/c++/features/c17/src/std_fun.cpp

执行结果：

```
[root@iZuf61kbf845xt6tz10abgZ c17]# ./std_fun                            
variant_fun
1
0
world, 3
optional_fun
1234
any_fun
i, 1
f, 2.2
f
next
NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, hello
tuple_fun
name: Jason, age: 25
5
9
as_const_fun
0
1

```