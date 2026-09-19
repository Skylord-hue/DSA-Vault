#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

Node* buildtree(vector<int>& preorder, int& index) {
    if (index >= static_cast<int>(preorder.size())) {
        return nullptr;
    }

    if (preorder[index] == -1) {
        ++index;
        return nullptr;
    }

    Node* root = new Node(preorder[index++]);
    root->left = buildtree(preorder, index);
    root->right = buildtree(preorder, index);
    return root;
}

void preorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
void inorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
void postorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void levelTransversal(Node* root) {
    queue<Node*> q;

    if (root == nullptr) {
        return;
    }

    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if (curr == nullptr) {
            // cout << "NULL ";
            continue;
        }

        cout << curr->data << " ";
        q.push(curr->left);
        q.push(curr->right);
    }
}

int main() {
    vector<int> preorderData = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};

    int index = 0;
    Node* root = buildtree(preorderData, index);


    
    preorder(root);
    cout << '\n';

    inorder(root);
    cout << '\n';
    
    postorder(root);
    cout << '\n';

    levelTransversal(root);
    cout << '\n';

    return 0;
}