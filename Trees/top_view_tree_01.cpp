#include <iostream>
#include <vector>
#include <queue>
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
void left_view(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    cout << root->data << " ";
    Node *curr = root->left;
    while (curr != nullptr)
    {
        cout << curr->data << " ";
        curr = curr->left;
    }
}
void right_view(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    // cout << root->data << " ";
    Node *curr = root->right;
    while (curr != nullptr)
    {
        cout << curr->data << " ";
        curr = curr->right;
    }
}
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

int main()
{
    vector<int> preorderData = {1, 2, -1, -1, 3, 4, 6,7, 5, 3, 6};

    int index = 0;
    Node *root = buildtree(preorderData, index);

    left_view(root);
    cout<< "\n";
    right_view(root);
    return 0;
}