题目链接：https://leetcode.com/problems/word-break/

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

Note:

-The same word in the dictionary may be reused multiple times in the segmentation.
-You may assume the dictionary does not contain duplicate words.
Example 1:

Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
Example 2:

Input: s = "applepenapple", wordDict = ["apple", "pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
             Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
Output: false

基本思路是：如果string的前一部分在字典中，后一部分可以分割，那么string就可以分割。用DP做。一维矩阵，从前往后，一个一个的确定`string[0:j]`（包括`j`）是否能够分割。那么在每一位`j`上，从后往前扫，看如果目前的`string[start:j]`在字典中，剩下的`string[0:start-1]`是不是可以分割。返回`dp.back()`。

时间O(N^2), 空间O(N)。

```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        size_t n = s.size();
        vector<bool> dp(n+1, false);
        unordered_set<string> set(wordDict.begin(), wordDict.end());
        dp[0] = true;
        for (int j = 1; j <= n; j++) {
            for (size_t len = 1; len <= j; len++) {
                string substr = s.substr(j - len, len);
                dp[j] = set.find(substr) != set.end() && dp[j-len];
                if (dp[j] == true) break;
            }
        }
        return dp.back();
    }
};
```