/*
 * Problem: Last Stone Weight II (LeetCode 1049)
 *
 * Description:
 * You are given an array of integers stones. Smash stones together.
 * Return the smallest possible weight of the left stone.
 *
 * Intuition / Approach:
 * This mathematically reduces to finding a subset of stones whose sum is as close to totalSum/2 as possible.
 * Similar to Partition Equal Subset Sum, it's a 0/1 Knapsack problem.
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

class Solution {
public:
    // ----------------------------------------------------
    // APPROACH 1: Top-Down Memoization
    // Result: Accepted
    // Time: O(N * S/2), Space: O(N * S/2)
    // ----------------------------------------------------
    int helperMemo(vector<int>& stones, int i, int target, vector<vector<int>>& memo) {
        if (target < 0) return 0;
        if (i == stones.size()) return 0;
        if (memo[i][target] != -1) return memo[i][target];

        int skip = helperMemo(stones, i + 1, target, memo);
        int take = 0;
        if (stones[i] <= target) {
            take = stones[i] + helperMemo(stones, i + 1, target - stones[i], memo);
        }

        return memo[i][target] = max(take, skip);
    }

    // ====================================================
    int lastStoneWeightII(vector<int>& stones) {
        int totalSum = accumulate(stones.begin(), stones.end(), 0);
        int target = totalSum / 2;
        vector<vector<int>> memo(stones.size(), vector<int>(target + 1, -1));
        
        int bestSubsetSum = helperMemo(stones, 0, target, memo);
        
        // The remaining stones sum is (totalSum - bestSubsetSum)
        // The difference is (totalSum - bestSubsetSum) - bestSubsetSum
        return totalSum - 2 * bestSubsetSum;
    }
};

int main() {
    Solution sol;
    cout << "--- Last Stone Weight II ---\n";
    vector<int> stones = {2,7,4,1,8,1};
    cout << "Output: " << sol.lastStoneWeightII(stones) << " | Expected: 1\n";
    return 0;
}
