题目链接：https://leetcode.com/problems/coin-change/

You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:

Input: coins = [1, 2, 5], amount = 11 \
Output: 3 \
Explanation: 11 = 5 + 5 + 1

Example 2:

Input: coins = [2], amount = 3\
Output: -1

Note: You may assume that you have an infinite number of each kind of coin.

--- 

看第一个例子，coins = [1, 2, 5], amount = 11. 11分别减去1、2、5等于10、9、6。 看10怎么分：10减去1、2、5等于9， 8， 5。然后，发现一个有意思的现象：11分完有一种可能是9，10分完有一个可能也是9。所以如果用递归，那么9就要被计算两次，没有必要，说明用DP。从小到大计算。在计算某一个值`value`的时候，试着使用一个硬币`coin`。如果硬币值太大(`value - coin < 0`)，就不能用这枚硬币。如果能用(`value - coint >= 0`)，看剩下的值`value - coin`需要多少硬币。如果我们有多枚硬币，对于这个值`value`，使用每一枚硬币都有一个对应的硬币总使用量。这种做法需要二维数组，一个维度对应不同值的硬币，另一个维度对应能够凑出的值。不错吧。

但是。两维矩阵？用不着吧。最后我们要的是需要硬币数量的最小值，所以没有必要把所有硬币对应的硬币数量存下来。在计算每一个`value`所需的数量时，只保留最小值就够了。这样，一维数组就够了。当`value - coin == 0`的时候需要的硬币数量是多少呢？这时候剩下的值是0，不需要硬币，所以`dp[0] = 0`。 `dp`的初始值设为`INT_MAX`。
```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (coins.empty()) return -1;
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int value = 1; value <= amount; value++) {
            for (int coin: coins) {
                int left = value - coin;
                if (left < 0 || dp[left] == INT_MAX) continue;
                dp[value] = min(dp[value], 1 + dp[left]);
            }
        }
        return (dp.back() < INT_MAX) ? dp.back() : -1;
    }
};
```
你看我每次都要检车是否`dp[left] == INT_MAX`，因为要不然的话`INT_MAX + 1`就要溢出了。有人说，用INT_MAX干啥：硬币最小面额是1，全用1来破的话最大的硬币数量是`amount`，所以只要初始值设为比`amount`大就好了，那就设为`amount + 1`吧。然后代码就变成：
```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (coins.empty()) return -1;
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int value = 1; value <= amount; value++) {
            for (int coin: coins) {
                int left = value - coin;
                if (left < 0) continue;
                dp[value] = min(dp[value], 1 + dp[left]);
            }
        }
        return (dp.back() < amount + 1) ? dp.back() : -1;
    }
};
```
有什么区别呢？区别是不用检查`dp[left] == amount + 1`。为什么？因为`amount + 1`比INT_MAX小，小很多，所以不停的做`dp[left] + 1`也不会有关系。但是，你怎么知道`amount + 1`比`INT_MAX`小很多? 这个假设成立吗？不成立的。只是因为test case 没有包含`amount`值很大的情况。理论上完全有可能溢出，所以`amount + 1`这种初值需要假设，没有假设的时候很可爱，但是不严谨。