#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int helper(vector<int>& piles, int index, int m, vector<int>& suffixSum, vector<vector<int>>& memo) {
        int n = piles.size();
        
        // Base Case: If you can take all remaining stones, take them all.
        if (index + 2 * m >= n) return suffixSum[index];
        
        // Memoization Check
        if (memo[index][m] != -1) return memo[index][m];

        int maxVal = 0;
        
        // Try taking X piles (from 1 to 2*m)
        for (int x = 1; x <= 2 * m && index + x <= n; x++) {
            // Minimax Invariant: (Total Stones from here) - (Opponent's optimal stones from next state)
            maxVal = max(maxVal, suffixSum[index] - helper(piles, index + x, max(m, x), suffixSum, memo));
        }

        // Cache and Return
        return memo[index][m] = maxVal;
    }

    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        if (n == 0) return 0;
        
        // Precompute Suffix Sums
        vector<int> suffixSum(n);
        suffixSum[n - 1] = piles[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        // State Space: index (0 to N-1), M (1 to N)
        vector<vector<int>> memo(n, vector<int>(n + 1, -1));

        return helper(piles, 0, 1, suffixSum, memo);
    }
};
