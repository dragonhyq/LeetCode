题目链接：https://leetcode.com/problems/binary-tree-inorder-traversal/

Given a binary tree, return the inorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
```
   1
    \
     2
    /
   3
```

Output: [1,3,2]

Follow up: Recursive solution is trivial, could you do it iteratively?

---

Solution 1: Iterative

This question is about its iterative solution. Inorder traversal is `left -> self -> right`, which means whenever there is a `left`, go left. The iterative solution uses and reflects the rule clearly. We should all know the iterative solution by heart. 

The outer while loop has two conditions.
1. If `node == NULL`, then the inner while loop will exit directly, which then requires that stack `s.empty() == false`, which is the second condition of the outer while loop. 
2. Reversely, if `node != NULL`, then the inner while loop will put at least one node into the stack, which will ensure that the stack is not empty, and the operations afterwards will be fine.

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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> out;
        stack<TreeNode *> s;
        TreeNode * node = root;
        while (node || s.size()) {
            while (node) {
                s.push(node);
                node = node->left;
            }
            node = s.top(); 
            s.pop();
            out.push_back(node->val);
            node = node->right;
        }    
        return out;
    }
};
```

Solution 2: Recursive

The recursive solution may come to mind first. It is easy to think about _and_ write but does _not_ require or reveal as much understanding of the traversal rule as does the iterative solution. 
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> out;
        go(root, out);
        return out;
    }

    void go(TreeNode* root, vector<int>& out) {
        if (root == NULL) return;
        go(root->left, out);
        out.push_back(root->val);
        go(root->right, out);
    }
};
```

