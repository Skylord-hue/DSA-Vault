/*
 * Problem: Best Time to Buy and Sell Stock (LeetCode 121)
 *
 * Description:
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
 * You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
 * Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
 *
 * Intuition / Approach:
 * - State Machine DP: At any day, we are either holding stock (can sell) or not holding (can buy).
 * - Since we are limited to EXACTLY 1 transaction, we must track if we have used our transaction yet.
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
    int helperMemo(vector<int>& prices, int i, int holding, int usedTransaction, vector<vector<vector<int>>>& memo) {
        if (i == prices.size() || usedTransaction == 1) return 0;
        
        if (memo[i][holding][usedTransaction] != -1) return memo[i][holding][usedTransaction];

        if (holding == 1) {
            // Once we sell, we have completed the transaction (usedTransaction = 1)
            int sell = prices[i] + helperMemo(prices, i + 1, 0, 1, memo); 
            int hold = helperMemo(prices, i + 1, 1, usedTransaction, memo);
            return memo[i][holding][usedTransaction] = max(sell, hold);
        } else {
            // Buying does not complete the transaction yet, we are just holding now
            int buy = -prices[i] + helperMemo(prices, i + 1, 1, usedTransaction, memo);
            int skip = helperMemo(prices, i + 1, 0, usedTransaction, memo);
            return memo[i][holding][usedTransaction] = max(buy, skip);
        }
    }

    // ====================================================
    int maxProfit(vector<int>& prices) {
        // memo[day][holding][usedTransaction]
        vector<vector<vector<int>>> memo(prices.size(), vector<vector<int>>(2, vector<int>(2, -1)));
        return helperMemo(prices, 0, 0, 0, memo);
    }
};

int main() {
    Solution sol;
    cout << "--- Best Time to Buy and Sell Stock I (Single Transaction State Machine) ---\n\n";
    
    vector<int> prices1 = {7,1,5,3,6,4};
    cout << "Input: prices = [7,1,5,3,6,4]\n";
    cout << "Output: " << sol.maxProfit(prices1) << " \nExpected: 5 (Buy at 1, Sell at 6)\n\n";
    
    vector<int> prices2 = {7,6,4,3,1};
    cout << "Input: prices = [7,6,4,3,1]\n";
    cout << "Output: " << sol.maxProfit(prices2) << " \nExpected: 0\n\n";

    return 0;
}
