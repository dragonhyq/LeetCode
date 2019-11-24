Link: https://leetcode.com/problems/largest-number/

Given a list of non negative integers, arrange them such that they form the largest number.

Example 1:

Input: [10,2]\
Output: "210"\

Example 2:

Input: [3,30,34,5,9]\
Output: "9534330"

Note: The result may be very large, so you need to return a string instead of an integer.

---
My thought was device rules to sort the array. People's solutions were like that, except the rules
are not specifically implemented, but uses string comparison. the `sort()` function is used with custom
comparator, where the comparator is written in the form of lambda expression. 

If `nums` only has 0's, then the resulting string would be `"00000...000"`, and that as a number is just `"0"`.

```cpp
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> strs;
        string out = "";
        for (int num : nums) {
            strs.push_back(to_string(num));
        }     
        sort(strs.begin(), strs.end(), [] (const string& s1, const string & s1) {
            return s1 + s1 > s2 + s1;
        });
        for (string s : strs) {
            out += s;
        }
        return (out[0] == '0')? "0" : out; 
    }
};
```
Instead of converting the numbers to string and using a vector to store them, we can do the converstion
as the comparison is happening. But that way the time will be longer: we will be earning space at the cost of time. Below is the code. 
```cpp
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        string out = "";
        sort(nums.begin(), nums.end(), [] (int a, int b) {
            return to_string(a) + to_string(b) > to_string(b) + to_string(a);
        });
        for (int x : nums) {
            out += to_string(x);
        }
        return (out[0] == '0')? "0" : out; 
    }
};
```