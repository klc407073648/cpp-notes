# 树题型

[[toc]]

二叉搜索树定义：

```
二叉查找树（Binary Search Tree），它或者是一棵空树，或者是具有下列性质的二叉树： 
1.若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值； 
2.若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值； 
3.它的左、右子树也分别为二叉排序树。
```

注意点：需要考虑每个节点的上限和下限，例如**下述6的上下限为【10，15】**

![二叉搜索树](/_images/interview/code/question-type/tree/二叉搜索树.png)

#### [538. 把二叉搜索树转换为累加树](https://leetcode-cn.com/problems/convert-bst-to-greater-tree/)

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        if(root==nullptr)
            return root;

        queue<TreeNode*> queue;
        vector<int> vec;
        queue.push(root);
        
        //层次遍历获取所有值
        while(!queue.empty()){
            int size=queue.size();
            
            for(int i=0;i<size;i++){
                TreeNode* cur=queue.front();
                vec.push_back(cur->val);
                queue.pop();

                if(cur->left!=nullptr)
                    queue.push(cur->left); 

                if(cur->right!=nullptr)
                    queue.push(cur->right); 
            }
        }

		//排序，求累加值
        sort(vec.begin(),vec.end());
        int sum=0;
        vector<int> res(vec.size(),0);
        for(int i=vec.size()-1;i>=0;i--){
            sum+=vec[i];
            res[i]=sum;
        }

        queue.push(root);
        while(!queue.empty()){
            int size=queue.size();
            
            for(int i=0;i<size;i++){
                TreeNode* cur=queue.front();
                queue.pop();

				//大于或等于 node.val 的值之和
                for(int i=0;i<vec.size();i++){
                    if(vec[i]>=cur->val){
                        cur->val=res[i];
                        break;
                    }
                }
                
                if(cur->left!=nullptr)
                    queue.push(cur->left); 

                if(cur->right!=nullptr)
                    queue.push(cur->right); 
            }
        }

        return root;
    }
};
```

[114. 二叉树展开为链表](https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/)

```c++
class Solution {
public:
    vector<int> res;
    void flatten(TreeNode* root) {
        preorder(root);
        TreeNode *cur=root;
        for(int i=1;i<res.size();i++){
            cur->left=nullptr;
            cur->right=new TreeNode(res[i]);
            cur=cur->right;
        }
    }

    void preorder(TreeNode* root){
        if(!root)   return;

        res.push_back(root->val);
        preorder(root->left);
        preorder(root->right);
    }
};
```

[101. 对称二叉树](https://leetcode-cn.com/problems/symmetric-tree/)

```c++
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(!root)
            return true;
        return isSame(root->left,root->right);
    }

    bool isSame(TreeNode* left,TreeNode* right){
        if( (left!=nullptr && right!=nullptr && left->val!=right->val) || (left!=nullptr && right==nullptr) || (left==nullptr && right!=nullptr)){
            return false;
        }

        if(left==nullptr && right==nullptr)
            return true;
            
        bool l=isSame(left->left,right->right);
        bool r=isSame(left->right,right->left);

        return l&&r;
    }
};
```

[105. 从前序与中序遍历序列构造二叉树](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

```c++
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int pre_left=0;
        int pre_right=preorder.size();
        int in_left=0;
        int in_right=inorder.size();

        return inorderTraver(preorder,inorder,pre_left,pre_right,in_left,in_right);
    }

    TreeNode* inorderTraver(vector<int>& preorder, vector<int>& inorder,int pre_left,int pre_right,int in_left,int in_right){
        if(pre_left==pre_right){
            return nullptr;
        }

        int index=0;
        for(int i=in_left;i<in_right;i++){
            if(inorder[i]==preorder[pre_left]){
                index=i;
                break;
            }
        }

        TreeNode* root = new TreeNode(preorder[pre_left]);
        root->left=inorderTraver(preorder,inorder,pre_left+1,pre_left+1+index-in_left,in_left,index);//左子树
        root->right=inorderTraver(preorder,inorder,pre_left+1+index-in_left,pre_right,index+1,in_right);//右子树

        return root;
    }
};
```

