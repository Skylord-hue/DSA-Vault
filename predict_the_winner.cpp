#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        // dp[i][j] stores the max relative score diff for subarray nums[i...j]
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base case: single element remaining
        for (int i = 0; i < n; ++i) {
            dp[i][i] = nums[i];
        }

        // Interval DP traversal: i must go backwards to ensure subproblems are solved
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
            }
        }

        return dp[0][n - 1] >= 0;
    }
};
