# 第1章 简介

[[toc]]

# 概述

在本书里面，我们将计算机的范围限定在最为流行、使用最广泛的PC机，更具体地讲是采用**兼容x86指令的32位CPU的个人计算机**。原因很简单：因为笔者手上目前只有这种类型的计算机可供操作和实验，不过相信90％以上的读者也是。

撇开计算机硬件中纷繁复杂的各种设备、芯片及外围接口等，站在软件开发者的角度看，我们只须抓住硬件的几个关键部件。对于系统程序开发者来说，计算机多如牛毛的硬件设备中，有三个部件最为关键，它们分别是**中央处理器CPU、内存和I/O控制芯片**，这三个部件几乎就是计算机的核心了；对于普通应用程序开发者来说，他们似乎除了要关心CPU以外，其他的硬件细节基本不用关心，对于一些高级平台的开发者来说，连CPU都不需要关心，因为这些平台为它们提供了一个通用的抽象的计算机。

## 计算机硬件的发展

> 早期的计算机没有很复杂的图形功能，**CPU的核心频率也不高，跟内存的频率一样**，它们都是直接连接在同一个总线(Bus)上的。由于I/O设各诸如显示设备、键盘、软盘和磁盘等速度与CPU和内存相比还是慢很多。当时也没有复杂的图形设备，显示设备大多是只能输出字符的终端。为了**协调I/O设备与总线之间的速度**，也为了能够让CPU能够和I/O设备进行通信，一般每个设各都会有一个相应的**I/O控制器**。早期的计算机硬件结构如图

![](/_images/book-note/linkersAndLoaders/早期的计算机硬件结构.png)

> 后来由于**CPU核心频率的提升，导致内存跟不上CPU的速度**。于是产生了与内存频率一致的系统总线，而CPU采用倍频的方式与系统总线进行通信。接着随着图形化的操作系统普及，特别是3D游戏和多媒体的发展，使得图形芯片需要跟CPU和内存之间大量交换数据，慢速的I/O总己经无法满足图形设备的巨大需求。

为了协调CPU、内存和高速的图形设备，人们专门设计了一个高速的北桥芯片，以便它们之间能够高速地交换数据。由于北桥运行的速度非常高，所有相对低速的设备如果全都直接连接在北桥上，北桥既须处理高速设备，又须处理低速设各，设计就会十分复杂。

于是人们又设计了专门处理低速设备的南桥（South Bridge）芯片，磁盘、USB、键盘、鼠标等设备都连接在南桥上，由南桥将它们汇总后连接到北桥上。20世纪90年代的机在系统总线上采用的是PCI结构，而在低速设备上采用的ISA总线，采用PCI/ISA及南北桥设计的硬件构架如图所示。

![](/_images/book-note/linkersAndLoaders/硬件结构框架.png)

* ISA总线(Industrial Standard Architecture，工业标准结构总线)
* PCI总线(Pedpherd Component Interconnect，周边元件扩展接口)

位于中间是连接所有高速芯片的北桥（North bridge PCI Bridge），它就像人的心脏，连接并驱动身体的各个部位；它的左边是CPU，负责所有的控制和运算，就像人的大脑。北桥还连接着几个高速部件，包括左边的内存和下面的PCI总线。

### SMP与多核

在过去的50年里，CPU的频率**从几十KHz到现在的4GHz**，整整提高了数十万倍，基本上每18个月频率就会翻倍。但是自2004年以来，这种规律似乎己经失效，CPU的频率自从那时开始再也没有发生质的提高。原因是人们在制造**CPU的工艺方面己经达到了物理极限**，除CPU制造工艺有本质的突破，否则一直目前的“天花板"所限制。
则CPU的频率将一直被目前4GHz的天花板所限制。

在频率上短期内己经没有提高的余地了，于是人们开始想办法从另外一个角度来提高CPU的速度，就是增加CPU的数量。一个计算机拥有多个CPU早就不是什么新鲜事了，
很早以前就有了多CPU的计算机，其中最常见的一种形式就是**对称多处理器(SMP，Symmetrical Multi-Processing)**, 简单地讲就是每个CPU在系统中所处的地位和所发挥的功能都是一样的，是相互对称的。理论上讲，增加CPU的数量就可以提高运算速度，并且理想情况下，速度的提高与CPU的数量成正比。但实际上并非如此，因为我们的程序并不是都能分解成若干个完个不相干的了问题。

