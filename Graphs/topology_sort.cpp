// Topological sorting works on directed acyclic graphs (DAGs).

#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Graph
{
private:
    int vertices;
    vector<vector<int>> adjacencyList;

public:
    explicit Graph(int vertexCount)
        : vertices(vertexCount), adjacencyList(vertexCount) {}

    void addEdge(int from, int to)
    {
        adjacencyList[from].push_back(to);
    }

    void topologicalSort(int src, stack<int> &s, vector<bool> &visit)
    {
        visit[src] = true;

        for (int neigh : adjacencyList[src])
        {
            if (!visit[neigh])
            {
                visit[neigh] = true;
                topologicalSort(neigh, s, visit);
            }
        }
        s.push(src);
    }

    void ans()
    {
        stack<int> s;
        vector<bool> visit(vertices, false);
        for (int i = 0; i < vertices; i++)
        {
            if (!visit[i])
            {
                topologicalSort(i, s, visit);
            }
        }

        while (!s.empty())
        {
            cout << s.top() << " ";
            s.pop();
        }
    }
};

void printResult(const string &name, const vector<int> &order)
{
    cout << name << ": ";

    if (order.empty())
    {
        cout << "cycle detected";
    }
    else
    {
        for (int vertex : order)
        {
            cout << vertex << ' ';
        }
    }

    cout << '\n';
}

int main()
{
    Graph normalDag(6);
    normalDag.addEdge(5, 2);
    normalDag.addEdge(5, 0);
    normalDag.addEdge(4, 0);
    normalDag.addEdge(4, 1);
    normalDag.addEdge(2, 3);
    normalDag.addEdge(3, 1);
    
    normalDag.ans();
    return 0;
}
