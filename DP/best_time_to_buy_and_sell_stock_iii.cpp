/*
 * Problem: Best Time to Buy and Sell Stock III (LeetCode 123)
 *
 * Description:
 * You are given an array prices where prices[i] is the price of a given stock
 * on the ith day. Find the maximum profit you can achieve. You may complete at
 * most TWO transactions. Note: You may not engage in multiple transactions
 * simultaneously.
 *
 * Intuition / Approach:
 * - State Machine DP with 3 parameters: (day, holding, transactions_left)
 * - Identical to Stock IV, but k is strictly hardcoded to 2.
 */

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  // ----------------------------------------------------
  // APPROACH 1: Top-Down Memoization (State Machine)
  // Time: O(N * 2 * 2), Space: O(N * 2 * 2)
  // ----------------------------------------------------
  vector<vector<vector<int>>> dp;

  int helper(vector<int> &prices, int i, bool holding, int k) {
    if (i == prices.size())
      return 0;

    // If no transactions left and we aren't holding anything to sell, we're
    // done.
    if (k == 0 && !holding)
      return 0;

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
  int maxProfit(vector<int> &prices) {
    int n = prices.size();
    if (n == 0)
      return 0;

    int k = 2; // Strictly 2 transactions allowed
    dp = vector<vector<vector<int>>>(
        n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
    return helper(prices, 0, false, k);
  }

  // ----------------------------------------------------
  // APPROACH 2: Bottom-Up Tabulation (State Machine)
  // Time: O(N * 2 * 2), Space: O(N * 2 * 2)
  // ----------------------------------------------------
  int maxProfitTabulation(vector<int> &prices) {
    int n = prices.size();
    if (n == 0)
      return 0;

    int maxK = 2;
    // dpTab[day][holding][k]
    // Size: (N + 1) to handle the 'day == N' base case automatically with 0s.
    vector<vector<vector<int>>> dpTab(
        n + 1, vector<vector<int>>(2, vector<int>(maxK + 1, 0)));

    // Loop backwards from N - 1 down to 0 (Time traveling backwards)
    for (int i = n - 1; i >= 0; i--) {
      for (int holding = 0; holding <= 1; holding++) {
        for (int k = 0; k <= maxK; k++) {
          int result = 0;

          if (holding) { // Scenario A: You are HOLDING a stock
            // 1. Sell it today
            int sell = prices[i] + dpTab[i + 1][0][k];
            // 2. Skip and hold for tomorrow
            int hold = dpTab[i + 1][1][k];

            result = max(sell, hold);

          } else { // Scenario B: You are NOT holding a stock
            // 1. Skip and do nothing
            int skip = dpTab[i + 1][0][k];
            // 2. Buy it today (only if we have transactions left)
            if (k > 0) {
              int buy = -prices[i] + dpTab[i + 1][1][k - 1];
              result = max(buy, skip);
            } else {
              result = skip;
            }
          }

          dpTab[i][holding][k] = result;
        }
      }
    }

    // Target state: Start at Day 0, NOT holding a stock, with maxK transactions
    // available.
    return dpTab[0][0][maxK];
  }

  // ----------------------------------------------------
  // APPROACH 3: Ultimate Optimized Tabulation (Moving FORWARD)
  // Time: O(N * K), Space: O(K) -> NO 3D Grid Needed!
  // This perfectly matches your logic: we move forward in time,
  // and we explicitly update the "holding" (buy) and "not holding" (sell)
  // states by pulling from the past. Generalized for ANY 'K'.
  // ----------------------------------------------------
  int maxProfitOptimized(vector<int> &prices) {
    int n = prices.size();
    if (n == 0)
      return 0;

    int maxK = 2; // This works for ANY K (e.g., Stock IV)

    // The Past (Base cases before we start)
    // buy[k] tracks the maximum profit if we are HOLDING after k transactions
    // sell[k] tracks the maximum profit if we are NOT HOLDING after k
    // transactions
    vector<int> buy(maxK + 1, -prices[0]);
    vector<int> sell(maxK + 1, 0);

    // ONE single loop moving FORWARD through time
    for (int i = 1; i < n; i++) {
      // We update our states for each transaction based on yesterday's past
      for (int k = 1; k <= maxK; k++) {

        // If we decide to BUY today, we subtract the price from our profit
        // from the PREVIOUS completed transaction (sell[k-1]).
        buy[k] = max(buy[k], sell[k - 1] - prices[i]);

        // If we decide to SELL today, we add the price to our profit
        // from our current holding state (buy[k]).
        sell[k] = max(sell[k], buy[k] + prices[i]);
      }
    }

    // Return the max profit after completing all maxK transactions
    return sell[maxK];
  }
};

int main() {
  Solution sol;
  cout << "--- Best Time to Buy and Sell Stock III (At Most 2 Transactions) "
          "---\n\n";

  vector<int> prices1 = {3, 3, 5, 0, 0, 3, 1, 4};
  cout << "Input: prices = [3,3,5,0,0,3,1,4]\n";
  cout << "Output (Memoization): " << sol.maxProfit(prices1) << "\n";
  cout << "Output (Tabulation):  " << sol.maxProfitTabulation(prices1) << "\n";
  cout << "Output (Optimized):   " << sol.maxProfitOptimized(prices1) << "\n";
  cout << "Expected: 6\n\n";

  return 0;
}