当然很多时候多处理器是常有用的，最常见的情况就是在大型的数据库、网络服务器上，它们要**同时处理大量的请求，而这些请求之间往往是相互独立的，所以多处理器就可以最大效能地挥威力**。


## 系统软件

系统软件这个念其实比较模糊，传统意义上一般将用于管理计算机本身的软件称为系统软件，以区别普通的应用程序。

系统软件可以分成两块：

* 一块是平台性的，比如操作系统内核、驱动程序、运行库和数以千计的系统工具：
* 另外一块是用于程序开发的，比如编译器、汇编器、接器开发工具和开发库。

本书将着重介绍系统软件的一部分，主要是**链接器和库**（包括运行库和开发库）的相关内容。

计算机系统软件体系结构采用一种层的结构，有人说过一句名言：

> **"计算机科学领域的任何问题都可以通过增加一个间接的中间层来解决"**

> "Any problem in computer science can be solved by another layer Of indirection."

这句话几乎概括了计算机系统软件体系结构的设计要点，整个体系结构从上到下都是按照严格的层次结构设计的。不仅是计算机系统软件整个体系是这样的，体系里面的每个组件比如操作系统本身，很多应用程序、软件系统甚至很多硬件结构都是按照这种层次的结构组织和设计的。

系统软件体系结构中，各种软件的位置如图所示。

![](/_images/book-note/linkersAndLoaders/计算机软件体系结构.png)

**每个层次之间都须要相互通信**，既然须要通信就必须有一个通信的协议，我们一般将其称为接口(lnterface），**接口的下面那层是接口的提供者，由它定义接口：接口的上面那层是接口的使用者，它使用该接口来实现所需要的功能。**

虚拟机技术也是在硬件和操作系统之间增加了一层虚拟层，使得一个计算机上可以同时运行多个操作系统，这也是层次结构带来的好处。在尽可能少改变至不改变其他层的情况下，新增加一个层次就可以提供前所未有的功能。 ———— docker的layer思想也和这个类似

运行库使用操作系统提供的**系统调用接口(System call Interface)**，系统调用接口在实现中往往以软件中断方式提供，比如Linux使用0x80号中断作为系统调用接口。

操作系统内核层对于硬件层来说是硬们接口使用者，而硬件是接口定义者，硬件的接口定义决定了操作系统内核，具体来说就是**驱动程序如何操作硬件，如何与硬件进行通信。**


## 操作系统

不要让CPU打盹

从早期的一个CPU运行一个程序  ———— 通过监控程序采用多道程序的方法，让一个程序无需使用CPU时，其他等待CPU资源的程序可以运行 ————
改进后，每个程序运行一段时间后都能主动让出CPU给其他程序(分时系统)，存在问题(一个程序死循环导致其他程序得不到调用) ———— 引入多任务系统，所有应用程序都以进程方式运行，CPU采用抢占式即CPU在多个进程间快速切换，从而造成很多进程同时运行的假象。

* 并发: 两个或多个事件在同一时间间隔发生。(分时复用，单核，时间分片)
* 并行: 两个或多个事件在同一时刻发生。(多核处理器，绑核运行)

### 设备驱动

操作系统作为硬件层的上层，它是对硬件的管理和抽象。对于操作系统上面的运行库和应用程序来说，它们希望看到的是一个统一的**硬件访问模式**。作为应用程序的开发者，我们不希望在开发应用程序的时候直接读写硬件端口、处理硬件中断等这些繁琐的事情。由于硬件之间了差万别，它而的操作方式和访问方式都有区别。

当成熟的操作系统出现以后，硬件逐渐被抽象成了一系列概念。在UNIX中，硬件设备的访问形式跟访问普通的文件形式一样：在Windous系统中，图形硬件被抽象成了GDI，声音和多媒体没备被抽象成了DirectX对象：磁盘被抽象成了普通文件系统等等。

这些繁琐的硬件细节都交给了操作系统，具体地讲是**操作系统中的硬件驱动（Device Driver）程序来完成**。驱动程序可以看作是操作系统的一部分，它往往跟操作系统内核一起运行在特权级，但它又与操作系统内核之间有一定的独立性，使得驱动程序有比较好的灵活性。

因为PC的硬件多如牛毛，操作系统开发者不可能为每个硬件开发一个驱动程序，这些驱动程序的开发工作通常由硬件生产厂商完成。操作系统开发者为硬件生产厂商提供了一系列接口和框架，凡是按照这个接口和框架开发的驱动程序都可以在该操作系统上使用。———— 类似 适配器模式，根据操作系统提供的接口，硬件厂商做接口适配。

### 内存

**如何将有限的物理内存分配给多个程序使用？**

假设我们的计算机有128MB内存，程序A运行需要10MB，程序B需要100MB，程序c需要20MB。如果我们需要同时运行程序A和B，那么比较直接的做法是将内存的前
10MB分配给程序A，10MB、110MB分配给B。这样就能够实现A和B两个程序同时运行，但是这种简单的内存分配策略问题很多。

* **地址空间不隔离**
  * 恶意程序可能修改其他程序的内存数据
* **内存使用效率低**
  * 需要执行其他程序时，可能需要置换当前程序的内存到磁盘
* **程序运行地址不确定**
  * 每次程序运行都给它从内存中拿出一块空闲的区域

解决这个问题的思路：增加中间层，即使用一种间接的地址访问方法。

把程序给出的地址看作是一种虚拟地址（Virtual Address)，然后通过某些映射的方法，将这个虚拟地址转换成实际的物理地址。

