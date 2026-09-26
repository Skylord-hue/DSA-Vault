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
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (auto& f : flights) {
            adj[f[0]].push_back({f[1], f[2]});
        }

        // queue stores: {stops, {node, current_cost}}
        queue<pair<int, pair<int, int>>> q;
        q.push({0, {src, 0}});
        
        vector<int> dist(n, 1e9);
        dist[src] = 0;

        while (!q.empty()) {
            auto it = q.front();
            q.pop();
            int stops = it.first;
            int node = it.second.first;
            int cost = it.second.second;

            if (stops > k) continue;

            for (auto& iter : adj[node]) {
                int adjNode = iter.first;
                int edgeWeight = iter.second;

                if (cost + edgeWeight < dist[adjNode] && stops <= k) {
                    dist[adjNode] = cost + edgeWeight;
                    q.push({stops + 1, {adjNode, dist[adjNode]}});
                }
            }
        }

        return dist[dst] == 1e9 ? -1 : dist[dst];
    }
};

// =====================================================
//                     TEST CASES
// =====================================================
struct TestCase {
    string name;
    int n;
    vector<vector<int>> flights;
    int src;
    int dst;
    int k;
    int expected;
};

vector<TestCase> tests() {
    return {
        {"Example 1", 4, {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}}, 0, 3, 1, 700},
        {"Example 2", 3, {{0,1,100},{1,2,100},{0,2,500}}, 0, 2, 1, 200},
        {"Example 3", 3, {{0,1,100},{1,2,100},{0,2,500}}, 0, 2, 0, 500}
    };
}

// =====================================================
//                       DRIVER
// =====================================================
int main() {
    vector<TestCase> ts = tests();
    Solution sol;
    int passed = 0;

    cout << "=== CHEAPEST FLIGHTS WITHIN K STOPS (LC 787) ===\n";
    for (size_t i = 0; i < ts.size(); i++) {
        int got = sol.findCheapestPrice(ts[i].n, ts[i].flights, ts[i].src, ts[i].dst, ts[i].k);
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
