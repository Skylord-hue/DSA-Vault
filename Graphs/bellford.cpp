#include <iostream>
#include <climits>
#include <vector>

using namespace std;

struct Edge {
	int from;
	int to;
	int weight;
};

class Graph {
private:
	int vertices;
	vector<Edge> edges;

public:
	explicit Graph(int vertexCount) : vertices(vertexCount) {}

	void addEdge(int from, int to, int weight) {
		edges.push_back({from, to, weight});
	}

	bool bellmanFord(int source, vector<int>& distances) const {
		distances.assign(vertices, INT_MAX);
		distances[source] = 0;

		// Relax every edge at most V - 1 times.
		for (int pass = 1; pass < vertices; ++pass) {
			bool changed = false;

			for (const Edge& edge : edges) {
				if (distances[edge.from] == INT_MAX) {
					continue;
				}

				int newDistance = distances[edge.from] + edge.weight;
				if (newDistance < distances[edge.to]) {
					distances[edge.to] = newDistance;
					changed = true;
				}
			}

			if (!changed) {
				break;
			}
		}

		// A further improvement means a reachable negative-weight cycle.
		for (const Edge& edge : edges) {
			if (distances[edge.from] != INT_MAX &&
				distances[edge.from] + edge.weight < distances[edge.to]) {
				return false;
			}
		}

		return true;
	}
};

void printDistances(const vector<int>& distances) {
	for (int distance : distances) {
		if (distance == INT_MAX) {
			cout << "INF ";
		} else {
			cout << distance << ' ';
		}
	}
	cout << '\n';
}

int main() {
	Graph graph(5);
	graph.addEdge(0, 1, 6);
	graph.addEdge(0, 2, 7);
	graph.addEdge(1, 2, 8);
	graph.addEdge(1, 3, 5);
	graph.addEdge(1, 4, -4);
	graph.addEdge(2, 3, -3);
	graph.addEdge(2, 4, 9);
	graph.addEdge(3, 1, -2);
	graph.addEdge(4, 0, 2);
	graph.addEdge(4, 3, 7);

	vector<int> distances;
	if (graph.bellmanFord(0, distances)) {
		cout << "Shortest distances: ";
		printDistances(distances);
	} else {
		cout << "Negative-weight cycle detected\n";
	}

	Graph cyclicGraph(3);
	cyclicGraph.addEdge(0, 1, 1);
	cyclicGraph.addEdge(1, 2, -2);
	cyclicGraph.addEdge(2, 1, -2);

	if (!cyclicGraph.bellmanFord(0, distances)) {
		cout << "Negative-weight cycle detected\n";
	}

	return 0;
}
