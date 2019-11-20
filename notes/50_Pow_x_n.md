题目链接：https://leetcode.com/problems/powx-n/

Implement pow(x, n), which calculates x raised to the power n (x**n).

Example 1:

>Input: 2.00000, 10\
>Output: 1024.00000

Example 2:

>Input: 2.10000, 3\
>Output: 9.26100

Example 3:

>Input: 2.00000, -2\
>Output: 0.25000\
>Explanation: 2-2 = 1/22 = 1/4 = 0.25

Note:

* -100.0 < x < 100.0
* n is a 32-bit signed integer, within the range [−2^(31), 2^(31) − 1]

看到题，想，哐哐乘呗，考啥呢这是，confused，看眼discussion，提到O(logN)，明白了。

- 这里用的是int。 INT_MIN = -2147483648, -INT_MIN = 2147483648 = INT_MAX + 1。所以直接用myPow(x, -n)算n<0的情况是不行的，因为如果n == INT_MIN，-n会溢出。一个简答的解法是算myPow(x, -(n+1)), 然后把结果再乘以1/x。
- 直接的递归是不行的，因为可能会有重复计算。直接的解决方法是用一个map保留已经存在的幂。
```cpp
class Solution {
public:
    double myPow(double x, int n) {
        if (x == 0.0) return 0.0;
        if (n == 0) return 1.0;
        if (n < 0) return 1 / x * 1 / myPow(x, -(n+1));
        unordered_map<int, double> map;
        map[0] = 1.0;
        map[1] = x;
        return calc(n, map);
    }

    double calc(int n, unordered_map<int, double>& map) {
        if (map.count(n)) return map[n];
        int a = n / 2;
        int b = n - a;
        if (!map.count(a)) map[a] = calc(a, map);
        if (!map.count(b)) map[b] = calc(b, map);
        map[n] = map[a] * map[b];
        return map[n]; 
    }
};
```
- 其实用map没有必要。因为n拆成两个数a, b，只有可能a=b,或者a=b-1，那么就看n是不是偶数就好了。
```cpp
class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) return 1.0;
        if (n == 1) return x;
        if (n < 0) return 1 / x * 1 / myPow(x, -(n+1));
        double temp = myPow(x, n / 2);
        return (n & 1) ? temp * temp * x : temp * temp;
    }
};
```
- 另外-(n+1)这种做法，感觉是在刀尖上起舞，让人很不踏实，为什么一定要离INT_MIN这么近呢？用n/2就离的远得多。
```cpp
class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) return 1.0;
        // for positive or negative, n/2 truncates towards zero
        // -5 / 2 == -2
        double temp = myPow(x, n / 2);
        if (n < 0) return (n & 1) ? temp * temp / x : temp * temp;
        else return (n & 1) ? temp * temp * x : temp * temp;
    }
};
```
还有一种iterative的做法，我还没有想出来。未完待续。