/*
 * Problem: Longest Common Subsequence (LeetCode 1143)
 *
 * Description:
 * Given two strings text1 and text2, return the length of their longest common subsequence.
 *
 * Intuition / Approach:
 * - If text1[i] == text2[j], we found a common character: 1 + helper(i+1, j+1)
 * - If they don't match, we branch: max(helper(i+1, j), helper(i, j+1))
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    // ----------------------------------------------------
    // APPROACH 1: Pure Recursion
    // Result: TLE (Time Limit Exceeded - exactly as seen in your screenshot!)
    // Time: O(2^(M+N))
    // ----------------------------------------------------
    int helperRec(const string& s1, const string& s2, int i, int j) {
        if (i == s1.size() || j == s2.size()) return 0;
        
        if (s1[i] == s2[j]) {
            return 1 + helperRec(s1, s2, i + 1, j + 1);
        } else {
            return max(helperRec(s1, s2, i + 1, j), helperRec(s1, s2, i, j + 1));
        }
    }

    // ----------------------------------------------------
    // APPROACH 2: Top-Down Memoization
    // Result: Accepted
    // Time: O(M*N), Space: O(M*N)
    // ----------------------------------------------------
    int helperMemo(const string& s1, const string& s2, int i, int j, vector<vector<int>>& memo) {
        if (i == s1.size() || j == s2.size()) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        
        if (s1[i] == s2[j]) {
            return memo[i][j] = 1 + helperMemo(s1, s2, i + 1, j + 1, memo);
        } else {
            return memo[i][j] = max(helperMemo(s1, s2, i + 1, j, memo), helperMemo(s1, s2, i, j + 1, memo));
        }
    }

    // ====================================================
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> memo(text1.size(), vector<int>(text2.size(), -1));
        return helperMemo(text1, text2, 0, 0, memo);
    }
};

int main() {
    Solution sol;
    cout << "--- Longest Common Subsequence ---\n";
    cout << "Output: " << sol.longestCommonSubsequence("abcde", "ace") << " | Expected: 3\n";
    return 0;
}
