/*
 * Problem: Coin Change (LeetCode 322)
 *
 * Description:
 * You are given an integer array coins representing coins of different denominations and an integer amount.
 * Return the fewest number of coins that you need to make up that amount.
 * If that amount of money cannot be made up by any combination of the coins, return -1.
 *
 * Intuition / Approach:
 * Unbounded Knapsack variant. For each amount, we can either:
 * - Not use the current coin (move to next coin)
 * - Use the current coin (stay on the same coin index, since we have infinite supply)
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // ----------------------------------------------------
    // APPROACH 1: Pure Recursion
    // Result: TLE on LeetCode
    // Why: O(2^N) or worse because it re-evaluates the same subproblems repeatedly.
    // ----------------------------------------------------
    int helperRec(vector<int>& coins, int idx, int amount) {
        if (amount == 0) return 0;
        if (idx < 0 || amount < 0) return 1e9; // Invalid

        int notTake = helperRec(coins, idx - 1, amount);
        int take = 1e9;
        if (coins[idx] <= amount) {
            take = 1 + helperRec(coins, idx, amount - coins[idx]);
        }

        return min(take, notTake);
    }

    // ----------------------------------------------------
    // APPROACH 2: Top-Down Memoization
    // Time: O(N * Amount), Space: O(N * Amount)
    // Result: Accepted
    // ----------------------------------------------------
    int helperMemo(vector<int>& coins, int idx, int amount, vector<vector<int>>& memo) {
        if (amount == 0) return 0;
        if (idx < 0 || amount < 0) return 1e9;
        
        if (memo[idx][amount] != -1) return memo[idx][amount];

        int notTake = helperMemo(coins, idx - 1, amount, memo);
        int take = 1e9;
        if (coins[idx] <= amount) {
            take = 1 + helperMemo(coins, idx, amount - coins[idx], memo);
        }

        return memo[idx][amount] = min(take, notTake);
    }

    // ====================================================
    // MAIN FUNCTION: The LeetCode Entry Point
    // ====================================================
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> memo(n, vector<int>(amount + 1, -1));
        
        int ans = helperMemo(coins, n - 1, amount, memo);
        return ans >= 1e9 ? -1 : ans;
    }
};

int main() {
    Solution sol;
    cout << "--- Coin Change ---\n\n";
    
    vector<int> coins1 = {1, 2, 5};
    int amount1 = 11;
    cout << "Input: coins = [1,2,5], amount = 11\n";
    cout << "Output: " << sol.coinChange(coins1, amount1) << " \nExpected: 3 (5+5+1)\n\n";
    
    vector<int> coins2 = {2};
    int amount2 = 3;
    cout << "Input: coins = [2], amount = 3\n";
    cout << "Output: " << sol.coinChange(coins2, amount2) << " \nExpected: -1\n\n";

    return 0;
}
