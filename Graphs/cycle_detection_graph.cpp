#include <iostream>
using namespace std;

// =====================================================
//                       GRAPH
// =====================================================
class Graph {
    int V;
    bool directed;
    vector<vector<int>> adj;

    // undirected: DFS + parent
    bool dfsUndirected(int src, int par, vector<bool>& visit) {
        visit[src] = true;
        for (int neigh : adj[src]) {
            if (!visit[neigh]) {
                if (dfsUndirected(neigh, src, visit)) return true;
            } else if (neigh != par) {
                return true;  // visited and not my parent -> cycle
            }
        }
        return false;
    }

    // directed: DFS + recursion path
    bool dfsDirected(int src, vector<bool>& visit, vector<bool>& onPath) {
        visit[src] = true;
        onPath[src] = true;
        for (int neigh : adj[src]) {
            if (!visit[neigh]) {
                if (dfsDirected(neigh, visit, onPath)) return true;
            } else if (onPath[neigh]) {
                return true;  // back edge to a node on current path -> cycle
            }
        }
        onPath[src] = false;  // backtrack
        return false;
    }

public:
    Graph(int V, bool directed) : V(V), directed(directed), adj(V) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }

    bool hasCycle() {
        vector<bool> visit(V, false);
        vector<bool> onPath(V, false);
        for (int i = 0; i < V; i++) {
            if (visit[i]) continue;
            bool found = directed ? dfsDirected(i, visit, onPath)
                                  : dfsUndirected(i, -1, visit);
            if (found) return true;
        }
        return false;
    }
};

// =====================================================
//                     TEST CASES
// =====================================================
struct TestCase {
    string name;
    int V;
    vector<pair<int, int>> edges;
    bool expected;
};

vector<TestCase> undirectedTests() {
    return {
        {"triangle",                        3, {{0,1},{1,2},{2,0}},                true},
        {"single edge (parent trap)",       2, {{0,1}},                            false},
        {"path",                            4, {{0,1},{1,2},{2,3}},                false},
        {"tree",                            5, {{0,1},{0,2},{1,3},{1,4}},          false},
        {"square cycle",                    4, {{0,1},{1,2},{2,3},{3,0}},          true},
        {"single node, no edges",           1, {},                                 false},
        {"disconnected, no cycle",          5, {{0,1},{2,3}},                      false},
        {"disconnected, cycle in 2nd comp", 6, {{0,1},{1,2},{3,4},{4,5},{5,3}},    true},
        {"cycle not through node 0",        5, {{0,1},{1,2},{2,3},{3,1},{3,4}},    true},
        {"self loop",                       1, {{0,0}},                            true},
    };
}

vector<TestCase> directedTests() {
    return {
        {"triangle",                        3, {{0,1},{1,2},{2,0}},                true},
        {"chain",                           4, {{0,1},{1,2},{2,3}},                false},
        {"diamond DAG",                     4, {{0,1},{0,2},{1,3},{2,3}},          false},
        {"cross edge, no cycle",            3, {{0,1},{0,2},{1,2}},                false},
        {"2-node cycle",                    2, {{0,1},{1,0}},                      true},
        {"self loop",                       1, {{0,0}},                            true},
        {"single node, no edges",           1, {},                                 false},
        {"disconnected DAG",                5, {{0,1},{2,3}},                      false},
        {"disconnected, cycle in 2nd comp", 6, {{0,1},{1,2},{3,4},{4,5},{5,3}},    true},
        {"cycle not through node 0",        4, {{0,1},{1,2},{2,3},{3,1}},          true},
        {"back edge from deep node",        5, {{0,1},{1,2},{2,3},{3,4},{4,2}},    true},
    };
}

// =====================================================
//                       DRIVER
// =====================================================
int runSuite(const string& title, const vector<TestCase>& tests, bool directed) {
    cout << "=== " << title << " ===\n";
    int passed = 0;
    for (size_t i = 0; i < tests.size(); i++) {
        const TestCase& t = tests[i];

        Graph g(t.V, directed);
        for (auto [u, v] : t.edges) g.addEdge(u, v);

        bool got = g.hasCycle();
        bool ok = (got == t.expected);
        passed += ok;

        cout << (ok ? "PASS" : "FAIL") << "  #" << i + 1 << " " << t.name;
        if (!ok) {
            cout << "  (expected " << (t.expected ? "cycle" : "no cycle")
                 << ", got " << (got ? "cycle" : "no cycle") << ")";
        }
        cout << "\n";
    }
    cout << passed << "/" << tests.size() << " passed\n\n";
    return passed;
}

int main() {
    runSuite("UNDIRECTED", undirectedTests(), false);
    runSuite("DIRECTED", directedTests(), true);  // comment one out to test one by one
    return 0;
}