这样，只要我们能够妥地控制这个**虚拟地址到物理地址的映射过程**，就可以保证任意一个程序所能够访问的物理内存区域跟另外一个程序相压不重叠，以达到**地址空间隔离**的效果。

### 关于隔离

**C++命令空间，docker运行隔离**

所谓的地址空间是个比较抽象的概念，你可以把它想象成一个很大的数组，每个数组的元素是一个字节，而这个数组大小由地址空间的地址长度决定，比如32位的地址空间的大小为2^32=4294967296字节，即4GB,地址空间有效的地址是0~4294967295，用十六进制表示就是0x00000000~0xFFFFFFFF。

地址空间分两种：虚拟地址空间(Virtual Address Space)和物理地址空间(Physical Address Space)。

物理地址空间是实实在在存在的，存在于计算机中，32位机器的物理空间就有4GB。虚拟地址空间是指虚拟的、人们想象出来的地址空间，其实它并不存在，**每个进程都有自己独立的虚拟空间，而且每个进程只能访问自己的地址空间，这样就有效地做到了进程隔离。**

### 分段

分段思想：将一段与程序所需内存空间大小的虚拟空间映射到某个地址空间。这个映射过程由软件来设置，比如操作系统来设置这个映射函数。

![](/_images/book-note/linkersAndLoaders/段映射机制.png)

分段没有内存使用效率的问题。分段对内存区域的映射还是按照**程序为单位**，如果内存不足，被换入换出到磁盘的都是整个程序，会造成大量的磁盘访问操作，从而严重影响速度。

根据程序的局部性原理，当一个程序在运行时，在某个时间段内，它只是频繁地用到了一小部分数据，即程序的很多数据其实在一个时间段内都是不会被用到的。人们很自然地想到了**更小粒度的内存分割和映射的方法**，使得程序的局部性原理得到充分的利用，大大提高了内存的使用率。这种方法就是**分页(Paging)**。

备注：mmap将一个文件或者其它对象映射进内存。mmap()系统调用使得进程之间通过映射同一个普通文件实现共享内存。普通文件被映射到进程地址空间后，进程可以像访问普通内存一样对文件进行访问，不必再调用read()，write()等操作。

### 分页

分页思想：把地址空间人为地等分成固定大小的页，通常为4KB大小。

以32位的PC机为例，4GB物理内存按照4KB每页分的话，总共有1048576个页。

把虚拟空间的页就叫虚拟页(VP,Virtual Page), 把物理内存中的页叫做物理页(PP,Physical Page), 把磁盘中的页叫做磁盘页(DP,Disk Page)。图中的线表示映射关系，可以看到虚拟空间的有些页被映射到同一个物理页，这样就可以实现内存共享。

![](/_images/book-note/linkersAndLoaders/分页映射关系.png)

虚拟存储的实现需要依靠硬件的支持，对于不同的CPU来说是不同的。但是几乎所有的硬件都采用一个叫MMU(Memory Management Unit)的部件来进行页映射。

![](/_images/book-note/linkersAndLoaders/虚拟地址到物理地址的转换.png)

## 线程基础

线程(Thread), 有时被称为轻量级进程(Lightweight Process,LWP), 是程序执行流的最小单元。

