#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// =====================================================
//                      SOLUTION
// =====================================================
class Solution {
    bool bfsCheck(int start, vector<vector<int>>& graph, vector<int>& color) {
        queue<int> q;
        q.push(start);
        color[start] = 0; // color 0

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neigh : graph[node]) {
                // If uncolored, color with opposite color and push
                if (color[neigh] == -1) {
                    color[neigh] = !color[node];
                    q.push(neigh);
                } 
                // If same color as parent, it's not bipartite
                else if (color[neigh] == color[node]) {
                    return false;
                }
            }
        }
        return true;
    }

public:
    bool isBipartite(vector<vector<int>>& graph) {
        int V = graph.size();
        vector<int> color(V, -1);

        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                if (!bfsCheck(i, graph, color)) {
                    return false;
                }
            }
        }
        return true;
    }
};

// =====================================================
//                     TEST CASES
// =====================================================
struct TestCase {
    string name;
    vector<vector<int>> graph;
    bool expected;
};

vector<TestCase> tests() {
    return {
        {"Example 1 (Not Bipartite)", {{1,2,3},{0,2},{0,1,3},{0,2}}, false},
        {"Example 2 (Bipartite)", {{1,3},{0,2},{1,3},{0,2}}, true},
        {"Disconnected Bipartite", {{1},{0},{3},{2}}, true}
    };
}

// =====================================================
//                       DRIVER
// =====================================================
int main() {
    vector<TestCase> ts = tests();
    Solution sol;
    int passed = 0;

    cout << "=== IS GRAPH BIPARTITE (LC 785) ===\n";
    for (size_t i = 0; i < ts.size(); i++) {
        bool got = sol.isBipartite(ts[i].graph);
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
