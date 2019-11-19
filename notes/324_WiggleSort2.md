题目链接：https://leetcode.com/problems/wiggle-sort-ii/

Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example 1:

>Input: nums = [1, 5, 1, 1, 6, 4]\
>Output: One possible answer is [1, 4, 1, 5, 1, 6].

Example 2:

>Input: nums = [1, 3, 2, 2, 3, 1]\
>Output: One possible answer is [2, 3, 1, 3, 1, 2].

Note: You may assume all input has valid answer.

Follow Up: Can you do it in O(n) time and/or in-place with O(1) extra space?

---
这个题需要琢磨琢磨。

解法一：复制原数组，排序，然后赋值原数组。有两种情况，第一种是前半段严格小于后半段：
(偶数个元素)`[1, 1, 2, 2] -> [1, 2, 1, 2]`，或者，
（奇数个元素）`[1, 1, 1, 2, 2] -> [1, 2, 1, 2, 1]`。这种情况下，在最终的数组里，偶数index来自于前半段，奇数index来自于后半段，至于来自于某段中的哪一个，没有限制。没有限制的话，我们可以按一个顺序，比如从前往后走。代码暂时写为：
```cpp
// j points to the first element of the "smaller" part
// k points to the first element of the "larger" part
int j = 0, k = (nums.size() + 1) / 2; 
vector<int> temp = nums;
sort(temp.begin(), temp.end());
for (int i = 0; i < nums.size(); i++) {
    nums[i] = nums & 1 ? temp[k++] : temp[j++];
}

```
第二种情况，是前半段小于等于后半段，比如：`[1, 2a, 2b, 3]`。如果按照第一种方法，最后得出的数组为`[1, 2b, 2a, 3]`，不满足题意。需要把等于的元素分开，所以要按反方向赋值：
```
<---  |  <----
[1, 2a, 2b, 3]
[2a, 3, 1, 2b]
```
这样我们有了同时处理两种情况的代码，也就是最终代码。代码首先排序，然后按照前半段不严格小于后半段的情况给数组赋值。时间O(NlogN)，空间O(N)。
```cpp
class Solution {
public:
    void wiggleSort(std::vector<int>& nums) {
        int j = (nums.size() - 1) / 2, k = nums.size() - 1;
        std::vector<int> temp = nums;
        std::sort(temp.begin(), temp.end());
        for (int i = 0; i < nums.size(); i++) {
            nums[i] = i & 1 ? temp[k--] : temp[j--];
        }
    }
};
```

解法二：
解法一虽然简单，但是提出了一个很重要的点：前半段不严格小于后半段的情况，也就是前后中间有一部分的值是一样的。只要把这些值处理好就行了，而前半段小于这个值的那些元素和后半段大于这些值的那些元素，不重要，不需要排序。我们只需要知道中间那个值是多少（中数），然后确定它左边的值小于中数，右边的值大于中数，就可以了。求中数可以用quick select。有了中数，还需要数组分为三段长这样：
```
[< median ... | == median ... | > median ...]
```
这个把一个数组分成小于、等于、大于三段的问题基本和[75题：Sort Colors](75_SortColors.md)是一样的。分成三段之后，按照解法一最后一步赋值就好了。这个方法虽然时间上是O(N)，但空间上还是O(N)。遗憾的是，我手写出来比第一种解法要慢很多。。。:sweat:，很显然是需要优化的。代码如下：
```cpp
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        vector<int> temp = nums;
        int j = (nums.size() - 1) / 2, k = nums.size() - 1;
        int index = (nums.size() - 1) / 2;
        int median = findValue(temp, index);
        threeWayPartition(temp, median);
        for (int i = 0; i < nums.size(); i++) {
            nums[i] = i & 1 ? temp[k--] : temp[j--];
        }
    }

    void threeWayPartition(vector<int>& nums, int median) {
        int i = 0, j = 0, k = nums.size() - 1;
        while (j <= k) {
            if (nums[j] < median) swap(nums[j++], nums[i++]);
            else if (nums[j] > median) swap(nums[j], nums[k--]);
            else j++;
        }
    }

    int findValue(vector<int>& nums, int k) {
        int start = 0, end = nums.size() - 1;
        while (start < end) {
            int i = partition(nums, start, end);
            if (i == k) return nums[i];
            if (i < k) start = i + 1;
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
            if (nums[j] <= pivot) {
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
目前，我还不懂怎么把空间降成O(1)。