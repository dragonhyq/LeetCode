Link: https://leetcode.com/problems/generate-parentheses/

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:
```
[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
```
___
There is only one key to this problem: in a partially formed string, there cannot be more `')'`'s than `'('`'s. If there are, then at least one `')'` have not been matched, and it never will be, because `')'` can only be matched by a `'('` before it. 
```cpp
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        int nleft = n, nright = n;
        vector<string> out;
        string s = "";
        go(out, s, nleft, nright);
        return out;
    }

    void go(vector<string>& out, string& s, int nleft, int nright) {
        if (nleft == 0 && nright == 0) {
            out.push_back(s);
            return;
        }
        if (nleft > 0) {
            s.push_back('(');
            go(out, s, nleft - 1, nright);
            s.pop_back();
        }
        if (nright > nleft) {
            s.push_back(')');
            go(out, s, nleft, nright - 1);
            s.pop_back();
        }
    }
};
```
To save space we use string refenrence in the `go()` function. 