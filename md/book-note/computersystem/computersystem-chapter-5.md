# 第5章 优化程序性能

[[toc]]

# 参考资料

* [《深入理解计算机系统》学习笔记整理（CSAPP 学习笔记）](https://www.cnblogs.com/xsqblogs/p/14688428.html)
* [汇编指令学习](https://blog.csdn.net/weixin_39962356/article/details/111344962 )

# 优化程序性能
编写高效程序需要做到以下几点：

  1.合适的算法和数据结构

  2.编写出编译器能够有效优化以转换成高效可执行代码的源代码（例如，在C语言中，指针运算和强制类型转换使得编译器很难对它进行优化）。

  3.针对处理运算量特别大的计算，将一个任务分成多部分，即利用并行性。

## 优化编译器的能力和局限性

**GCC优化指令**
  **-Og:**默认配置，不优化。

  -O1:编译器试图优化代码大小和执行时间，它主要对代码的分支，常量以及表达式等进行优化，但不执行任何会占用大量编译时间的优化。

  -O2:GCC执行几乎所有不包含时间和空间权衡的优化（比如，尝试更多的寄存器级的优化以及指令级的优化）。与-O相比，此选项增加了编译时间，但提高了代码的效率。

  **-O3:**比-O2更优化，对于-O3编译选项，在-O2的基础上，打开了更多的优化项（比如，使用伪寄存器网络，普通函数的内联，以及针对循环的更多优化）。不过可能导致编译出来的二级制程序不能debug。

  **-Os:**主要是对代码大小的优化，我们基本不用做更多的关心。 通常各种优化都会打乱程序的结构，让调试工作变得无从着手。并且会打乱执行顺序，依赖内存操作顺序的程序需要做相关处理才能确保程序的正确性。

妨碍编译器优化的因素：

* 内存别名使用
* 函数调用

### 内存别名使用

  两个指针可能指向同一个内存位置的情况成为内存别名使用。

```cpp
void twiddle1 (long *xp,long*yp)
{
	*xp+ = *yp;
	*xp+ = *yp;
}
void twiddle2(long *xp,long*yp)
{
	*xp+ = 2 * *yp;
}
```

分析：

twiddle1它们都是将存储在由指针yp指示的位置处的值两次加到指针xp指示的位置处的值。twiddle2需要3次内存引用（读* xp，读yp，写* xp）。 twiddle1需要6次（2次读* xp，2次读yp，2次写* xp），一般，我们认为twiddle2要优于twiddle2。那么将twiddle1优化是不是就能产生类似twiddle2的代码了？

答案显然是不可以的。当 xp和 yp指向相同内存单元时 ，twiddle1执行后的结果是：xp的值增加4倍。而twiddle2的结果是xp的值增加3倍。因此，两个程序是有本质差别的。

以上这个例子就介绍了内存别名使用，在只执行安全的优化中，<font color='red'>**编译器必须假设不同的指针可能会指向内存中同一位置。**</font>

### 函数调用

```cpp
long func1(){
	return f() + f() + f() + f() 
}

long func2(){
	return 4*f()
}

long counter=0;
long f(){
 	return counter++
}
```

这个函数有个副作用——它修改了全局程序状态的一部分。改变它的调用次数会改变程序的行为：
func1返回的是0+1+2+3=6，func2返回的是4*0=0

大多数编译器不会试图判断一个函数是否有副作用，即编译器会假设最糟的情况，并保持所有的函数调用不变。

## 表示程序性能
  程序性能度量标准：每元素的周期数（Cycles Per Element，CPE）。这种度量标准帮助我们在更细节的级别上理解迭代程序的循环性能。

  处理器活动的顺序是由时钟控制的，时钟提供了某个频率的规律信号，通常用千兆赫兹（GHz），即十亿周期每秒来表示。例如，当表明一个系统有“4GHz”处理器，这表示处理器时钟运行频率这表示处理器时钟运行频率为每秒4 × 10 ^9 个周期。每个时钟周期的时间是时钟频率的倒数。通常是以纳秒（ nanosecond，1纳秒等于1 0 ^-8秒）或皮秒（ picosecond，1皮秒等于10^-12 秒）为单位的。例如，一个4GHz的时钟其周期为0.25纳秒，或者250皮秒。从程序员的角度来看，用时钟周期来表示度量标准要比用纳秒或皮秒来表示有帮助得多。用时钟周期来表示，度量值表示的是执行了多少条指令，而不是时钟运行得有多快。

## 程序示例

程序优化的第一步就是消除不必要的工作，让代码尽可能有效地执行所期望的任务。这包括消除不必要的函数调用、条件测试和内存引用。这些优化不依赖目标机器的任何具体属性。了解了处理器的运作，就可以进行程序优化的第二步，利用处理器提供的指令级并行能力，同时执行多条指令。

为了清晰地说明如何去优化一个程序，这里使用一个如下向量数据结构的运行示例。

向量由两部分组成：头部和数据数组

```cpp
typedef long data_t;
typedef struct {
    long len;
    data_t *data;
} vec_rec, *vec_ptr;

vec_ptr new_vec(long len)
{
    /* 为头部结构体分配内存 */
    vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec));
    data_t *data = NULL;
    if (!result) return NULL;/* 头部创建失败 */
    result->len = len;
    if (len > 0)
    {
        data = (data_t*) calloc(len, sizeof(data_t));
        if(!data)
        {
            free((void*) result);
            return NULL;/* 存储空间分配失败 */
        }
    }
    result->data = data;
    return result;
}

int get_vec_element(vec_ptr v, long index, data_t *dest)
{
    if(index < 0 || index >= v->len) return 0;
    *dest = v->data[index];
    return 1;
}

long vec_length(vector v)
{
    return v->len;
}

//求和
#define IDENT 0
#define OP +

//求积
#define IDENT 1
#define OP *

void combine1(vec_ptr v, data_t *dest)
{
    long i;
 
    *dest = IDENT;
    for (i = 0; i < vec_length(v); i++)
    {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest + val;
    }
}
```

简单地使用命令行选项“-O1”，就会进行一些基本的优化。

![优化-O1](/_images/book-note/computersystem/optimizeProgram/优化-O1.png)

## 消除循环的低效率

```cpp
void combine2 (vec_ptr v, data_t *dest)
{
	long i;
	long length=vec_length(v);
	*dest = IDENT;
	for (i=0;i< length;i++)
	{
		data_t val;
		get_vec_element(v,i,&val);
		*dest = *dest OP val;
	}
}
```

可以看出combine2函数只计算一次向量长度，保存在length中，以提升程序运行的效率。

这个优化叫做**代码移动，这类优化主要解决那些需要执行多次但每次计算结果不会改变的计算**。

编译器会试着进行代码移动以优化程序，但是对于有些函数来说，调用次数不同或者调用位置不同会导致调用结果也有不同，如一个计算函数自身被调用次数的函数。编译器不能可靠的发现对某些函数进行代码移动是否会带来负面影响，那么它就不会对这段代码进行优化。为了改进代码，程序员必须经常帮助编译器显示地完成代码移动。

编程时，应该关注看上去无足轻重的代码片段有隐藏的渐近低效率。

![combine2](/_images/book-note/computersystem/optimizeProgram/combine2.png)

## 减少过程调用

从combine2的代码中我们可以看出，每次循环迭代都会调用get_vec_element来获取下一个向量元素。对每个向量引用，这个函数要把向量索引i与循环边界做比较，很明显会造成低效率。在处理任意的数组访问时，边界检查可能是个很有用的特性，但是对 combine2代码的简单分析表明所有的引用都是合法的。

```cpp
data_t *get_vec_start(vec_ptr v)
{
	return v->data;
}
/* Move call to vec_length out of loop */
void combine3 (vec_ptr v, data_t *dest)
{
	long i;
	long length=vec_length(v);
    data_t *data = get_vec_start(v);
	*dest = IDENT;
	for (i=0;i< length;i++)
	{
		*dest = *dest OP data[i];
	}
}
```

作为替代，假设为我们的抽象数据类型增加一个函数get_vec_start。这个函数返回数组的起始地址，然后就能写出此combine3所示的过程，其内循环里没有函数调用。它没有用函数调用来获取每个向量元素，而是直接访问数组。

  事实上，经过这一步后，并没有使得性能有较大提升，后面会详细讲到。这只是我们优化路上的一步。

![combine3](/_images/book-note/computersystem/optimizeProgram/combine3.png)

## 消除不必要的内存引用

```cpp
#Inner loop of combines. data_t double, OP =
#dest in %rbx, data+i in %rdx, data+length in %rax 
.L17:
vmovsd (%rbx),%xmm()           # Read product from dest 
vmulsd (%rdx),%xmm0,%xmm0      # Multiply product by data[i]
vmovsd %xmm, (%rbx）           # Store product at dest
addq $8,%rdx                   # Increment data+i
cmp %rax,%rdx                  # Compare to data+length 
jne .L17
```

  在这段循环代码中，我们看到，指针dest的地址存放在寄存器%rbx中，它还改变了代码，将第i个数据元素的指针保存在寄存器%rdx中，注释中显示为data+i。每次迭代，这个指针都加8。循环终止操作通过比较这个指针与保存在寄存器各ax中的数值来判断。我们可以看到每次迭代时，累积变量的数值都要从内存读出再写入到内存。这样的读写很浪费，因为**每次迭代开始时从dest读出的值就是上次迭代最后写入的值。**

  我们能够消除这种不必要的内存读写， combine4所示的方式如下。**引入一个临时变量acc，它在循环中用来累积计算出来的值。**只有在循环完成之后结果才存放在dest中。正如下面的汇编代码所示，编译器现在可以用寄存器%xmm0来保存累积值。

```cpp
#Inner loop of combines. data_t double, OP =
#dest in %rbx, data+i in %rdx, data+length in %rax 
.L25:
vmulsd (%rdx),%xmm0,%xmm0      # Multiply product by data[i]
addq $8,%rdx                   # Increment data+i
cmp %rax,%rdx                  # Compare to data+length 
jne .L25

void combine4 (vec_ptr v, data_t *dest)
{
	long i;
	long length vec_length(v);
    data_t *data = get_vec_start(v);
	data acc = IDENT;
	for (i=0;i< length;i++)
	{
		acc = acc OP data[i];
	}
	*dest = acc;
}
```

  把结果累积在临时变量中。将累积值存放在局部变量acc（累积器（ accumulator）的简写）中，消除了每次循环迭代中从内存中读出并将更新值写回的需要。

  程序性能如下（以int整数为例），单位为CPE。

![combine4](/_images/book-note/computersystem/optimizeProgram/combine4.png)

直接使用编译优化选项：

![使用编译优化选项](/_images/book-note/computersystem/optimizeProgram/使用编译优化选项.png)

## 理解现代处理器

目前为止，运用的优化都不依赖于目标机器的任何特性。这些优化只是简单地<font color='red'>**消除循环的低效率、减少过程调用、消除不必要的内存引用等**</font>，这些因素会给优化编译器造成困难。

随着试图进一步提高性能，必须考虑利用处理器微体系结构的优化，即处理器用来执行指令的底层系统设计。

当一系列操作必须按照严格顺序执行时，就会遇到延迟界限，因为在下一条指令开始之前，延迟界限能够限制程序性能。

吞吐量界限刻画了处理器功能单元的原始计算能力。

### 整体操作
基本概念

* 超标量（superscalar）：在每个时钟周期执行多个操作
* 乱序（out-of-order）：指令执行的顺序不一定要与它们在机器级程序中的顺序一致

 ![乱序处理器的框图](/_images/book-note/computersystem/optimizeProgram/乱序处理器的框图.png)


  如上图所示，为一个乱序处理器的框图。整个设计有两个主要部分：<font color='red'>**指令控制单元（ Instruction Control Unit,ICU）和执行单元（ Execution Unit,EU）。前者负责从内存中读出指令序列，并根据这些指令序列生成一组针对程序数据的基本操作；而后者执行这些操作。**</font>

  **指令高速缓存（Instruction cache**）：一个特殊的高速存储器，它包含最近访问的指令。

  **分支预测（branch prediction）**：处理器会猜测是否会选择分支，同时还预测分支的目标地址。使用**投机执行（ speculative execution）**的技术，处理器会开始取出位于它预测的分支，会跳到的地方的指令，并对指令译码，甚至在它确定分支预测是否正确之前就开始执行这些操作。如果过后确定分支预测错误，会将状态重新设置到分支点的状态，并开始取出和执行另一个方向上的指令。标记为取指控制的块包括分支预测，以完成确定取哪些指令的任务。

  **指令译码逻辑**：一条指令会被译码成多个操作。例如，addq %rax,8(%rdx)，。这条指令会被译码成为三个操作：一个操作从内存中加载一个值到处理器中，一个操作将加载进来的值加上寄存器%rax中的值,而一个操作将结果存回到内存。

  **读写内存**是由加载和存储单元实现的。加载单元处理从内存读数据到处理器的操作。这个单元有一个加法器来完成地址计算。类似，存储单元处理从处理器写数据到内存的操作。它也有一个加法器来完成地址计算。如图中所示，加载和存储单元通过**数据高速缓存（ data cache）**来访问内存。数据高速缓存是一个高速存储器，存放着最近访问的数据值。

  **退役单元（ retirement unit）**:记录正在进行的处理，并确保它遵守机器级程序的顺序语义。退役单元控制这些寄存器的更新。指令译码时，关于指令的信息被放置在一个先进先出的队列中。这个信息会一直保持在队列中，直到发生以下两个结果中的一个。首先，一旦一条指令的操作完成了，而且所有引起这条指令的分支点也都被确认为预测正确，那么这条指令就可以退役（ retired）了，所有对程序寄存器的更新都可以被实际执行了。另一方面，如果引起该指令的某个分支点预测错误，这条指令会被清空（ flushed），丢弃所有计算出来的结果。通过这种方法，预测错误就不会改变程序的状态了。(**任何对程序寄存器的更新都只会在指令退役时才会发生**)

  **寄存器重命名（ register renaming）**：当一条更新寄存器r的指令译码时，产生标记t，得到一个指向该操作结果的唯一的标识符。条目（r,t）被加入到一张表中，该表维护着每个程序寄存器r与会更新该寄存器的操作的标记t之间的关联。当随后以寄存器r作为操作数的指令译码时，发送到执行单元的操作会包含t作为操作数源的值。当某个执行单元完成第一个操作时，会生成一个结果（v,t），指明标记为t的操作产生值v。所有等待t作为源的操作都能使用v作为源值，这就是一种形式的数据转发。通过这种机制，值可以从一个操作直接转发到另一个操作，而不是写到寄存器文件再读出来，使得第二个操作能够在第一个操作完成后尽快开始。重命名表只包含关于有未进行写操作的寄存器条目。当一条被译码的指令需要寄存器r，而又没有标记与这个寄存器相关联，那么可以直接从寄存器文件中获取这个操作数。有了寄存器重命名，即使只有在处理器确定了分支结果之后才能更新寄存器，也可以预测着执行操作的整个序列。

### 功能单元的性能

  延迟（ latency）：它表示完成运算所需要的总时间。

  发射时间（ Issue time）：它表示两个连续的同类型的运算之间需要的最小时钟周期数。(发射时间为1：完全流水线化)

**浮点数加法器流水线化分为三个阶段**：一个阶段处理指数值，一个阶段将小数相加，而另一个阶段对结果进行舍入。

  容量（ capacity）：它表示能够执行该运算的功能单元的数量。

  延迟界限：完成合并运算的函数所需要的最小CPE值。

  最大吞吐量：发射时间的倒数。给出了CPE的最小界限。对于一个容量为C，发射时间为I的操作来说，处理器可能获得的吞吐量为每时钟周期C/I个操作。

在Core i7 Haswell处理器的设计中，整数乘法、浮点乘法和加法被认为是重要的操作，即使为了获得低延迟的较高的流水线化程度需要大量的硬件。另一方面，除法相对不太常用，而且要想实现低延迟或完全流水线是很困难的。

![延迟和吞吐量](/_images/book-note/computersystem/optimizeProgram/延迟和吞吐量.png)

### 处理器操作的抽象模型

我们可以用数据流表示处理器上执行的机器级程序性能，这是一种图形，展现不同操作之间的数据相关是如何限制它们的执行顺序的。这些限制形成了图中的**关键路径**，这是执行一组机器指令所需时钟周期数的下界。

目前为止，combine4是最快的代码：

![combine4的数据](/_images/book-note/computersystem/optimizeProgram/combine4的数据.png)

从机器级代码到数据流图：

以combine4的代码为例，汇编代码如下：

```
.L25:
vmulsd (%rdx),%xmm0,%xmm0      # Multiply product by data[i]
addq $8,%rdx                   # Increment data+i
cmp %rax,%rdx                  # Compare to data+length 
jne .L25
```

combine4的内循环代码的图形化表示：

 ![combine4的内循环代码的图形化表示](/_images/book-note/computersystem/optimizeProgram/combine4的内循环代码的图形化表示.png)

对于形成循环的代码片段，可以将访问到的寄存器分为四类:

只读、只写、局部、循环。

抽象成数据流图，可以得到：

 ![combine4数据流图](/_images/book-note/computersystem/optimizeProgram/combine4数据流图.png)

以乘法为例子，数据操作流有两条，分别是mul和add两个操作对于acc和data[i]的修改组成，如下：

可见，如果mul需要5个周期，add需要1个周期，那么mul将成为关键路径，循环结束需要5n的周期。另外，从上面的CPE图可以看到，对于整数加法，CPE为1.27，而根据关键路径图预测的CPE应该为1.0，实际值比预测值慢，说明关键路径提供的只是下界。还有其他因素限制性能，比如可用的功能单元数量和任何一步中功能单元之间能够传递数值的数量等。

总结一下，根据抽象数据流表示说明，combine4的关键路径长L* n是由对acc的连续更新造成的，这条路径将CPE限制为最多L。对于整数加法，测量出的CPE大于关键路径所期望的CPE。

## 循环展开
  循环展开是一种程序变换，**通过增加每次迭代计算的元素的数量，减少循环的迭代次数。**

循环展开能够从两个方面改进程序的性能。

* 减少了不直接有助于程序结果的操作的数量，例如循环索引计算和条件分支。
* 它提供了一些方法，可以进一步变化代码，减少整个计算中关键路径上的操作数量。    

```cpp
/*使用2×1循环展开。这种变换能减小循环开销的影响*/
void combine5(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    long limit = length-1;
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;
    
    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=2) {
        acc = (acc OP data[i]) OP data[i+1];
    }
    /* Finish any remaining elements */
    for (; i < length; i++) {
        acc = acc OP data[i];
    }
    *dest = acc;
}
```
![combine5](/_images/book-note/computersystem/optimizeProgram/combine5.png)
  上述代码是使用的"2 * 1循环展开"的版本。第一个循环每次处理数组的两个元素。也就是每次迭代，循环索引i加2，在一次迭代中，对数组元素i和i+1使用合并运算。（注意访问不要越界，正确设置limit，n个元素，一般设置界限n-1)。

  K×1循环展开次数和性能提升并不是正比关系，一般来讲，最多循环展开一次后，性能提升就不会很大了（主要原因是关键路径中n个mul操作，迭代次数减半，但是每次迭代中还是有两个顺序的乘法操作。)

