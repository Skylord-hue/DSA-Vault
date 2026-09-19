#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

class Graph
{
public:
    int V;
    list<int> *l;

    Graph(int vertices) : V(vertices), l(new list<int>[vertices])
    {
    }

    void addEdge(int u, int v)
    {
        l[u].push_back(v);
        l[v].push_back(u);
    }

    void bfs(int start)
    {
        vector<bool> visit(V, false);
        queue<int> q;

        q.push(start);
        visit[start] = true;

        while (!q.empty())
        {
            int val = q.front();
            q.pop();

            cout << val << " ";

            for (int neighbour : l[val])
            {
                if (!visit[neighbour])
                {
                    visit[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }
    }

    void dfsHelper(int start, vector<bool> &visit)
    {
        visit[start] = true;
        cout << start << " ";

        for (int neighbour : l[start])  
        {
            if (!visit[neighbour])
            {
                dfsHelper(neighbour, visit);
            }
        }
    }

    void dfs(int start)
    {
        vector<bool> visit(V, false);
        dfsHelper(start, visit);
    }
};

int main()
{
    Graph G(5);
    G.addEdge(0, 1);
    G.addEdge(0, 2);
    G.addEdge(0, 3);
    G.addEdge(1, 4);

    cout << "BFS traversal : ";
    G.bfs(0);
    cout << endl;
    cout << "DFS transversal : ";
    G.dfs(0);
    cout << endl;
    return 0;
}