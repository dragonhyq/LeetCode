题目链接：https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

Example 1:

Input: nums = [5,7,7,8,8,10], target = 8\
Output: [3,4]

Example 2:

Input: nums = [5,7,7,8,8,10], target = 6\
Output: [-1,-1]

---

这个题我是按照对称的方式来做的。找最小index的时候用的是`mid = left + (right - left) / 2`， 找最大index时候用的是`mid = left + (right + 1 - left) / 2`，第一个偏向`left`，第二个偏向`right`。其实找到一个之后可以把找到的index给第二个搜索，减小搜索范围，不过并不会从O(logN)减少到O(N)。

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = findFirst(nums, target);
        if (first == -1) return {-1, -1};
        return {first, findLast(nums, target)};  
    }

    int findFirst(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (target == nums[mid]) right = mid;
            else if (target < nums[mid]) right = mid - 1;
            else left = mid + 1;
        }
        return (nums[left] == target) ? left : -1;
    }

    int findLast(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right + 1 - left) / 2;
            if (target == nums[mid]) left = mid;
            else if (target < nums[mid]) right = mid - 1;
            else left = mid + 1;
        }
        return (nums[left] == target) ? left : -1;
    }
};
```