## 提高并行性

### 多个累积变量
```cpp
/*2 * 2 loop unrolling*/
/*运用2×2循环展开。通过维护多个累积变量，这种方法利用了多个功能单元以及它们的流水线能力*/
void combine6(vec_ptr v, data_t *dest)
{
	long i;
    long length = vec_length(v);
    long limit = length-1;
    data_t *data = get_vec_start(v);
    data_t acc0 = IDENT;
    data_t acc1 = IDENT;
    
    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=2) {
		acc0 = acc0 OP data[i];
		acc1 = acc1 OP data[i+1];
    }
    /* Finish any remaining elements */
    for (; i < length; i++) {
        acc0 = acc0 OP data[i];
    }
    *dest = acc0 OP acc1;
}
```

  上述代码用了两次循环展开，以使每次迭代合并更多的元素，也使用了两路并行，将索引值为偶数的元素累积在变量acc0中，而索引值为奇数的元素累积在变量acc1中。因此，我们将其称为”2×2循环展开”。同前面一样，我们还包括了第二个循环，对于向量长度不为2的倍数时，这个循环要累积所有剩下的数组元素。然后，我们对acc0和acc1应用合并运算，计算最终的结果。

  事实上，combine6比combine5性能提升近2倍左右。

![combine6](/_images/book-note/computersystem/optimizeProgram/combine6.png)