一个标准的线程由线程D、当前指令指针(PC)、寄存器集合和堆栈组成。通常意义上，一个进程由一个到多个线程组成，各个线程之间共享程序的内存空间（包括代码段、数据段、堆等)及一些进程级的资源（如打开文件和信号）。

一个经典的线程与进程的关系如图所示。

![](/_images/book-note/linkersAndLoaders/进程内的线程.png)

### 线程的访问权限

线程的访问非常自由，**它可以访问进程内存里的所有数据，甚至包括其他线程的堆栈**（如果它知道其他线程的堆栈地址，那么这就是很少见的情况)，但实际运用中线程也拥有自己
的私有存储空间，包括以下几方面。

* 栈（尽管并非完全无法被其他线程访问，但一般情况下仍然可以认为是私有的数据）。
* 线程局部存储(Thread Local Storage,.TLS)。线程局部存储是某些操作系统为线程单独提供的私有空间，但通常只具有很有限的容量。
* 寄存器（包括PC寄存器），寄存器是执行流的基本数据，因此为线程私有。

从C程序员的角度来看，数据在线程之间是否私有如表所示。

![](/_images/book-note/linkersAndLoaders/线程的访问权限.png)

### 线程调度与优先级

不论是在多处理器的计算机上还是在单处理器的计算机上，线程总是“并发”执行的。当线程数量小于等于处理器数量时（并且操作系统支持多处理器），**线程的并发是真正的并发，不同的线程运行在不同的处理器上**，彼此之间互不相干。但对于线程数量大于处理器数量的情况，线程的并发实际上就是模拟出来的分时复用。

线程调度的状态：

* 运行(Running): 线程正在执行。
* 就绪(Ready): 线程可以立刻运行，但CPU已经被占用。
* 等待(Waiting):  线程正在等待某一事件（通常是I/O或同步）发生，无法执行。


![](/_images/book-note/linkersAndLoaders/线程状态切换.png)

线程调度自多任务操作系统问世以来就不断地被提出不同的方案和算法。现在主流的调度方式尽管各不相同，但都带有**优先级调度(Priority Schedule)和轮转法(Round Robin)的痕迹**。所谓轮转法，即是之前提到的让各个线程轮流执行一小段时间的方法。

一般把频繁等待的线程称之为IO密集型线程(IO Bound Thread), 而把很少等待的线程称为CPU密集型线程(CPU Bound Thread)。IO密集型线程总是比CPU密集型线程**容易得到优先级的提升**。


在**优先级调度下，存在一种饿死(Starvation)的现象**，一个线程被饿死，是说它的优先级较低，在它执行之前，总是有较高优先级的线程试图执行，因此这个低优先级线程始终无法执行。当一个CPU密集型的线程获得较高的优先级时，许多低优先级的进程就很可能饿死。而一个高优先级的IO密集型线程由于大部分时间都处于等待状态，因此相对不容易造成其他线程饿死。为了避免饿死现象，**调度系统常常会逐步提升那些等待了过长时间的得不到执行的线程的优先级**。在这样的手段下，一个线程只要等待足够长的时间，其优先级一定会提高到足够让它执行的程度。

在优先级调度的环境下，线程的优先级改变一般有三种方式。

* 用户指定优先级。
* 根据进入等待状态的频繁程度提升或降低优先级。
* 长时间得不到执行而被提升优先级。

### 可抢占线程和不可抢占线程

线程调度有一个特点，那就是线程在用尽时间片之后会被强制剥夺继续执行的权利，而进入就绪状态，这个过程叫做**抢占(Preemption)**,即之后执行的别的线程抢占了当前线程。

在不可抢占线程中，线程主动放弃执行无非两种情况。

* 当线程试图等待某事件时(I/O等)。
* 线程主动放弃时间片。

因此，在不可抢占线程执行的时候，有一个显著的特点，那就是线程调度的时机是确定的，线程调度只会发生在线程主动放弃执行或线程等待某事件的时候。这样可以避免一些因为**抢占式线程里调度时机不确定而产生的问题（线程安全）**。但即使如此，非抢占式线程在今日已经十分少见。

## Linux的多线程

Linux下创建新任务：

![](/_images/book-note/linkersAndLoaders/Linux创建新任务.png)

写时复制：

![](/_images/book-note/linkersAndLoaders/写时复制.png)

### 线程安全

#### 竞争和原子操作

API的原子操作，例如atomic(atomic是c++11推出的原子变量)

#### 同步与锁

