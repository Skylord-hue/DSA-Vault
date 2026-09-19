#include <iostream>
#include <climits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int val) : V(val), adj(val) {}

    void addEdge(int u , int v ,int w){
        adj[u].push_back({v,w});
    }

    vector<int> dijkstra(int source) {
        vector<int> distances(V, INT_MAX);
        distances[source] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (currentDistance > distances[u]) {
                continue;
            }

            for (const auto& [neighbor, weight] : adj[u]) {
                if (distances[u] != INT_MAX &&
                    distances[u] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[u] + weight;
                    pq.push({distances[neighbor], neighbor});
                }
            }
        }

        return distances;
    }
};

int main() {
    Graph graph(5);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 1);
    graph.addEdge(2, 1, 2);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 3, 5);
    graph.addEdge(3, 4, 3);

    vector<int> distances = graph.dijkstra(0);
    for (int distance : distances) {
        cout << distance << ' ';
    }
    cout << '\n';

    return 0;
}