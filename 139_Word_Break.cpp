class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        size_t n = s.size();
        vector<bool> dp(n+1, false);
        unordered_set<string> set(wordDict.begin(), wordDict.end());
        dp[0] = true;
        for (int j = 1; j <= n; j++) {
            for (size_t len = 1; len <= j; len++) {
                string substr = s.substr(j - len, len);
                dp[j] = set.find(substr) != set.end() && dp[j-len];
                if (dp[j] == true) break;
            }
        }
        return dp.back();
    }
};