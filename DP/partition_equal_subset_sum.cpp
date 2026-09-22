#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>

using namespace std;

/*
 * ============================================================================
 * Problem: LeetCode 416 - Partition Equal Subset Sum
 * Category: Dynamic Programming (0/1 Knapsack Reduction)
 *
 * Mathematical Invariant & Derivation Evolution:
 * ----------------------------------------------------------------------------
 * 1. Parity Check:
 *    Let S = sum(nums). If S is odd (S % 2 != 0), it is mathematically
 *    impossible to partition into two equal integer subsets. Return false.
 *    If S is even, target subset sum W = S / 2.
 *
 * 2. Progression of Approaches (Narendra's Derivation History):
 *    - Approach 1 (Initial Paper Derivation): Pure Backtracking with sumCheck(a, b).
 *      Recurrence explores all 2^N subsets. sumCheck takes O(N) at each leaf.
 *      Total Time: O(N * 2^N) -> TLE on LeetCode.
 *
 *    - Approach 2 (Narendra's Memoized DP): Top-Down with Early Pruning.
 *      State: helper(i, picked, rest)
 *      Early prune: picked > rest (equivalent to picked > W).
 *      Memoization: memo[i][picked] bounds table to N * (W + 1).
 *      Time: O(N * W), Space: O(N * W) table + O(N) recursion stack.
 *
 *    - Approach 3 (Optimal Space-Optimized Tabulation): Bottom-Up 1D DP.
 *      State: dp[w] = true if subset sum w is achievable.
 *      Base: dp[0] = true.
 *      Loop Invariant: w runs backwards from W down to num.
 *      Why backwards? Running backwards ensures each element is used at most
 *      once (0/1 choice), preventing the same number from being reused in the same step.
 *      Time: O(N * W), Space: O(W) auxiliary.
 * ============================================================================
 */

class Solution {
public:
    // ------------------------------------------------------------------------
    // Approach 1: Narendra's Initial Paper Backtracking Derivation (O(N * 2^N))
    // ------------------------------------------------------------------------
    bool sumCheck(vector<int>& a, vector<int>& b) {
        int s1 = 0, s2 = 0;
        for (int x : a) s1 += x;
        for (int x : b) s2 += x;
        return s1 == s2;
    }

    bool backtrackHelper(vector<int>& nums, vector<int>& ans, int i) {
        if (sumCheck(nums, ans)) return true;
        if (i == nums.size()) return false;

        int val = nums[i];

        // Pick nums[i]
        ans.push_back(val);
        nums[i] = 0;
        if (backtrackHelper(nums, ans, i + 1)) return true;

        // Undo pick (backtrack)
        ans.pop_back();
        nums[i] = val;

        // Skip nums[i]
        return backtrackHelper(nums, ans, i + 1);
    }

    bool canPartition_Backtrack(vector<int> nums) {
        vector<int> ans;
        return backtrackHelper(nums, ans, 0);
    }

    // ------------------------------------------------------------------------
    // Approach 2: Narendra's Optimized Memoized DP (O(N * W) Time, O(N * W) Space)
    // ------------------------------------------------------------------------
    bool memoHelper(vector<int>& nums, int i, int picked, int rest, vector<vector<int>>& memo) {
        if (picked == rest) return true;
        if (i == nums.size() || picked > rest) return false;
        if (memo[i][picked] != -1) return memo[i][picked];

        int val = nums[i];

        // Choice: Pick val (moves from rest to picked) OR Skip val
        bool res = memoHelper(nums, i + 1, picked + val, rest - val, memo)
                || memoHelper(nums, i + 1, picked, rest, memo);

        return memo[i][picked] = res;
    }

    bool canPartition_Memo(vector<int>& nums) {
        int total = 0;
        for (int x : nums) total += x;
        if (total % 2 != 0) return false;

        vector<vector<int>> memo(nums.size(), vector<int>(total / 2 + 1, -1));
        return memoHelper(nums, 0, 0, total, memo);
    }

    // ------------------------------------------------------------------------
    // Approach 3: Optimal 1D Space Tabulation (O(N * W) Time, O(W) Space)
    // ------------------------------------------------------------------------
    bool canPartition_Optimal(vector<int>& nums) {
        int total = 0;
        for (int x : nums) total += x;
        if (total % 2 != 0) return false;

        int target = total / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true; // Base case: subset sum 0 is always possible (empty set)

        for (int num : nums) {
            // Traverse backwards to preserve 0/1 knapsack invariant
            for (int w = target; w >= num; --w) {
                if (dp[w - num]) {
                    dp[w] = true;
                }
            }
            if (dp[target]) return true; // Early exit if target achieved
        }

        return dp[target];
    }
};

// ============================================================================
// Test Harness & Verification Suite
// ============================================================================
struct TestCase {
    int id;
    vector<int> nums;
    bool expected;
    string desc;
};

int main() {
    Solution solver;
    cout << "============================================================\n";
    cout << "   LC 416: PARTITION EQUAL SUBSET SUM VERIFICATION SUITE    \n";
    cout << "============================================================\n\n";

    vector<TestCase> cases = {
        {1, {1, 5, 11, 5}, true, "Standard Case: Split into {1, 5, 5} and {11}, sum = 11"},
        {2, {1, 2, 3, 5}, false, "Odd total sum (11) -> mathematically impossible"},
        {3, {2, 2, 2, 2}, true, "Even duplicates: Split into {2, 2} and {2, 2}, sum = 4"},
        {4, {1, 2, 5}, false, "Even total sum (8), target = 4, but cannot form 4"},
        {5, {100}, false, "Single element cannot be split into two non-empty subsets"}
    };

    for (auto& tc : cases) {
        bool memoAns = solver.canPartition_Memo(tc.nums);
        bool optAns = solver.canPartition_Optimal(tc.nums);
        bool passed = (memoAns == tc.expected) && (optAns == tc.expected);

        cout << "Test " << tc.id << ": " << tc.desc << "\n";
        cout << "  Input: nums = [";
        for (size_t i = 0; i < tc.nums.size(); ++i) {
            cout << tc.nums[i] << (i + 1 < tc.nums.size() ? ", " : "");
        }
        cout << "]\n";
        cout << "  Memoized DP: " << (memoAns ? "true" : "false");
        cout << " | Optimal 1D: " << (optAns ? "true" : "false");
        cout << " | Expected: " << (tc.expected ? "true" : "false");
        cout << " -> " << (passed ? "[PASS]" : "[FAIL]") << "\n\n";
    }

    return 0;
}
