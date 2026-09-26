/*
 * Problem: Best Time to Buy and Sell Stock III (LeetCode 123)
 *
 * Description:
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
 * Find the maximum profit you can achieve. You may complete at most TWO transactions.
 * Note: You may not engage in multiple transactions simultaneously.
 *
 * Intuition / Approach:
 * - State Machine DP with 3 parameters: (day, holding, transactions_left)
 * - Identical to Stock IV, but k is strictly hardcoded to 2.
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // ----------------------------------------------------
    // APPROACH 1: Top-Down Memoization (State Machine)
    // Time: O(N * 2 * 2), Space: O(N * 2 * 2)
    // ----------------------------------------------------
    vector<vector<vector<int>>> dp;

    int helper(vector<int>& prices, int i, bool holding, int k) {
        if (i == prices.size()) return 0;
        
        // If no transactions left and we aren't holding anything to sell, we're done.
        if (k == 0 && !holding) return 0;

        if (dp[i][holding][k] != -1) 
            return dp[i][holding][k];

        int result;
        if (holding) {
            int sell = prices[i] + helper(prices, i + 1, false, k);
            int hold = helper(prices, i + 1, true, k);
            result = max(sell, hold);
        } else {
            int skip = helper(prices, i + 1, false, k);
            if (k > 0) { 
                int buy = -prices[i] + helper(prices, i + 1, true, k - 1);
                result = max(buy, skip);
            } else {
                result = skip;
            }
        }

        return dp[i][holding][k] = result;
    }

    // ====================================================
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        
        int k = 2; // Strictly 2 transactions allowed
        dp = vector<vector<vector<int>>>(n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
        return helper(prices, 0, false, k);
    }
};

int main() {
    Solution sol;
    cout << "--- Best Time to Buy and Sell Stock III (At Most 2 Transactions) ---\n\n";
    
    vector<int> prices1 = {3,3,5,0,0,3,1,4};
    cout << "Input: prices = [3,3,5,0,0,3,1,4]\n";
    cout << "Output: " << sol.maxProfit(prices1) << " \nExpected: 6\n\n";
    
    return 0;
}
