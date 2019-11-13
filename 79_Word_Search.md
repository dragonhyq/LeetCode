题目链接：https://leetcode.com/problems/word-search/

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

Example:
```
board = 
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
```

Given word = `"ABCCED"`, return true.\
Given word = `"SEE"`, return true.\
Given word = `"ABCB"`, return false.

---

首先，在board里面找到word里面第一个字母，假设位置为`(i, j)`，然后做DFS看word剩下的部分是否能够找到，搜索是上下左右四个方向的。如果找不到，就回到`(i, j)`，继续找下一个和word首字母一样的字母。做DFS的时候，用一个`visited`矩阵记录走过的路。走完失败了的话，就把`visited`返回原来的值，就好像没有走过一样，也就是回溯。

```cpp
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.size() == 0 || board[0].size() == 0) return false;
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (search(word, i, j, 0, board, visited) == true) return true;
            }
        } 
        return false;    
    }

    bool search(string word, int i, int j, int index, vector<vector<char>>& board, vector<vector<bool>>& visited) {
        // word[index] found at board[i][j]
        if (index == word.size()) return true;
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) return false;
        if (visited[i][j] == true) return false;
        if (word[index] != board[i][j]) return false;
        visited[i][j] = true;
        bool up = search(word, i-1, j, index+1, board, visited);
        if (up == true) return true;
        bool down = search(word, i+1, j, index+1, board, visited);
        if (down == true) return true;
        bool left = search(word, i, j-1, index+1, board, visited);
        if (left == true) return true;
        bool right = search(word, i, j+1, index+1, board, visited);
        if (right == true) return true;
        visited[i][j] = false;
        return false;
    }


};
```