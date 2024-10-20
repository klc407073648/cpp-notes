# 第4章 静态链接

[[toc]]

# 文章总结

![](/_images/book-note/linkersAndLoaders/静态链接.png)

# 概述

使用下面这两个源代码文件“a.c”和“b.c”作为例子展开分析：

![](/_images/book-note/linkersAndLoaders/a和b模块.png)

假设我们的程序只有这两个模块“a.c”和“b.c”。首先使用gcc将"a.c”和“b.c”分别编译成目标文件"a.o”和"b.o”：

`gcc -c a.c b.c`

经过编译以后就得到了“a.o”和“b.o”这两个目标文件。从代码中可以看到，总共定义了两个全局符号，一个是变量“shared”，另外一个是函数"swap；“a.c”里面定义了一个全局符号就是“main”。模块“a.c”里面引用到了“b.c”里面的"swap"和“shared”。接下来要做的就是把“a.o”和“b.o”这两个目标文件链接在一起并最终形成一个可执行文件“ab”。

# 空间与地址分配

可执行文件中的代码段和数据段都是由输入的目标文件中合并而来的。

## 按序叠加

一个最简单的方案就是将输入的目标文件按照次序叠加起来。

![](/_images/book-note/linkersAndLoaders/简单的空间分配策略.png)

但是这样做会造成一个问题，在有很多输入文件的情况下，输出文件将会有很多零散的段。比如一个规模稍大的应用程序可能会有数百个目标文件，如果每个目标文件都分别有.text段、.data段和.bss段，那最后的输出文件将会有成百上千个零散的段。这种做法非常浪费空间，因为**每个段都须要有一定的地址和空间对齐要求**，比如对于x86的硬件来说，段的装载地址和空间的对齐单位是页，即4096字节。如果一个段只要一个字节，也需要占用4096字节。

## 相似段合并

一个更实际的方法是将相同性质的段合并到一起。

![](/_images/book-note/linkersAndLoaders/实际的空间分配策略.png)

“链接器为目标文件分配地址和空间”这句话中的“地址和空间”其实有两个含义**：第一个是在输出的可执行文件中的空间；第二个是在装载后的虚拟地址中的虚拟地址空间。**

对于有实际数据的段，比如“.text”和“.data”来说，它们在文件中和虚拟地址中都要分配空间，因为它们在这两者中都存在：而对于“.bss”这样的段来说，分配空间的意义只局限于虚拟地址空间，因为它在文件中并没有内容。事实上，在这里谈到的空间分配**只关注于虚拟地址空间的分配，因为这个关系到链接器后面的关于地址计算的步骤**，而可执行文件本身的空间分配与链接过程关系并不是很大。

现在的链接器空间分配的策略基本上都采用上述方法中的第二种（相似段合并），使用这种方法的链接器一般都采用一种叫两步链接（Two-pass Linking）的方法。也就是说整个链接过程分两步。

第一步：空间与地址分配。扫描所有的输入目标文件，并且获得它们的各个段的长度、属性和位置，并且将输入目标文件中的符号表中所有的符号定义和符号引用收集起来，统一放到一个全局符号表。这一步中，**链接器将能够获得所有输入目标文件的段长度，并且将它们合并，计算出输出文件中各个段合并后的长度与位置，并建立映射关系。**

第二步：符号解析与重定位。使用上面第一步中收集到的所有信息，**读取输入文件中段的数据、重定位信息，并且进行符号解析与重定位、调整代码中的地址等**。事实上第二步是链接过程的核心，特别是重定位过程。

使用 ld 链接器将 a.o 和 b.o 链接起来。

`ld a.o b.o -e main -o ab`

![](/_images/book-note/linkersAndLoaders/ld_ab.png)

