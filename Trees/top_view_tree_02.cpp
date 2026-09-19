#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

Node *buildtree(vector<int> &preorder, int &index)
{
    if (index >= static_cast<int>(preorder.size()))
    {
        return nullptr;
    }

    if (preorder[index] == -1)
    {
        ++index;
        return nullptr;
    }

    Node *root = new Node(preorder[index++]);
    root->left = buildtree(preorder, index);
    root->right = buildtree(preorder, index);
    return root;
}
void preorder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void top_view(Node *root)
{
    queue<pair<Node *, int>> q;
    map<int, int> mp;

    q.push({root, 0});
    while (!q.empty())
    {
        Node *curr = q.front().first;
        int HD = q.front().second;
        q.pop();

        if (curr == nullptr)
        {
            continue;
        }

        if (mp.find(HD) == mp.end())
        {
            mp[HD] = curr->data;
        }

        if (curr->left)
        {
            q.push({curr->left, HD - 1});
        }
        if (curr->right)
        {
            q.push({curr->right, HD + 1});
        }
    }

    for (auto &entry : mp)
    {
        cout << entry.second << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> preorderData = {1, 2, -1, -1, 3, 4, 5, 6, 7, -1, -1, -1, 8, -1, -1, 9, -1, -1, 10, -1, -1};

    int index = 0;
    Node *root = buildtree(preorderData, index);

    preorder(root);
    cout<< "\n";
    top_view(root);

    return 0;
}