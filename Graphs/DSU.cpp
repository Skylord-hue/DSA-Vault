#include <iostream>
#include <vector>

using namespace std;

class Edge {
public:
    int u, v, w;

    Edge(int u, int v, int w) {
        this->u = u;
        this->v = v;
        this->w = w;
    }
};

class Graph {
    vector<Edge> edges;
    vector<int> parent;
    vector<int> rankValue;

public:
    Graph(int vertexCount)
        : parent(vertexCount), rankValue(vertexCount, 0) {
        for (int vertex = 0; vertex < vertexCount; vertex++) {
            parent[vertex] = vertex;
        }
    }

    int find(int vertex) {
        if (parent[vertex] == vertex) {
            return vertex;
        }

        parent[vertex] = find(parent[vertex]);
        return parent[vertex];
    }

    void unite(int first, int second) {
        int firstRoot = find(first);
        int secondRoot = find(second);

        if (firstRoot == secondRoot) {
            return;
        }

        if (rankValue[firstRoot] < rankValue[secondRoot]) {
            parent[firstRoot] = secondRoot;
        } else if (rankValue[firstRoot] > rankValue[secondRoot]) {
            parent[secondRoot] = firstRoot;
        } else {
            parent[secondRoot] = firstRoot;
            rankValue[firstRoot]++;
        }
    }
};

int main() {
    Graph graph(5);
    graph.unite(0, 1);

    return 0;
}

/*
   The same DSU logic can also be written with standalone functions:

   int find(vector<int>& parent, int vertex) {
       if (parent[vertex] == vertex) {
           return vertex;
       }

       parent[vertex] = find(parent, parent[vertex]);
       return parent[vertex];
   }

   void unite(vector<int>& parent, vector<int>& rankValue,
              int first, int second) {
       int firstRoot = find(parent, first);
       int secondRoot = find(parent, second);

       if (firstRoot == secondRoot) {
           return;
       }

       if (rankValue[firstRoot] < rankValue[secondRoot]) {
           parent[firstRoot] = secondRoot;
       } else if (rankValue[firstRoot] > rankValue[secondRoot]) {
           parent[secondRoot] = firstRoot;
       } else {
           parent[secondRoot] = firstRoot;
           rankValue[firstRoot]++;
       }
   }

   int main() {
       int vertexCount = 5;
       vector<int> parent(vertexCount);
       vector<int> rankValue(vertexCount, 0);

       for (int vertex = 0; vertex < vertexCount; vertex++) {
           parent[vertex] = vertex;
       }

       unite(parent, rankValue, 0, 1);
       return 0;
   }
*/