链接前后的程序中所使用的地址已经是程序在进程中的虚拟地址，即各个段中的VMA(Virtual Memory Address）和Size，而忽略文件偏移（File Off）。

可以看到，在链接之前，上图中目标文件中的所有段的都是0，因为虚拟空间还没有被分配，所以它们默认都为0。等到链接之后，可执行文件“ab”中的各个段都被分配到了相应的虚拟地址。这里的输出程序“ab”中，“.text”段被分配到了地址0x088094，大小为0x72字节；“.data”段从地址0x089108开始，大小为4字节。整个链接过程前后，目标文件各段的分配、程序虚拟地址如图所示。

![](/_images/book-note/linkersAndLoaders/目标文件_可执行文件_进程空间.png)

## 符号地址的确定

当按照空间分配方法进行分配完成之后，链接器开始计算各个符号的虚拟地址。

因为各个符号在段内的相对位置是固定的，所以这时候其实“main”、“shared”和“swap"的地址也已经是确定的了，只不过链接器须要给每个符号加上一个偏移量，使它们能够调整到正确的虚拟地址。

# 符号解析与重定位

## 重定位

“a.c”源程序里使用了“shared”变量和“swap”函数，那么编译器在将“a.c”编译成指令时，如何访问“shared”变量和“swap”函数？

![](/_images/book-note/linkersAndLoaders/a_o反汇编.png)

mov指令码 C7 44 24 04 00 00 00 00  ———— shared地址部分为“0x00000000”

相对偏移调用指令call的指令码 E8     FC FF FF FF ———— swap的函数调用为“0xFFFFFFFC”（小端）

编译器把这两条指令的地址部分暂时用地址“0x00000000”和“0xFFFFFFFC”代替着，把真正的地址算工作留给了链接器。

![](/_images/book-note/linkersAndLoaders/ab_o反汇编.png)

经过修正以后，“shared”和“swap”的地址分别为“0x08049108”和“0x00000009”（小端字节序）。

## 重定位表

对于可重定位的ELF文件来说，它必须包含有重定位表，用来描述如何修改相应的段里的内容。

可以使用objdump来查看目标文件的定位表：

![](/_images/book-note/linkersAndLoaders/a_o重定位.png)

这个命令可以用来查看“a.o”里面要重定位的地方，即“a.o”所有引用到外部符号的地址。

每个要被重定位的地方叫一个重定位入口（Relocation Entry)，可以看到“a.o”里面有两个重定位入口。重定位入口的偏移(Offset)表示该入口在要被重定位的段中的位置，“RELOCATION RECORDS FORl [.text]”表示这个重定位表是**代码段的重定位表**，所以偏移表示代码段中须要被调整的位置。对照前面的反汇编结果可以知道，这里的0x1c和0x27分别就是代码段中“mov”指令和"call"指令的地址部分。

重定位表结构

```cpp
typedef struct{
    Elf32_Addr r_offset;
    Elf32_Word r_info;
} Elf32_Rel;
```

## 符号解析

直接使用ld来链接“a.o”会提示shared和swap两个符号没有定义:

```
[root@VM-16-6-centos test]# ld a.o
ld: warning: cannot find entry symbol _start; defaulting to 00000000004000b0
a.o: In function `main':
a.c:(.text+0x1c): undefined reference to `shared'
a.c:(.text+0x27): undefined reference to `swap'
```

平时在编写程序的时候最常碰到的问题之一，就是链接时符号未定义。导致这个问题的原因很多，**最常见的一般都是链接时缺少了某个库，或者输入目标文件路径不正确或符号的声明与定义不一样。**

重定位的过程中，每个重定位的入口都是对一个符号的引用，那么当链接器须要对某个符号的引用进行重定位时，它就要确定这个符号的目标地址。这时候链接器就会去查找由所有输入目标文件的符号表组成的全局符号表，找到相应的符号后进行重定位。

“a.o”的符号表：

```
[root@VM-16-6-centos test]# readelf -s a.o

Symbol table '.symtab' contains 11 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS a.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    6
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    7
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    5
     8: 0000000000000000    52 FUNC    GLOBAL DEFAULT    1 main
     9: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND shared
    10: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND swap
