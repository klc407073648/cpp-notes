# BFS (Breadth-First Search)

[[toc]]

> BFS(宽度优先搜索)是按"层"的概念进行的搜索算法，利用Queue记录需要被展开的TreeNode

适合解决与层数相关的Tree题目。

 ![tree层结构](/_images/interview/code/question-routine/BFS/tree层结构.png)

BFS General Steps:
1. Initialize Queue with <font color='red'>all entry points</font> (tree only one,graph has more than one)
2. While queue is not empty
   a. for each node in queue (currently)
   b. poll out element (add to result)
   c. expand it , offer children to the queue <font color='red'>in order</font>
   d. increase level

## 实践应用

### 例题 102. 二叉树的层序遍历

 ![二叉树的层序遍历](/_images/interview/code/question-routine/BFS/二叉树的层序遍历.png)

以下为解题代码：

```c++
class Solution {
public:
vector<vector<int>>  res;
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>>  res;
        if(root==nullptr){
            return res;
        }
        queue<TreeNode*> queue;
        queue.push(root);

        while(!queue.empty()){
            int size=queue.size();
            vector<int> vec;
            for(int i=0;i<size;i++){
                TreeNode* cur=queue.front();
                vec.push_back(cur->val);
                if(cur->left!=nullptr){
                    queue.push(cur->left);
                }

                if(cur->right!=nullptr){
                    queue.push(cur->right);
                }

                queue.pop();
            }
            res.push_back(vec);
        }

        return res;
    }
};
```


### 例题 104. 二叉树的最大深度

  ![二叉树的最大深度](/_images/interview/code/question-routine/BFS/二叉树的最大深度.png)

以下为解题代码：
```

```