### 重新结合变换
```cpp
/*2 * 1a loop unrolling*/
/*运用2×1a循环展开，重新结合合并操作。这种方法增加了可以并行执行的操作数量*/
void combine7(vec_ptr v, data_t *dest)
{
	long i;
    long length = vec_length(v);
    long limit = length-1;
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;
    
    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=2) {
		acc = acc OP (data[i] OP data[i+1]);
    }
    /* Finish any remaining elements */
    for (; i < length; i++) {
        acc = acc OP data[i];
    }
    *dest = acc;
}
```

  我们可以看到关键路径上只有n/2个操作。每次迭代内的第一个乘法都不需要等待前一次迭代的累积值就可以执行。因此，最小可能的CPE减少了2倍。这种改进方式几乎达到了吞吐量的极限。

  在执行重新结合变换时，我们又一次改变向量元素合并的顺序。对于整数加法和乘法，这些运算是可结合的，这表示这种重新变换顺序对结果没有影响。对于浮点数情况，必须再次评估这种重新结合是否有可能严重影响结果。我们会说对大多数应用来说，这种差别不重要。

  总的来说，**重新结合变换能够减少计算中关键路径上操作的数量，通过更好地利用功能单元的流水线能力得到更好的性能**。大多数编译器不会尝试对浮点运算做重新结合，因为这些运算不保证是可结合的。当前的GCC版本会对整数运算执行重新结合，但不是总有好的效果。通常，我们发现循环展开和并行地累积在多个值中，是提高程序性能的更可靠的方法。

