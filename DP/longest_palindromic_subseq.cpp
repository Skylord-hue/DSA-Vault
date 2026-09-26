#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
 * Problem: Longest Palindromic Subsequence (LeetCode 516)
 *
 * Description:
 * Given a string s, find the longest palindromic subsequence's length in s.
 * A subsequence is a sequence that can be derived from another sequence by deleting some or no elements 
 * without changing the order of the remaining elements.
 *
 * Intuition / Approach:
 * We use two pointers, `i` at the start and `j` at the end of the string.
 * - If s[i] == s[j], these two characters form a palindrome match. Add 2 to the length and shrink the window (i+1, j-1).
 * - If s[i] != s[j], we have two choices:
 *      1. Skip the left character (i+1, j)
 *      2. Skip the right character (i, j-1)
 *   We take the maximum of these two choices.
 * - To optimize overlapping subproblems from the recursive tree, we use a 2D memoization table (dp).
 */
class Solution {
public:
    // ----------------------------------------------------
    // APPROACH 1: Brute Force Subsequence Generation
    // Generates ALL subsequences and checks if they are palindromes.
    // Time: O(2^N * N), Space: O(N) for string copies in recursion
    // Result: Massive TLE (Time Limit Exceeded)
    // ----------------------------------------------------
    bool isPalindrome(string s) {
        int l = 0, r = s.size() - 1;
        while (l < r) {
            if (s[l] != s[r]) return false;
            l++; r--;
        }
        return true;
    }

    int helperBrute(const string &s, int i, string curr) {
        if (i == s.size()) {
            if (isPalindrome(curr)) return curr.size();
            return 0;
        }
        int pick = helperBrute(s, i + 1, curr + s[i]); // include s[i]
        int skip = helperBrute(s, i + 1, curr);        // exclude s[i]
        return max(pick, skip);
    }

    // ----------------------------------------------------
    // APPROACH 2: Pure Recursion (Two Pointers)
    // Optimal recursive structure, but overlapping subproblems.
    // Time: O(2^N), Space: O(N) stack depth
    // Result: TLE on LeetCode, but proves the core logic!
    // ----------------------------------------------------
    int helperRec(const string &s, int i, int j) {
        if (i > j) return 0;      // crossed over
        if (i == j) return 1;     // single char left

        if (s[i] == s[j]) {
            // pick both ends -> +2, move both pointers in
            return 2 + helperRec(s, i + 1, j - 1);
        } else {
            // skip either left or right end, take the best
            int skipLeft  = helperRec(s, i + 1, j);
            int skipRight = helperRec(s, i, j - 1);
            return max(skipLeft, skipRight);
        }
    }

    // ----------------------------------------------------
    // APPROACH 3: Top-Down Memoization
    // Caches the results of the recursive tree (Your final code from today)
    // Time: O(N^2), Space: O(N^2) for memo + O(N) stack
    // Result: Accepted
    // ----------------------------------------------------
    int helperMemo(const string &s, int i, int j, vector<vector<int>>& dp) {
        if (i > j) return 0;
        if (i == j) return 1;
        if (dp[i][j] != -1) return dp[i][j];

        if (s[i] == s[j])
            dp[i][j] = 2 + helperMemo(s, i + 1, j - 1, dp);
        else
            dp[i][j] = max(helperMemo(s, i + 1, j, dp), helperMemo(s, i, j - 1, dp));

        return dp[i][j];
    }

    // ====================================================
    // MAIN FUNCTION: The LeetCode Entry Point
    // ====================================================
    int longestPalindromeSubseq(string s) {
        // Just uncomment the specific approach you want to run!

        // return helperBrute(s, 0, "");
        
        // return helperRec(s, 0, s.size() - 1);

        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return helperMemo(s, 0, n - 1, dp);
    }
};

int main() {
    Solution sol;
    
    cout << "--- Longest Palindromic Subsequence ---\n\n";
    
    // Test Case 1
    string s1 = "bbbab";
    cout << "Input: s = \"" << s1 << "\"\n";
    cout << "Output: " << sol.longestPalindromeSubseq(s1) << " \nExpected: 4 (e.g., 'bbbb')\n\n";
    
    // Test Case 2
    string s2 = "cbbd";
    cout << "Input: s = \"" << s2 << "\"\n";
    cout << "Output: " << sol.longestPalindromeSubseq(s2) << " \nExpected: 2 (e.g., 'bb')\n\n";

    // Test Case 3
    string s3 = "a";
    cout << "Input: s = \"" << s3 << "\"\n";
    cout << "Output: " << sol.longestPalindromeSubseq(s3) << " \nExpected: 1 (e.g., 'a')\n\n";

    return 0;
}
