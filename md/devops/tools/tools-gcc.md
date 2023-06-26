# Tools - GCC和动静态库

[[toc]]

# 参考

* [gcc 命令详解及最佳实践](https://blog.csdn.net/lu_embedded/article/details/117848775)

# 概述

GCC（英文全拼：GNU Compiler Collection）是 GNU 工具链的主要组成部分，是一套以 GPL 和 LGPL 许可证发布的程序语言编译器自由软件，由 Richard Stallman 于 1985 年开始开发。

GCC 原名为 GNU C语言编译器，因为它原本只能处理 C 语言，但如今的 GCC 不仅可以编译 C、C++ 和 Objective-C，还可以通过不同的前端模块支持各种语言，包括 Java、Fortran、Ada、Pascal、Go 和 D 语言等等。

# 编译过程

GCC 的编译过程可以划分为四个阶段：预处理（Pre-Processing）、编译（Compiling）、汇编（Assembling）以及链接（Linking）。

![](/_images/devops/tools/编译过程.png)

Linux 程序员可以根据自己的需要控制 GCC 的编译阶段，以便检查或使用编译器在该阶段的输出信息，帮助调试和优化程序。以 C 语言为例，从源文件的编译到可执行文件的运行，整个过程大致如下。

![](/_images/devops/tools/编译整体过程.png)

## 语法

```
gcc [options] file...
```

## 选项

可以通过 `gcc --help` 查看具体的选项内容。

<<< @/md/devops/tools/src/gcc/gcc_help.txt

## 示例

### 阶段编译

假设有文件 hello.c，内容如下：

<<< @/md/devops/tools/src/gcc/hello.c

编译 hello.c，默认输出 a.out

`gcc hello.c`

编译 hello.c 并指定输出文件为 hello

`gcc hello.c -o hello`

只执行预处理，输出 hello.i 源文件

`gcc -E hello.c -o hello.i`

只执行预处理和编译，输出 hello.s 汇编文件

`gcc -S hello.c`

也可以由 hello.i 文件生成 hello.s 汇编文件

`gcc -S hello.i -o hello.s`

只执行预处理、编译和汇编，输出 hello.o 目标文件

`gcc -c hello.c`

也可以由 hello.i 或 hello.s 生成目标文件 hello.o

```
gcc -c hello.i -o hello.o
gcc -c hello.s -o hello.o
```

由 hello.o 目标文件链接成可执行文件 hello

`gcc hello.o -o hello`

hello.i 和 hello.s 文件内容如下

::: details
<<< @/md/devops/tools/src/gcc/hello.i
<<< @/md/devops/tools/src/gcc/hello.s
::: 

## 使用静态库

创建一个 fun.c 文件，内容如下：

<<< @/md/devops/tools/src/gcc/fun.c

将 fun.c 编译成静态库 libfun.a

```
gcc -c fun.c
ar rcs libfun.a fun.o
```

查看文件描述 TODO

```
$ file *
fun.c:    C source, ASCII text
fun.o:    ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped
libfun.a: current ar archive
```

修改 hello1.c 文件，调用 fun 函数

<<< @/md/devops/tools/src/gcc/hello1.c


编译 hello1.c 并链接静态库 libfun.a（加上 -static 选项）

`gcc hello1.c -static libfun.a -o hello1`

也可以使用 -L 指定库的搜索路径，并使用 -l 指定库名

`gcc hello1.c -L. -static -lfun -o hello1`

运行结果

```
[root@VM-16-6-centos test]# ./hello1
Hello, World!
Here is a static library!
```

查看 hello1 文件描述

```
[root@VM-16-6-centos test]# file hello1
hello1: ELF 64-bit LSB executable, x86-64, version 1 (GNU/Linux), statically linked, for GNU/Linux 2.6.32, BuildID[sha1]=0fc4821ab804afd1d4a1d486616964714e9a7f6b, not stripped
```

## 使用共享库

创建一个 shareFun.c 文件，内容如下：

<<< @/md/devops/tools/src/gcc/shareFun.c


编译 hello1.c 并链接共享库 libshareFun.so

`gcc shareFun.c -shared -fPIC -o libshareFun.so`

也可以使用 -L 和 -l 选项指定库的路径和名称

`gcc hello1.c -L. -lshareFun -o hello1`

运行结果

```
[root@VM-16-6-centos test]# export LD_LIBRARY_PATH=$(pwd)
[root@VM-16-6-centos test]# ./hello1
Hello, World!
Here is a shared library!
```

### 动态库修改使用

```
# 修改动态库并重新生成
[root@VM-16-6-centos test]# vi shareFun.c
[root@VM-16-6-centos test]# gcc shareFun.c -shared -fPIC -o libshareFun.so

# 不需要重新编译 hello1，新增内容 “Test”，可以直接看到，运行时重新加载so
[root@VM-16-6-centos test]# ./hello1
Hello, World!
Test Here is a shared library!
```

查看链接内容：

```
[root@VM-16-6-centos test]# ldd hello1
        linux-vdso.so.1 =>  (0x00007fff03bbd000)
        /$LIB/libonion.so => /lib64/libonion.so (0x00007fd57b8b1000)
        libshareFun.so => /home/klc/test/libshareFun.so (0x00007fd57b596000)
        libc.so.6 => /lib64/libc.so.6 (0x00007fd57b1c8000)
        libdl.so.2 => /lib64/libdl.so.2 (0x00007fd57afc4000)
        /lib64/ld-linux-x86-64.so.2 (0x00007fd57b798000)
```

修改完后，新增内容 “111”，**查看链接信息的确变化了**。

```
[root@VM-16-6-centos test]# vi shareFun.c
[root@VM-16-6-centos test]# gcc shareFun.c -shared -fPIC -o libshareFun.so
[root@VM-16-6-centos test]# ./hello1
Hello, World!
Test111 Here is a shared library!
[root@VM-16-6-centos test]# ldd hello1
        linux-vdso.so.1 =>  (0x00007ffe2e427000)
        /$LIB/libonion.so => /lib64/libonion.so (0x00007f11fdad2000)
        libshareFun.so => /home/klc/test/libshareFun.so (0x00007f11fd7b7000)
        libc.so.6 => /lib64/libc.so.6 (0x00007f11fd3e9000)
        libdl.so.2 => /lib64/libdl.so.2 (0x00007f11fd1e5000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f11fd9b9000)
```

## 动态库和静态库比较

```
TODO 加动态库的优缺点
```