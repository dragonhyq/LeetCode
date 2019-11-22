题目链接：https://leetcode.com/problems/longest-palindromic-substring/

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"\
Output: "bab"\
Note: "aba" is also a valid answer.

Example 2:

Input: "cbbd"\
Output: "bb"

---
解法一：

首先想到的是dp。用一个二维数组，`dp[i][j]`表示`s[i:(j+1)]`（也就是从`s[i]`到`s[j]`，包含`s[j]`）是否是palindrome. `0 <= i < s.size()`, `0 <= j < s.size()`。分为三种情况：
1. `i == j`, 单个字符，肯定是palindrome
2. `j == i + 1`，两个字符，如果`s[i] == s[j]`, 就是回文串，否则不是
3. `j > i + 1`，多于两个字符，如果`s[i] == s[j]`并且`dp[i+1][j-1]`（也就是两边相同，中间是回文串）就是回文串，否则不是。

要注意populate `dp`数组的顺序，`j-1`要在`j`之前做。代码里面用到了`bool`型的二维数组。用`vetor<vector<bool>>`也行。
```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int maxLen = 0;
        int n = s.size();
        int i0;
        bool dp[n][n] = {false};
        for (int j = 0; j < s.size(); j++) {
            for (int i = 0; i <= j; i++) {
                if (j - i <= 1) dp[i][j] = (s[i] == s[j]);
                else dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1];
                if (dp[i][j] && j - i + 1 > maxLen) {
                    i0 = i;
                    maxLen = j - i + 1;
                }
            }
        }
        return s.substr(i0, maxLen);
    }
};
```
解法二：

中心扩散。找一个中心，向两边扩散，遇到不一样的字符时停下来。分为奇数长度回文串和偶数长度回文串两种。中心可能存在于`s`的任何地方，所以要扫。这个思路其实非常清晰，但是我一开始并没有想到。:neutral_face:
```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int left, right;
        int left0, maxLen = 0;
        int n = s.size();
        // odd length
        for (int i = 0; i < n; i++) {
            left = right = i;
            while (left >= 0 && right < n && s[left] == s[right]) {
                left--; 
                right++;
            }
            if (right - left - 1 > maxLen) {
                maxLen = right - left - 1;
                left0 = left + 1;
            }    
        }

        // even length
        for (int i = 0; i < n-1; i++) {
            left = i;
            right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right]) {
                left--;
                right++;
            }
            if (right - left - 1 > maxLen) {
                maxLen = right - left - 1;
                left0 = left + 1;
            }
        }
        return s.substr(left0, maxLen);    
    }
};
```

解法三：

马拉车！Manacher's Algorithm!主要参考了以下博客：
1. [最长回文字符串算法-Manacher’s Algorithm-马拉车算法](https://blog.csdn.net/liuwei0604/article/details/50414542)
2. [leetcode-5 最长回文子串-画蛇添足的马拉车算法](https://my.oschina.net/pingpangkuangmo/blog/3045160)

目前的代码中`P`数组记录的is exactly the length of the longest substring. 还有别的版本，我还需要想一下两者哪个好。目前的代码中`C=1`, `R=1`，然后扫描的时候`i=1`扫到`i=n-2`, which are not natural and could introduce bugs. 另外`while (t[i + 1 + P[i]] == t[i - 1 - P[i]])`也使得需要保证不越界然后再取值。总之，代码需要改，I shall be back!

```cpp
class Solution {
public:
    std::string longestPalindrome(std::string s) {
        if (s.empty()) return "";
        std::string t = "&#";
        for (int i = 0; i < s.size(); i++) {
            t += s[i];
            t += '#';
        }
        t += '^';

        int n = t.size();
        std::vector<int> P(t.size(), 0);
        int C = 1, R = 1, i0, maxCenter, maxLen = 0;
        for (int i = 1; i < n-1; i++) {
            if (i <= R) {
                int i_mirror = 2 * C - i;
                P[i] = std::min(P[i_mirror], R - i);
            }
            else 
                P[i] = 0;
            while (t[i + 1 + P[i]] == t[i - 1 - P[i]])
                P[i]++;
            if (i + P[i] > R) {
                C = i;
                R = i + P[i];
            }
        }
        for (int i = 1; i < n-1; i++) {
            if (P[i] > maxLen) {
                maxCenter = i;
                maxLen = P[i];
            }
        }
        i0 = (maxCenter - maxLen - 1) / 2;
        return s.substr(i0, maxLen);
    }
};
```