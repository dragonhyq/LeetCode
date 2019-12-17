Link: https://leetcode.com/problems/top-k-frequent-elements/

Given a non-empty array of integers, return the k most frequent elements.

Example 1:

Input: nums = `[1,1,1,2,2,3]`, k = 2\
Output: `[1,2]`

Example 2:

Input: nums = [1], k = 1\
Output: [1]

Note:
- You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
- Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
___

Fist we count the number of time each element occurs. Then, there are multiple ways to solve this problem. 

### Solution 1

We can use a max heap. Push all distinct elements into the heap then pop the first k. 
```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        priority_queue<pair<int, int>> q;
        vector<int> out;
        for (int num: nums) map[num]++;
        for (auto it: map) {
            q.push(make_pair(it.second, it.first));
        }
        for (int i = 0; i < k; i++) {
            out.push_back(q.top().second);
            q.pop();
        }
        return out;
    }
};
```

### Solution 2

We can also use a min heap and keep the size of the heap to be k at its maximum. This is someone else's code. Notice that the elements of the heap are not pairs but integers, and we iterate through the heap in the end to determine if a number goes into `out`. 
```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        priority_queue<int, vector<int>, greater<int> > q;
        vector<int> out;
        for (int num: nums) map[num]++;
        for (auto it: map) {
            q.push(it.second);
            // keep a maximum of k elements in the heap
            while (q.size() > k) q.pop();
        }
        for (auto it: map) {
            if (it.second >= q.top()) out.push_back(it.first);
        }
        return out;
    }
};
```
### Solution 3

People call it bucket sort. I disagree. There is no sort in this. Bucket storage maybe? Basically, reverse the count map by storing all the elements corresponding to each count. People call it bucket, I call it `groups`, for it's just, groups ... Anyways, scan `groups` from the end to the beginning because its index correspondes to the count. When you reach k elements, return. The time complexity is O(N). 

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        vector<vector<int>> groups(nums.size() + 1, vector<int>());
        vector<int> out;
        for (int num: nums) map[num]++;
        for (auto it: map) {
            groups[it.second].push_back(it.first);
        }
        // groups[0] has zero numbers in it
        for (int i = groups.size() - 1; i > 0; i--) {
            for (int j = 0; j < groups[i].size(); j++) {
                out.push_back(groups[i][j]);
                if (out.size() == k) return out;
            }
        }
        return out;
    }
};
```

### Solution 4

Quick select. I will come back and finish this. 