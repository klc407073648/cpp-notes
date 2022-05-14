# 第六章：算法之set

[[toc]]

# set相关算法

STL提供了四种与set相关的算法，分别是并集（union）、交集（intersection）、差集（difference）和对称差集（symmetric difference），这4个算法接受的set必须是有序区间，都至少接受4个参数，分别表示两个set区间。所谓的set可细分为数学上的定义和STL的定义两种，数学上的set允许元素重复而未经排序，；例如{1,5,5,3,2}，STL的定义要求元素不得重复，且必须经过排序，例如{1,3,5,6}。

测试程序如下：

```cpp
#include <set>  // multiset
#include <iostream>
#include <algorithm>
#include <iterator> // ostream_iterator

using namespace std;

template <class T>
struct display {
    void operator() (const T& x) {
        cout << x << ' ';
    }
};

int main() {
    int ia1[6] = {1, 3, 5, 7, 9, 11};
    int ia2[7] = {1, 1, 2, 3, 5, 8, 13};

    multiset<int> S1(ia1, ia1 + 6);
    multiset<int> S2(ia2, ia2 + 7);

    for_each(S1.begin(), S1.end(), display<int>());
    cout << endl;
    for_each(S2.begin(), S2.end(), display<int>());
    cout << endl;

    auto first1 = S1.begin();
    auto last1 = S1.end();

    auto first2 = S2.begin();
    auto last2 = S2.end();

    cout << "Union of S1 and S2: ";
    set_union(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
    cout << endl;

    first1 = S1.begin();
    first2 = S2.begin();
    cout << "Intersection of S1 and S2: ";
    set_intersection(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
    cout << endl;

    first1 = S1.begin();
    first2 = S2.begin();
    cout << "Difference of S1 and S2(S1-S2): ";
    set_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
    cout << endl;

    first1 = S1.begin();
    first2 = S2.begin();
    cout << "Symmetric difference of S1 and S2: ";
    set_symmetric_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
    cout << endl;
	
	first1 = S2.begin();
    first2 = S1.begin();
	last1 = S2.end();
    last2 = S1.end();
    cout << "Difference of S2 and S1(S2-S1): ";
    set_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
    cout << endl;
	
	return 0;
}
```
执行结果：

```cpp
[root@192 6_STL_algorithms]# ./6_5_set-algorithms
1 3 5 7 9 11
1 1 2 3 5 8 13
Union of S1 and S2: 1 1 2 3 5 7 8 9 11 13
Intersection of S1 and S2: 1 3 5
Difference of S1 and S2(S1-S2): 7 9 11
Symmetric difference of S1 and S2: 1 2 7 8 9 11 13
Difference of S2 and S1(S2-S1): 1 2 8 13
```

​