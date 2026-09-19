#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>

using namespace std;

class CustomTopologicalSort {
    int V;
    vector<list<int>> adj;

    // Helper to check if an element is currently in the stack
    bool isPresent(stack<int> s, int target) {
        while (!s.empty()) {
            if (s.top() == target) return true;
            s.pop();
        }
        return false;
    }

    // Helper to check if val is sitting above neighbor (closer to stack top)
    bool isValAboveNeighbor(stack<int> s, int val, int N) {
        while (!s.empty()) {
            int topEl = s.top();
            s.pop();
            if (topEl == val) return true;  // val is closer to top (above N) - Violation!
            if (topEl == N) return false;   // N is closer to top (above val) - Correct!
        }
        return false;
    }

    // Your custom "Apponder" function using your exact 2x2 nested cases!
    void apponder(stack<int>& s, int val) {
        // Base Case: If val has no neighbors, just push val if not present
        if (adj[val].empty()) {
            if (!isPresent(s, val)) {
                s.push(val);
            }
            return;
        }

        for (int N : adj[val]) {
            bool valPresent = isPresent(s, val);
            bool neighborPresent = isPresent(s, N);

            // ==================== OUTER BRANCH 1: val is NOT present ====================
            if (!valPresent) {
                
                // INNER CASE 1.1: neighbor is NOT present
                if (!neighborPresent) {
                    s.push(val); // Append val
                    s.push(N);   // Append neighbor on top
                } 
                // INNER CASE 1.2: neighbor IS present
                else {
                    stack<int> s2;
                    // Peel stack to remove neighbor (N)
                    while (!s.empty() && s.top() != N) {
                        s2.push(s.top());
                        s.pop();
                    }
                    if (!s.empty()) s.pop(); // Pop N

                    // Insert val below N, then push N on top
                    s.push(val);
                    s.push(N);

                    // Restore the stack
                    while (!s2.empty()) {
                        s.push(s2.top());
                        s2.pop();
                    }
                }
            } 
            // ==================== OUTER BRANCH 2: val IS present ====================
            else {
                
                // INNER CASE 2.1: neighbor is NOT present
                if (!neighborPresent) {
                    s.push(N); // Naturally sits above val (since val is already in stack)
                } 
                // INNER CASE 2.2: neighbor IS present
                else {
                    // Both are present. We must ensure val is below N.
                    if (isValAboveNeighbor(s, val, N)) {
                        stack<int> s2;
                        
                        // Extract both val and N from the stack
                        while (!s.empty()) {
                            int topEl = s.top();
                            s.pop();
                            if (topEl == val || topEl == N) {
                                continue; // Temporarily skip them
                            }
                            s2.push(topEl);
                        }
                        
                        // Push val first, then N (val is now safely below N)
                        s.push(val);
                        s.push(N);
                        
                        // Restore remaining stack elements
                        while (!s2.empty()) {
                            s.push(s2.top());
                            s2.pop();
                        }
                    }
                }
            }
        }
    }

public:
    CustomTopologicalSort(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v); // u -> v
    }

    void sort() {
        stack<int> s;
        // Run your search across all vertices
        for (int i = V - 1; i >= 0; i--) {
            apponder(s, i);
        }

        // Print stack from bottom-to-top to see the sorting order
        vector<int> result;
        while (!s.empty()) {
            result.push_back(s.top());
            s.pop();
        }
        reverse(result.begin(), result.end()); // Bottom-to-top print

        cout << "Your Custom Topological Sort: ";
        for (int node : result) {
            cout << node << " ";
        }
        cout << endl;
    }
};

int main() {
    CustomTopologicalSort g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    g.sort(); 
    return 0;
}