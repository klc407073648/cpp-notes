# 常见排序算法知识体系详解

> 排序算法是《数据结构与算法》中最基本的算法之一。

[[toc]]

# 概述

排序算法可以分为内部排序和外部排序，内部排序是数据记录在内存中进行排序，而外部排序是因排序的数据很大，一次不能容纳全部的排序记录，在排序过程中需要访问外存。

常见的内部排序算法有：插入排序、希尔排序、选择排序、冒泡排序、归并排序、快速排序、堆排序、基数排序等。用一张图概括：

![](/_images/programming/algorithm/sort/排序算法总结.png)

进一步，更详细的内容如下：

![](/_images/programming/algorithm/sort/详细内容.png)

> 补充: 算法稳定性 -- 假设在数列中存在a[i]=a[j]，若在排序之前，a[i]在a[j]前面；并且排序之后，a[i]仍然在a[j]前面。则这个排序算法是稳定的！ 

# 文章导航

* [冒泡排序](/md/c++/programming/algorithm/sort/algorithm-sort-bubble.md)
* [选择排序](/md/c++/programming/algorithm/sort/algorithm-sort-select.md)
* [插入排序](/md/c++/programming/algorithm/sort/algorithm-sort-insert.md)
* [希尔排序](/md/c++/programming/algorithm/sort/algorithm-sort-shell.md)
* [归并排序](/md/c++/programming/algorithm/sort/algorithm-sort-merge.md)
* [快速排序](/md/c++/programming/algorithm/sort/algorithm-sort-quick.md)
* [堆排序](/md/c++/programming/algorithm/sort/algorithm-sort-heap.md)
* [计数排序](/md/c++/programming/algorithm/sort/algorithm-sort-counting.md)
* [桶排序](/md/c++/programming/algorithm/sort/algorithm-sort-bucket.md)
* [基数排序](/md/c++/programming/algorithm/sort/algorithm-sort-radix.md)

