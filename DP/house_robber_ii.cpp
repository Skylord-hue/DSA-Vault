/**
 * Problem: House Robber Ii
 * Topic: DP
 * Author: Narendra (125102018)
 * Created: 2026-09-19 11:11
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Fast I/O
void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

class Solution {
public:
  // TODO: Implement solution
  int rob(vector<int> &nums) {
    int n = nums.size();
    if (n == 0)
      return 0;
    if (n == 1)
      return nums[0];

    // Case 1: Rob houses from index 0 to n-2 (excluding the last house)
    int max1 = robRange(nums, 0, n - 2);

    // Case 2: Rob houses from index 1 to n-1 (excluding the first house)
    int max2 = robRange(nums, 1, n - 1);

    return max(max1, max2);
  }

private:
  // Helper function to rob houses in a given range [start, end]
  int robRange(const vector<int> &nums, int start, int end) {
    int prev2 = 0; // Max money ending at i-2
    int prev1 = 0; // Max money ending at i-1

    for (int i = start; i <= end; i++) {
      // At current house i, we have two choices:
      // 1. Rob current house: nums[i] + prev2 (can't rob i-1)
      // 2. Don't rob current house: prev1
      int current = max(nums[i] + prev2, prev1);

      // Update for next iteration
      prev2 = prev1;
      prev1 = current;
    }

    return prev1;
  }
};

int main() {
  fast_io();
  Solution solver;
  vector<int> nums = {2, 3, 2};
  cout << solver.rob(nums) << endl;
  return 0;
}