## 一些限制因素
### 寄存器溢出
  我们可以看到对这种循环展开程度的增加没有改善CPE，有些甚至还变差了。现代x86-64处理器有16个寄存器，并可以使用16个YMM寄存器来保存浮点数。一旦循环变量的数量超过了可用寄存器的数量，程序就必须在栈上分配一些变量。
例如，下面的代码片段展示了在10×10循环展开的内循环中，累积变量acc0是如何更新的：

```
# Updating of accumulator acco in 10 x 10 unrolling 
vmulsd (%rdx),%xmm,%xmm0       #acc0 *=data[i]
```

  我们看到该累积变量被保存在寄存器%xmm0中，因此程序可以简单地从内存中读取data[i],并与这个寄存器相乘。

  与之相比，20×20循环展开的相应部分非常不同：

```
# Updating of accumulator acco in 20 x 20 unrolling 
vmovsd 40(%rsp),%xmm0
vmulsd (%rdx),%xmm0,%xmm0
vmovsd %xmmO,40(%rsp)
```

  累积变量保存为栈上的一个局部变量，其位置距离栈指针偏移量为40。程序必须从内存中读取两个数值：累积变量的值和data[i]的值，将两者相乘后，将结果保存回内存。

  一旦编译器必须要诉诸寄存器溢出，那么维护多个累积变量的优势就很可能消失。幸运的是，x86-64有足够多的寄存器，大多数循环在出现寄存器溢出之前就将达到吞吐量限制。

