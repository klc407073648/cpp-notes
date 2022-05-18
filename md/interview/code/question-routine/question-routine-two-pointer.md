# 双指针 Two Pointers

[[toc]]

https://turingplanet.org/2020/09/18/leetcode_planning_list/#Queue

双指针（Two Pointers）是一种<font color='red'>通过使用两个index pointers操作数组的方法</font>，使用双指针来迭代数组的话，一个array会被分为三个区域：[0, i), [i, j), [j, array.length)。

使用双指针时，我们必须要清楚地定义好每一块区域的含义，才能进行后续的解题。双指针解法一般分两种：<font color='red'>同向和反向</font>。

## 同向双指针

在同向双指针套路中，两个指针朝相同方向移动，但是快慢不同。其三个区域会被分割为下图所示：

 ![同向双指针](/_images/interview/code/question-routine/TwoPointers/同向双指针.png)

其中 [0, i) 的数据代表处理好的数据，[i, j) 中的数据是那些处理过但不需要的数据，[j, array.length) 区间的数据为接下来待处理的数据。

这里的三个区间的开和闭需要根据题目要求定义，但是要保持一致。用此方法处理过的数组，处理好的数据的相对位置要保持一致的。同向双指针的解题步骤如下：

1. Initialize two pointers i and j, usually both equal to 0
2. while j < array.length:
   - if we need array[j], then we keep it by assigning array[i] = array[j], and move i forward, make it ready at the next position
   - otherwise skip it. We do not need to move i since its spot is not fulfilled

## 反向双指针

反向双指针中的两个指针反向而行，同样分为三个区间：

 ![反向双指针](/_images/interview/code/question-routine/TwoPointers/反向双指针.png)

其中 [0, i) 和 (j, array.length) 内的数据均为处理好的数据，[i, j] 中的数据待处理。用此方法处理过的数组不会保留原来元素的相对位置。解题步骤如下：

1. Initialize two pointers i = 0, j = array.length – 1
2. while i <= j:
   - Decide what you should do based on the value of array[i] and array[j]
   - Move at least one pointer forward in its direction

## 实践应用

接下来我们就来讲解两道经典题目，帮助大家深入理解如何使用双指针套路。

### 例题 344. Reverse String

 ![旋转字符串](/_images/interview/code/question-routine/TwoPointers/旋转字符串.png)

这是一道很经典的字符串反转问题，如果可以使用上文的双指针套路，那么应该采取同向还是反向呢？

根据观察调换字符串的规律，我们发现只要从外往里，不断调换头部和尾部的元素就能颠倒一个字符串，那很明显和我们提到的反向双指针相关。

 ![Hello](/_images/interview/code/question-routine/TwoPointers/Hello.png)

以下为解题代码：

```
public char[] reverseString(char[] str) {
    // initialize
    int i = 0; j = str.length - 1;
    // two pointers opposite direction
    while (i < j) {
        // swap str[i] and str[j]
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
    return str;
}
```

可以发现代码逻辑和我们提到的反向指针套路完全一致，头尾为双指针的初始位置，根据题目要求，不断调换i, j指向的元素，每次循环后，i向右移动，j向左移动，直到两指针相遇即可。

### 例题 26. Remove Duplicates From Sorted Array

 ![移除重复数](/_images/interview/code/question-routine/TwoPointers/移除重复数.png)

此题要求我们删除重复字符，要注意的是去重之后元素的相对位置不能改变，比如[1, 2, 2, 3]去重后是[1, 2, 3]，而不能是[1, 3, 2]。既然输入数组是排好序的，那么对于每段重复元素，他们必定是相连的，我们只需要记录头元素即可，然后依次记录下那些互不重合的元素，就能解决此题了。这种需要依次记录下所需要元素的问题，就能完全使用同向指针的套路来解决，以下是解题步骤和代码：

1. Initialize two pointers i = 0, j = 0
2. while j < array.length:
   - if array[j] != array[i – 1], meaning it’s not a duplicate of what we had so far, then we keep it by array[i++] = array[j++]. Remember by definition [0, i) is already processed, not including i, so the last processed element is i – 1.
   - otherwise, it’s a duplicate of array[i], skip it with j++

```
public int removeDuplicates(int[] arr) {
    // initialization
    int i = 0, j = 0;
    while (j < arr.length) {
        // if not duplicate, keep it, otherwise skip it
        if (i == 0 || arr[j] != arr[i - 1]) {
            arr[i++] = arr[j++];
        } else {
            j++;
        }
    }
    // i is now at the length of the new array, [0, i) is what we want
    return i;
}
```

简单来说，[0 ~ i) 区间的元素是我们决定留下来的元素，i 指向的位置需要放入的是下一个不重复元素，j 指针是用来遍历整个数组的。在遍历过程中，如果 array[j] 和 array[i – 1] 不同，代表出现了一个新的不重复元素，那么就将新元素赋给 array[i]，否则向右移动 j 指针，直到 j 指针遍历完整个数组为止。

## 总结

可见双指针是用来解决很多常见数组题目的利器，其中包括同向和反向两个变种，大家需要根据题目的要求对三个区间的定义做相对应的调整。以下是和双指针相关的经典题目，大家可以通过实践来巩固此套路：

1. Container With Most Water (11)
2. Trapping Rain Water (42)
3. Move Zeros (283)
4. Remove Duplicates From Sorted Array II (80)
5. Remove All Adjacent Duplicates In String (1047)
