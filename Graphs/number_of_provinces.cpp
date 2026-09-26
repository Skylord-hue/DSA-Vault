#include <iostream>
#include <vector>
#include <string>

using namespace std;

// =====================================================
//                      SOLUTION
// =====================================================
class Solution {
    void dfs(int node, vector<vector<int>>& isConnected, vector<bool>& visit) {
        visit[node] = true;
        for (int i = 0; i < isConnected.size(); i++) {
            if (isConnected[node][i] == 1 && !visit[i]) {
                dfs(i, isConnected, visit);
            }
        }
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visit(n, false);
        int provinces = 0;

        for (int i = 0; i < n; i++) {
            if (!visit[i]) {
                provinces++;
                dfs(i, isConnected, visit);
            }
        }
        return provinces;
    }
};

// =====================================================
//                     TEST CASES
// =====================================================
struct TestCase {
    string name;
    vector<vector<int>> isConnected;
    int expected;
};

vector<TestCase> tests() {
    return {
        {"Two Provinces", {{1,1,0},{1,1,0},{0,0,1}}, 2},
        {"Three Provinces", {{1,0,0},{0,1,0},{0,0,1}}, 3},
        {"Fully Connected", {{1,1,1},{1,1,1},{1,1,1}}, 1}
    };
}

// =====================================================
//                       DRIVER
// =====================================================
int main() {
    vector<TestCase> ts = tests();
    Solution sol;
    int passed = 0;

    cout << "=== NUMBER OF PROVINCES (LC 547) ===\n";
    for (size_t i = 0; i < ts.size(); i++) {
        int got = sol.findCircleNum(ts[i].isConnected);
        bool ok = (got == ts[i].expected);
        passed += ok;

        cout << (ok ? "PASS" : "FAIL") << "  #" << i + 1 << " " << ts[i].name;
        if (!ok) {
            cout << "  (expected " << ts[i].expected << ", got " << got << ")";
        }
        cout << "\n";
    }
    cout << passed << "/" << ts.size() << " passed\n";
    return 0;
}
