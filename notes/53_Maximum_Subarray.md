题目链接：https://leetcode.com/problems/maximum-subarray/

Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Example:

Input: [-2,1,-3,4,-1,2,1,-5,4],\
Output: 6\
Explanation: [4,-1,2,1] has the largest sum = 6.

Follow up:

If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.

---
目前我只会O(N)的解法。用一个DP数组，对每一个i，保存截止到nums[i]并包含nums[i]的subarray的最大值。那么如果知道dp[i-1]，想知道dp[i]就可以做两个选择：
1. dp[i-1] < 0, 如果带上截止为nums[i]的subarray，只会把dp[i]拉低，所以不能带，要重新启动，即只包含nums[i]
2. dp[i-1] >= 0, 要带上截止为nums[i]的subarray，会使得dp[i]增加。

最后返回max(dp)。不过其实不用保存dp数组，设一个变量保存最大值就够了。
```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxAll = INT_MIN;
        int maxCur = -1;
        for (int x : nums) {
            if (maxCur < 0) maxCur = x;
            else maxCur += x;
            maxAll = max(maxAll, maxCur);
        }    
        return maxAll;
    }
};
```