/*
 * Problem: Edit Distance (LeetCode 72)
 *
 * Description:
 * Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
 * You have the following three operations permitted on a word: Insert a character, Delete a character, Replace a character.
 *
 * Intuition / Approach:
 * We use two pointers, `i` for `word1` and `j` for `word2`.
 * - If word1[i] == word2[j], we advance both pointers (cost 0).
 * - If they don't match, we have 3 choices (each costs 1):
 *     1. Insert: Advance j (matches inserted char with word2[j]).
 *     2. Delete: Advance i (skip char in word1).
 *     3. Replace: Advance both i and j.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    /*
    // ----------------------------------------------------
    // APPROACH 1: Narendra's Initial Recursive Attempt (From Screenshot)
    // Result: WRONG & TLE 
    // Why it was wrong:
    // 1. Pass by Value: `string word1` was passed by value, causing O(N) copies per recursive call.
    // 2. Over-simulation: It literally modified the string using `insert` and `erase`. 
    //    These are O(N) operations inside a recursive loop! We only need to logically shift indices.
    // ----------------------------------------------------
    int helperWrong(string word1, string word2, int i, int j) {
        if (i == word1.size()) return word2.size() - j;
        if (j == word2.size()) return word1.size() - i;

        if (word1[i] == word2[j]) {
            return helperWrong(word1, word2, i + 1, j + 1);
        }

        char word = word1[i];

        // replace
        word1[i] = word2[j];
        int replace = 1 + helperWrong(word1, word2, i + 1, j + 1);
        word1[i] = word; // backtrack

        // delete
        word1.erase(word1.begin() + i);
        int deleted = 1 + helperWrong(word1, word2, i, j);
        word1.insert(word1.begin() + i, word); // backtrack

        // insert
        word1.insert(word1.begin() + i, word2[j]);
        int insert_op = 1 + helperWrong(word1, word2, i + 1, j + 1);
        word1.erase(word1.begin() + i); // backtrack

        return min({replace, deleted, insert_op});
    }
    */

    // ----------------------------------------------------
    // APPROACH 2: Top-Down Memoization (Staff Approved)
    // Passes strings by CONST REFERENCE. Uses indices to track state.
    // Time: O(M*N), Space: O(M*N)
    // Result: Accepted
    // ----------------------------------------------------
    int helperMemo(const string& word1, const string& word2, int i, int j, vector<vector<int>>& memo) {
        if (i == word1.size()) return word2.size() - j;
        if (j == word2.size()) return word1.size() - i;

        if (memo[i][j] != -1) return memo[i][j];

        if (word1[i] == word2[j]) {
            return memo[i][j] = helperMemo(word1, word2, i + 1, j + 1, memo);
        }

        int replace_op = 1 + helperMemo(word1, word2, i + 1, j + 1, memo);
        int delete_op  = 1 + helperMemo(word1, word2, i + 1, j, memo);
        int insert_op  = 1 + helperMemo(word1, word2, i, j + 1, memo);

        return memo[i][j] = min({replace_op, delete_op, insert_op});
    }

    // ====================================================
    // MAIN FUNCTION: The LeetCode Entry Point
    // ====================================================
    int minDistance(string word1, string word2) {
        vector<vector<int>> memo(word1.size(), vector<int>(word2.size(), -1));
        return helperMemo(word1, word2, 0, 0, memo);
    }

    // ----------------------------------------------------
    // APPROACH 3: Bottom-Up Tabulation (Your logic!)
    // Time: O(M*N), Space: O(M*N)
    // ----------------------------------------------------
    int minDistanceTabulation(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        
        // Setup DP matrix of size (M+1) x (N+1)
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // "if one of the word characters finish first, we will just count the word for the another one"
        // Base Case 1: word1 finishes first, we insert the rest of word2
        for (int j = 0; j <= n; j++) {
            dp[m][j] = n - j;
        }
        // Base Case 2: word2 finishes first, we delete the rest of word1
        for (int i = 0; i <= m; i++) {
            dp[i][n] = m - i;
        }
        
        // Run loops backwards exactly mirroring the memoization logic
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                
                if (word1[i] == word2[j]) {
                    // Match: Move both pointers (Diagonal)
                    dp[i][j] = dp[i + 1][j + 1];
                } else {
                    // Mismatch: 1 + min(replace, delete, insert)
                    int replace_op = 1 + dp[i + 1][j + 1];
                    int delete_op  = 1 + dp[i + 1][j];
                    int insert_op  = 1 + dp[i][j + 1];
                    
                    dp[i][j] = min({replace_op, delete_op, insert_op});
                }
            }
        }
        
        // Target state is exactly the start of both words
        return dp[0][0];
    }
    // ----------------------------------------------------
    // APPROACH 4: Forward Tabulation (Your brilliant idea!)
    // Time: O(M*N), Space: O(M*N)
    // ----------------------------------------------------
    int minDistanceForwardTabulation(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        
        // Setup DP matrix of size (M+1) x (N+1)
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // Base Case: Match prefix of word1 with empty word2 (costs i deletes)
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }
        // Base Case: Match prefix of word2 with empty word1 (costs j inserts)
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }
        
        // Loop FORWARD!
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                
                if (word1[i - 1] == word2[j - 1]) {
                    // Match: Grab the cost from the prefix without these two chars
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // Mismatch: 1 + min(replace, delete, insert)
                    int replace_op = 1 + dp[i - 1][j - 1];
                    int delete_op  = 1 + dp[i - 1][j];
                    int insert_op  = 1 + dp[i][j - 1];
                    
                    dp[i][j] = min({replace_op, delete_op, insert_op});
                }
            }
        }
        
        // Target state is the end of both words!
        return dp[m][n];
    }
};

int main() {
    Solution sol;
    cout << "--- Edit Distance ---\n\n";
    
    string w1 = "horse", w2 = "ros";
    cout << "Input: word1 = \"" << w1 << "\", word2 = \"" << w2 << "\"\n";
    cout << "Output (Memoization): " << sol.minDistance(w1, w2) << "\n";
    cout << "Output (Backward Tab): " << sol.minDistanceTabulation(w1, w2) << "\n";
    cout << "Output (Forward Tab):  " << sol.minDistanceForwardTabulation(w1, w2) << "\n";
    cout << "Expected: 3\n\n";
    
    string w3 = "intention", w4 = "execution";
    cout << "Input: word1 = \"" << w3 << "\", word2 = \"" << w4 << "\"\n";
    cout << "Output (Memoization): " << sol.minDistance(w3, w4) << "\n";
    cout << "Output (Backward Tab): " << sol.minDistanceTabulation(w3, w4) << "\n";
    cout << "Output (Forward Tab):  " << sol.minDistanceForwardTabulation(w3, w4) << "\n";
    cout << "Expected: 5\n\n";

    return 0;
}
