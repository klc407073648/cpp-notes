# 字符串题型

[[toc]]

![整数反转](/_images/interview/code/question-type/string/整数反转.png)

题解：

```c
int reverse(int x)
{
    int res = 0;
    while (x)
    {
        int t = x % 10;
        // int newRes = res * 10 + t; C++ 这样写 res * 10 这里可能就溢出错误了
        // if ((newRes - t) / 10 != res) return 0;
        // res = newRes;
        if (res > INT_MAX / 10 || res < INT_MIN / 10)
            return 0;
        res = res * 10 + t;
        x /= 10;
    }
    return res;
}


if (res > (pow(2,31) - 1) / 10 || res < -pow(2,31) / 10)
   return 0;
```

技巧:INT_MAX和INT_MIN，或者用pow(2,31) - 1和 -pow(2,31)表示。

![字符串中的第一个唯一字符](/_images/interview/code/question-type/string/字符串中的第一个唯一字符.png)

题解：

```c++
int firstUniqChar(string s)
{
    //vector<int> vec(26,0);
    int vec[26] = {0};

    int size = s.size();
    for (int i = 0; i < size; i++)
    {
        vec[s[i] - 'a']++;//vec[s[i] - 97]++;
    }

    for (int i = 0; i < size; i++)
    {
        if (vec[s[i] - 'a'] == 1)
            return i;
    }

    return -1;
}
```

技巧:注意vector和a[]数组初始化，同时记住小写a对应数值为97，大写A对应字符为65，两者之差为32。

判断回文串：

```c++
bool isPalinderome(string str){
        int left=0;
        int right=str.size()-1;

        while(left<right){
            if(str[left++]!=str[right--]){
                return false;
            }
        }
        return true;
    }
```

全排列：

```c++
vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;

        if(nums.size()==0){
            return res;
        }

        int size=nums.size();
        int depth=0;
        vector<bool> isUsed(size,false);
        vector<int> tmpRes;

        for(int i=0;i<size();i++){
            if(isUsed[i]){
                continue;
            }
            isUsed[i] =true;
            tmp.push_back(nums[i]);
            dfs(nums,depth+1,isUsed,tmpRes,res)
            isUsed[i] =false;
            tmp.pop_back();
        }

        return res;
    }

    void dfs(vector<int>& nums,int depth,vector<bool> isUsed,vector<int> tmpRes,vector<vector<int>>& res){
        if(depth==nums.size()){
            res.push_back(tmpRes);
        }
    }
```

可以采用广度优先遍历和深度优先遍历

647. 回文子串
```c++
class Solution {
public:
    int countSubstrings(string s) {
        int size=s.size();
        int count=size;
        for(int i=0;i<size-1;i++){
            vector<char> cur={s[i]};
            for(int j=i+1;j<size;j++){
                cur.push_back(s[j]);
                if(isSubString(cur)){
                    count++;
                }
            }
        }

        return count;
    }

    bool isSubString(vector<char> s){
        int left=0,right=s.size()-1;

        while(left<right){
            if(s[left]!=s[right]){
                return false;
            }
            left++;
            right--;
        }
        return true;
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

