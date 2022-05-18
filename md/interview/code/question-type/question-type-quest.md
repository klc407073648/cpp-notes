无重复字符的最长子串:

```
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int maxLen=0;
        int size=s.size();
        map<char,int> res;

        for(int i=0;i<size;i++){
            for(int j=i;j<size;j++){
                if(res.count(s[j])){
                    break;
                }
                else{
                    res[s[j]]=1;
                }
            }
            maxLen=maxLen>res.size()?maxLen:res.size();
            res.clear();
        }

        return maxLen;

    }
};
```

考虑使用set


三数之和:
```
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        map<vector<int>,int> mymap;
        int size=nums.size();
        for(int i=0;i<size;i++){
            for(int j=i+1;j<size;j++){
                for(int k=j+1;k<size;k++){
                if(nums[i]+nums[j]+nums[k]==0){
                    vector<int> tmp={nums[i],nums[j],nums[k]};
                    sort(tmp.begin(),tmp.end());
                    if(mymap.count(tmp)){
                        //ok
                    }
                    else{
                        mymap[tmp]=1;
                        res.push_back(tmp);
                    }
                }
              }
            }
        }

        return res;
    }
};
```
排序+双指针，自然规避掉重复解

只出现一次的数字:
```
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        map<int,int> res;
        for(int i=0;i<nums.size();i++){
            if(res.count(nums[i])){
                res[nums[i]]++;
            }
            else{
                res[nums[i]]=1;
            }
        }

        map<int,int>::iterator iter=res.begin();
        for(;iter!=res.end();iter++){
            if(iter->second==1){
                return iter->first;
            }   
        }
        return 0;
    }
};
```

数组中的全部元素的异或运算结果即为数组中只出现一次的数字。


组合总和：
回溯算法  和 深度优先遍历


多数元素：

```
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        map<int,int> res;
        int size=nums.size();

        for(int i=0;i<size;i++){
            if(res.count(nums[i])){
                res[nums[i]]++;
            }
            else{
                res[nums[i]]=1;
            }
        }

        map<int,int>::iterator iter=res.begin();

        for(;iter!=res.end();iter++){
            if(iter->second > size/2){
                return iter->first;
            }
        }

        return nums[0];
    }
};
```

优化，考虑遍历的时候维护最大数。

```
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> counts;
        int majority = 0, cnt = 0;
        for (int num: nums) {
            ++counts[num];
            if (counts[num] > cnt) {
                majority = num;
                cnt = counts[num];
            }
        }
        return majority;
    }
};
```

比特位计数
```
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> res;

        for(int i=0;i<=n;i++){

            if(i==0){
                res.push_back(0);
                continue;
            }

            int tmp=i;
            int count=0;

            while(tmp){
                if(tmp&1==1){
                    count++;
                }

                tmp=tmp/2;
            }

            res.push_back(count);
        }

        return res;
    }
};
```

找到所有数组中消失的数字
```
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int size=nums.size();
        vector<int> res(size+1,0);
        vector<int> result;
        for(int i=0;i<size;i++){
            res[nums[i]]++;
        }

        for(int i=1;i<res.size();i++){
            if(res[i]==0){
                result.push_back(i);
            }
        }

        return result;
    }
};
```

括号生成：

```
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string curStr="";
        getResult(n,n,curStr,res);
        return res;
    }

    void getResult(int left,int right,string& curStr,vector<string>& res){
        if(left==0 && right==0){
            res.push_back(curStr);
            return;
        }

        if(left>0){
            curStr.push_back('(');
            getResult(left-1,right,curStr,res);
            curStr.pop_back();
        }
        
        if(right>left){
            curStr.push_back(')');
            getResult(left,right-1,curStr,res);
            curStr.pop_back();
        }
    }
};
```

合并区间
```
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
        sort(intervals.begin(),intervals.end());
        //sort(intervals.begin(),intervals.end(),compare);
    
        for(int i=0;i<intervals.size()-1;i++){
            if(intervals[i][1]<intervals[i+1][0]){
                res.push_back(intervals[i]);
            }
            else if(intervals[i][1]>=intervals[i+1][0] && intervals[i][1]<=intervals[i+1][1]){
                intervals[i+1][0]=intervals[i][0];
            }
            else if(intervals[i][1]>intervals[i+1][1]){
                intervals[i+1][0]=intervals[i][0];
                intervals[i+1][1]=intervals[i][1];
            }
        }

        res.push_back(intervals[intervals.size()-1]);
        return res;
    }

    static bool compare(const vector<int>& nums1,const vector<int>& nums2){
        if(nums1[0]<nums2[0] || (nums1[0]==nums2[0] && nums1[1]<nums2[1])){
            return true;
        }
        return false;
    }
};
```

