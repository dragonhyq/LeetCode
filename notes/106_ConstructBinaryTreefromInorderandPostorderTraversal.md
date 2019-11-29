link: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

inorder = `[9,3,15,20,7]`\
postorder = `[9,15,7,20,3]`\
Return the following binary tree:
```
    3
   / \
  9  20
    /  \
   15   7
```
----
There is also a question which lets you build a binary tree given inorder and preorder traversal. I will add to it later. 

inorder: left -> self -> right\
postorder: left -> right -> self

The idea is this. First you find the root node in the post order list, which is simply the last element. Then you find that element in the inorder list. Then you divide both the inorder list and the postorder list into left child and right child. We use a map to store the index of an element in the inorder list so that we don't have to search for it. 
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for (int i = 0; i < inorder.size(); i++) idx[inorder[i]] = i;
        return build(postorder, 0, postorder.size(), inorder, 0, inorder.size()); 
        
    }
    TreeNode* build(vector<int>& postorder, int start_post, int end_post, vector<int>& inorder, int start_in, int end_in) {
        if (start_post == end_post) return NULL;
        int val = postorder[end_post-1];
        TreeNode *node = new TreeNode(val);
        int i = idx[val];
        node->left = build(postorder, start_post, start_post + i - start_in, inorder, start_in, i);
        node->right = build(postorder, start_post + i - start_in, end_post - 1, inorder, i+1, end_in);
        return node;
    }
private:
    unordered_map<int, int> idx;
};

``` 

Now here is the question: 

Preorder, inorder, postorder; given two out of three, which two do you need in order to build a unique tree? 

The answer is you first need the inorder, then you need either the preorder or the postorder. Why. 

inorder: `left -> self -> right`\
preorder: `self -> left -> right`\
postorder: `left -> right -> self`

Notice that in preorder and postorder, `left` is always followed by `right`: `(left -> right)`, which means if only given preorder and postorder, you cannot distinguish between `left` and `right`. You need inorder to do that. 