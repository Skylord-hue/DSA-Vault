#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// ============================================================================
// Apna College: Fractional Knapsack (Greedy Approach)
// ============================================================================

// Helper struct for items
struct Item {
    int value;
    int weight;
};

// Comparator to sort items in descending order of value/weight ratio
bool compare(Item a, Item b) {
    double r1 = (double)a.value / (double)a.weight;
    double r2 = (double)b.value / (double)b.weight;
    return r1 > r2;
}

// ----------------------------------------------------------------------------
// FUNCTION TO IMPLEMENT (Erased as requested — write your derivation here!)
// ----------------------------------------------------------------------------
double fractionalKnapsack(vector<int>& val, vector<int>& wt, int W) {
    int n = val.size();

    // ========================================================================
    // [WRITE YOUR CODE HERE]
    // 1. Calculate ratio = val[i] / (double)wt[i]
    // 2. Sort items descending by ratio
    // 3. Greedily fill knapsack with whole items or fractional parts
    // ========================================================================

    return 0.0; // Replace with your logic
}

// ============================================================================
// Apna College Playlist Test Cases in main()
// ============================================================================
int main() {
    cout << "============================================================\n";
    cout << "     APNA COLLEGE: FRACTIONAL KNAPSACK TEST RUNNER          \n";
    cout << "============================================================\n\n";

    // ------------------------------------------------------------------------
    // Lecture Test Case 1 (Primary example from Shraddha Didi's video):
    // val[] = {60, 100, 120}
    // wt[]  = {10, 20, 30}
    // W     = 50
    //
    // Calculation:
    //   item 0: ratio = 60/10 = 6.0  -> Pick whole  (wt 10, val 60, rem W = 40)
    //   item 1: ratio = 100/20 = 5.0 -> Pick whole  (wt 20, val 100, rem W = 20)
    //   item 2: ratio = 120/30 = 4.0 -> Pick 20/30 (fraction = 2/3, val = 80)
    // Total Expected = 60 + 100 + 80 = 240
    // ------------------------------------------------------------------------
    {
        vector<int> val = {60, 100, 120};
        vector<int> wt = {10, 20, 30};
        int W = 50;
        double expected = 240.0;

        cout << "--- Test Case 1 (Apna College Video Example) ---\n";
        cout << "val = {60, 100, 120}\nwt  = {10, 20, 30}\nW   = 50\n";
        double ans = fractionalKnapsack(val, wt, W);
        cout << fixed << setprecision(2);
        cout << "Output:   " << ans << "\n";
        cout << "Expected: " << expected << "\n";
        cout << "Status:   " << (ans == expected ? "[PASS]" : "[FAIL]") << "\n\n";
    }

    // ------------------------------------------------------------------------
    // Lecture Test Case 2 (Uneven weights & fractions):
    // val[] = {100, 60, 120}
    // wt[]  = {20, 10, 30}
    // W     = 50
    // Expected = 240
    // ------------------------------------------------------------------------
    {
        vector<int> val = {100, 60, 120};
        vector<int> wt = {20, 10, 30};
        int W = 50;
        double expected = 240.0;

        cout << "--- Test Case 2 (Unordered Input) ---\n";
        cout << "val = {100, 60, 120}\nwt  = {20, 10, 30}\nW   = 50\n";
        double ans = fractionalKnapsack(val, wt, W);
        cout << "Output:   " << ans << "\n";
        cout << "Expected: " << expected << "\n";
        cout << "Status:   " << (ans == expected ? "[PASS]" : "[FAIL]") << "\n\n";
    }

    return 0;
}