有效的括号:
```
class Solution {
public:
    bool isValid(string s) {
        stack<char> res;
        int size=s.size();

        for(int i=0;i<size;i++){
            if( s[i]=='(' || s[i]=='[' || s[i]=='{'){
                res.push(s[i]);
            }
            else if( s[i]==')' ){
                if(res.size()==0 || (res.top()!='(')){
                    return false;
                }
                res.pop();
            }
            else if( s[i]==']' ){
                if(res.size()==0 || (res.top()!='[')){
                    return false;
                }
                res.pop();
            }
            else if( s[i]=='}'){
                if(res.size()==0 || (res.top()!='{')){
                    return false;
                }
                res.pop();
            }
        }

        if(res.size()!=0){
            return false;
        }
        
        return true;
    }
};
```

最长有效括号:
```
class Solution {
public:
    int longestValidParentheses(string s) {
        int size=s.size();
        int maxLen=0;
        int left=0;
        int right=0;

        for(int i=0;i<size;i++){
            if(s[i]=='('){
                left++;
            }
            else if(s[i]==')'){
                right++;
            }

            if(right>left){
                left=right=0;
            }
            else if(left==right){
                maxLen=maxLen>2*left?maxLen:2*left;
            }     
        }
        
        //最初方法漏了从右边遍历的情况
        left = right = 0;
        for (int i = size - 1; i >= 0; i--) {
            if(s[i]=='('){
                left++;
            }
            else if(s[i]==')'){
                right++;
            }
            
            if (left > right) {
                left = right = 0;
            }
            else if (left == right) {
                maxLen=maxLen>2*left?maxLen:2*left;
            } 
        }

        return maxLen;
    }
};

//利用栈结构

class Solution {
public:
    int longestValidParentheses(string s) {
        int maxans = 0;
        stack<int> stk;
        stk.push(-1);
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                stk.push(i);
            } else {
                stk.pop();
                if (stk.empty()) {
                    stk.push(i);
                } else {
                    maxans = max(maxans, i - stk.top());
                }
            }
        }
        return maxans;
    }
};

```

思考用动态规划？？

寻找两个正序数组的中位数：

合并数组后找中位数的值，注意double要提前转换。
```
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        double result;
        int num1=nums1.size();
        int num2=nums2.size();
        int sum=num1+num2;
        vector<int> res;

        int i=0,j=0;
        while(i<num1 && j<num2){
            if(nums1[i]<nums2[j]){
                res.push_back(nums1[i]);
                i++;
            }
            else{
                res.push_back(nums2[j]);
                j++;
            }
        }

        while(i<num1 && j>=num2){
            res.push_back(nums1[i]);
            i++;
        }

        while(i>=num1 && j<num2){
            res.push_back(nums2[j]);
            j++;
        }

        if(sum%2==0)
            return (double(res[sum/2]) + double(res[(sum/2) -1]))/2;
        else
             return double(res[sum/2]);
    }
};
```

只保存找到中位数对应位置的内容
```
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        double result;
        int num1=nums1.size();
        int num2=nums2.size();
        int sum=num1+num2;
        vector<int> res;

        int i=0,j=0;
        bool isFind=false;
        while(i<num1 && j<num2){
            if(nums1[i]<nums2[j]){
                res.push_back(nums1[i]);
                i++;
            }
            else{
                res.push_back(nums2[j]);
                j++;
            }
            if((i+j)==sum/2+1){
                isFind=true;
                break;
            }
        }

        while(i<num1 && j>=num2 && !isFind){
            res.push_back(nums1[i]);
            i++;
            if((i+j)==sum/2+1){
                break;
            }
        }

        while(i>=num1 && j<num2&& !isFind){
            res.push_back(nums2[j]);
            j++;
            if((i+j)==sum/2+1){
                break;
            }
        }

        if(sum%2==0)
            return (double(res[sum/2]) + double(res[(sum/2) -1]))/2;
        else
             return double(res[sum/2]);
    }
};
```

环形链表
```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow=head;
        ListNode *fast=head;

        while(slow!=NULL && fast!=NULL){
            if(slow->next){
                slow=slow->next;
            }
            else
            {
                break;
            }

            if(fast->next && fast->next->next){
                fast=fast->next->next;
            }
            else
            {
                break;
            }

            if(slow==fast){
                return true;
            }
        }

        return false;
    }
};



public class Solution {
    public boolean hasCycle(ListNode head) {
        if (head == null || head.next == null) {
            return false;
        }
        ListNode slow = head;
        ListNode fast = head.next;
        while (slow != fast) {
            if (fast == null || fast.next == null) {
                return false;
            }
            slow = slow.next;
            fast = fast.next.next;
        }
        return true;
    }
}
```


