### Problem

Link: https://leetcode.com/problems/fraction-to-recurring-decimal/

Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

Example 1:

Input: numerator = 1, denominator = 2\
Output: "0.5"

Example 2:

Input: numerator = 2, denominator = 1\
Output: "2"

Example 3:

Input: numerator = 2, denominator = 3\
Output: "0.(6)"
___
### Solution

This question is **very** annoying, mostly because of the overflow problem when the numerator or the denominator is -2147483648. The range of `int` is [-2147483648, 2147483647], so if you negate -2147483648, the result will overflow. You cannot multiple it with -1, neither can you do `abs()` on it, because both will throw "overflow" error at you. 
To solve it, we need to _first_ cast the number to long, and _then_ negate it. 

Recurrence happen when you meet a residual that you have seen before, so you need to keep track of the past residuals. More precisely, keep track of the length of the string when a non-zero residual appears. The code went through several rounds of modification. Overall it was not a pleasant experience to work this problem. I'll see if I will feel better when I do it again. I have also added test code and results. Be sure to take a look at the result and see differet cases with the recurrence: `0.(3)`, `0.1(6)`, `0.(012)`.  
```cpp
#include <iostream>
#include <string>
#include <unordered_map>

class Solution {
public:
    std::string fractionToDecimal(int numerator, int denominator) {
        long num = numerator, denom = denominator;
        std::string s;
        num = num >= 0? num : (-1) * num;
        denom = denom >= 0? denom : (-1) * denom;
        s = positiveFraction(num, denom);
        if (numerator == 0) return "0";
        else if ((numerator > 0 && denominator > 0) || (numerator < 0 && denominator < 0) ) return s;
        else return "-" + s;
    }

    std::string positiveFraction(long positive_num, long positive_denom){
        std::string out = "";
        std::unordered_map<long, int> startIndex; // residual -> start index of string 
        long a = positive_num, b = positive_denom;
        long q, r;
        int i_start;

        q = a / b;
        r = a % b;
        if (r == 0) {
            return std::to_string(q);
        }
        out = std::to_string(q) + ".";
        i_start = out.size() - 1;
        while (r != 0) {
            if (startIndex.count(r)) {
                out.insert(startIndex[r], "(");
                out +=")";
                break;
            }
            i_start++;
            startIndex[r] = i_start;
            a = r * 10;
            q = a / b;
            r = a % b;
            out += std::to_string(q);
        }
        return out;
    }
};

int main() {

    Solution s;
    std::cout << s.fractionToDecimal(0, 1) << std::endl;
    std::cout << s.fractionToDecimal(0, -1) << std::endl;
    std::cout << s.fractionToDecimal(-10, 5) << std::endl;
    std::cout << s.fractionToDecimal(10, -5) << std::endl;
    std::cout << s.fractionToDecimal(2, 3) << std::endl;
    std::cout << s.fractionToDecimal(1, 3) << std::endl;
    std::cout << s.fractionToDecimal(3, 1) << std::endl;
    std::cout << s.fractionToDecimal(2, 5) << std::endl;
    std::cout << s.fractionToDecimal(12, 5) << std::endl;
    std::cout << s.fractionToDecimal(4, 333) << std::endl;
    std::cout << s.fractionToDecimal(1, 6) << std::endl;
    std::cout << s.fractionToDecimal(-1, -2147483648) << std::endl;
}
```  
Program output:
```
0
0
-2
-2
0.(6)
0.(3)
3
0.4
2.4
0.(012)
0.1(6)
0.0000000004656612873077392578125
```