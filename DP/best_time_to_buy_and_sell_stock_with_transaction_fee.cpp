/*
 * Problem: Best Time to Buy and Sell Stock with Transaction Fee (LeetCode 714)
 *
 * Description:
 * You are given an array prices where prices[i] is the price of a given stock on the ith day,
 * and an integer fee representing a transaction fee.
 * Find the maximum profit you can achieve. You may complete as many transactions as you like,
 * but you need to pay the transaction fee for each transaction.
 *
 * Intuition / Approach:
 * - State Machine DP: (day, holding)
 * - Simply subtract the fee when you sell (or when you buy).
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

    int helper(vector<int>& prices, int i, bool holding, int fee) {
        if (i == prices.size()) return 0;

        if (dp[i][holding] != -1) 
            return dp[i][holding]; 

        int result;
        if (holding) {
            // Pay fee when selling
            int sell = prices[i] - fee + helper(prices, i + 1, false, fee); 
            int hold = helper(prices, i + 1, true, fee);
            result = max(sell, hold);
        } else {
            int buy = -prices[i] + helper(prices, i + 1, true, fee);
            int skip = helper(prices, i + 1, false, fee);
            result = max(buy, skip);
        }

        return dp[i][holding] = result;
    }

    // ====================================================
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if (n == 0) return 0;
        dp = vector<vector<int>>(n, vector<int>(2, -1));
        return helper(prices, 0, false, fee);
    }
};

int main() {
    Solution sol;
    cout << "--- Best Time to Buy and Sell Stock with Transaction Fee ---\n\n";
    
    vector<int> prices1 = {1,3,2,8,4,9};
    int fee1 = 2;
    cout << "Input: prices = [1,3,2,8,4,9], fee = 2\n";
    cout << "Output: " << sol.maxProfit(prices1, fee1) << " \nExpected: 8\n\n";
    
    return 0;
}
