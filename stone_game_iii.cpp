#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Returns the MAXIMUM RELATIVE SCORE DIFFERENCE (Current Player - Opponent)
    int helper(vector<int>& stoneValue, int index, vector<int>& memo) {
        int n = stoneValue.size();
        
        // Base case: no stones left, difference is 0
        if (index >= n) return 0;
        
        if (memo[index] != -1e9) return memo[index];

        int maxDiff = -1e9;
        int takenSoFar = 0;

        // Try taking X = 1, 2, or 3 stones
        for (int X = 1; X <= 3 && index + X <= n; X++) {
            takenSoFar += stoneValue[index + X - 1];
            
            // The Invariant: My Score - (Opponent's best Relative Difference)
            // By subtracting the opponent's best response, we get our net lead.
            int myNetDiff = takenSoFar - helper(stoneValue, index + X, memo);
            maxDiff = max(maxDiff, myNetDiff);
        }

        return memo[index] = maxDiff;
    }

    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> memo(n, -1e9);

        // aliceNetScore is (Alice's Score - Bob's Score)
        int aliceNetScore = helper(stoneValue, 0, memo);

        if (aliceNetScore > 0) return "Alice";
        if (aliceNetScore < 0) return "Bob";
        return "Tie";
    }
};
