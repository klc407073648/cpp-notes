# Tools - GCC警告选项

[[toc]]

# 参考

* [gcc警告选项汇总](https://blog.csdn.net/qq_17308321/article/details/79979514)
* [gcc 优化选项原文](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#Optimize-Options)

# GCC警告选项

警告：不是错误的，但是有风险或表明可能有错误。

英文原文：Warning Options - Using the GNU Compiler Collection (GCC)

加上-Wall吧，gcc 默认不加参数的情况下 连定义了返回值的函数没有返回值都不报错。

## 开启和关闭告警方法

1. <font color='red'>**-w （小写）禁止所有警告消息。**</font>

2. <font color='red'>**以“-W”(大写）开头开启特定的警告。**</font>

例如：

- Wreturn-type(返回值告警),
- Wsign-compare（有符号和无符号对比告警）
- Wall (除extra外的所有告警)
- Wextra (all外的其他告警)

如 `gcc -Wall test.c -o test`

3. 以“-Wno-”开头关闭特定的警告;

例如：

-Wno-return-type （取消返回值告警）
-Wno-sign-compare（取消有符号和无符号对比告警）

如： `gcc -Wall -Wno-unused test.c -o test `

## 批量开启告警（即-Wall和-Wextra 批量开启的告警）

某些选项（如-Wall和-Wextra ）会打开其他选项，例如-Wunused ，这可能会启用其他选项，例如-Wunused-value 。

### -Wall 

该选项相当于同时使用了下列所有的选项：

```
* unused-function：遇到仅声明过但尚未定义的静态函数时发出警告。
* unused-label：遇到声明过但不使用的标号的警告。
* unused-parameter：从未用过的函数参数的警告。
* unused-variable：在本地声明但从未用过的变量的警告。
* unused-value：仅计算但从未用过的值得警告。
* Format：检查对printf和scanf等函数的调用，确认各个参数类型和格式串中的一致。
* implicit-int：警告没有规定类型的声明。
* implicit-function-：在函数在未经声明就使用时给予警告。
* char-subscripts：警告把char类型作为数组下标。这是常见错误，程序员经常忘记在某些机器上char有符号。
* missing-braces：聚合初始化两边缺少大括号。
* Parentheses：在某些情况下如果忽略了括号，编译器就发出警告。
* return-type：如果函数定义了返回类型，而默认类型是int型，编译器就发出警告。同时警告那些不带返回值的 return语句，如果他们所属的函数并非void类型。
* sequence-point：出现可疑的代码元素时，发出报警。
* Switch：如果某条switch语句的参数属于枚举类型，但是没有对应的case语句使用枚举元素，编译器就发出警告（在switch语句中使用default分支能够防止这个警告）。超出枚举范围的case语句同样会导致这个警告。
* strict-aliasing：对变量别名进行最严格的检查。
* unknown-pragmas：使用了不允许的#pragma。
* Uninitialized：在初始化之前就使用自动变量。
```

（不要被它的表面意思迷惑，下面是使用-Wall选项的时候没有生效的一些警告项,而且还有-Wextra）

```
* cast-align：一旦某个指针类型强制转换时，会导致目标所需的地址对齐边界扩展，编译器就发出警告。例如，某些机器上只能在2或4字节边界上访问整数，如果在这种机型上把char *强制转换成int *类型， 编译器就发出警告。
* sign-compare：将有符号类型和无符号类型数据进行比较时发出警告。
* missing-prototypes ：如果没有预先声明函数原形就定义了全局函数，编译器就发出警告。即使函数定义自身提供了函数原形也会产生这个警告。这样做的目的是检查没有在头文件中声明的全局函数。
* Packed：当结构体带有packed属性但实际并没有出现紧缩式给出警告。
* Padded：如果结构体通过充填进行对齐则给出警告。
* unreachable-code：如果发现从未执行的代码时给出警告。
* Inline：如果某函数不能内嵌（inline），无论是声明为inline或者是指定了-finline-functions 选项，编译器都将发出警告。
* disabled-optimization：当需要太长时间或过多资源而导致不能完成某项优化时给出警告。
```

上面是使用-Wall选项时没有生效，但又比较常用的一些警告选项。

### -Wextra

但不要被-Wall的名字迷惑，它并没有开启所有告警，**-Wextra用于启用一些未由-Wall启用的额外警告标志。**

```
-Wclobbered  
-Wcast-function-type  
-Wempty-body  
-Wignored-qualifiers  如果函数的返回类型具有类型限定符（如const ，则发出警告。 对于ISO C这样的类型限定符没有效果，因为函数返回的值不是左值。 对于C ++来说，警告只是针对标量类型或void发出的。 ISO C禁止在函数定义上使用合格的void返回类型，所以这种返回类型总是会在没有这个选项的情况下收到警告。
-Wimplicit-fallthrough=3 
-Wmissing-field-initializers  
-Wmissing-parameter-type (C only)  
-Wold-style-declaration (C only)  
-Woverride-init  
-Wsign-compare (C only) 
-Wtype-limits   由于数据类型范围有限而导致比较始终为真或始终为false，但不警告常量表达式。例如，警告如果将一个无符号变量与<或与0进行比较>=
-Wuninitialized  
-Wshift-negative-value (in C++03 and in C99 and newer)  
-Wunused-parameter (only with -Wunused or -Wall) 
-Wunused-but-set-parameter (only with -Wunused or -Wall)  
```

选项-Wextra还会打印以下情况的警告消息：

  指针与整数零与< ， <= ， >或>= 。
（仅限C ++）枚举器和非枚举器都出现在条件表达式中。
（仅限C ++）不明确的虚拟基础。
（仅限C ++）为已声明为register的数组下标。
（仅限C ++）取得已声明register的变量的地址。
（仅限C ++）基类不在派生类的复制构造函数中初始化。
 

## 将告警转为错误

-Werror ：所有告警当错误报

将所有的警告当成错误进行处理。**一旦加上有警告就编译不通过。除非特别严格，一般不会使用。**

-Werror=  将指定的警告转换为错误。

Format：检查对printf和scanf等函数的调用，确认各个参数类型和格式串中的一致。

```
printf("%d %d", 1);
error: format '%d' expects a matching 'int' argument [-Werror=format]
```

反过来：

-Wno-error取消编译选项-Werror

实例2：

```
假设我们使用了一个人的代码A目录，里面有一个-Werror的选项，把所有的警告当做错误；又使用了另一个人的代码B目录，里面存在一堆Warning。这样，当我们把它们合在一起编译的时候，A中的-Werror选项会导致B的代码编译不过。但我们又不想去修改B的代码，怎么办？
方法是，先add_subdirectory(A)，之后，加上一句
set(CMAK_CXX_FLAGS "${CMAK_CXX_FLAGS} -Wno-error")
-Wno-这个前缀，就是用来取消一个编译选项的
然后，再add_subdirectory(B)
```

## 其他告警项

-Wfatal-errors 发生第一个错误时中止编译

在发生第一个错误时中止编译。

-Wchkp

警告由指针界限检查器（ -fcheck-pointer-bounds ）发现的无效内存访问。

-Wno-coverage-mismatch

如果使用-fprofile-use选项时反馈配置文件不匹配，则警告 。 如果在使用-fprofile-gen编译和使用-fprofile-use编译时源文件发生更改，则具有配置文件反馈的文件可能无法与源文件匹配，并且GCC无法使用配置文件反馈信息。 默认情况下，此警告已启用并被视为错误。 -Wno-coverage-mismatch可用于禁用警告或-Wno-error = coverage-mismatch可用于禁用该错误。 禁用此警告的错误可能会导致代码质量不佳，并且仅在非常小的更改情况下才有用，例如修复现有代码库的错误。 不建议完全禁用该警告。

-Wno-cpp 禁止#warning指令发出的警告消息。

（仅限于Objective-C，C ++，Objective-C ++和Fortran）

禁止#warning指令发出的警告消息。

-Wshadow
当一个局部变量遮盖住了另一个局部变量，或者全局变量时，给出警告。很有用的选项，建议打开。 -Wall 并不会打开此项。

-Wpointer-arith
对函数指针或者void *类型的指针进行算术操作时给出警告。也很有用。 -Wall 并不会打开此项。

-Wcast-qual
当强制转化丢掉了类型修饰符时给出警告。 -Wall 并不会打开此项。

-Waggregate-return
如果定义或调用了返回结构体或联合体的函数，编译器就发出警告。

-Winline
无论是声明为 inline 或者是指定了-finline-functions 选项，如果某函数不能内联，编译器都将发出警告。如果你的代码含有很多 inline 函数的话，这是很有用的选项。

-Wundef
当一个没有定义的符号出现在 #if 中时，给出警告。

-Wredundant-decls
如果在同一个可见域内某定义多次声明，编译器就发出警告，即使这些重复声明有效并且毫无差别。

-Wstrict-prototypes
如果函数的声明或定义没有指出参数类型，编译器就发出警告。很有用的警告。

-Wctor-dtor-privacy （C++ only）
当一个类没有用时给出警告。因为构造函数和析构函数会被当作私有的。

-Wnon-virtual-dtor（C++ only）
当一个类有多态性，而又没有虚析构函数时，发出警告。-Wall会开启这个选项。

-Wreorder（C++ only）
如果代码中的成员变量的初始化顺序和它们实际执行时初始化顺序不一致，给出警告。

-Wno-deprecated（C++ only）
使用过时的特性时不要给出警告。

-Woverloaded-virtual（C++ only）
如果函数的声明隐藏住了基类的虚函数，就给出警告。

-Winit-self (C, C++, Objective-C and Objective-C++ only)
警告使用自己初始化的未初始化变量。 请注意，此选项只能与-Wuninitialized选项一起使用。


# GCC编译选项

- static: 在支持动态链接的系统上，阻止连接共享库。该选项在其它系统上无效。

- nostdlib: 不连接系统标准启动文件和标准库文件，只把指定的文件传递给连接器。

## 优化项|优化等级

* -O0禁止编译器进行优化。默认为此项。
* -O1尝试优化编译时间和可执行文件大小。
* -O2更多的优化，会尝试几乎全部的优化功能，但不会进行“空间换时间”的优化方法。
* -O3在 -O2 的基础上再打开一些优化选项：-finline-functions， -funswitch-loops 和 -fgcse-after-reload 。
* -Os对生成文件大小进行优化。它会打开 -O2 开的除了会那些增加文件大小的全部选项。