sort(res.begin(),res.end());
vector<vector<int>>::iterator new_end=unique(res.begin(),res.end());
res.erase(new_end,res.end());


旋转图像:
```
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n=matrix.size();

        //00 11 
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < (n + 1) / 2; ++j) {
                swap(matrix[i][j],matrix[j][n-i-1]);
                swap(matrix[i][j],matrix[n-i-1][n-j-1]);
                swap(matrix[i][j],matrix[n-j-1][i]);
            }
        }
    }
};
```

位运算  异或

跳跃游戏——未全部通过
```
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int size=nums.size()-1;
        int pos=0;
        bool res=false;
        dfs(size,pos,nums,res);

        return res;
    }

    void dfs(int size,int pos,vector<int> nums,bool& res){
        if(pos==size){
            res=true;
        }

        for(int i=nums[pos];i>=1;i--){
            if(pos+i<=size){
                dfs(size,pos+i,nums,res);
            }
        }
    }
};
```
考虑找到提前返回

49. 字母异位词分组

考虑set，且每个字符出现一次的场景，遍历找到出现字符串相同的为一组

```
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>>  res;
        int size=strs.size();
        vector<int> vec(size,0);

        for(int i=0;i<size;i++){
            if(vec[i]==1)
                continue;

            set<char> myset;
            string cur=strs[i];
            vector<string> curRes;
            for(int c=0;c<cur.size();c++){
                myset.insert(cur[c]);
            }
            curRes.push_back(cur);

            for(int j=i+1;j<size;j++){
                if(vec[j]==1)
                  continue;
                string curStr=strs[j];
                set<char> tmpSet=myset;

                if(curStr.size()==cur.size()){
                    for(int c=0;c<curStr.size();c++){
                        if(tmpSet.count(curStr[c])){
                            tmpSet.erase(curStr[c]);
                        }
                    }

                    if(tmpSet.size()==0)
                    {
                        curRes.push_back(curStr);
                        vec[j]=1;
                    }
                }
            }
            
            res.push_back(curRes);
        }

        return res;

    }
};


优化解法:
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string,vector<string>> mp;
        int size=strs.size();
        for(int i=0;i<size;i++){
            string cur=strs[i];
            sort(cur.begin(),cur.end());
            mp[cur].emplace_back(strs[i]);
        }

        vector<vector<string>> ans;
        for(map<string,vector<string>>::iterator iter=mp.begin();iter!=mp.end();iter++){
            ans.emplace_back(iter->second);
        }

        return ans;
    }
};
```

142. 环形链表 II

```
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *cur=head;
        set<ListNode*> mset;
        mset.insert(head);
        while(cur!=NULL ){  
            cur=cur->next;

            if(mset.count(cur)){
                return cur;
            }
            else{
                mset.insert(cur);
            }
        }

        return NULL;
    }
};

优化set实际上还是红黑树，可以用hashmap的unordered_set提高查询速度

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode*> mset;
        while(head!=NULL ){  
            if(mset.count(head))
                return head;
            
            mset.insert(head);
            head=head->next;
        }

        return NULL;
    }
};
```

64. 最小路径和
```
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
       
        for(int j=n-2;j>=0;j--){
            grid[m-1][j]=grid[m-1][j]+grid[m-1][j+1];
        }

        for(int i=m-2;i>=0;i--){
            grid[i][n-1]=grid[i][n-1]+grid[i+1][n-1];
        }

        for(int i=m-2;i>=0;i--){
            for(int j=n-2;j>=0;j--){
                grid[i][j]=grid[i][j]+min(grid[i][j+1],grid[i+1][j]);
            }
        }

        return grid[0][0];
    }
};
```

200. 岛屿数量

