

# 二分查找 Binary Search

[[toc]]

二分查找：

```cpp
int binarySearch(vector<int> &nums, int target)
{
	int left = 0;
	int right = nums.size() - 1;
	// 二分查找
	while (left <= right)
	{
		// 防止溢出
		int mid = left + ((right - left) >> 1);

		if (nums[mid] == target)
		{
			return mid;
		}
		else if (nums[mid] < target)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	return -1;
}
```

Binary Search 两大基本原则

1. 每次都要缩减搜索区域 —— Shrink the search space every iteration (or recursion)
2. 每次缩减不能排除潜在答案 —— Cannot exclude potential answers during each shrinking

三大模板

*  找一个准确值
  * 循环条件：l <= r
  * 缩减搜索空间：l = mid +1 , r = mid -1
* 找一个模糊值
  * 循环条件：l < r
  * 缩减搜索空间：l = mid , r = mid -1 或者 l = mid + 1, r = mid
* 万用型
  * 循环条件：l < r - 1
  * 缩减搜索空间：l = mid , r = mid

备注：有时候<font color='red'>mid = l + (r-l+1)/2</font>，保证每次mid停在靠右的位置(对应奇偶的情况)

适用题型：

```
搜索插入位置
搜索旋转排序数组————即变形的二分查找，在局部具有排序性
```

vector操作

```
vector<int> vec = {1,2};//初始化
```

两数之和:

```
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

方法一：暴力枚举，两次for循环
方法二：哈希法，每次只需要判断 target-nums[i] 是否存在
```



