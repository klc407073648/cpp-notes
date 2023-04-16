# C++函数 - va_list函数学习

> 使用场景描述: 当函数的入参个数不确定时，使用va_list函数进行动态处理，增加编程的灵活性。

[[toc]]

## va_list 使用方法以及注意事项

**使用方法**: 
1. 首先在函数中定义一个具有va_list型的变量，这个变量是指向参数的指针。
2. 然后用va_start宏初始化变量刚定义的va_list变量，使其指向第一个可变参数的地址。
3. 然后va_arg返回可变参数，va_arg的第二个参数是你要返回的参数的类型（如果多个可变参数，依次调用va_arg获取各个参数）。
4. 最后使用va_end宏结束可变参数的获取。


**注意事项**: 
1. 可变参数的类型和个数完全由代码控制，它并不能智能地识别不同参数的个数和类型。
2. 如果我们不需要一一详解每个参数，只需要将可变列表拷贝到某个缓冲区，可以用vsprintf函数。
3. 因为编译器对可变参数的函数原型检查不够严格，对编程查错不利，不利于我们写出高质量的代码。

**补充**: 

vasprintf()函数 :int vasprintf (char **buf, const char *format, va_list ap)

将格式化数据从可变参数列表写入缓冲区

## 具体使用方法

下述实例，采用了myFun1和myFun2两种方式讲述了va_list的具体实现过程。myFun1主要采用根据格式format（即可变参数类型顺序已经确定），将可变参数一个个赋值到最终的string中，myFun2采用执行时指定可变参数类型，从而完成处理。

::: details
<<< @/md/c++/function/src/va_listFun/main.cpp
::: 

执行结果: 
```
[root@localhost funTest]# ./main
ret:Test va_list_Fun num:100 character:A str:mystring
count: 5
sumNum: 15
```
