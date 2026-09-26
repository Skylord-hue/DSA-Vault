/*
 * Problem: Coin Change II (LeetCode 518)
 *
 * Description:
 * Return the number of combinations that make up that amount.
 *
 * Intuition / Approach:
 * Unbounded knapsack (combinations).
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int helperMemo(int amount, vector<int>& coins, int i, vector<vector<int>>& memo) {
        if (amount == 0) return 1;
        if (i < 0 || amount < 0) return 0;
        if (memo[i][amount] != -1) return memo[i][amount];

        int notTake = helperMemo(amount, coins, i - 1, memo);
        int take = 0;
        if (coins[i] <= amount) {
            take = helperMemo(amount - coins[i], coins, i, memo); // stay on i for unbounded
        }

        return memo[i][amount] = take + notTake;
    }

    int change(int amount, vector<int>& coins) {
        vector<vector<int>> memo(coins.size(), vector<int>(amount + 1, -1));
        return helperMemo(amount, coins, coins.size() - 1, memo);
    }
};

int main() {
    Solution sol;
    cout << "--- Coin Change II ---\n";
    vector<int> coins = {1, 2, 5};
    cout << "Output: " << sol.change(5, coins) << " | Expected: 4\n";
    return 0;
}
