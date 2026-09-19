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

Node *buildtree(vector<int> &preorder, vector<int> &inorder, int &index, int left, int right)
{
    if (left >= right)
    {
        return nullptr;
    }

    int val = preorder[index];
    Node *root = new Node(val);
    index++;
    int pos = -1;

    for (int i = left; i < right; i++)
    {
        if (val == inorder[i])
        {
            pos = i;
            break;
        }
    }

    root->left = buildtree(preorder, inorder, index, left, pos);
    root->right = buildtree(preorder, inorder, index, pos + 1, right);

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

void inorder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void postorder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void levelTraversal(Node *root)
{
    queue<Node *> q;

    if (root == nullptr)
    {
        return;
    }

    q.push(root);

    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();

        if (curr == nullptr)
        {
            continue;
        }

        cout << curr->data << " ";
        q.push(curr->left);
        q.push(curr->right);
    }
}

int main()
{
    vector<int> preorderData = {1, 2, 3, 4, 5};
    vector<int> inorderData = {2, 1, 4, 3, 5};
    int index = 0;
    Node *root = buildtree(preorderData, inorderData, index, 0, inorderData.size());

    preorder(root);
    cout << '\n';

    inorder(root);
    cout << '\n';

    postorder(root);
    cout << '\n';

    levelTraversal(root);
    cout << '\n';

    return 0;
}