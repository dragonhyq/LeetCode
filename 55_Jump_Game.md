题目链接：https://leetcode.com/problems/jump-game/

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

Example 1:

Input: `[2,3,1,1,4]`\
Output: true\
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:

Input: `[3,2,1,0,4]`\
Output: false\
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.

---
解法一：

这道题我一看，用dp，从前往后，把每一个点能走到的点设成true，看最后dp.back()是不是true。一跑，超时了:joy:。
```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        vector<bool> dp(nums.size(), false);
        dp[0] = true;
        for (int i = 0; i < nums.size(); i++) {
            if (dp[i] == false) continue;
            for (int j = i+1; j <= i+nums[i] && i < nums.size(); j++) {
                dp[j] = true;
            }
        }
        return dp.back();
    }
};
```

解法二：

看牛人写的，原来可以是O(N)的。设一个`reach`变量，表示能够到达的index。还是从前往后扫，在点`i`时，如果能够到达，即`reach >= i`，就更新`reach`。如果`reach < i`，说明点`i`是到达不了的：扫描是从前往后扫的，说明`i`前面没有任何一个点能够到达`i`，那直接返回`false`，肯定是到不了最后一个点了，即使`i == nums.size() - 1`。最后检查是否`reach >= nums.size() - 1`。
```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int reach = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (reach < i) return false;
            reach = max(reach, i + nums[i]);
        }
        return reach >= nums.size() - 1;
    }
};
```
或者把`i <= reach`的检查放在for的条件里。没啥区别。
```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int reach = 0;
        for (int i = 0; i < nums.size() && i <= reach; i++) {
            reach = max(reach, i + nums[i]);
        }
        return reach >= nums.size() - 1;
    }
};
```