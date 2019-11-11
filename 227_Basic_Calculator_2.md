题目链接：https://leetcode.com/problems/basic-calculator-ii/

Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, \+, \-, \*, / operators and empty spaces. The integer division should truncate toward zero.

Example 1:

>Input: "3\+2\*2"\
>Output: 7

Example 2:

>Input: " 3/2 "\
>Output: 1

Example 3:

>Input: " 3\+5 / 2 "\
>Output: 5

Note:
- You may assume that the given expression is always valid.
- Do not use the eval built-in library function.
---

这个题不难，但容易出错。基本思路是，在遇到运算符的时候，把当前的数字能处理的处理了。处理过的数字放在一个stack里，最后把stack里面的数字加起来。`s`的最后是一个数字，不是运算符，所以还要当作运算符再处理一次。空格不要管。运行的时候遇到说`int`本身不够存放大的数，所以改成`long`。

我觉得`num = num * 10 + s[i] - '0';`这个运算挺赞的。

其实可以把运算符和数字都先单独挑出来，然后再扫一遍。但是没必要，一次扫完完事。这题考的是谨慎。

```cpp
class Solution {
public:
    int calculate(string s) {
        int n = s.size();
        char last_op = '+';
        long num = 0;
        stack<long> num_list;
        long total = 0;
        for (size_t i = 0; i < n; i++) {
            if (s[i] >= '0' && s[i] <= '9') num = num * 10 + s[i] - '0';
            if (s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-' || i == n-1) {
                if (last_op == '+') num_list.push(num);
                else if (last_op == '-') num_list.push(-num);
                else if (last_op == '*') {
                    int last_num = num_list.top();
                    num_list.pop();
                    num_list.push(last_num * num);
                } 
                else {
                    int last_num = num_list.top();
                    num_list.pop();
                    num_list.push(last_num / num);
                }
                last_op = s[i];
                num = 0;
            }
        }
        while (num_list.size()) {
            total += num_list.top();
            num_list.pop();
        }         
        return total;
    }
};
```