```

“GLOBAL”类型的符号，除了“main”函数是定义在代码段之外，其他两个“shared”和“swap”都是“UND”，即“undefined”未定义类型，这种未定义的符号都是因为该目标文件中有关于它们的重定位项。所以在链接器扫描完所有的输入目标文件之后，所有这些未定义的符号都应该能够在全局符号表中找到，否则链接器就报符号未定义错误。

## COMMON块

当不同的目标文件需要的COMMON块空间大小不一致时，以最大的那块为准。

这种使用COMMON块的方法实际上是一种类似“黑客"的取巧办法，直接导致需要COMMON机制的原因是编译器和链接器允许不同类型的弱符号存在，但最本质的原因还是链接器不支持符号类型，即**链接器无法判断各个符号的类型是否一致**。

## C++相关问题

### 重复代码消除

C++编译器在很多时候会产生重复的代码，比如模板(Templates)、外部内联函数（Extern lnline Function）和虚函数表（Virtual Function Table)都有可能在不同的编单元里生成相同的代码。

一个比较有效的做法就是将**每个模板的实例代码都单独地存放在一个段里，每个段只包含一个模板实例**。比如有个模板函数是add<T>()，某个编译单元以int类型和float类型实例化了该模板函数，那么该编译单元的目标文件中就包含了两个该模板实例的段。，当别的编译单元也以int或float类型实例化该模板函数后，也会生成同样的名字，这样链接器在最终链接的时候可以区分这些相同的模板实例段，然后**将它们合并入最后的代码段。**

这种做法的确被目前主流的编器所采用，GNU GCC编译器和VISUAL C++编译器都采用了类似的方法。GCC把这种类似的须要在最终链接时合并的段叫“Link Once”，它的做法是将这种类型的段命名为“.gnu.linkonce.name”,其中“name”是该模板函数实例的修饰后名称。

### 函数级别链接

VISUAL C++编译器提供了一个编译选项叫函数级别链接（Functiona-Level Linking,/Gy), 这个选项的作用就是让所有的函数都像前面模板函数一样，单独保存到一个段里面。当链接器须要用到某个函数时，**它就将它合并到输出文件中，对于那些没有用的函数则将它们抛弃**。这种做法可以很大程度上**减小输出文件的长度，减少空间浪费**。但是这个**优化选项会减慢编译和链接过程，因为链接器须要计算各个函数之间的依赖关系**，并且所有函数都保持到独的段中，目标函数的段的数量大大增加，重定位过程也会因为段的数目的增加而变得复杂，目标文件随着段数目的增加也会变得相对较大。

GCC编译器也提供了类似的机制，它有两个选择分别是“-ffunction-sections”和“-fdata-sections”，**这两个选项的作用就是将每个函数或变量分别保持到独立的段中。**

## 全局构造与析构

Linux系统下一般程序的入口是“_start”, 这个函数是Linux系统库(Glibc)的一部分，当我们的程序与Glibc库链接在一起形成最终可执行文件以后，这个函数就是程序的初始化部分的入口，程序初始化部分完成一系列初始化过程之后，会调用main函数来执行程序的
主体。在main函数执行完成以后，返回到初始化部分，它进行一些清理工作，然后结束进程。对于有些场合，程序的一些特定的操作必须在main函数之前被执行，还有一些操作必须在main函数之后被执行，其中很具有代表性的就是c++的全局对象的构造和析构函数。

因此ELF文件还定义了两种特殊的段。

* .init该段里面保存的是可执行指令，它构成了进程的初始化代码。因此，当一个程序开始运行时，在main函数被调用之前，Glibc的初始化部分安排执行这个段的中的代码。
* .fini该段保存着进程终止代码指令。因此，当一个程序的main函数正常退出时，Glibc会安排执行这个段中的代码。

利用这两个特性，c++的全局构造和析构函数就由此实现。

## C++与ABI

如果要使**两个编译器编译出来的目标文件能够相互链接**，那么这两个目标文件必须满足下面这些条件都是相同的：

* **目标文件格式**
* **符号修饰标准**
* **变量的内存分布方式**
* **函数的调用方式**

其中把符号修饰标准、变量内存布局、函数调用方式等这些跟可执行代码二进制兼容性相关的内容称为ABI（Application Binary Interface）。

最大的问题之一就是各种硬件平台、编程语言、编译器、链接器和操作系统之间的ABI相互不兼容，由于ABI相互的不兼容，各个目标文件之间无法相互链接，二进制兼容性更加无从谈起。

对于C语言的目标代码而言，以下几个方面会决定目标文件之间是否二进制兼容：

* 内置类型（如int、float、char等）的大小和在存储器中的放置方式（大端、小端、对齐方式等）。
* 组合类型（如struct、union、数组等）的存储方式和内存分布。
* 外部符号(external-linkage)与用户定义的符号之间的命名方式和解析方式，如函数名func在C语言的目标文件中是被解成外部符号_func。
* 函数调用方式，比如参数入栈顺序、返回值如何保持等。
* 堆栈的分布方式，比如参数和局部变量在堆栈里的位置，参数传递方法等。
* 寄存器使用约定，函数调用时哪些寄存器可以修改，哪些须要保存等。

**C++要做到二进制兼容比C来得更为不易。**

* 继承类体系的内存分布，如基类，虚基类在继承类中的位置
* 指向成员函数的指针（pointer-to-member)的内存分布，如何通过指向成员函数的指针来调用成员函数，如何传递this指针。
* 如何调用虚函数，vtable的内容和分布形式，vtable指针在object中的位置等。
* ·template如何实例化。
* 外部符号的修饰。
* 全局对象的构造和析构。
* 异常的产生和捕获机制。
* 标准库的细节问题，RTTI如何实现等。
* 内嵌函数访问细节。

## 静态库链接

静态库可以看成一组目标文件的集合，即很多目标文件经过压缩打包后形成的一个文件。

使用ar工具查看文件包含了哪些目标文件
```
[root@VM-16-6-centos lib64]# ar -t libc.a
init-first.o
libc-start.o
sysdep.o
version.o
check_fds.o
libc-tls.o
elf-init.o
...
```

使用objdump查看libc.a的符号结果：
```
[root@VM-16-6-centos lib64]# objdump -t libc.a
...
printf.o:     file format elf64-x86-64
0000000000000000 g     F .text  000000000000009e __printf
0000000000000000         *UND*  0000000000000000 vfprintf
0000000000000000 g     F .text  000000000000009e printf
0000000000000000 g     F .text  000000000000009e _IO_printf
...
```

使用GCC命令编译“test.c”，“-verbose”表示将整个编译链接过程的中间步骤打印出来。

```
[root@VM-16-6-centos test]# gcc -static --verbose -fno-builtin test.c
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/libexec/gcc/x86_64-redhat-linux/4.8.5/lto-wrapper
Target: x86_64-redhat-linux
Configured with: ../configure --prefix=/usr --mandir=/usr/share/man --infodir=/usr/share/info --with-bugurl=http://bugzilla.redhat.com/bugzilla --enable-bootstrap --enable-shared --enable-threads=posix --enable-checking=release --with-system-zlib --enable-__cxa_atexit --disable-libunwind-exceptions --enable-gnu-unique-object --enable-linker-build-id --with-linker-hash-style=gnu --enable-languages=c,c++,objc,obj-c++,java,fortran,ada,go,lto --enable-plugin --enable-initfini-array --disable-libgcj --with-isl=/builddir/build/BUILD/gcc-4.8.5-20150702/obj-x86_64-redhat-linux/isl-install --with-cloog=/builddir/build/BUILD/gcc-4.8.5-20150702/obj-x86_64-redhat-linux/cloog-install --enable-gnu-indirect-function --with-tune=generic --with-arch_32=x86-64 --build=x86_64-redhat-linux
Thread model: posix
gcc version 4.8.5 20150623 (Red Hat 4.8.5-44) (GCC)
COLLECT_GCC_OPTIONS='-static' '-v' '-fno-builtin' '-mtune=generic' '-march=x86-64'
/usr/libexec/gcc/x86_64-redhat-linux/4.8.5/cc1 -quiet -v test.c -quiet -dumpbase test.c -mtune=generic -march=x86-64 -auxbase test -version -fno-builtin -o /tmp/ccxU9fiu.s 
GNU C (GCC) version 4.8.5 20150623 (Red Hat 4.8.5-44) (x86_64-redhat-linux)
        compiled by GNU C version 4.8.5 20150623 (Red Hat 4.8.5-44), GMP version 6.0.0, MPFR version 3.1.1, MPC version 1.0.1
GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
ignoring nonexistent directory "/usr/lib/gcc/x86_64-redhat-linux/4.8.5/include-fixed"
ignoring nonexistent directory "/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../x86_64-redhat-linux/include"
#include "..." search starts here:
#include <...> search starts here:
 /usr/lib/gcc/x86_64-redhat-linux/4.8.5/include
 /usr/local/include
 /usr/include
End of search list.
GNU C (GCC) version 4.8.5 20150623 (Red Hat 4.8.5-44) (x86_64-redhat-linux)
        compiled by GNU C version 4.8.5 20150623 (Red Hat 4.8.5-44), GMP version 6.0.0, MPFR version 3.1.1, MPC version 1.0.1
GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
Compiler executable checksum: 231b3394950636dbfe0428e88716bc73
COLLECT_GCC_OPTIONS='-static' '-v' '-fno-builtin' '-mtune=generic' '-march=x86-64'
 as -v --64 -o /tmp/ccNzvQpa.o /tmp/ccxU9fiu.s
GNU assembler version 2.27 (x86_64-redhat-linux) using BFD version version 2.27-44.base.el7_9.1
COMPILER_PATH=/usr/libexec/gcc/x86_64-redhat-linux/4.8.5/:/usr/libexec/gcc/x86_64-redhat-linux/4.8.5/:/usr/libexec/gcc/x86_64-redhat-linux/:/usr/lib/gcc/x86_64-redhat-linux/4.8.5/:/usr/lib/gcc/x86_64-redhat-linux/
LIBRARY_PATH=/usr/lib/gcc/x86_64-redhat-linux/4.8.5/:/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/:/lib/../lib64/:/usr/lib/../lib64/:/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../:/lib/:/usr/lib/
COLLECT_GCC_OPTIONS='-static' '-v' '-fno-builtin' '-mtune=generic' '-march=x86-64'
 /usr/libexec/gcc/x86_64-redhat-linux/4.8.5/collect2 --build-id --no-add-needed --hash-style=gnu -m elf_x86_64 -static /usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crt1.o /usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crti.o /usr/lib/gcc/x86_64-redhat-linux/4.8.5/crtbeginT.o -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5 -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64 -L/lib/../lib64 -L/usr/lib/../lib64 -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../.. /tmp/ccNzvQpa.o --start-group -lgcc -lgcc_eh -lc --end-group /usr/lib/gcc/x86_64-redhat-linux/4.8.5/crtend.o /usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crtn.o
