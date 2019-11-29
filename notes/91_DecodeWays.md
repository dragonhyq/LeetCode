### Problem 
Link: https://leetcode.com/problems/decode-ways/

A message containing letters from A-Z is being encoded to numbers using the following mapping:
```
'A' -> 1
'B' -> 2
...
'Z' -> 26
```
Given a non-empty string containing only digits, determine the total number of ways to decode it.

Example 1:

Input: "12"  
Output: 2  
Explanation: It could be decoded as "AB" (1 2) or "L" (12).  

Example 2:

Input: "226"\
Output: 3\
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
___
### Solution

First we talk about the general idea. Consider string `'xxx12'`, if we look at character `'2'`, there are two possible ways we can interpret it:\
1. `'xxx1' + '2'`. The number of splits equals that of `'xxx1'`.
2. `'xxx' + '12'`. The number of splits equals that of `'xxx'`. 
So the splits of `'xxx12'` is built up upon those of `'xxx1'` and `'xxx'`. Interestingly similar to Fibonacci sequence don't you think? More generally we consider a string `"xyzab"`:
```
  xyz       a     b
prev2   prev1   cur
```
So it seems like `cur = prev1 + prev2` where 
- `prev2`: number of splits up till `z`
- `prev1`: number of splits up till `a`
- `cur`: number of splits up till `b`, what we care about

But, not quite. Only numbers that range from 1 to 26 can be encoded, which means 0 and anything larger than 26 cannot. If `b == '0'`, then `b` itself cannot be decoded and therefore we cannot use `prev1`. We can then only consider `ab`. If `int("ab")` is less than 10 or is greater than 26 (which means it reduces to a single digit number) then we cannot consider `ab` either and therefore we cannot use `prev2`. The updated rule looks something like
```
cur = 0
if (b > '0') cur += prev1
if (int(ab) >= 10 && int(ab) <= 26) cur += prev2 
```
We can use an array to store the `cur` of every character, but with `prev1` and `prev2`, the index will be kind of a mess. And also we do _not_ need an array, just a few variables. 

I initialized `prev1` and `prev2` to be both 1's. This is so that when `s[0]` and `s[:2]` both can be decoded, we get the correct `cur`. Small engineering detail.     
```cpp
class Solution {
public:
    int numDecodings(string s) {
        int prev2 = 1, prev1 = 1, cur;
        int digit, last_digit = 0, twoDigits;
        for (int i = 0; i < s.size(); i++){
            digit = s[i] - '0';
            cur = (digit == 0) ? 0 : prev1;
            twoDigits = last_digit * 10 + digit;
            if (twoDigits >= 10 && twoDigits <= 26) cur += prev2;
            last_digit = digit;
            prev2 = prev1;
            prev1 = cur;
        }
        return cur;
    }
};
```
