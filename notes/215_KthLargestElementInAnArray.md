题目链接：https://leetcode.com/problems/kth-largest-element-in-an-array/

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

Example 1:

>Input: [3,2,1,5,6,4] and k = 2\
>Output: 5

Example 2:

>Input: [3,2,3,1,2,4,5,5,6] and k = 4\
>Output: 4

Note: You may assume k is always valid, 1 ≤ k ≤ array's length.

---
用快速选择法：找一个值作为pivot，看排在数组里第几位，然后调整pivot。整个思路是快速排序的一部分。pivot随机从数组中选，以使最终时间为O(N)。如果不随机选，比如总是选数组中的某一个位置，那么时间复杂度为**Omega(N)**, 不是O(N)。
```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int start = 0, end = nums.size() - 1;
        while (start < end) {
            int i = partition(nums, start, end);
            if (i == k-1) return nums[i];
            if (i < k-1) start = i + 1;
            else end = i - 1;
        }
        return nums[start];
    }    

    int partition(vector<int>& nums, int left, int right) {
        int index = rand() % (right - left + 1) + left;
        swap(nums[index], nums[right]);
        int pivot = nums[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (nums[j] >= pivot) {
                i++;
                swap(nums[i], nums[j]);
            }
        }
        i++;
        swap(nums[i], nums[right]);
        return i; 
    }
};
```