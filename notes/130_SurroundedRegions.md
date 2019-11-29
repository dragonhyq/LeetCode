Link: https://leetcode.com/problems/surrounded-regions/

Given a 2D board containing `'X'` and `'O'` (the letter O), capture all regions surrounded by `'X'`.

A region is captured by flipping all `'O'`s into `'X'`s in that surrounded region.

Example:
```
X X X X
X O O X
X X O X
X O X X
```
After running your function, the board should be:
```
X X X X
X X X X
X X X X
X O X X
```
Explanation:

Surrounded regions shouldn’t be on the border, which means that any `'O'` on the border of the board are not flipped to `'X'`. Any `'O'` that is not on the border and it is not connected to an `'O'` on the border will be flipped to `'X'`. Two cells are connected if they are adjacent cells connected horizontally or vertically.   
***
The only point about this question is understanding the definition of _surrounded regions_, which is this: any `'O'` that can be connected to a boundary `'O'` is not considered as surrounded. Surrounded regions are `'O'`'s that cannot be reached from any boundary `'O'`. Hence the solution:  
1. Mark all `'O'`'s that are connected to a boundary `'O'` by changing it to any character other than `'X'`, say `'1'`.
2. Change the remaining `'O'`'s to `'X'` (what the question asks for).
3. Change the `'1'`'s back to `'O'`.

I first attempted to follow exactly that: First, convert all four boundaries. Then, for each boundary `'O'`, find and mark connected `'O'`'s. Then, change the remaining (surrounded)`'O'`'s and unmarked connected `'O'`'s. To find connected `'O'`'s, I used DFS, for which I also used a `visited` matrix. The code was as follows:
```cpp
class Solution {
public:
    void solve(vector<vector<char>>& board) {

        if (board.empty() || board[0].empty()) return;
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        // change all 'O' on the boundary to '1'
        for (int j = 0; j < n; j++) if (board[0][j] == 'O') board[0][j] = '1';   
        for (int i = 0; i < m; i++) if (board[i][n-1] == 'O') board[i][n-1] = '1';
        for (int j = n-1; j >= 0; j--) if (board[m-1][j] == 'O') board[m-1][j] = '1';
        for (int i = m-1; i >= 0; i--) if (board[i][0] == 'O') board[i][0] = '1';

        // for every point on the boundary, do DFS
        for (int j = 0; j < n-1; j++) dfs(board, visited, 0, j, m, n);     
        for (int i = 0; i < m-1; i++) dfs(board, visited, i, n-1, m, n); 
        for (int j = n-1; j > 0; j--) dfs(board, visited, m-1, j, m, n); 
        for (int i = m-1; i > 0; i--) dfs(board, visited, i, 0, m, n); 

        // change every 'O' to 'X'
        for (int i = 0; i < m; i++) 
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                if (board[i][j] == '1') board[i][j] = 'O';
        }

    }

    void dfs(vector<vector<char>> &board, vector<vector<bool>> &visited, int i, int j, int m, int n) {
        if (i < 0 || i > m-1 || j < 0 || j > n-1 || visited[i][j] || board[i][j] == 'X') return;
        visited[i][j] = true;
        if (board[i][j] == 'O') board[i][j] = '1';
        dfs(board, visited, i, j+1, m, n);
        dfs(board, visited, i, j-1, m, n);
        dfs(board, visited, i+1, j, m, n);
        dfs(board, visited, i-1, j, m, n);       
    }
};
```
While working, the code was not great: it uses extra memory: the `visited`. The condition of advancing in DFS is  
1. within range
2. element is not `'X'`  

Can we drop `visited`? If we don't use `visited`, then we stop when we step out of range or when we see `'X'`, but what if we see a `'1'`? The boundary `'O'` will be converted to `'1'` first, and we need to advance from `'1'` to go to the `'O'`'s adjacent to it. Since we do not have `visited` anymore, we must also stop when we see a `'1'`, because maybe it has already been visited? So we advance and we do not advance when we see a `'1'`? Dilemma. 

The solution is to _not_ convert the boundary `'O'`, and leave the conversion to the DFS. For the DFS, we only advance when  
1. within range
2. element is `'O'`

And still, we only start the DFS on the boundaries. 

Also, after DFS, in the scanning phase, we do a `if else` rather than two `if`'s, the reason is clear: an element can only have one value. 
```cpp
class Solution {
public:
    void solve(vector<vector<char>>& board) {

        if (board.empty() || board[0].empty()) return;
        int m = board.size(), n = board[0].size();

        // for every point on the boundary, do DFS
        for (int j = 0; j < n; j++) {
            dfs(board, 0, j, m, n);  
            dfs(board, m-1, j, m, n);
        }   
        for (int i = 0; i < m; i++) {
            dfs(board, i, 0, m, n); 
            dfs(board, i, n-1, m, n);
        } 

        // change every 'O' to 'X'
        for (int i = 0; i < m; i++) 
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                else if (board[i][j] == '1') board[i][j] = 'O';
        }

    }

    void dfs(vector<vector<char>> &board, int i, int j, int m, int n) {
        if (i < 0 || i > m-1 || j < 0 || j > n-1 || board[i][j] != 'O') return;
        board[i][j] = '1';
        dfs(board, i, j+1, m, n);
        dfs(board, i, j-1, m, n);
        dfs(board, i+1, j, m, n);
        dfs(board, i-1, j, m, n);       
    }
};
```
We can choose to not pass `m` and `n` to the DFS, but that is minor and does not affect the efficiency of the solution. 