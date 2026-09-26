/*
 * Problem: House Robber (LeetCode 198)
 *
 * Description:
 * You cannot rob adjacent houses. Maximize money.
 *
 * Intuition / Approach:
 * 1D DP. At each house, either rob it (money + max from i-2) or skip it (max from i-1).
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        int prev2 = 0;
        int prev1 = nums[0];

        for (int i = 1; i < n; i++) {
            int take = nums[i] + prev2;
            int notTake = prev1;
            
            int cur = max(take, notTake);
            prev2 = prev1;
            prev1 = cur;
        }

        return prev1;
    }
};

int main() {
    Solution sol;
    cout << "--- House Robber ---\n";
    vector<int> nums = {2, 7, 9, 3, 1};
    cout << "Output: " << sol.rob(nums) << " | Expected: 12\n";
    return 0;
}
