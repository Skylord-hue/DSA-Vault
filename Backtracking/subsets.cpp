#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * ============================================================================
 * Problem: LeetCode 78 - Subsets
 * Category: Backtracking / Power Set Generation
 *
 * Mathematical Invariant & Proof:
 * ----------------------------------------------------------------------------
 * 1. Combinatorial Bound:
 *    For an array of size N with unique elements, every element has a binary
 *    choice: either it is included in the subset, or it is excluded.
 *    Total number of subsets = 2^N.
 *
 * 2. Loop-Based Backtracking Invariant:
 *    - State: helper(nums, result, ans, index)
 *    - At the start of each helper call, ans is a valid subset of size k.
 *      Push it to result immediately.
 *    - The loop `for(int i = index; i < nums.size(); i++)` branches into
 *      all possible subsequent elements without revisiting previous indices.
 *      This strictly prevents permutations and eliminates duplicate subsets.
 *    - Action: ans.push_back(nums[i]) -> Recurse with i + 1 -> ans.pop_back() (backtrack).
 *
 * 3. Complexity Bounds:
 *    - Time Complexity:  O(N * 2^N) because there are 2^N subsets, and copying
 *      each subset of average length N/2 into the result takes O(N) time.
 *    - Space Complexity: O(N) auxiliary recursion call stack depth (excluding output).
 * ============================================================================
 */

class Solution {
public:
    void helper(vector<int>& nums, vector<vector<int>>& result, vector<int>& ans, int index) {
        // Invariant: ans is always a valid subset at this node of the decision tree
        result.push_back(ans);

        for (int i = index; i < (int)nums.size(); i++) {
            ans.push_back(nums[i]);        // Pick nums[i]
            helper(nums, result, ans, i + 1); // Recurse on remaining elements
            ans.pop_back();               // Backtrack: undo pick
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> ans;
        helper(nums, result, ans, 0);
        return result;
    }
};

// ============================================================================
// Test Harness & Verification Suite
// ============================================================================
int main() {
    Solution solver;
    cout << "============================================================\n";
    cout << "          LC 78: SUBSETS BACKTRACKING VERIFICATION          \n";
    cout << "============================================================\n\n";

    vector<int> nums = {1, 2, 3};
    auto res = solver.subsets(nums);

    cout << "Input: nums = [1, 2, 3]\n";
    cout << "Generated Subsets (Count = " << res.size() << " | Expected = 8):\n";

    for (size_t i = 0; i < res.size(); ++i) {
        cout << "  " << (i + 1) << ". [";
        for (size_t j = 0; j < res[i].size(); ++j) {
            cout << res[i][j] << (j + 1 < res[i].size() ? ", " : "");
        }
        cout << "]\n";
    }

    bool pass = (res.size() == 8);
    cout << "\nStatus: " << (pass ? "[PASS]" : "[FAIL]") << "\n";

    return 0;
}
