题目链接：https://leetcode.com/problems/evaluate-reverse-polish-notation/

Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are \+, \-, \*, /. Each operand may be an integer or another expression.

Note:

Division between two integers should truncate toward zero.
The given RPN expression is always valid. That means the expression would always evaluate to a result and there won't be any divide by zero operation.

Example 1:

Input: ["2", "1", "+", "3", "*"]\
Output: 9\
Explanation: ((2 + 1) * 3) = 9

Example 2:

Input: ["4", "13", "5", "/", "+"]\
Output: 6\
Explanation: (4 + (13 / 5)) = 6

Example 3:

Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]\
Output: 22\
Explanation: 
((10 * (6 / ((9 + 3) * -11))) + 17) + 5\
= ((10 * (6 / (12 * -11))) + 17) + 5\
= ((10 * (6 / -132)) + 17) + 5\
= ((10 * 0) + 17) + 5\
= (0 + 17) + 5\
= 17 + 5\
= 22

---
没觉得有啥难度。可能判断当前的token是不是运算符算是一个点吧。

```cpp
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> s;
        for (string& t: tokens) {
            if (t.size() == 1 && !(t[0] >= '0' && t[0] <= '9')) {
                int b = s.top(); s.pop();
                int a = s.top(); s.pop();
                if (t[0] == '+') s.push(a + b);
                else if (t[0] == '-') s.push(a - b);
                else if (t[0] == '*') s.push(a * b);
                else s.push(a / b);
            }
            else {
                s.push(stoi(t));
            }
        }    
        return s.top();
    }
};
```