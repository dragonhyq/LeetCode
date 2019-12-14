Link: https://leetcode.com/problems/permutations/

Given a collection of distinct integers, return all possible permutations.

Example:

Input: `[1,2,3]`\
Output:
```
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
```
___

Create an empty vector `cur`, short for "current". Keep adding elements to it, until the vector's length reaches the length of `nums`. We use `used` to track which elements have been inserted. My first attempt is below:
```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> out;
        if (nums.empty()) return out;
        vector<bool> used(nums.size(), false);
        vector<int> cur;
        go(out, used, nums, cur);
        return out;
    }

    void go(vector<vector<int>>& out, vector<bool>& used, vector<int>& nums, vector<int> cur) {
        if (cur.size() == nums.size()) {
            out.push_back(cur);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (!used[i]) {
                cur.push_back(nums[i]);
                used[i] = true;
                go(out, used, nums, cur);
                used[i] = false;
                cur.pop_back();
            }
        }
    }
};
```
In function `go()`, we scan the entire `used` from the start, regardless of how many elements we may have inserted to `cur`. This is because `used` does not have a  struture that we can predict: some of its elements are `true`, but we don't know which ones. 

What if we do know which ones are `true`? Actually, assume we have inserted `n` elements into `cur`, and we want the first `used` to reflect those elements, i.e. `used[:n] = true`. Can we do that? No, because `used` and `nums` have corresponding indeces: `used[i]` marks whether `nums[i]` has been inserted. Well, how about we keep it that way? We know `n` elements have been inserted to `cur`, and we want to set the first `n` elements in `used` to `true`, then, just swap those `n` elements to the front of `nums`. Thus, the first `n` elements of `nums` are in `cur`, and the first `n` elements of `used` are `true`, and to process the rest of `nums`, we only need to start from element No. (n+1). But we will not need `cur` anymore because it will be the same as `nums` ..., because we have been moving elements around in `nums`. We also don't need `used` anymore because we know how many elements have been inserted: `n`. The resulting code is
```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> out;
        go(0, out, nums);
        return out;
    }

    void go(int start, vector<vector<int>>& out, vector<int>& nums) {
        if (start == nums.size()) {
            out.push_back(nums);
            return;
        }

        for (int i = start; i < nums.size(); i++) {
            swap(nums[i], nums[start]);
            go(start + 1, out, nums);
            swap(nums[i], nums[start]);   
        }
    }
};
```
The time complexity should not change, but space will be saved. 