/*
 * Problem: Perfect Squares (LeetCode 279)
 *
 * Description:
 * Given an integer n, return the least number of perfect square numbers that sum to n.
 *
 * Intuition / Approach:
 * Unbounded Knapsack / DP. Try all perfect squares <= n.
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // ----------------------------------------------------
    // APPROACH 1: Top-Down Memoization
    // Result: Accepted
    // Time: O(N * sqrt(N))
    // ----------------------------------------------------
    int helperMemo(int n, vector<int>& memo) {
        if (n == 0) return 0;
        if (memo[n] != -1) return memo[n];

        int minCoins = 1e9;
        for (int i = 1; i * i <= n; i++) {
            minCoins = min(minCoins, 1 + helperMemo(n - i * i, memo));
        }

        return memo[n] = minCoins;
    }

    // ====================================================
    int numSquares(int n) {
        vector<int> memo(n + 1, -1);
        return helperMemo(n, memo);
    }
};

int main() {
    Solution sol;
    cout << "--- Perfect Squares ---\n";
    cout << "Output: " << sol.numSquares(12) << " | Expected: 3 (4+4+4)\n";
    return 0;
}
