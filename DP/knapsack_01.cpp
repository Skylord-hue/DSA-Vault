#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ============================================================================
// Apna College: 0/1 Knapsack (Dynamic Programming)
// Functions erased as requested — implement your derivations here!
// ============================================================================

// 1. Recursive Approach (0/1 Choice Tree)
int knapsack(vector<int>& val, vector<int>& wt, int W, int n) {
    // ========================================================================
    // [WRITE YOUR RECURSION HERE]
    // Base Case: n == 0 or W == 0 -> return 0
    // If wt[n-1] <= W: max(val[n-1] + knapsack(W-wt[n-1]), knapsack(W))
    // Else: knapsack(W)
    // ========================================================================

    return 0; // Replace with your logic
}

// 2. Memoization (Top-Down DP with dp[n+1][W+1] initialized to -1)
int knapsackMemo(vector<int>& val, vector<int>& wt, int W, int n, vector<vector<int>>& dp) {
    // ========================================================================
    // [WRITE YOUR MEMOIZATION HERE]
    // ========================================================================

    return 0; // Replace with your logic
}

// 3. Tabulation (Bottom-Up 2D DP table)
int knapsackTab(vector<int>& val, vector<int>& wt, int W, int n) {
    // ========================================================================
    // [WRITE YOUR TABULATION HERE]
    // ========================================================================

    return 0; // Replace with your logic
}

// ============================================================================
// Apna College Playlist Test Cases in main()
// ============================================================================
int main() {
    cout << "============================================================\n";
    cout << "         APNA COLLEGE: 0/1 KNAPSACK TEST RUNNER             \n";
    cout << "============================================================\n\n";

    // ------------------------------------------------------------------------
    // Lecture Test Case 1 (Primary example from Apna College DP 2 video):
    // val[] = {15, 14, 10, 45, 30}
    // wt[]  = {2, 5, 1, 3, 4}
    // W     = 7
    //
    // Optimal: Pick item 3 (wt 3, val 45) + item 4 (wt 4, val 30)
    // Total wt = 7 <= 7, Total val = 75
    // Expected Output = 75
    // ------------------------------------------------------------------------
    {
        vector<int> val = {15, 14, 10, 45, 30};
        vector<int> wt  = {2, 5, 1, 3, 4};
        int W = 7;
        int n = val.size();
        int expected = 75;

        cout << "--- Test Case 1 (Apna College Video Example 1) ---\n";
        cout << "val = {15, 14, 10, 45, 30}\n";
        cout << "wt  = {2, 5, 1, 3, 4}\n";
        cout << "W   = 7\n";

        // Testing Tabulation (or switch to knapsack/knapsackMemo)
        int ans = knapsackTab(val, wt, W, n);
        cout << "Tabulation Output: " << ans << " | Expected: " << expected << "\n";
        cout << "Status: " << (ans == expected ? "[PASS]" : "[FAIL]") << "\n\n";
    }

    // ------------------------------------------------------------------------
    // Lecture Test Case 2 (Standard Example from Video):
    // val[] = {60, 100, 120}
    // wt[]  = {10, 20, 30}
    // W     = 50
    //
    // Optimal: Pick item 1 (wt 20, val 100) + item 2 (wt 30, val 120) = 220
    // Expected Output = 220
    // ------------------------------------------------------------------------
    {
        vector<int> val = {60, 100, 120};
        vector<int> wt  = {10, 20, 30};
        int W = 50;
        int n = val.size();
        int expected = 220;

        cout << "--- Test Case 2 (Apna College Video Example 2) ---\n";
        cout << "val = {60, 100, 120}\n";
        cout << "wt  = {10, 20, 30}\n";
        cout << "W   = 50\n";

        int ans = knapsackTab(val, wt, W, n);
        cout << "Tabulation Output: " << ans << " | Expected: " << expected << "\n";
        cout << "Status: " << (ans == expected ? "[PASS]" : "[FAIL]") << "\n\n";
    }

    return 0;
}