### 分支预测何预测错误惩罚
  现代处理器的工作远远超前于当前正在执行的指令。

1.不要过分关心可预测的分支

  我们已经看到错误的分支预测的影响可能非常大，但是这并不意味着所有的程序分支都会减缓程序的执行。实际上，现代处理器中的分支预测逻辑非常善于辨别不同的分支指令的有规律的模式和长期的趋势。例如，在合并函数中结束循环的分支通常会被预测为选择分支，因此只在最后一次会导致预测错误处罚。

2.书写适合用条件传送实现的代码

  程序中的许多测试是完全不可预测的，依赖于数据的任意特性，例如一个数是负数还是正数。对于这些测试，分支预测逻辑会处理得很糟糕。对于本质上无法预测的情况，如果编译器能够产生使用条件数据传送而不是使用条件控制转移的代码，可以极大地提高程序的性能。

  我们发现GCC能够为以一种更“功能性的”风格书写的代码产生条件传送，在这种风格的代码中，我们用条件操作来计算值，然后用这些值来更新程序状态，这种风格对立于一种更“命令式的”风格，这种风格中，我们用条件语句来有选择地更新程序状态。

## 理解内存性能
**加载的性能**

* 现代处理器有专门的功能单元来执行加载和存储操作，这些单元有内部的缓冲区来保存未完成的内存操作请求集合。一个包含加载操作的程序的性能既依赖于流水线的能力，也依赖于加载

