题目链接：https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Note that you cannot sell a stock before you buy one.

Example 1:

Input: [7,1,5,3,6,4]\
Output: 5\
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5. Not 7-1 = 6, as selling price needs to be larger than buying price.

Example 2:

Input: [7,6,4,3,1] \
Output: 0\
Explanation: In this case, no transaction is done, i.e. max profit = 0.

---

设一个最小股价，不断更新。对于每一个股价，计算卖出能够得到的最大利润。同时记录最大利润。我思路有点不是很清楚，需要回头再想一想。
```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int low = INT_MAX;
        int maxProfit = 0;
        for (int x: prices) {
            low = min(low, x);
            maxProfit = max(maxProfit, x - low);
        }    
        return maxProfit;
    }
};
```