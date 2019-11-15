题目链接：https://leetcode.com/problems/product-of-array-except-self/

Given an array nums of n integers where n > 1,  return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Example:

Input:  [1,2,3,4]\
Output: [24,12,8,6]\
Note: Please solve it without division and in O(n).

Follow up:
Could you solve it with constant space complexity? (The output array does not count as extra space for the purpose of space complexity analysis.)

---
初始思路是建立两个数组，分别记录nums[i]左边和右边的乘积，然后乘起来。不过其实不用两个数组，一个就好了，而且可以作为最后的输出，所以空间复杂度是O(1)。
```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        if (nums.empty()) return vector<int>();
        int n = nums.size();
        vector<int> val(n);
        int right = 1;
        val[0] = 1;
        for (int i = 1; i < n; i++) {
            val[i] = val[i-1] * nums[i-1];
        }
        for (int i = n-1; i >= 0; i--) {
            val[i] = right * val[i];
            right *= nums[i];
        }
        return val;
    }
};
```