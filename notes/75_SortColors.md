题目链接：https://leetcode.com/problems/sort-colors/

Given an array with n objects colored red, white or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note: You are not suppose to use the library's sort function for this problem.

Example:

>Input: [2,0,2,1,1,0]\
>Output: [0,0,1,1,2,2]

Follow up:\ 
A rather straight forward solution is a two-pass algorithm using counting sort. First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's. Could you come up with a one-pass algorithm using only constant space?

这道题推广开去意思是这样：给你一个数`x`，让你把数组分成三段：第一段都小于`x`，第二段都等于`x`，第三段都大于`x`。这道题`x=1`。就管这个问题叫，“三段分割”吧， 也叫[Dutch National Flag Problem](https://en.wikipedia.org/wiki/Dutch_national_flag_problem#Pseudocode)。我觉得这个解法应该背下来：容易理解，但更应该记住。
```cpp
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int i = 0, j = 0, k = nums.size() - 1;
        while (j <= k) {
            if (nums[j] < 1) {
                swap(nums[i++], nums[j++]);
            }
            else if (nums[j] > 1) {
                swap(nums[k--], nums[j]);
            }
            else j++;
        }
    }
};
```