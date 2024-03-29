Link: https://leetcode.com/problems/validate-binary-search-tree/

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
 

Example 1:
```
    2
   / \
  1   3
```
Input: [2,1,3]\
Output: true

Example 2:
```
    5
   / \
  1   4
     / \
    3   6
```
Input: [5,1,4,null,null,3,6]\
Output: false\
Explanation: The root node's value is 5 but its right child's value is 4.

---
I find the iterative solution clear and elegant. The idea is this: if it is a valid BST then its inorder traversal will only give strictly increasing values in order. When the next number is not strictly larger than the previous, return false. 

Some may be tempted to use `INT_MIN` for generating the first value of the traversal. It is not recommended because if we change the type to `long` or anything that has more capacity, `INT_MIN` would fail. Let's use pointers. 
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
    bool isValidBST(TreeNode* root) {
        TreeNode *prev = NULL;
        stack<TreeNode*> s;
        TreeNode* node = root;
        while (node != NULL || !s.empty()) {
            while (node) {
                s.push(node);
                node = node->left;
            }
            node = s.top(); 
            s.pop();
            if (prev != NULL && prev->val >= node->val) return false;
            prev = node;
            node = node->right;
        }
        return true;
    }
};
```

