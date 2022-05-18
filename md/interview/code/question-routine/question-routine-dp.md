# DP (Dynamic Programming)

[[toc]]

> 从Search到DP，DP知识Seach上做一些优化与改进

## Search

当一个大问题是由多个子问题构成时，我们可以<font color='red'>通过不断分解问题来最终构建我们相求的大问题</font>。这个过程称为搜索(Search)。

搜索空间(Search Space)可以用Tree的形式展现出来，便于理解。

时间复杂度取决于这棵树的深度和每个node的children个数。

Search<font color='red'>**最重要的就是定义好状态，保证每个子问题都能用一个状态来描述**</font>。

## Top Down DFS模板

Top Down DFS模板

1. Define State of subproblems
2. Initialize initial state
3. Call dfs(init_state)

dfs(state)

1. Base Case Check
2. For each subproblem x
    a. <font color='red'>update state = next_state_x</font>
    b. branch down ——> call dfs(next_state_x)
    c. <font color='red'>restore state</font>

## 实践应用

### 78. 子集

  ![子集](/_images/interview/code/question-routine/DP/子集.png)

对于本题而言：

dfs(state)

1. Base Case Check

2. For each subproblem x
   a. update state = next_state_x
      1. (pos+1,subset)
      2. (pos+1,subset+nums[pos])
   b. branch down ——> call dfs(next_state_x)
   c. restore state

以下为解题代码：

```
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> cur;
        int n=nums.size();
        dfs(n,0,cur,nums,res);

        return res;
    }

    void dfs(int n,int pos,vector<int> cur,vector<int>& nums,vector<vector<int>>& res){
        if(pos==n){
            res.push_back(cur);
            return;
        }

        cur.push_back(nums[pos]);
        dfs(n,pos+1,cur,nums,res);
        cur.pop_back();
        dfs(n,pos+1,cur,nums,res);

    }
};
```

## Dynamic Programming

如果我们Search Space有重复子问题的话，可以记录下这些子问题的答案来保证不会重复计算多次。所以DP也称为Search + Memoization

时间复杂度取决于子问题的个数。

搜索空间(Search Space)可以用Tree的形式展现出来，便于理解。

所有DP都可以写成Bottom Up DFS 的形式。

<font color='red'>**重点仍然是定义好状态，定义好状态后，可以从一个中间状态出发思考递归规则**</font>。

## Bottom Down DFS模板

Bottom Down DFS模板

1. Define State of subproblems
2. Initialize memo to record calculated subproblems
3. retun dfs(top_level_answer_state)

dfs(state)

1. Base Case Check

2. <font color='red'>If current problem is calculated , return its answer</font>

3. For each subproblem x

   a. Ask  subprobelm for their answers ——>  call dfs(subproblem_state)
   b. Build up current state problem answer based on subproblem answers

4. <font color='red'>Store current problem answer</font>

## 实践应用

### 139. 单词拆分

  ![单词拆分](/_images/interview/code/question-routine/DP/单词拆分.png)

以下为解题代码：

```

```

## 2D Dynamic Programming

* 2D Array ——> state = (row,col)
* 2 1D Array ——> Each 1D state
* 1D Array + K ——> state = (i,k)
* 1D Array ——> 2D statr (subarray)
