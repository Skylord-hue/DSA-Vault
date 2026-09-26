#include <iostream>
#include <vector>
#include <string>

using namespace std;

// =====================================================
//                      SOLUTION
// =====================================================
class Solution {
    void dfs(int node, int target, vector<vector<int>>& graph, vector<int>& path, vector<vector<int>>& result) {
        path.push_back(node);
        
        if (node == target) {
            result.push_back(path);
        } else {
            for (int neigh : graph[node]) {
                dfs(neigh, target, graph, path, result);
            }
        }
        
        path.pop_back(); // backtrack
    }

public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> result;
        vector<int> path;
        int target = graph.size() - 1;
        
        dfs(0, target, graph, path, result);
        
        return result;
    }
};

// =====================================================
//                     TEST CASES
// =====================================================
struct TestCase {
    string name;
    vector<vector<int>> graph;
    int expected_paths;
};

vector<TestCase> tests() {
    return {
        {"Example 1", {{1,2},{3},{3},{}}, 2},
        {"Example 2", {{4,3,1},{3,2,4},{3},{4},{}}, 5}
    };
}

// =====================================================
//                       DRIVER
// =====================================================
int main() {
    vector<TestCase> ts = tests();
    Solution sol;
    int passed = 0;

    cout << "=== ALL PATHS FROM SOURCE TO TARGET (LC 797) ===\n";
    for (size_t i = 0; i < ts.size(); i++) {
        vector<vector<int>> got = sol.allPathsSourceTarget(ts[i].graph);
        bool ok = (got.size() == ts[i].expected_paths);
        passed += ok;

        cout << (ok ? "PASS" : "FAIL") << "  #" << i + 1 << " " << ts[i].name;
        if (!ok) {
            cout << "  (expected " << ts[i].expected_paths << " paths, got " << got.size() << ")";
        }
        cout << "\n";
    }
    cout << passed << "/" << ts.size() << " passed\n";
    return 0;
}
