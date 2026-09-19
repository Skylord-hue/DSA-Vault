/*
Question:
Given the root of a binary tree, find the size of the largest subtree that is also a Binary Search Tree (BST).

Test Case 1:
Input Tree:
        10
       /  \
      5    15
     / \   / \
    1   8 12 20
Expected Output: 7

Test Case 2:
Input Tree:
        10
       /  \
      5    15
     / \     \
    1   8     7
Expected Output: 3

Test Case 3:
Input Tree:
        5
       / \
      2   4
Expected Output: 1
*/

#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;


class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// 1st Method -> Brute force approach
bool isBST(Node *root, int lowerBound, int upperBound)
{
    if (root == nullptr)
        return true;

    if (root->data <= lowerBound || root->data >= upperBound)
        return false;

    return isBST(root->left, lowerBound, root->data) &&
           isBST(root->right, root->data, upperBound);
}

int countNodes(Node *root)
{
    if (root == nullptr)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

void largestBSTSize(Node *root, int &ans)
{
    if (root == nullptr)
        return;

    if (isBST(root, INT_MIN, INT_MAX))
        ans = max(ans, countNodes(root));

    largestBSTSize(root->left, ans);
    largestBSTSize(root->right, ans);
}

int sizeOfBST(Node *root)
{
    int ans = 0;
    largestBSTSize(root, ans);
    return ans;
}

int main()
{
    // Test Case 1
    Node *root1 = new Node(10);
    root1->left = new Node(5);
    root1->right = new Node(15);
    root1->left->left = new Node(1);
    root1->left->right = new Node(8);
    root1->right->left = new Node(12);
    root1->right->right = new Node(20);

    cout << "Test 1: " << sizeOfBST(root1) << endl;

    // Test Case 2
    Node *root2 = new Node(10);
    root2->left = new Node(5);
    root2->right = new Node(15);
    root2->left->left = new Node(1);
    root2->left->right = new Node(8);
    root2->right->right = new Node(7);

    cout << "Test 2: " << sizeOfBST(root2) << endl;

    // Test Case 3
    Node *root3 = new Node(5);
    root3->left = new Node(2);
    root3->right = new Node(4);

    cout << "Test 3: " << sizeOfBST(root3) << endl;

    return 0;
}
