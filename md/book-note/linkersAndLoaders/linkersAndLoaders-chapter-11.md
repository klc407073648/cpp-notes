# 第11章 运行库

[[toc]]

# 文章总结

![](/_images/book-note/linkersAndLoaders/运行库.png)

# 入口函数和程序初始化

典型程序的运行步骤：

* 操作系统在创建进程后，把控制权交到了程序的入口，这个入口往往是运行库中的某个入口函数。
* **入口函数对运行库和程序运行环境进行初始化**，包括堆、I/O、线程、全局变量构造等等。
* 入口函数在完成初始化之后，调用main函数，正式开始执行程序主体部分。
* main函数执行完毕以后，返回到入口函数，**入口函数进行清理工作**，包括全局变量析构、堆销毁、关闭I/O等，然后进行系统调用结束进程。

## GLIBC入口函数

```cpp
void _start()
{
    %ebp = 0;
    int argc= pop from stack
    char** argv = top of stack；
    __libc_start_main(main, argc, argv, __libc_csu_init, __libc_csu_fnit, edx, top of stack);
}
```

其中argv除了指向参数表外，还隐含紧接着环境变量表。

函数执行过程：

_start ——> __libc_start_main ——> exit ——> _exit 

## MSVC CRT入口函数

MSVC CRT入口函数(MSVC CRT全名Microsoft Visual C++ C Runtime,是Windows下的C运行库)，默认函数名为mainCRTStartup，它的总体流程是：

* 初始化和OS版本有关的全局变量。
* 初始化堆。
* 初始化I/O。
* 获取命令行参数和环境变量。
* 初始化C库的一些数据。
* 调用main并记录返回值。
* 检查错误并将main的返回值返回。

## 运行库与I/O

IO（或I/O）的个称是Input/Output,即输入和输出。对于计算机来说，I/O代表了计算与外界的交互，交互的对象可以是人或其他设备。

对于程序来说，I/O涵盖的范围还要宽广一些。一个程序的I/O指代了程序与外界的交互，包括文件、管道、网络、命令行、信号等。更广义地讲，I/O指代任何操作系统理解为“文件"的事物。许多操作系统，包括Linux和Windows，都将各种具有输入和输出概念的实体一一一包括设备、磁盘文件、命令行等一一统称为文件，因此这里所说的文件是一个广义的概念。

在操作系统层面上，文件操作也有类似于FILE的一个概念，在Linux里，这叫做文件描述符(File Descriptor)，而在Windows里，叫做句柄(Handle)）。**用户通过某个函数打开文件以获得句枘，此后用户操纵文件皆通过该句柄进行。**

设计这么一个句柄的原因在于句柄可以**防止用户随意读写操作系统内核的文件对象**。无论是Linux还是Windows，文件句柄总是和内核的文件对象相关联的，但如何关联细节用户并不可见。**内核可以通过句柄来计算出内核里文件对象的地址，但此能力并不对用户开放。**

在Linux中，值为0、1、2的fd分别代表标准输入、标准输出和标准错误输出。在程序中打开文件得到的fd从3开始增长。fd具体是什么呢？在内核中，每一个进程都有一个私有的“打开文件表”，这个表是一个指针数组，每一个元素都指向一个内核的打开文件对象。而fd，就是这个表的下标。当用户打开一个文件时，内核会在内部生成一个打开文件对象，并在这个表里找到一个空项，让这一项指向生成的打开文件对象，并返回这一项的下标作为fd。由于这个表处于内核，并且用户无法访问到，因此用户即使拥有fd，也无法得到打开文件对象的地址，只能够通过系统提供的函数来操作。

在c语言里，操纵文件的渠道则是FILE结构，不难想象，c语言中的FILE结构必定和fd有一对一的关系，每个FILE结构都会记录自己唯一对应的fd。

FILE、fd、打开文件表和打开文件对象的关系如图所示。

![](/_images/book-note/linkersAndLoaders/FILE_fd_打开文件表.png)

在crt/src/ioinit.c，有一个数组：
```cpp
int _nhandle;
ioinfo *__pioinfo[64];
```

这就是用户态的打开文件表。这个表实际是一个二维数组，第二维的大小为32个ioinfo结构，因此该表总共可以容纳的元素总量为64*32=20
48个句柄。此外_nhandle记录该表的实际元素个数。**使用指针数组而不是二维数组的原因是使用指针数组更加节省空**，而如果使用二维数组，则不论程里打开了几个文件都必须始终消耗2048个ioinfo的空间。

Windows的FILE、句柄和内核对象的内部结构与Linux不同。

![](/_images/book-note/linkersAndLoaders/Windows的FILE_句柄和内核对象.png)

## C/C++运行库

任何一个C程序，它的背后都有一套庞大的代码来进行支撑，以使得该程序能够正常运行。这套代码至少包括入口函数，及其所依赖的函数所构成的函数集合。当然，它还理应包括各种标准库函数的实现。这样的一个代码集合称之为运行时库(Runtime Library)。而c语言的运行库，即被称为C运行库(CRT)。

辅助程序运行的运行库，/usr/lib/crt1.o, /usr/lib/crti.o, /usr/lib/crtn.o。

crt1.o里面包含的就是程序的入口函数_start，由它负责调用__libc_start_main初始化libc并且调用main函数进入真正的程序主体。(objdump -dr /usr/lib/crt1.o)

从反汇编crt1.o可以看到，它向libc启动函数__libc_start_main()传递了两个函数指针“__libc_csu_init”和“__libc_csu_fini”，这两个函数负责调用_init()和_finit()。crti.o 和 crtn.o 这两个目标文件中包含的代码实际上就是_init()函数和_finit()函数的开始和结尾部分。

## 运行库与多线程

### CRT的多线程困扰

![](/_images/book-note/linkersAndLoaders/多线程数据共享.png)