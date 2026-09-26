#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cmath>

using namespace std;

// =====================================================
//                      SOLUTION
// =====================================================
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        // Min-heap to pick edge with minimum weight: {weight, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<bool> inMST(n, false);
        
        pq.push({0, 0});
        int totalCost = 0;
        int edgesUsed = 0;

        while (edgesUsed < n) {
            auto top = pq.top();
            pq.pop();
            
            int weight = top.first;
            int currNode = top.second;
            
            if (inMST[currNode]) continue;
            
            inMST[currNode] = true;
            totalCost += weight;
            edgesUsed++;
            
            for (int nextNode = 0; nextNode < n; nextNode++) {
                if (!inMST[nextNode]) {
                    int dist = abs(points[currNode][0] - points[nextNode][0]) + 
                               abs(points[currNode][1] - points[nextNode][1]);
                    pq.push({dist, nextNode});
                }
            }
        }
        
        return totalCost;
    }
};

// =====================================================
//                     TEST CASES
// =====================================================
struct TestCase {
    string name;
    vector<vector<int>> points;
    int expected;
};

vector<TestCase> tests() {
    return {
        {"Example 1", {{0,0},{2,2},{3,10},{5,2},{7,0}}, 20},
        {"Example 2", {{3,12},{-2,5},{-4,1}}, 18}
    };
}

// =====================================================
//                       DRIVER
// =====================================================
int main() {
    vector<TestCase> ts = tests();
    Solution sol;
    int passed = 0;

    cout << "=== MIN COST TO CONNECT ALL POINTS (LC 1584) ===\n";
    for (size_t i = 0; i < ts.size(); i++) {
        int got = sol.minCostConnectPoints(ts[i].points);
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
