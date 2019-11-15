题目链接：https://leetcode.com/problems/spiral-matrix/

Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

Example 1:

Input:
```[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
```
Output: [1,2,3,6,9,8,7,4,5]

Example 2:

Input:
```[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
```
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

---

没想出来很厉害的方法。
```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> val;
        int m = matrix.size(); if (m == 0) return val;
        int n = matrix[0].size(); if (n == 0) return val;
        int num_val = m * n;
        vector<int> dr {0, 1, 0, -1};
        vector<int> dc {1, 0, -1, 0};
        int r = 0, c = 0;
        int i_op = 0;
        int top = 0, bottom = m-1, left = 0, right = n-1;
        for (int i = 0; i < num_val; i++) {
            val.push_back(matrix[r][c]);
            if (i_op == 0 && c + 1 > right) {i_op++; top++;}
            else if (i_op == 1 && r + 1 > bottom) {i_op++; right--;}
            else if (i_op == 2 && c - 1 < left) {i_op++; bottom--;}
            else if (i_op == 3 && r - 1 < top) {i_op = 0; left++;}
            r += dr[i_op];
            c += dc[i_op];
        }
        return val;
    }
};
```