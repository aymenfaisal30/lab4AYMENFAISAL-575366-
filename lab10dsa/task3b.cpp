#include <iostream>
using namespace std;

const int MAX = 100;

// BST node
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

// Store BST values in sorted order
void inorder(
    Node* root,
    int values[],
    int& index)
{
    if (root == NULL)
    {
        return;
    }

    inorder(root->left, values, index);

    values[index] = root->cost;
    index++;
    inorder(root->right, values, index);
}

// find subsetss
void findSubsets(
    int values[],
    int size,
    int index,
    int currentSum,
    int target,
    int subset[],
    int count)
{
    // target reached
    if (currentSum == target)
    {
        cout << "Subset found: ";
        for (int i = 0; i < count; i++)
        { cout << subset[i] << " "; }

        cout << endl;
        return;
    }

    // All values processed
    if (index == size)
    { return; }

    // Pruning
    if (currentSum + values[index] > target)
    { return; }

    // CHOICE 1: Include current value
    subset[count] = values[index];

    findSubsets(
        values,
        size,
        index + 1,
        currentSum + values[index],
        target,
        subset,
        count + 1
    );

    // CHOICE 2: Exclude current value
    findSubsets(
        values,
        size,
        index + 1,
        currentSum,
        target,
        subset,
        count
    );
}

int main()
{
    // Create BST
    Node* root = new Node(10);

    root->left = new Node(5);
    root->right = new Node(15);
    root->left->left = new Node(3);
    root->left->right = new Node(7);

    // Normal arrays instead of vectors
    int values[MAX];
    int size = 0;

    // Convert BST into sorted array
    inorder(root, values, size);

    int target = 22;
    int subset[MAX];

    cout << "Subsets with sum " << target << ":\n";

    findSubsets(
        values,
        size,
        0,
        0,
        target,
        subset,
        0
    );

    return 0;
}