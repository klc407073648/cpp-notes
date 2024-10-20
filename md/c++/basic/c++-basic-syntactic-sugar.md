# C++ 基础 - 语法糖

# 概念

语法糖（Syntactic Sugar），也译为糖衣语法，是一种编程语言的设计概念，指的是一种**语法结构或编码风格**，它在语法上提供了更简洁、更易读的方式来表达某个特定的操作或概念，但在底层实现上仍使用了相对复杂的语法规则或操作。

语法糖并不会引入新的功能或概念，它只是在现有的语言中提供了一种更方便、更直观的表达方式，以减少程序员的编码工作量和提高代码可读性。

# 特点

* **简洁性**：语法糖通过简化语法结构或编码方式，减少了代码的复杂性和冗余性，使代码更易于理解和编写。
* **可读性**：语法糖通常使代码更加自然、直观，更符合人类的思维方式，提高了代码的可读性和可维护性。
* **隐藏细节**：语法糖可以隐藏底层复杂的操作或实现细节，使得使用者无需关心具体的实现细节，只需关注高层的逻辑或目标。
* **语法糖与语义等价**：虽然语法糖在语法上提供了更简洁的表达方式，但它们在底层的语义上与原始的语法结构是等价的，即它们执行相同的操作或实现相同的功能。

# 应用

语法糖在编程语言中被广泛应用，常见的示例包括：

* **迭代器（Iterators）**：提供了遍历容器元素的简洁方式，如C++中的基于范围的 for 循环range-based-for。
* **Lambda 表达式（Lambda Expressions）**：提供了一种更简洁、更灵活的定义匿名函数的方式。
* **自动类型推导（Type Inference）**：编译器根据上下文推断变量的类型，减少了显式类型声明的需要。
* **操作符重载（Operator Overloading）**：允许对操作符进行自定义定义，使其适用于用户定义的类型。
* **属性访问器（Property Accessors）**：通过简洁的语法实现属性的读取和设置操作。

总结： 语法糖是一种在编程语言中提供的便利性语法结构，通过简化和优化代码的编写方式，用更简练的言语表达较复杂的含义，提高了代码的可读性和可维护性，使编程更加高效。

https://zhuanlan.zhihu.com/p/621666482

闭包函数传递
atomic thread_local  TODO

# 使用

* **引用**：用于引用其他变量的内存地址，避免了直接操作指针的复杂性和不安全性，同时也使得代码更加简洁和易读。

::: details
```cpp
void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}
```
::: 


* **函数重载**：通过函数重载来定义多个同名函数，它们的参数列表不同，能够更方便地调用不同类型的函数。

::: details
```cpp
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}
```
::: 

* **运算符重载**：通过运算符重载来对C++内置的运算符进行重新定义，使得运算符能够适用于自定义类型。

::: details
<<< @/md/c++/basic/src/Complex.cpp
::: 

* **类和对象**：是一种封装数据和行为的方式，可以将数据和行为组织成一个对象，更加方便地使用。

* **模板**：允许编写通用代码来处理多种类型和数据结构。通过使用模板，程序员可以在编写代码时避免大量的复制和粘贴操作，从而提高代码的可读性和可维护性。

* **STL容器**：C++标准库中提供了许多容器，如vector、map、list等，可以更方便地操作数据结构。

* **智能指针**：可以自动管理动态内存，避免内存泄漏等问题，使得程序更加安全可靠。

* **Lambda表达式**：C++11中引入了Lambda表达式，可以方便地定义匿名函数，使得程序更加简洁和易读。

* **constexpr**：constexpr是一种编译时常量表达式，它允许在编译时计算表达式的值，并在编译期间进行常量优化，从而提高程序的性能。

::: details
<<< @/md/c++/basic/src/constexpr.cpp
::: 

* **range-based for循环**：提供了一种更加简洁的遍历数组、容器、以及其他可以遍历的数据结构的方法。

::: details
<<< @/md/c++/basic/src/range_based_for.cpp
::: 

* **模板元编程**：利用模板进行计算的技术，可以在编译时执行某些计算，以获得更高效的代码或者更好的抽象能力。它通过使用模板的特殊化、递归和constexpr函数等特性来实现。(模板编程是利用C++模板生成通用代码的技术，主要用于在运行时处理类型和值。模板元编程是在编译期间利用C++模板进行计算和生成代码，主要用于在编译时处理类型和进行静态计算。)

::: details
<<< @/md/c++/basic/src/template_meta.cpp
::: 

* **const关键字**：可以用于修饰变量、函数参数、函数返回值等，使得程序更加安全和可靠。

* **static关键字**：可以用于修饰类的成员变量和成员函数，使得这些成员可以在不创建对象的情况下被访问。

* **friend关键字**：C++中的friend关键字可以用于授权其他类或函数访问本类的私有成员，使得程序更加灵活和方便。

* **namespace命名空间**：C++中的namespace命名空间可以将相关的函数、变量、类等组织到一个命名空间中，使得程序更加清晰和易读。

* **using关键字**：C++中的using关键字可以用于定义别名、引入命名空间等，使得程序更加简洁和易读。

* **explicit关键字**：C++中的explicit关键字可以用于**限制类型转换**，使得程序更加安全和可靠。

::: details
<<< @/md/c++/basic/src/explicit.cpp
::: 

* **override关键字**：用来修饰派生类中覆盖基类虚函数的成员函数，表示该成员函数必须是虚函数，且必须和基类函数具有相同的函数签名。

::: details
<<< @/md/c++/basic/src/override.cpp
::: 

* **final关键字**：用于修饰类、虚函数，表示它们不能被继承或重写。

