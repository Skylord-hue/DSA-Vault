#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// =====================================================
//                      SOLUTION
// =====================================================
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);

        for (auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]);
            indegree[pre[0]]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        vector<int> order;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            order.push_back(node);

            for (int neigh : adj[node]) {
                indegree[neigh]--;
                if (indegree[neigh] == 0) {
                    q.push(neigh);
                }
            }
        }

        if (order.size() == numCourses) return order;
        return {};
    }
};

// =====================================================
//                     TEST CASES
// =====================================================
struct TestCase {
    string name;
    int numCourses;
    vector<vector<int>> prerequisites;
    bool expected_possible;
};

vector<TestCase> tests() {
    return {
        {"Simple Line", 2, {{1,0}}, true},
        {"Simple Cycle", 2, {{1,0}, {0,1}}, false},
        {"Valid DAG", 4, {{1,0}, {2,0}, {3,1}, {3,2}}, true}
    };
}

// =====================================================
//                       DRIVER
// =====================================================
int main() {
    vector<TestCase> ts = tests();
    Solution sol;
    int passed = 0;

    cout << "=== COURSE SCHEDULE II (LC 210) ===\n";
    for (size_t i = 0; i < ts.size(); i++) {
        vector<int> got = sol.findOrder(ts[i].numCourses, ts[i].prerequisites);
        bool possible = !got.empty() || (ts[i].numCourses == 0);
        bool ok = (possible == ts[i].expected_possible);
        passed += ok;

        cout << (ok ? "PASS" : "FAIL") << "  #" << i + 1 << " " << ts[i].name;
        if (!ok) {
            cout << "  (expected possible: " << ts[i].expected_possible << ", got possible: " << possible << ")";
        }
        cout << "\n";
    }
    cout << passed << "/" << ts.size() << " passed\n";
    return 0;
}
