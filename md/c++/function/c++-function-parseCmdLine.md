# C++函数 - getopt函数分析以及命令行解析

> 在Linux下运行可执行程序时，一般需要带特定参数以指定运行的方式。通过是采用getopt()函数解析传入的参数内容，其头文件为<unistd.h>。

[[toc]]

下面来具体介绍getopt的原型: 

```cpp
int getopt(int argc,char * const argv[ ],const char * optstring);
```

参数argc和argv分别代表参数个数和内容，参数 optstring为选项字符串。

**getopt() 所设置的全局变量包括**: 

* extern char *optarg;
* extern int optind, opterr, optopt;
* optarg——指向当前选项参数（如果有）的指针。 
* optind——再次调用 getopt() 时的下一个 argv 指针的索引。
* opterr——是否将错误信息输出到stderr，为0时表示不输出。
* optopt——不在选项字符串optstring中的选项。

**选项和参数的概念**:

* 单个字符，表示选项;(例如 g++ -o main main.cpp -std=c++11，其中o就是命令行的选项，而后面的main就是选项所带的参数。)
* 单个字符后接一个冒号: 表示该选项后必须跟一个参数。`参数紧跟在选项后或者以空格隔开`。该参数的指针赋给optarg。
* 单个字符后跟两个冒号，表示该选项后必须跟一个参数。`参数必须紧跟在选项后不能以空格隔开`。该参数的指针赋给optarg。

**短参数的定义**:

   getopt()使用optstring所指的字串作为短参数列表，像"1ac:d::"就是一个短参数列表。短参数的定义是一个'-'后面跟一个字母或数字，例如-a, -b就是一个短参数。每个数字或字母定义一个参数。 

　　其中短参数在getopt定义里分为三种: 

 1. 不带值的参数，它的定义即是参数本身。
 2. 必须带值的参数，它的定义是在参数本身后面再加一个冒号。
 3. 可选值的参数，它的定义是在参数本身后面加两个冒号 。

　　以"1ac:d::"为例，其中的1,a就是不带值的参数，c是必须带值的参数，d是可选值的参数。
　　在实际调用中，'-1 -a -c cvalue -d', '-1 -a -c cvalue -ddvalue', '-1a -ddvalue -c cvalue'都是合法的。注意事项: 

 1. 不带值的参数可以连写，像1和a是不带值的参数，它们可以-1 -a分开写，也可以-1a或-a1连写。
 2. 参数不分先后顺序，'-1a -c cvalue -ddvalue'和'-d -c cvalue -a1'的解析结果是一样的。
 3. 要注意可选值的参数的值与参数之间不能有空格，必须写成-ddvalue这样的格式，如果写成-d dvalue这样的格式就会解析错误。

测试程序1，解析输入的ip,port和msg:


5. 类的this可以通过对象或者指针来绑定

测试程序1: 

::: details
<<< @/md/c++/function/src/parseCmdLine/main.cpp
::: 

执行结果: bash
```
[root@192 main函数命令行解析]# ./main
ip: 127.0.0.1
port: 8080
msg: Hello World
[root@192 main函数命令行解析]# ./main -i 10.43.33.115 -p 8888 -m Test
ip: 10.43.33.115
port: 8888
msg: Test
```

测试程序2，解析输入的"abcde":

执行结果: 
```bash
[root@192 main函数命令行解析]# ./main -a -b 123 -c 456 -d -e 555
HAVE option: -a
HAVE option: -b
The value of -b is 123
HAVE option: -c
The value of -c is 456
HAVE option: -d
HAVE option: -e
The value of -e is [root@192 main函数命令行解析]# ./main -b 123 -c 456 -d -e555 -a2
HAVE option: -b
The value of -b is 123
HAVE option: -c
The value of -c is 456
HAVE option: -d
HAVE option: -e
The value of -e is 555
HAVE option: -a
HAVE option: -2
```