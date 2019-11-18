题目链接：https://leetcode.com/problems/longest-substring-without-repeating-characters/

Given a string, find the length of the longest substring without repeating characters.

Example 1:

Input: "abcabcbb"\
Output: 3 \
Explanation: The answer is "abc", with the length of 3. 

Example 2:

Input: "bbbbb"\
Output: 1\
Explanation: The answer is "b", with the length of 1.

Example 3:

Input: "pwwkew"\
Output: 3\
Explanation: The answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

---
不知道这个题属于啥类型，没有感觉。解法本质上是跟踪一个没有duplicate的窗口，然后更新最长长度。遇到duplicate的时候，看看有没有必要缩小窗口。如果duplicate在窗口的左边，就没有必要缩小窗口。窗口，是因为所求的substring是连续的。
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<int, int> map;
        int i = 0;
        int maxlen = 0;
        for (int j = 0; j < s.size(); j++) {
            if (map.count(s[j]) && map[s[j]] >= i) {
                i = map[s[j]] + 1;
            }
            maxlen = max(maxlen, j - i + 1);
            map[s[j]] = j;
        }
        return maxlen;
    }
};
```