为了避免多个线程同时读写同一个数据而产生不可预料的后果，需要将各个线程对同一个数据的访问同步(Synchronization)。所谓同步，既是指在一个线程访问数据未结束的时候，其他线程不得对同一个数据进行访问。

同步的最常见方法是使用锁(Lock)。锁是一种非强制机制，每一个线程在访问数据或资源之前首先试图获取(Acquire)锁，并在访问结束之后释放(Release)锁。在锁已经被占用的时候试图获取锁时，线程会等待，直到锁重新可用。

**二元信号量(Binary Semaphore)**: 最简单的一种锁，它只有两种状态：占用与非占用。它适合只能被唯一一个线程独占访问的资源，**信号量在整个系统可以被任意线程获取并释放，即同一个信号量可以被系统中的一个线程获取之后由另一个线程释放。。**

**多元信号量**简称信号量(Semaphore): 允许多个线程并发访问的资源, 是一个初始值为N的信号量允许N个线程并发访问。

**互斥量(Mutx)**：和二元信号量很类似，但互斥量则要求哪个线程获取了互斥量，哪个线程就要负责释放这个锁，**其他线程越俎代庖去释放互斥量是无效的**。

**临界区(Critical Section)**：在术语中，把临界区的锁的获取称为进入临界区，而把锁的释放称为离开临界区。临界区和互斥量与信号量的区别在于，互斥量和信号量在系统的任何进程里都是可见的，也就是说，一个进程创建了一个互斥量或信号量，另一个进程试图去获取该锁是合法的。然而，**临界区的作用范围仅限于本进程，其他的进程无法获取该锁**。除此之外，临界区具有和互斥量相同的性质。

**读写锁(Read-Write Lock)**：对于同一个锁，读写锁有两种获取方式共享的(Shared)或独占的(Exclusive)。读写锁的行为可以总结如下：

![](/_images/book-note/linkersAndLoaders/读写锁行为.png)

**条件变量**：对于条件变量，线程可以有两种操作，首先线程可以等待条件变量（线程池会这样使用），一个条件变量可以被多个线程等待。其次，线程可以唤醒条件变量，此时某个或所有等待此条件变量的线程都会被唤醒并继续支持。也就是说，使用条件变量可以让许多线程一起等待某个事件的发生，当事件发生时(条件变量被唤醒)，所有的线程可以一起恢复执行。

#### 可重入与线程安全

一个函数被重入，表示这个函数没有执行完成，由于外部因素或内部调用，又一次进入该函数执行。一个函数要被重入，只有两种情况：

1. 多个线程同时执行这个函数。
2. 函数自身（可能是经过多层调用之后）调用自身。

一个函数被称为可重入的，表明该函数被重入之后不会产生任何不良后果。

举个例子，如下面这个sqrt函数就是可重入的：

```cpp
int sqr(int x){
  return x*x;
}
```

一个函数要成为可重入，必须具有以下几个特点：

* 不使用任何（局部）静态或全局的非const变量
* 不返回任何（局部）静态或全局的非const变量的指针。
* 仅依赖于调用方提供的参数。
* 不依赖任何单个资源的锁(mutex等)。
* 不调用任何不可重入的函数。

可重入是并发安全的强力保障，一个可重入的函数可以在多线程环境下放心使用。

### 过度优化

CPU动态调度，执行程序时，为了提高效率**有可能交换指令的顺序**。同样，编译器在进行优化的时候，也可能为了效率而交换两条相邻指令的执行顺序。

可以使用volatile关键字试图阻止过度优化，volatile基本可以做到两件事情：

1. 阻止编译器为了提高速度将一个变量缓存到寄存器内而不写回。
2. 阻止编译器调整操作volatile变量的指令顺序。

因为即使volatile能够阻止编译器调整顺序，也无法阻止CPU动态调度换序。

```cpp
volatile T*pInst 0;
T* GetInstance()
{
  if(pInst==NULL)
  {
    lock();
    if (pInst =NULL)
        pInst new T;
    unlock();
  }
  return pInst
}
```

TODO 双重if可以让lock的开销降到最低。

## 多线程内部

三种线程模型

一对一模型：

![](/_images/book-note/linkersAndLoaders/一对一模型.png)

多对一模型：

![](/_images/book-note/linkersAndLoaders/多对一模型.png)

多对多模型：

![](/_images/book-note/linkersAndLoaders/多对多模型.png)