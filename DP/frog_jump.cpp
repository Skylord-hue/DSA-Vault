#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

// Problem: Frog Jump (Apna College DP 5 / AtCoder Frog 1 / GFG Geek Jump)
// A frog is at stair 0 and wants to reach stair (n - 1).
// From stair i, it can jump to (i + 1) or (i + 2).
// Cost of jumping from i to j is |height[i] - height[j]|.
// Find the minimum total energy consumed to reach (n - 1).

class Solution {
public:
    // Approach 1: Tabulation with O(1) Space Optimization
    // Time Complexity: O(N)
    // Space Complexity: O(1)
    int frogJump(int n, const vector<int>& heights) {
        if (n <= 1) return 0;

        int prev2 = 0; // dp[0]
        int prev1 = abs(heights[1] - heights[0]); // dp[1]

        for (int i = 2; i < n; ++i) {
            int jumpOne = prev1 + abs(heights[i] - heights[i - 1]);
            int jumpTwo = prev2 + abs(heights[i] - heights[i - 2]);
            int curr = min(jumpOne, jumpTwo);

            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

    // Follow-up: Frog Jump with K distance
    // Time Complexity: O(N * K)
    // Space Complexity: O(K) or O(N)
    int frogJumpK(int n, int k, const vector<int>& heights) {
        vector<int> dp(n, 0);
        dp[0] = 0;

        for (int i = 1; i < n; ++i) {
            int minEnergy = INT_MAX;
            for (int j = 1; j <= k; ++j) {
                if (i - j >= 0) {
                    int jump = dp[i - j] + abs(heights[i] - heights[i - j]);
                    minEnergy = min(minEnergy, jump);
                }
            }
            dp[i] = minEnergy;
        }

        return dp[n - 1];
    }
};

int main() {
    Solution solver;

    // Test Case 1
    vector<int> heights1 = {10, 20, 30, 10};
    // Expected: 20 (0 -> 1 -> 3 : |10-20| + |20-10| = 20, or 0 -> 2 -> 3: |10-30| + |30-10| = 40)
    cout << "Test Case 1 Output: " << solver.frogJump(heights1.size(), heights1) << " | Expected: 20" << endl;

    // Test Case 2
    vector<int> heights2 = {30, 10, 60, 10, 60, 50};
    // Expected: 40 (0 -> 2 -> 4 -> 5 : |30-60| + |60-60| + |60-50| = 30 + 0 + 10 = 40)
    cout << "Test Case 2 Output: " << solver.frogJump(heights2.size(), heights2) << " | Expected: 40" << endl;

    // Follow-up K-distance test
    cout << "K-Distance (k=2) Test 2: " << solver.frogJumpK(heights2.size(), 2, heights2) << " | Expected: 40" << endl;

    return 0;
}
