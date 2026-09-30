/*
 * Problem: Longest Increasing Subsequence (LeetCode 300)
 *
 * Description:
 * Given an integer array nums, return the length of the longest strictly increasing subsequence.
 *
 * Intuition / Approach:
 * - We need to decide at each step `i` whether to pick `nums[i]` or not.
 * - To make a valid pick, `nums[i]` must be strictly greater than the last picked element.
 * - We track `j` (the index of the last picked element) along with `i`.
 * - To avoid negative indexing in memoization (since `j` starts at -1), we shift `j` by +1 in the DP table.
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // ----------------------------------------------------
    // APPROACH 1: Top-Down Memoization (The User's Solution)
    // Time: O(N^2), Space: O(N^2)
    // ----------------------------------------------------
    int helperMemo(vector<int>& nums, int i, int j, vector<vector<int>>& dp) {
        if (i == nums.size()) return 0;

        // dp indexed with j+1 since j can be -1 (no element picked yet)
        if (dp[i][j + 1] != -1) return dp[i][j + 1];

        // Option 1: Skip current element
        int skip = helperMemo(nums, i + 1, j, dp);

        // Option 2: Pick current element (if valid)
        int pick = 0;
        if (j == -1 || nums[j] < nums[i]) {
            pick = 1 + helperMemo(nums, i + 1, i, dp); 
        }

        return dp[i][j + 1] = max(pick, skip);
    }

    // ====================================================
    // MAIN FUNCTION: The LeetCode Entry Point
    // ====================================================
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        // dp table of size (N+1) x (N+1) to accommodate the j+1 shift
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return helperMemo(nums, 0, -1, dp);
    }

    // ----------------------------------------------------
    // APPROACH 2: 1D Tabulation (Your exact logic!)
    // Time: O(N^2), Space: O(N)
    // ----------------------------------------------------
    int lengthOfLISTabulation(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        // 1. "we don't have any value, so we will analyze it to..."
        // Initialize DP array. Every element is a subsequence of length 1 by default!
        vector<int> dp(n, 1);
        int maxLIS = 1; // Track the absolute maximum we find anywhere
        
        // 2. "if you are at any eye index... loop it for the end value"
        for (int i = 0; i < n; i++) {
            
            // 3. "check the already answered... from the previous one"
            for (int prev = 0; prev < i; prev++) {
                
                // 4. "if it is greater than..."
                if (nums[i] > nums[prev]) {
                    // "...we will add that value to the previous value we had"
                    dp[i] = max(dp[i], dp[prev] + 1);
                }
            }
            
            // We just keep track of the maximum value we ever store in our DP
            maxLIS = max(maxLIS, dp[i]);
        }
        
        return maxLIS;
    }
};

int main() {
    Solution sol;
    cout << "--- Longest Increasing Subsequence ---\n\n";
    
    vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "Input: nums = [10, 9, 2, 5, 3, 7, 101, 18]\n";
    cout << "Output (Memoization): " << sol.lengthOfLIS(nums1) << "\n";
    cout << "Output (Tabulation):  " << sol.lengthOfLISTabulation(nums1) << "\n";
    cout << "Expected: 4\n\n";
    
    vector<int> nums2 = {0, 1, 0, 3, 2, 3};
    cout << "Input: nums = [0, 1, 0, 3, 2, 3]\n";
    cout << "Output (Memoization): " << sol.lengthOfLIS(nums2) << "\n";
    cout << "Output (Tabulation):  " << sol.lengthOfLISTabulation(nums2) << "\n";
    cout << "Expected: 4\n\n";

    vector<int> nums3 = {7, 7, 7, 7, 7, 7, 7};
    cout << "Input: nums = [7, 7, 7, 7, 7, 7, 7]\n";
    cout << "Output (Memoization): " << sol.lengthOfLIS(nums3) << "\n";
    cout << "Output (Tabulation):  " << sol.lengthOfLISTabulation(nums3) << "\n";
    cout << "Expected: 1\n\n";

    return 0;
}
