# C++函数 - Linux系统调用Hook

[[toc]]

# 参考资料

* [Linux系统调用Hook姿势总结](https://blog.csdn.net/tianxuhong/article/details/50974400)
* [LD_PRELOAD用法](https://www.cnblogs.com/saolv/p/9761371.html)
* [动态链接库dlopen的函数的使用](https://blog.csdn.net/woyebuzhidao888/article/details/46634591)

# 系统调用Hook简介

系统调用属于一种软中断机制，它有操作系统提供的功能入口(sys_call)以及CPU提供的硬件支持(int 3 trap)共同完成。

Hook技术是一个相对较宽的话题，**因为操作系统从ring3到ring0是分层次的结构**，在每一个层次上都可以进行相应的Hook，它们使用的技术方法以及取得的效果也是不尽相同的。本文主要关注"系统调用的Hook学习"，讲解从ring3到ring0中所涉及到的Hook技术，来实现系统调用的监控功能。

## Hook原理

Hook技术无论对安全软件还是恶意软件都是十分关键的一项技术，其本质就是**劫持函数调用**。但是由于处于Linux用户态，每个进程都有自己独立的进程空间，所以必须先注入到所要Hook的进程空间，修改其内存中的进程代码，替换其过程表的符号地址。

## 操作系统RING3到RING0的分层结构

Intel的CPU将特权级别分为4个级别：RING0,RING1,RING2,RING3。

Windows只使用RING0和RING3，RING0只给操作系统用，RING3谁都能用。

如果普通应用程序企图执行RING0指令，则Windows会显示“非法指令”错误信息。因为有CPU的特权级别作保护。

ring0是指CPU的运行级别，ring0是最高级别，ring1次之，ring2更次之……

![CPU的特权级别](/_images/c++/cpu-privilege.png)

**以Linux+x86为例**
操作系统（内核）的代码运行在最高运行级别RING0上，可以使用特权指令，控制中断、修改页表、访问设备等。 应用程序的代码运行在最低运行级别上RING3上，不能做受控操作。如果要做，例如访问磁盘，写文件的操作，则必须通过**系统调用**（函数），执行系统调用的时候，CPU的运行级别会从RING3切换到RING0，并跳转到系统调用对应的内核代码位置执行，这样内核就替我们完成了设备访问的操作，完成之后再从RING0返回RING3。整个过程也称**作用户态和内核态的切换**。

## Ring3中Hook技术

***LD_PRELOAD动态连接.so函数劫持***

在linux操作系统的动态链接库的世界中，LD_PRELOAD就是这样一个环境变量，它可以影响程序的运行时的链接(Runtime linker)，它允许用户在程序运行前优先加载的动态链接库。Loader在进行动态链接的时候，会将有相同符号名的符号覆盖成LD_PRELOAD指定的so文件中的符号。换句话说，可以用我们自己编写的so库中的函数替换原来库里有的函数，从而达到hook的目的。

```
LD_PRELOAD是个环境变量，用于动态库的加载，动态库加载的优先级最高。一般情况下，其加载顺序为LD_PRELOAD>LD_LIBRARY_PATH>/etc/ld.so.cache>/lib>/usr/lib。程序中我们经常要调用一些外部库的函数，以malloc为例，如果我们有个自定义的malloc函数，把它编译成动态库后，通过LD_PRELOAD加载，当程序中调用malloc函数时，调用的其实是我们自定义的函数，
```

Linux用的C语言库使用的是glibc，存在一个libc.so.6的文件。默认情况下，linux所编译的程序中对标准C函数的链接，都是通过动态链接方式来链接libc.so.6函数库的。这也意味着我们在通过注入的.so来实现**函数覆盖劫持之后**需要从libc.so.6中取得原本的正常函数，让程序能够继续正常执行。

正常程序main.c:

``` cpp
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if( strcmp(argv[1], "test") )
  {
    printf("Compare inconsistent\n");
  }
  else
  {
    printf("Compare consistent\n");
  }
  return 0;
}
```

用于劫持函数的.so代码hook.c:

``` cpp
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>

/*
hook的目标是strcmp，所以typedef了一个STRCMP函数指针
hook的目的是要控制函数行为，从原库libc.so.6中拿到strcmp指针，保存成old_strcmp以备调用
*/
typedef int(*STRCMP)(const char*, const char*);
 
int strcmp(const char *s1, const char *s2)
{
  static void *handle = NULL;
  static STRCMP old_strcmp = NULL;
    
  handle = dlopen ("libc.so.6", RTLD_LAZY);  
  if (!handle) {  
     fprintf (stderr, "%s ", dlerror());  
     exit(1);  
  }
  else
  {
     old_strcmp = (STRCMP)dlsym(handle, "strcmp"); 
  }
   
  printf("oops!!! hack function invoked. s1=<%s> s2=<%s>\n", s1, s2);
  dlclose(handle);
  return old_strcmp(s1, s2);
}
```

使用过程：

```
[root@VM-0-10-centos code]# gcc -o test main.c
[root@VM-0-10-centos code]# gcc -fPIC -shared -o hook.so hook.c -ldl
[root@VM-0-10-centos code]# LD_PRELOAD=./hook.so ./test 123
oops!!! hack function invoked. s1=<123> s2=<test>
Compare inconsistent
[root@VM-0-10-centos code]# LD_PRELOAD=./hook.so ./test test
oops!!! hack function invoked. s1=<test> s2=<test>
Compare consistent
```

补充知识：

```
dlopen

基本定义
功能：打开一个动态链接库 
包含头文件： 
#include <dlfcn.h> 
函数定义： 
void * dlopen( const char * pathname, int mode ); 
函数描述： 
在dlopen的（）函数以指定模式打开指定的动态连接库文件，并返回一个句柄给调用进程。使用dlclose（）来卸载打开的库。 
mode：分为这两种 
RTLD_LAZY 暂缓决定，等有需要时再解出符号 
RTLD_NOW 立即决定，返回前解除所有未决定的符号。 
RTLD_LOCAL 
RTLD_GLOBAL 允许导出符号 
RTLD_GROUP 
RTLD_WORLD 
返回值: 
打开错误返回NULL 
成功，返回库引用 
编译时候要加入 -ldl (指定dl库) 
例如 
gcc test.c -o test -ldl

使用 dlopen
dlopen()是一个强大的库函数。该函数将打开一个新库，并把它装入内存。该函数主要用来加载库中的符号，这些符号在编译的时候是不知道的。比如 Apache Web 服务器利用这个函数在运行过程中加载模块，这为它提供了额外的能力。一个配置文件控制了加载模块的过程。这种机制使得在系统中添加或者删除一个模块时，都 不需要重新编译了。 
可以在自己的程序中使用 dlopen()。dlopen() 在 dlfcn.h 中定义，并在 dl 库中实现。它需要两个参数：一个文件名和一个标志。文件名可以是我们学习过的库中的 soname。标志指明是否立刻计算库的依赖性。如果设置为 RTLD_NOW 的话，则立刻计算；如果设置的是 RTLD_LAZY，则在需要的时候才计算。另外，可以指定 RTLD_GLOBAL，它使得那些在以后才加载的库可以获得其中的符号。 
当库被装入后，可以把 dlopen() 返回的句柄作为给 dlsym() 的第一个参数，以获得符号在库中的地址。使用这个地址，就可以获得库中特定函数的指针，并且调用装载库中的相应函数。

--------------------------------------------------------------------------------------------------------------------------

dlsym

dlsym()的函数原型是 
void* dlsym(void* handle,const char* symbol) 
该函数在<dlfcn.h>文件中。 
handle是由dlopen打开动态链接库后返回的指针，symbol就是要求获取的函数的名称，函数返回值是void*,指向函数的地址，供调用使用

取动态对象地址：
#include <dlfcn.h>
void *dlsym(void *pHandle, char *symbol);
dlsym根据动态链接库操作句柄(pHandle)与符号(symbol),返回符号对应的地址。
使用这个函数不但可以获取函数地址，也可以获取变量地址。比如，假设在so中
定义了一个void mytest()函数，那在使用so时先声明一个函数指针：
void (*pMytest)(),然后使用dlsym函数将函数指针pMytest指向mytest函数，
pMytest = (void (*)())dlsym(pHandle, "mytest");

--------------------------------------------------------------------------------------------------------------------------

dlclose
dlclose（） 
包含头文件： 
#include <dlfcn.h> 
函数原型为: 
int dlclose (void *handle); 
函数描述： 
dlclose用于关闭指定句柄的动态链接库，只有当此动态链接库的使用计数为0时,才会真正被系统卸载。

--------------------------------------------------------------------------------------------------------------------------

dlerror
dlerror（） 
包含头文件： 
#include <dlfcn.h> 
函数原型: 
const char *dlerror(void); 
函数描述： 
当动态链接库操作函数执行失败时，dlerror可以返回出错信息，返回值为NULL时表示操作函数执行成功。

LINUX创建与使用动态链接库并不是一件难事。
编译函数源程序时选用-shared选项即可创建动态链接库，注意应以.so后缀命名，最好放到公用库目录(如/lib,/usr/lib等)下面，并要写好用户接口文件，以便其它用户共享。
使用动态链接库，源程序中要包含dlfcn.h头文件，写程序时注意dlopen等函数的正确调用，编译时要采用-rdynamic选项与-ldl选项 ，以产生可调用动态链接库的执行代码。
```

# Ring0中Hook技术

## Kernel Inline Hook

传统的kernel inline hook技术就是修改内核函数的opcode，通过写入jmp或push ret等指令跳转到新的内核函数中，从而达到劫持的目的。对于这类劫持攻击，目前常见的做法是"函数返回地址污点检测"，通过对原有指令返回位置的汇编代码作污点标记，通过查找jmp，push ret等指令来进行防御

备注：*OPCode* 操作码(Operation Code,*OPCode*):描述机器语言指令中,指定要执行某种操作的机器码。

在系统调用函数中一定会递归的嵌套有很多的子函数，即它必定要调用它的下层函数。从汇编的角度看，对一个子函数的调用是采用"段内相对短跳转 jmp offset"的方式来实现的，即CPU根据offset来进行一个偏移量的跳转。

如果我们把下层函数在上层函数中的offset替换成我们"Hook函数"的offset，这样上层函数调用下层函数时，就会跳到我们的"Hook函数"中，我们就可以在"Hook函数"中做过滤和劫持内容的工作。

```
asmlinkage ssize_t sys_read(unsigned int fd, char __user * buf, size_t count)
{
  struct file *file;
  ssize_t ret = -EBADF;
  int fput_needed;

  file = fget_light(fd, &fput_needed);
  if (file) 
    {
    loff_t pos = file_pos_read(file);
    ret = vfs_read(file, buf, count, &pos);
    file_pos_write(file, pos);
    fput_light(file, fput_needed);
  }

  return ret;
}
EXPORT_SYMBOL_GPL(sys_read);
```

在sys_read()中，调用了子函数vfs_read()来完成读取数据的操作，在sys_read()中调用子函数vfs_read()的汇编命令是:

call 0xc106d75c <vfs_read>

等同于:

jmp offset(相对于sys_read()的基址偏移)

所以，目标就是找到call  0xc106d75c <vfs_read>这条汇编，把其中的offset改成我们的Hook函数对应的offset，即可实现劫持目的。

```sql
1. 搜索sys_read的opcode
2. 如果发现是call指令，根据call后面的offset计算要跳转的地址是不是我们要hook的函数地址
    1) 如果"不是"就重新计算Hook函数的offset，用Hook函数的offset替换原来的offset
    2) 如果"已经是"Hook函数的offset，则说明函数已经处于被劫持状态了，我们的Hook引擎应该直接忽略跳过，避免重复劫持
```

## 利用0x80中断劫持system_call->sys_call_table进行系统调用Hook

要对系统调用(sys_call_table)进行替换，必须要获取该地址后才可以进行替换。但是Linux 2.6版的内核出于安全的考虑没有将系统调用列表基地址的符号sys_call_table导出，但是我们可以采取一些hacking的方式进行获取。

因为系统调用都是通过0x80中断来进行的，故可以通过查找0x80中断的处理程序来获得sys_call_table的地址。其基本步骤是

```
1. 获取中断描述符表(IDT)的地址(使用C ASM汇编)
2. 从中查找0x80中断(系统调用中断)的服务例程(8*0x80偏移)
3. 搜索该例程的内存空间，
4. 从其中获取sys_call_table(保存所有系统调用例程的入口地址)的地址
5. 获取到了sys_call_table的基地址之后，我们就可以修改指定offset对应的系统调用了，从而达到劫持系统调用的目的
```

# 总结

hook函数的实现方法：

1. 编写自己的动态库，利用LD_PRELOAD优先加载同名的自定义函数  （自定义strcmp来覆盖C标准库的strcmp）
2. 找到程序调用对应的汇编命令，修改对应的offset地址  （call  0xc106d75c <vfs_read>）
3. 获取sys_call_table的基地址，修改指定函数offset对应的系统调用了
