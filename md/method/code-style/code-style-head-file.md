# 编码规范 - 头文件包含规范

[[toc]]

# C/C++头文件包含规范

## Self-contained 头文件自包含

* 所有头文件要能够自给自足，即头文件需要包含**本身依赖**的其他头文件。
* 换言之，用户和重构工具不需要为特别场合而包含额外的头文件。

## 头文件中尽量减少对其他头文件的依赖

* 头文件包含另一个头文件的同时会引入一项新的依赖(dependency)，这个依赖也会随着该头文件的被包含而扩散出去，从而导致**依赖扩散**。

* 只要头文件被修改，代码就要重新编译，如果你的头文件包含了其它头文件，**这些头文件的任何改动都将导致那些包含了你的头文件的代码重新编译**。

### 多余的头文件包含

* 头文件包含必须遵循最少必要原则，尽量少包含。
* 能包含小的头文件，不包含大的头文件。
* 及时清理不需要的头文件包含，不能只增不删。

### 可以在source文件包含的，不要包含着头文件中

例如，Test.h头文件以及对应Test.cpp文件。

Test.h只要包含改头文件所依赖的其他头文件，不能将Test.cpp所需要用到的头文件全都放在Test.h中。

### 头文件仅声明，不作实现

如果头文件里包含函数实现，在其他多个源文件中使用include方式包含时，会提示多重定义(multiple definition)

### 头文件是只包含必要的声明

* 不是所有函数实现都需要在头文件中声明，只声明需要发布的函数接口。

* 私有函数不在头文件中声明，从而减少头文件的依赖。例如，某些工具类方法可以声明和实现在.cpp函数的类外。

### define 保护

* 所有头文件都应该使用 #define 来防止头文件被多重包含, 命名格式例如: 

```cpp
#ifndef Data_MySQL_MySQLException_INCLUDED
#define Data_MySQL_MySQLException_INCLUDED
```

### 使用前置声明(forward declarations)

* 「前置声明」（forward declaration）是类、函数和模板的纯粹声明，没伴随着其定义. 

看法一：

* 尽可能地避免使用前置声明。使用 #include 包含需要的头文件即可。 
* 前置声明隐藏了依赖关系，头文件改动时，用户的代码会跳过必要的重新编译过程。

看法二：

* 通过前置声明的方式，减少头文件中依赖的其他头文件。将头文件的包含动作延迟到源文件中去实现。

* 使用场景：头文件只用到对应内容的指针或引用不涉及具体内容。或用到一个结构体声明，但不想包一个很大的头文件将依赖扩散。（struct Foo;在源文件中#include <Foo.h>）

可以参考：[C++前置声明](/md/c++/tips/c++-tips-forward-declaration.md)

## 避免错误依赖和反向依赖

* 包含每个头文件时，需要分析是不是合适的依赖，避免包含错误的头文件，导致其依赖的其他头文件项变多。

```cpp
//log.h

#include<logType.h>
#include<logTime.h>

//不应该包含项
#include<message.h>
#include<httpType.h>
```

## 尽可能将代码拆分成相对独立的，粒度小的单元，放到不同的文件中

* 不能使得一个类代码很臃肿，包含特别多的功能，不方便维护。

* 通过拆分成小的，独立的模块更利于维护。

## 包含头文件顺序

头文件Test.h和源文件Test.cpp，对应的头文件包含顺序都需要满足：

1. Test.h （如果自己定义的头文件有错，编译时会提前暴露自身的错误而不是其他库的。）
2. 本项目内的.h文件
3. 其它库的.h文件
4. C系统文件
5. C++系统文件

没有唯一的标准，都是适合自己的习惯，google C++ 头文件顺序：

1. 主体功能文件（这一条规则保证维护这些文件的人们首先看到构建中止的消息而不是维护其他包的人们。）
2. C系统文件
3. C++系统文件
4. 其它库的.h文件
5. 本项目内的.h文件

## 包含头文件时，使用源码的目录树结构，不使用相对路径

使用源码的目录树结构，而不是相对路径：

* 为保证唯一性, 头文件的命名应该基于所在项目源代码树的全路径

* #include <drogon/orm/Result.h>  √
* #include <../../Result.h>       ×

## 头文件中不允许使用using namespace XXX·措施

* 头文件使用 `using namespace XXX` 会破坏 namespace 的封装性
* 因为头文件会被包含在其他的头文件和cpp文件中。导致C++编译器将头文件字符串直接拷贝，强制其他的头文件也使用 `using namespace XXX`,从而引起编译错误，或者使用错误的类型，造成麻烦。

```cpp
//正例
namespace HttpProxy{
    using Poco::ByteOrder;
    using Poco::UInt16;
}

// 反例

namespace HttpProxy{
    using namespace Poco;
}
```


# 保证措施

* 代码扫描工具识别多余包含
* Code Review发现头文件包含是否规范