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
};

int main() {
    Solution sol;
    cout << "--- Edit Distance ---\n\n";
    
    string w1 = "horse", w2 = "ros";
    cout << "Input: word1 = \"" << w1 << "\", word2 = \"" << w2 << "\"\n";
    cout << "Output: " << sol.minDistance(w1, w2) << " \nExpected: 3\n\n";
    
    string w3 = "intention", w4 = "execution";
    cout << "Input: word1 = \"" << w3 << "\", word2 = \"" << w4 << "\"\n";
    cout << "Output: " << sol.minDistance(w3, w4) << " \nExpected: 5\n\n";

    return 0;
}
