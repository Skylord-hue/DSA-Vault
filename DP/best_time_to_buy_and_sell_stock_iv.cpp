/*
 * Problem: Best Time to Buy and Sell Stock IV (LeetCode 188)
 *
 * Description:
 * You are given an integer array prices and an integer k.
 * Find the maximum profit you can achieve. You may complete at most k transactions.
 * Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
 *
 * Intuition / Approach:
 * - State Machine DP with 3 parameters: (day, holding, transactions_left)
 * - User implementation choice: Deduct a transaction 'k' at the moment of BUYING.
 *   This is perfectly valid, as a transaction requires both a buy and a sell.
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // ----------------------------------------------------
    // APPROACH 1: Top-Down Memoization (State Machine)
    // Time: O(N * 2 * K), Space: O(N * 2 * K)
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
            // Sell the stock (Transaction count k was already reduced when we bought)
            int sell = prices[i] + helper(prices, i + 1, false, k);
            int hold = helper(prices, i + 1, true, k);
            result = max(sell, hold);
        } else {
            // Not holding
            int skip = helper(prices, i + 1, false, k);
            if (k > 0) { 
                // ONLY try buying if we actually have transactions left
                int buy = -prices[i] + helper(prices, i + 1, true, k - 1);
                result = max(buy, skip);
            } else {
                result = skip;
            }
        }

        return dp[i][holding][k] = result;
    }

    // ====================================================
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0; // edge case: no prices or no transactions allowed
        
        dp = vector<vector<vector<int>>>(n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
        return helper(prices, 0, false, k);
    }
};

int main() {
    Solution sol;
    cout << "--- Best Time to Buy and Sell Stock IV (At Most K Transactions) ---\n\n";
    
    vector<int> prices1 = {2,4,1};
    int k1 = 2;
    cout << "Input: k = 2, prices = [2,4,1]\n";
    cout << "Output: " << sol.maxProfit(k1, prices1) << " \nExpected: 2\n\n";
    
    vector<int> prices2 = {3,2,6,5,0,3};
    int k2 = 2;
    cout << "Input: k = 2, prices = [3,2,6,5,0,3]\n";
    cout << "Output: " << sol.maxProfit(k2, prices2) << " \nExpected: 7\n\n";

    return 0;
}