::: details
<<< @/md/c++/basic/src/final.cpp
::: 

* **thread_local关键字**：用于定义线程局部变量，即每个线程拥有一份独立的变量副本，互不干扰。这在多线程编程中非常有用，可以避免因多个线程之间共享变量而导致的线程安全问题。

::: details
<<< @/md/c++/basic/src/thread_local.cpp
::: 

* **move语义**：它通过将资源所有权从一个对象转移到另一个对象来实现内存拷贝的最小化。

::: details
<<< @/md/c++/basic/src/move.cpp
::: 

* **noexcept关键字**：noexcept关键字可以放在函数声明和函数定义的括号后面，表示该函数不会抛出任何异常。

::: details
```cpp
void myFunction() noexcept {
    cout << "Function called" << endl;
}
```
::: 

* **lambda表达式**：可以方便地定义匿名函数，使得程序更加简洁和易读。

* **nullptr关键字**：用于代替旧的C++版本中使用的NULL宏定义或0指针常量，以表示空指针。

* **initializer_list**：使用initializer_list可以更加简洁地初始化数组、容器或者其他数据结构，也可以方便地作为函数参数传递列表。

::: details
<<< @/md/c++/basic/src/initializer_list.cpp
::: 

* **constexpr函数**：C++11中引入了constexpr函数，可以在编译时计算出结果，使得程序更加高效。

* **user-defined literals**：C++11中引入了user-defined literals，称为用户自定义字面量（user-defined literals），它允许程序员定义自己的字面量后缀，以扩展现有的字面量语法。

::: details
<<< @/md/c++/basic/src/user_defined_literals.cpp
::: 

* **uniform initialization**：用一种简洁明了的方式初始化各种类型的对象。在传统的初始化语法中，可能需要使用圆括号、花括号或等号，而**uniform initialization语法糖只需要用一对花括号**即可。

* **std::optional**：C++17中引入了std::optional，提供了一种简洁而直观的方式来表示一个值可能存在或不存在的情况，避免了使用空指针的问题，使得程序更加安全和可靠。

::: details
<<< @/md/c++/basic/src/optional.cpp
::: 

* **if constexpr**：C++17中引入了if constexpr语句，可以在编译时选择不同的代码分支，使得程序更加灵活和高效。

* **std::variant**：C++17 中引入的一个新类模板，它可以存储一组类型中的任意一个，并且能够在运行时进行类型检查和转换。

::: details
<<< @/md/c++/basic/src/variant.cpp
::: 

* **std::any**：C++17引入了std::any库，它是一种类型安全的容器，可以存储任意类型的数据。与void*不同，std::any可以检查是否存储了值，并且可以安全地检索和转换存储的值。

::: details
<<< @/md/c++/basic/src/any.cpp
::: 

* **std::string_view**：C++17引入了std::string_view库，它是一种轻量级的字符串视图，用于表示字符串的非拥有者视角。与std::string不同，std::string_view并不拥有字符串的所有权，而是将其作为一个指针和大小的组合视图。

::: details
<<< @/md/c++/basic/src/string_view.cpp
::: 

* **structured bindings**：C++17中引入了structured bindings，它提供了一种方便的方式来将复杂的数据类型解包成多个变量。它使得代码更加简洁、易读，减少了代码的重复性。

::: details
<<< @/md/c++/basic/src/structured_bindings.cpp
::: 

* **inline变量**：内联变量允许我们在头文件中定义变量，而无需担心多重定义错误。它的工作方式类似于内联函数，可以将定义和声明放在同一个头文件中，而不需要在每个使用该变量的源文件中重复声明。避免了多个编译单元之间的链接问题，使得程序更加灵活。

* **constexpr lambda**：C++20中引入了constexpr lambda，可以定义编译时计算的lambda表达式，使得程序更加高效和灵活。

* **concepts**：C++20中引入了concepts，可以定义泛型代码的约束条件，使得程序更加健壮和易读。

* **spaceship operator**：C++20中引入了spaceship operator，可以定义自定义类型之间的比较操作，使得程序更加灵活和易读。

::: details
<<< @/md/c++/basic/src/spaceship_operator.cpp
::: 

* **std::atomic_ref**：C++20中引入了std::atomic_ref，用于对共享变量进行原子操作，可以避免使用原子变量的开销，提高程序的效率。

* **coroutine**：C++20中引入了coroutine，可以方便地实现协程，使得程序更加高效和灵活。
* **std::span**：C++20中引入了std::span，用于表示连续的内存空间，可以方便地操作数组和容器，提高了程序的效率。
* **std::format**：C++20中引入了std::format，用于格式化字符串，避免了使用printf的安全性问题，使得程序更加安全和易读。
* **consteval函数**：C++20中引入了consteval函数，可以在编译时计算出结果，与constexpr函数类似，但更加严格和高效。
* **std::bit_cast**：C++20中引入了std::bit_cast，用于进行类型间的位拷贝，避免了使用memcpy的安全性问题，使得程序更加安全和高效。
* **requires表达式**：C++20中引入了requires表达式，可以用于定义函数和类的约束条件，使得程序更加健壮和易读。
* **std::stop_token**：C++20中引入了std::stop_token，用于取消异步操作，避免了使用回调函数的复杂性问题，使得程序更加简洁和易读。
* **std::synchronized**：C++20中引入了std::synchronized，用于实现线程安全的操作，避免了使用锁的复杂性问题，使得程序更加灵活和易读。
* **co_await表达式**：C++20中引入了co_await表达式，用于等待协程的完成，使得程序更加高效和灵活