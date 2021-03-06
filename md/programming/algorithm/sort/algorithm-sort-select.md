# 排序 - 选择排序(Selection sort)

> 选择排序(Selection sort)是一种简单直观的排序算法。

[[toc]]

# 概述

选择排序是一种简单直观的排序算法，无论什么数据进去都是 O(n²) 的时间复杂度。所以用到它的时候，数据规模越小越好。唯一的好处可能就是不占用额外的内存空间了吧。

核心思想：

1. 首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置。
2. 再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。
3. 重复第二步，直到所有元素均排序完毕。

## 动图演示

![](/_images/programming/algorithm/sort/selectionSort.gif)

## 复杂度和稳定性 

### 选择排序时间复杂度 

选择排序的时间复杂度是O(N2)。 

假设被排序的数列中有N个数。遍历一趟的时间复杂度是O(N)，需要遍历多少次呢? N-1！因此，选择排序的时间复杂度是O(N2)。

### 选择排序稳定性 

> 选择排序的稳定性是有一些争议的，不过一般提到排序算法，往往默认是**数组**实现，所以通常认为选择排序是不稳定的。

* 什么是排序算法的稳定性？ 

假定在待排序的记录序列中，存在多个具有相同的关键字的记录，若经过排序，这些记录的相对次序保持不变，即在原序列中，r[i]=r[j]，且r[i]在r[j]之前，而在排序后的序列中，r[i]仍在r[j]之前，则称这种排序算法是稳定的；否则称为不稳定的。 

* 数组实现和链表实现的差异 

用数组实现的选择排序是不稳定的，用链表实现的选择排序是稳定的。 不过，一般提到排序算法时，大家往往会默认是数组实现，所以选择排序是不稳定的。

* 此外，排序算法的稳定性也是可以改变的，只是需要额外的时间和空间 

有很多办法可以将任意排序算法变成稳定的，但是，往往需要额外的时间或者空间；而我们默认情况谈算法的稳定性是不考虑这种实现的。

疑问？选择排序为什么是不稳定的？

## 代码实现

<<< @/md/programming/algorithm/sort/src/selectSort.cpp
