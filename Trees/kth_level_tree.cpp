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

void kth_level(Node *root,int k)
{
    if (root == nullptr)
    {
        return;
    }

    queue<Node *> q;
    q.push(root);
    int i = 1;
    while (!q.empty())
    {
        int levelSize = q.size(); // Number of nodes at the current level
        
        while (levelSize > 0)
        {
            Node *curr = q.front();
            q.pop();
            if(i == k){
                cout << curr->data << " ";
                
            }
            // Only push children if they exist
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);

            levelSize--;
        }
        i++;
        cout << endl; // Move to the next line after finishing the current level
    }
}

// 2nd method 

void kth_level_02(Node* root,int k){
    if(root == nullptr){
        return;
    }
    if(k==1){
        cout<< root->data<< " ";
    }

    kth_level_02(root->left,k-1);
    kth_level_02(root->right,k-1);
}

int main()
{
    vector<int> preorderData = {1, 2, -1, -1, 3, 4, 5, 6, 7, -1, -1, -1, 8, -1, -1, 9, -1, -1, 10, -1, -1};

    int index = 0;
    Node *root = buildtree(preorderData, index);

    preorder(root);
    cout << "\n";
    int k = 3;
    // int index = 0;
    kth_level(root,k);

    cout<< " \n";

    kth_level_02(root,2);

    return 0;
}