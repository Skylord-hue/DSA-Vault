/*
 * Problem: Best Time to Buy and Sell Stock with Cooldown (LeetCode 309)
 *
 * Description:
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
 * Find the maximum profit you can achieve. You may complete as many transactions as you like
 * with the following restriction: After you sell your stock, you cannot buy stock on the next day.
 *
 * Intuition / Approach:
 * - State Machine DP: (day, holding)
 * - To implement the cooldown constraint, simply jump to `i + 2` after a sell instead of `i + 1`.
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // ----------------------------------------------------
    // APPROACH 1: Top-Down Memoization (State Machine)
    // Time: O(N * 2), Space: O(N * 2)
    // ----------------------------------------------------
    vector<vector<int>> dp;

    int helper(vector<int>& prices, int i, bool holding) {
        // Base case captures i = N and i = N + 1 (from i + 2 jumps)
        if (i >= prices.size()) return 0;

        if (dp[i][holding] != -1) 
            return dp[i][holding]; // already solved, reuse it

        int result;
        if (holding) {
            // Sell forces a 1-day cooldown, so we jump to i + 2
            int sell = prices[i] + helper(prices, i + 2, false); 
            int hold = helper(prices, i + 1, true);
            result = max(sell, hold);
        } else {
            // Buy as normal
            int buy = -prices[i] + helper(prices, i + 1, true);
            int skip = helper(prices, i + 1, false);
            result = max(buy, skip);
        }

        return dp[i][holding] = result;
    }

    // ====================================================
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        dp = vector<vector<int>>(n + 1, vector<int>(2, -1)); 
        return helper(prices, 0, false);
    }
};

int main() {
    Solution sol;
    cout << "--- Best Time to Buy and Sell Stock with Cooldown ---\n\n";
    
    vector<int> prices1 = {1,2,3,0,2};
    cout << "Input: prices = [1,2,3,0,2]\n";
    cout << "Output: " << sol.maxProfit(prices1) << " \nExpected: 3 (Buy 1, Sell 2, Cooldown, Buy 0, Sell 2)\n\n";
    
    vector<int> prices2 = {1};
    cout << "Input: prices = [1]\n";
    cout << "Output: " << sol.maxProfit(prices2) << " \nExpected: 0\n\n";

    return 0;
}