**单元的延迟**

* 要确定一台机器上加载操作的延迟，我们可以建立由一系列加载操作组成的一个计算，一条加载操作的结果决定下一条操作的地址。举例如下：

## 性能提高技术
  虽然只考虑了有限的一组应用程序，但是我们能得出关于如何编写高效代码的很重要的经验教训。总结如下：

**(1)高级设计**

  为遇到的问题选择适当的算法和数据结构。要特别警觉，避免使用那些会渐进地产生糟糕性能的算法或编码技术。

**(2)基本编码原则**

  避免限制优化的因素，这样编译器就能产生高效的代码。

  消除连续的函数调用。在可能时，将计算移到循环外。考虑有选择地妥协程序的模块性以获得更大的效率。

  消除不必要的内存引用。引入临时变量来保存中间结果。只有在最后的值计算出来时，才将结果存放到数组或全局变量中。

**(3)低级优化**

  结构化代码以利用硬件功能。

  展开循环，降低开销，并且使得进一步的优化成为可能。

  通过使用例如多个累积变量和重新结合等技术，找到方法提高指令级并行。

  用功能性的风格重写条件操作，使得编译采用条件数据传送。

**(4)使用性能分析工具**

  当处理大型程序时，将注意力集中在最耗时的部分变得很重要。代码剖析程序和相关的工具能帮助我们系统地评价和改进程序性能。我们描述了 GPROF，一个标准的Unix剖析工具。还有更加复杂完善的剖析程序可用，例如 Intel的VTUNE程序开发系统，还有 Linux系统基本上都有的 VALGRIND。这些工具可以在过程级分解执行时间，估计程序每个基本块（ basic block）的性能。（基本块是内部没有控制转移的指令序列，因此基本块总是整个被执行的。)

  最后要给读者一个忠告，要警惕，在为了提高效率重写程序时避免引入错误。在引人新变量、改变循环边界和使得代码整体上更复杂时，很容易犯错误。一项有用的技术是在优化函数时，用检查代码来测试函数的每个版本，以确保在这个过程没有引入错误。检查代码对函数的新版本实施一系列的测试，确保它们产生与原来一样的结果。对于高度优化的代码，这组测试情况必须变得更加广泛，因为要考虑的情况也更多。例如，使用循环展开的检査代码需要测试许多不同的循环界限，保证它能够处理最终单步迭代所需要的所有不同的可能的数字。