```

重点关注：

* /usr/libexec/gcc/x86_64-redhat-linux/4.8.5/**cc1** -quiet -v test.c -quiet -dumpbase test.c -mtune=generic -march=x86-64 -auxbase test -version -fno-builtin -o /tmp/ccxU9fiu.s 
* **as** -v --64 -o /tmp/ccNzvQpa.o /tmp/ccxU9fiu.s
/usr/libexec/gcc/x86_64-redhat-linux/4.8.5/**collect2** --build-id --no-add-needed --hash-style=gnu -m elf_x86_64 -static /usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crt1.o /usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crti.o /usr/lib/gcc/x86_64-redhat-linux/4.8.5/crtbeginT.o -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5 -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64 -L/lib/../lib64 -L/usr/lib/../lib64 -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../.. /tmp/ccNzvQpa.o --start-group -lgcc -lgcc_eh -lc --end-group /usr/lib/gcc/x86_64-redhat-linux/4.8.5/crtend.o /usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crtn.o

第一步是调用cc1程序，这个程序实际上就是GCC的c语言编译器，它将“test.c”编译成一个临时的汇编文件“/tmp/ccxU9fiu.s”;然后调用as程序，as程序是GNU的汇编器，它将"/tmp/ccxU9fiu.s"汇编成临时目标文件"/tmp/ccNzvQpa.o"，这个“/tmp/ccNzvQpa”实际上就是前面的“hello.o”；接着最关键的步骤是最后一步，GCC调用collect2程序来完成最后的链接。collect2是ld的一个包装 ，它会调用ld链接器来完成对目标文件的链接，然后再对链接结果进行一些处理，主要是收集所有与程序初始化相关的信息并且构造初始化的结构。

**思考**：

Q: 为什么静态运行库里面一个目标文件只包含一个函数？比如libc.a里面printf.o只有printf()函数、strlen.o只有strlen()函数，为什么要这样组织？

A：链接器在链接静态库的时候是以**目标文件为单位的**。比如我们引用了静态库中的printf()函数，那么链接器就会把库中包含printf()函数的那个目标文件链接进来，如果很多函数都放在一个目标文件中，很可能很多没用的函数都被一起链接进了输出结果中。由于运行库有成百上千个函数，数量非常庞大，每个函数独立地放在一个目标文件中可以尽量减少空间的浪费，那些没有被用到的目标文件（函数）就不要链接到最终的输出文件中。