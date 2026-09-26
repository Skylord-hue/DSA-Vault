/*
 * Problem: Best Time to Buy and Sell Stock II (LeetCode 122)
 *
 * Description:
 * You are given an integer array prices where prices[i] is the price of a given stock on the ith day.
 * On each day, you may decide to buy and/or sell the stock. You can only hold at most one share of the stock at any time.
 * However, you can buy it then immediately sell it on the same day.
 * Find and return the maximum profit you can achieve. (Infinite transactions)
 *
 * Intuition / Approach:
 * - State Machine DP: At any day, we are either holding stock (can sell) or not holding (can buy).
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // ----------------------------------------------------
    // APPROACH 1: Pure Recursion (User's code)
    // Result: TLE (Time Limit Exceeded)
    // Time: O(2^N)
    // Note: This logic naturally solves the "Infinite Transactions" variant (LC 122), 
    // because after selling, it goes back to 'holding = false', allowing another buy.
    // ----------------------------------------------------
    int helperRec(vector<int>& prices, int i, bool holding) {
        if (i == prices.size()) return 0;
        
        if (holding) {
            int sell = prices[i] + helperRec(prices, i + 1, false); 
            int hold = helperRec(prices, i + 1, true); 
            return max(sell, hold);
        } else {
            int buy = -prices[i] + helperRec(prices, i + 1, true); 
            int skip = helperRec(prices, i + 1, false); 
            return max(buy, skip);
        }
    }

    // ----------------------------------------------------
    // APPROACH 2: Top-Down Memoization
    // Result: Accepted
    // Time: O(N * 2) -> O(N), Space: O(N * 2)
    // ----------------------------------------------------
    int helperMemo(vector<int>& prices, int i, int holding, vector<vector<int>>& memo) {
        if (i == prices.size()) return 0;
        
        if (memo[i][holding] != -1) return memo[i][holding];

        if (holding) {
            int sell = prices[i] + helperMemo(prices, i + 1, 0, memo); 
            int hold = helperMemo(prices, i + 1, 1, memo); 
            return memo[i][holding] = max(sell, hold);
        } else {
            int buy = -prices[i] + helperMemo(prices, i + 1, 1, memo); 
            int skip = helperMemo(prices, i + 1, 0, memo); 
            return memo[i][holding] = max(buy, skip);
        }
    }

    // ====================================================
    // MAIN FUNCTION: The LeetCode Entry Point
    // ====================================================
    int maxProfit(vector<int>& prices) {
        // holding can be 0 (false) or 1 (true)
        vector<vector<int>> memo(prices.size(), vector<int>(2, -1));
        return helperMemo(prices, 0, 0, memo);
    }
};

int main() {
    Solution sol;
    cout << "--- Best Time to Buy and Sell Stock II (Infinite Transactions) ---\n\n";
    
    vector<int> prices1 = {7,1,5,3,6,4};
    cout << "Input: prices = [7,1,5,3,6,4]\n";
    cout << "Output: " << sol.maxProfit(prices1) << " \nExpected: 7\n\n";
    
    vector<int> prices2 = {1,2,3,4,5};
    cout << "Input: prices = [1,2,3,4,5]\n";
    cout << "Output: " << sol.maxProfit(prices2) << " \nExpected: 4\n\n";

    return 0;
}
