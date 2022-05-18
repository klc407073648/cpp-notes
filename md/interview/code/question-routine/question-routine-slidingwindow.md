
# 滑动窗口 

[[toc]]

> 滑动窗口 这种高级双指针技巧的算法框架。

模板:

```c++
/* 滑动窗口算法框架 */
void slidingWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;

    int left = 0, right = 0;
    int valid = 0; 
    while (right < s.size()) {
        // c 是将移入窗口的字符
        char c = s[right];
        // 右移窗口
        right++;
        // 进行窗口内数据的一系列更新
        ...

        /*** debug 输出的位置 ***/
        printf("window: [%d, %d)\n", left, right);
        /********************/

        // 判断左侧窗口是否要收缩
        while (window needs shrink) {
            // d 是将移出窗口的字符
            char d = s[left];
            // 左移窗口
            left++;
            // 进行窗口内数据的一系列更新
            ...
        }
    }
}
```

## 实践

### 76. 最小覆盖子串

 ![最小覆盖子串](/_images/interview/code/question-routine/SlideWindow/最小覆盖子串.png)

解题：

```c++
class Solution {
public:
    unordered_map <char, int> ori, cnt;

    bool check() {
        for (const auto &p: ori) {
            if (cnt[p.first] < p.second) {
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        for (const auto &c: t) {
            ++ori[c];
        }

        int l = 0, r = -1;
        int len = INT_MAX, ansL = -1, ansR = -1;

        while (r < int(s.size())) {
            if (ori.find(s[++r]) != ori.end()) {
                ++cnt[s[r]];
            }
            while (check() && l <= r) {
                if (r - l + 1 < len) {
                    len = r - l + 1;
                    ansL = l;
                }
                if (ori.find(s[l]) != ori.end()) {
                    --cnt[s[l]];
                }
                ++l;
            }
        }

        return ansL == -1 ? string() : s.substr(ansL, len);
    }
};
```





## 实践应用

### 例题 46. 全排列

 ![全排列](/_images/interview/code/question-routine/Backtrack/全排列.png)

以下为解题代码：
```c++
class Solution {
public:
    void backtrack(vector<vector<int>>& res, vector<int>& output, int first, int len){
        // 所有数都填完了
        if (first == len) {
            res.emplace_back(output);
            return;
        }
        for (int i = first; i < len; ++i) {
            // 动态维护数组
            swap(output[i], output[first]);
            // 继续递归填下一个数
            backtrack(res, output, first + 1, len);
            // 撤销操作
            swap(output[i], output[first]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > res;
        backtrack(res, nums, 0, (int)nums.size());
        return res;
    }
};

```

[438. 找到字符串中所有字母异位词](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/)

```c++
class Solution {
public:
    unordered_map<char, int> need, window;
    vector<int> findAnagrams(string s, string p) {
        for (char c : p) need[c]++;

        int left = 0, right = 0;
        vector<int> res;
        while (right < s.size()) {
            ++window[s[right++]];
            
            if((right-left)==p.size()){
                if(check()){
                    res.push_back(left);
                }
                --window[s[left++]];
            }
        }
        return res;
    }

    bool check() {
        for (const auto &p: need) {
            if ( !window.count(p.first) || window[p.first] != p.second) {
                return false;
            }
        }
        return true;
    }
};
```