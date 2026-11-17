#include <iostream>
#include <stack>
using namespace std;

// Binary Tree Node
struct Node
{
    int cost;
    Node* left;
    Node* right;

    Node(int value)
    {
        cost = value;
        left = NULL;
        right = NULL;
    }
};

// Print stack in correct order
void printPath(stack<int> path)
{
    if (path.empty())
    {
        return;
    }

    int value = path.top();
    path.pop();
    printPath(path);
    cout << value << " ";
}

// Find paths from a particular node
void findPathsFrom(
    Node* root,
    int target,
    int sum,
    stack<int>& path)
{
    if (root == NULL)
    {
        return;
    }

    // Add current node
    path.push(root->cost);

    sum += root->cost;

    // Check target
    if (sum == target)
    {
        cout << "Path found: ";

        printPath(path);

        cout << endl;
    }

    // Explore left child
    findPathsFrom(
        root->left,
        target,
        sum,
        path
    );

    // Explore right child
    findPathsFrom(
        root->right,
        target,
        sum,
        path
    );

    // Backtracking
    path.pop();
}

// Find paths starting from every node
void findAllPaths(Node* root, int target)
{
    if (root == NULL)
    {
        return;
    }

    stack<int> path;

    // Start from current node
    findPathsFrom(
        root,
        target,
        0,
        path
    );

    //  starting from left subtree
    findAllPaths(root->left, target);
    //  starting from right subtree
    findAllPaths(root->right, target);
}

int main()
{
    Node* root = new Node(10);

    root->left = new Node(5);
    root->right = new Node(12);
    root->left->left = new Node(3);
    root->left->right = new Node(7);
    root->right->right = new Node(8);

    int target = 22;
    cout << "Paths with sum " << target << ":\n";
    findAllPaths(root, target);

    return 0;
}