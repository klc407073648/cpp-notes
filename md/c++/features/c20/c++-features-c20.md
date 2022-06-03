# C++11特性:bind和function函数使用

[[toc]]

## std::bind

std::bind 的函数原型: 

``` cpp
simple(1): 	
template <class Fn, class... Args>
  /* unspecified */ bind (Fn&& fn, Args&&... args);

with return type (2): 
template <class Ret, class Fn, class... Args>
  /* unspecified */ bind (Fn&& fn, Args&&... args);
```
作用: 返回基于fn的函数对象，但其参数绑定到args。

每个参数都可以绑定到一个值或占位符: 

* 如果绑定到一个值，则调用返回的函数对象将始终使用该值作为参数。
* 如果是一个占位符，则调用返回的函数对象会转发一个传递给调用的参数（该参数的顺序号由占位符指定）。

**使用std::bind要注意的地方**

1. bind预先绑定的参数需要传具体的变量或值进去，对于预先绑定的参数，是pass-by-value的。除非该参数被std::ref或者std::cref包装，才pass-by-reference。
2. 对于不事先绑定的参数，需要传std::placeholders进去，从_1开始，依次递增。placeholder是pass-by-reference的；
3. bind的返回值是可调用实体，可以直接赋给std::function对象； 
4. 对于绑定的指针、引用类型的参数，使用者需要保证在可调用实体调用之前，这些参数是可用的；
5. 类的this可以通过对象或者指针来绑定

测试程序: 

[bindTest.cpp](./src/functionAndbind/bindTest.cpp)

执行结果: 
```bash
[root@192 function和bind函数学习]# ./bindTest
fn_five(): 5
fn_half(10): 5
fn_invert(10,2): 0.2
fn_rounding(10,3): 3
bound_member_fn():ten_two.multiply() 20
bound_member_data():ten_two.a 10
bound_member_fn_add(30,50): 80
```

## std::function
 
`类模版std::function是一种通用、多态的函数封装`。std::function的实例可以对任何可以调用的目标实体进行存储、复制、和调用操作，这些目标实体包括`普通函数、Lambda表达式、bind表达式、函数指针以及其它函数对象`。std::function对象是对C++中现有的可调用实体的一种类型安全的包装（我们知道像函数指针这类可调用实体，是类型不安全的）。

通过std::function对C++中各种可调用实体（普通函数、Lambda表达式、函数指针、以及其它函数对象等）的封装，形成一个新的可调用的std::function对象；让我们不再纠结那么多的可调用实体。

测试程序: 

[functionTest.cpp](./src/functionAndbind/functionTest.cpp)

执行结果: 
```bash
[root@192 function和bind函数学习]# ./functionTest
fun1 add:15
fun2 sub():5
fun3 Lam:50
fun4 Math::div:2
fun5 Math::print_sum:15
```