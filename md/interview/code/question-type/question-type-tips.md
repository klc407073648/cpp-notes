二分查找的刷题技巧：

搜索旋转排序数组————即<font color='red'>变形的二分查找，在局部具有排序性</font>


自定义排序

vector

```c++
static bool cmp_by_value(const pair<int,int> & lhs, const pair<int,int> & rhs) {
        return lhs.second > rhs.second;
    }

sort(tmp.begin(),tmp.end(),cmp_by_value);

struct cmp{
    bool operator()(const pair<int,int> & lhs, const pair<int,int> & rhs) {
        return lhs.second > rhs.second;
    }
};

sort(tmp.begin(),tmp.end(),cmp());
```

priority_queue:

```c++
struct cmp
{
    //重载()运算符 
    bool operator()(const vector<int>& n1, const vector<int>& n2)
    {
        return n1[1] > n2[1];
    }
};

priority_queue<vector<int>, vector<vector<int>>, cmp> heap;
```

二维数组查找，如果是有序的话，可以考虑对角线为起点。([240. 搜索二维矩阵 II](https://leetcode-cn.com/problems/search-a-2d-matrix-ii/))

和为K的子数组， 前缀和 + 哈希表优化
