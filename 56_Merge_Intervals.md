题目链接：https://leetcode.com/problems/merge-intervals/

```
Given a collection of intervals, merge all overlapping intervals.

Example 1:

Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
Example 2:

Input: [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
```
如果`intervals`没有任何结构的话，对于每一个interval，都得和其他每一个interval比，看是否有重叠。所以需要给`interval`排序，然后就可以从前往后扫描了。

```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;
        vector<int> temp = intervals[0];
        for (size_t i = 1; i < intervals.size(); i++) {
            if (overlaps(temp, intervals[i])) {
                temp = mergeTwo(temp, intervals[i]);
            }
            else {
                merged.push_back(temp);
                temp = intervals[i];
            }
        }
        merged.push_back(temp);
        return merged;
    }
    
    bool overlaps(vector<int> meetA, vector<int> meetB) {
        // assumes meetA[0] <= meetB[0]
        return meetA[1] >= meetB[0];
    }

    vector<int> mergeTwo(vector<int> meetA, vector<int> meetB) {
        return {meetA[0], max(meetA[1], meetB[1])};
    }
};
```