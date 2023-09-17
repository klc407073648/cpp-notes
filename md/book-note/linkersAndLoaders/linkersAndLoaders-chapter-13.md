# 第13章 运行库实现

[[toc]]

# 文章总结

![](/_images/book-note/linkersAndLoaders/运行库实现.png)

# C语言运行库

在开始实现MiniCRT之前，首先要对它进行基本的规划。“麻雀虽小五脏俱全”，虽MiniCRT很小，但它应该具备CRT的基本功能以及遵循几个基本设计原则，这些我们归结为如下几个方曲：

* 首先MiniCRT应该以ANIS C的标准库为目标，尽量做到与其接口相一致。
* 具有自己的入口函数(mini_crt_entry)。
* 基本的进程相关操作(exit)。
* 支持堆操作(malloc、free）。
* 支持基本的文件操作（fopen、fread、fwrite、fclose、fseek）。
* 支持基本的字符串操作（strcpy、strlen、strcmp)。
* 支持格式化字符串和输出操作(printf,sprintf)。
* 支持atexit()函数。
* 支持跨平台的，Windows和Linux两个操作系统。
* 实现尽量简单，以展示CRT的实现为目的，并不追求功能和性能。