```
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        int num=0;
        
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                queue<vector<int>> queue;
                vector<int> vec;
                if(grid[i][j]=='1'){
                  vec.push_back(i);
                  vec.push_back(j);
                  queue.push(vec);
                  num++;
                  while(!queue.empty()){
                    vector<int> curVec=queue.front();
                    queue.pop();

                    if(curVec[0]+1<m && grid[curVec[0]+1][curVec[1]]=='1'){
                        grid[curVec[0]+1][curVec[1]]='0';
                        vector<int> tmp;
                        tmp.push_back(curVec[0]+1);
                        tmp.push_back(curVec[1]);
                        queue.push(tmp);
                    }

                    if(curVec[1]+1<n && grid[curVec[0]][curVec[1]+1]=='1'){
                        grid[curVec[0]][curVec[1]+1]='0';
                        vector<int> tmp;
                        tmp.push_back(curVec[0]);
                        tmp.push_back(curVec[1]+1);
                        queue.push(tmp);
                    }

                    if(curVec[0]-1>=0 && grid[curVec[0]-1][curVec[1]]=='1'){
                        grid[curVec[0]-1][curVec[1]]='0';
                        vector<int> tmp;
                        tmp.push_back(curVec[0]-1);
                        tmp.push_back(curVec[1]);
                        queue.push(tmp);
                    }

                    if(curVec[1]-1>=0 && grid[curVec[0]][curVec[1]-1]=='1'){
                        grid[curVec[0]][curVec[1]-1]='0';
                        vector<int> tmp;
                        tmp.push_back(curVec[0]);
                        tmp.push_back(curVec[1]-1);
                        queue.push(tmp);
                    }
                  } 
                }
            }
        }

        return num;
    }
};


优化vector<int>的内容queue.push({row+1,col});

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        int num=0;
        
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                queue<vector<int>> queue;
                vector<int> vec;
                if(grid[i][j]=='1'){
                  queue.push({i,j});
                  num++;
                  while(!queue.empty()){
                    vector<int> curVec=queue.front();
                    queue.pop();
                    int row= curVec[0];
                    int col= curVec[1];

                    if(row+1<m && grid[row+1][col]=='1'){
                        grid[row+1][col]='0';
                        queue.push({row+1,col});
                    }

                    if(col+1<n && grid[row][col+1]=='1'){
                        grid[row][col+1]='0';
                        queue.push({row,col+1});
                    }

                    if(row-1>=0 && grid[row-1][col]=='1'){
                        grid[row-1][col]='0';
                        queue.push({row-1,col});
                    }

                    if(col-1>=0 && grid[row][col-1]=='1'){
                        grid[row][col-1]='0';
                        queue.push({row,col-1});
                    }
                  } 
                }
            }
        }

        return num;
    }
};

最优解，考虑queue<pair<int, int>> neighbors;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int nr = grid.size();
        if (!nr) return 0;
        int nc = grid[0].size();

        int num_islands = 0;
        for (int r = 0; r < nr; ++r) {
            for (int c = 0; c < nc; ++c) {
                if (grid[r][c] == '1') {
                    ++num_islands;
                    grid[r][c] = '0';
                    queue<pair<int, int>> neighbors;
                    neighbors.push({r, c});
                    while (!neighbors.empty()) {
                        auto rc = neighbors.front();
                        neighbors.pop();
                        int row = rc.first, col = rc.second;
                        if (row - 1 >= 0 && grid[row-1][col] == '1') {
                            neighbors.push({row-1, col});
                            grid[row-1][col] = '0';
                        }
                        if (row + 1 < nr && grid[row+1][col] == '1') {
                            neighbors.push({row+1, col});
                            grid[row+1][col] = '0';
                        }
                        if (col - 1 >= 0 && grid[row][col-1] == '1') {
                            neighbors.push({row, col-1});
                            grid[row][col-1] = '0';
                        }
                        if (col + 1 < nc && grid[row][col+1] == '1') {
                            neighbors.push({row, col+1});
                            grid[row][col+1] = '0';
                        }
                    }
                }
            }
        }

        return num_islands;
    }
};
```

221. 最大正方形
```
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m=matrix.size();
        int n=matrix[0].size();

        int maxSum=0;

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(matrix[i][j]=='1'){
                    int curSum=1;
                    queue<pair<int,int>> queue;
                    queue.push({i,j});

                    while(!queue.empty()){
                        int size=queue.size();
                        bool isTrue=true;
                        for(int c=0;c<size;c++){
                            pair<int,int> top=queue.front();
                            int row=top.first;
                            int col=top.second;

                            if( (row+1<m && matrix[row+1][col]=='1') && (col+1<n && matrix[row][col+1]=='1') && (row+1<m && col+1<n && matrix[row+1][col+1]=='1')){
                                queue.push({row+1,col});
                                queue.push({row,col+1});
                                queue.push({row+1,col+1});
                            }
                            else{
                                isTrue=false;
                                break;
                            }

                            queue.pop();
                        }
                        if(!isTrue){
                            break;
                        }
                        curSum++;
                    }
                    maxSum=max(curSum,maxSum);
                }
            }
        }
        return maxSum*maxSum;
    }
};
```

234. 回文链表

```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
         vector<int> vec;

         while(head){
             vec.push_back(head->val);
             head=head->next;
         }

         int left=0,right=vec.size()-1;

         while(left<right){
             if(vec[left]==vec[right]){
                 left++;
                 right--;
             }
             else
             {
                 break;
             }
         }

         return left>=right;
    }
};

优化解:
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> vals;
        while (head != nullptr) {
            vals.emplace_back(head->val);
            head = head->next;
        }
        for (int i = 0, j = (int)vals.size() - 1; i < j; ++i, --j) {
            if (vals[i] != vals[j]) {
                return false;
            }
        }
        return true;
    }
};

```