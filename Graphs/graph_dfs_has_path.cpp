#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// =====================================================
//                      SOLUTION
// =====================================================
class Solution {
    bool dfs(int node, int destination, vector<vector<int>>& adj, vector<bool>& visit) {
        if (node == destination) return true;
        
        visit[node] = true;
        
        for (int neigh : adj[node]) {
            if (!visit[neigh]) {
                if (dfs(neigh, destination, adj, visit)) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        vector<bool> visit(n, false);
        return dfs(source, destination, adj, visit);
    }
};

// =====================================================
//                     TEST CASES
// =====================================================
struct TestCase {
    string name;
    int n;
    vector<vector<int>> edges;
    int source;
    int destination;
    bool expected;
};

vector<TestCase> tests() {
    return {
        {"Example 1 (Path Exists)", 3, {{0,1},{1,2},{2,0}}, 0, 2, true},
        {"Example 2 (No Path)", 6, {{0,1},{0,2},{3,5},{5,4},{4,3}}, 0, 5, false},
        {"Single Node", 1, {}, 0, 0, true}
    };
}

// =====================================================
//                       DRIVER
// =====================================================
int main() {
    vector<TestCase> ts = tests();
    Solution sol;
    int passed = 0;

    cout << "=== FIND IF PATH EXISTS IN GRAPH (LC 1971 / HAS PATH) ===\n";
    for (size_t i = 0; i < ts.size(); i++) {
        bool got = sol.validPath(ts[i].n, ts[i].edges, ts[i].source, ts[i].destination);
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
