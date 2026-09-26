/*
 * Problem: Target Sum (LeetCode 494)
 *
 * Description:
 * You are given an integer array nums and an integer target.
 * You want to build an expression out of nums by adding one of the symbols '+' and '-' 
 * before each integer in nums and then concatenate all the integers.
 * Return the number of different expressions that you can build, which evaluates to target.
 *
 * Intuition / Approach:
 * This can be mapped to 0/1 Knapsack (Partition Equal Subset Sum).
 * We divide nums into two subsets S1 (positive sign) and S2 (negative sign).
 * S1 - S2 = target
 * S1 + S2 = totalSum
 * Therefore, 2*S1 = target + totalSum  =>  S1 = (target + totalSum) / 2
 * Now the problem reduces to finding the number of subsets with sum = S1.
 */

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    // ----------------------------------------------------
    // APPROACH 1: Pure Backtracking (The Initial Intuition)
    // Result: TLE on LeetCode
    // Why: O(2^N) time complexity because at each step we branch into 2 paths (+ or -).
    // ----------------------------------------------------
    int helperRec(vector<int>& nums, int i, int currentSum, int target) {
        if (i == nums.size()) {
            return currentSum == target ? 1 : 0;
        }
        int add = helperRec(nums, i + 1, currentSum + nums[i], target);
        int sub = helperRec(nums, i + 1, currentSum - nums[i], target);
        return add + sub;
    }

    // ----------------------------------------------------
    // APPROACH 2: Top-Down Memoization (Subset Sum Reduction)
    // Time: O(N * S1), Space: O(N * S1)
    // Result: Accepted
    // ----------------------------------------------------
    int subsetSumMemo(vector<int>& nums, int i, int sum, vector<vector<int>>& memo) {
        if (i < 0) {
            return sum == 0 ? 1 : 0;
        }
        
        if (memo[i][sum] != -1) return memo[i][sum];

        // Option 1: Don't include current number
        int notTake = subsetSumMemo(nums, i - 1, sum, memo);
        
        // Option 2: Include current number (if possible)
        int take = 0;
        if (nums[i] <= sum) {
            take = subsetSumMemo(nums, i - 1, sum - nums[i], memo);
        }

        return memo[i][sum] = take + notTake;
    }

    // ====================================================
    // MAIN FUNCTION: The LeetCode Entry Point
    // ====================================================
    int findTargetSumWays(vector<int>& nums, int target) {
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        
        // Impossible cases
        if (totalSum - target < 0 || (totalSum - target) % 2 != 0) {
            return 0;
        }
        
        int s1 = (totalSum - target) / 2;
        int n = nums.size();
        
        vector<vector<int>> memo(n, vector<int>(s1 + 1, -1));
        return subsetSumMemo(nums, n - 1, s1, memo);
    }
};

int main() {
    Solution sol;
    cout << "--- Target Sum ---\n\n";
    
    vector<int> nums1 = {1, 1, 1, 1, 1};
    int target1 = 3;
    cout << "Input: nums = [1,1,1,1,1], target = 3\n";
    cout << "Output: " << sol.findTargetSumWays(nums1, target1) << " \nExpected: 5\n\n";
    
    vector<int> nums2 = {1};
    int target2 = 1;
    cout << "Input: nums = [1], target = 1\n";
    cout << "Output: " << sol.findTargetSumWays(nums2, target2) << " \nExpected: 1\n\n";

    return 0;
}
