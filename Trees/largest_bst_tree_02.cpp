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

// 2nd Method : optimal approach
class INFO
{
public:
    int min;
    int max;
    int size;

    INFO(int a, int b, int c) {
        min = a;   // Fixed variable assignment direction
        max = b;
        size = c;
    }
}; // Added missing semicolon

INFO sizeOfBST(Node *root)
{
    // Base case: For a null node, return max possible min, and min possible max
    // so it doesn't violate the BST properties of leaf nodes.
    if (root == nullptr) {
        return INFO(INT_MAX, INT_MIN, 0);
    }

    INFO left = sizeOfBST(root->left);
    INFO right = sizeOfBST(root->right);

    // Check if the current tree rooted here is a valid BST
    if (root->data > left.max && root->data < right.min) {
        // It is a BST. 
        // Update the min/max for the parent. Use std::min/max in case left or right is null.
        int currentMin = min(root->data, left.min);
        int currentMax = max(root->data, right.max);
        
        return INFO(currentMin, currentMax, 1 + left.size + right.size);
    }

    // If it's NOT a valid BST, return values that will make the parent fail the BST check.
    // (INT_MIN for min, and INT_MAX for max guarantees failure for parent)
    // The size becomes the maximum valid BST size found so far.
    return INFO(INT_MIN, INT_MAX, max(left.size, right.size));
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

    INFO ans1 = sizeOfBST(root1);
    cout << "Test 1: " << ans1.size << endl;

    // Test Case 2
    Node *root2 = new Node(10);
    root2->left = new Node(5);
    root2->right = new Node(15);
    root2->left->left = new Node(1);
    root2->left->right = new Node(8);
    root2->right->right = new Node(7); // Invalidates the right subtree as a BST

    INFO ans2 = sizeOfBST(root2);
    cout << "Test 2: " << ans2.size << endl;

    // Test Case 3
    Node *root3 = new Node(5);
    root3->left = new Node(2);
    root3->right = new Node(4);

    INFO ans3 = sizeOfBST(root3);
    cout << "Test 3: " << ans3.size << endl;

    return 0;
}