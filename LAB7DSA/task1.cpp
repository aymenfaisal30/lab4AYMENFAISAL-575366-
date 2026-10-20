#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

// Each node stores a character and links to its children
struct Node {
    char data;
    Node* left;
    Node* right;
};

// This function creates the tree from the given string
Node* buildTree(string s, int& i) {
    if (i >= s.length() || s[i] == ',' || s[i] == ')')
        return nullptr;

    // Create a new node using the current character
    Node* root = new Node{s[i], nullptr, nullptr};
    i++;

    // Check if this node has child information
    if (i < s.length() && s[i] == '(') {
        i++; 

        // Build the left child first
        root->left = buildTree(s, i);

        if (i < s.length() && s[i] == ',')
            i++; 

        // Now build the right child
        root->right = buildTree(s, i);

        if (i < s.length() && s[i] == ')')
            i++; // Skip the closing brackettt
    }

    return root;
}

// Preorder visits the root, then the left and right children at lsst
void preorder(Node* root) {
    if (root == nullptr)
        return;

    cout << root->data;
    preorder(root->left);
    preorder(root->right);
}

// Inorder uses a stack to visit the left side first
void inorder(Node* root) {
    stack<Node*> st;
    Node* current = root;

    while (current != nullptr || !st.empty()) {
        // Keep moving left and save each node
        while (current != nullptr) {
            st.push(current);
            current = current->left;
        }

        current = st.top();
        st.pop();

        cout << current->data;

        // After visiting the node, move right
        current = current->right;
    }
}

// Postorder will use two stacks to print the root last
void postorder(Node* root) {
    if (root == nullptr)
        return;

    stack<Node*> s1, s2;
    s1.push(root);

    // Move nodes between the stacks
    while (!s1.empty()) {
        Node* current = s1.top();
        s1.pop();

        s2.push(current);

        if (current->left != nullptr)
            s1.push(current->left);

        if (current->right != nullptr)
            s1.push(current->right);
    }

    // Print nodes in postorder
    while (!s2.empty()) {
        cout << s2.top()->data;
        s2.pop();
    }
}

// This function checks if the string follows the tree format
bool parseValidTree(const string& s, int& i) {
    if (i >= s.length() ||
        !isalnum(static_cast<unsigned char>(s[i]))) 
        //It checks whether the current character is not an alphabet or a digit
        return false;

    i++; 

    // If there are no brackets, this node has no written children
    if (i >= s.length() || s[i] != '(')
        return true;
    i++; 

    // Check the left child if it exists
    if (i < s.length() && s[i] != ',') {
        if (!parseValidTree(s, i))
            return false;
    }

    // A comma separates the two child positions
    if (i >= s.length() || s[i] != ',')
        return false;

    i++;

    // Check the right child if it exists
    if (i < s.length() && s[i] != ')') {
        if (!parseValidTree(s, i))
            return false;
    }

    // Check for the closing bracket
    if (i >= s.length() || s[i] != ')')
        return false;

    i++;
    return true;
}

// Make sure the whole string is valid
bool validateTree(string s) {
    if (s.empty())
        return false;

    int i = 0;

    if (!parseValidTree(s, i))
        return false;

    return i == s.length();
}

// This function finds the height of the tree
int height(Node* root) {
    if (root == nullptr)
        return -1;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // Compare both sides and use the greater height
    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

// Print each node with its distance from the root
void printDepth(Node* root, int depth = 0) {
    if (root == nullptr)
        return;

    cout << root->data << " has depth " << depth << endl;

    // Each step down the tree increases the depth
    printDepth(root->left, depth + 1);
    printDepth(root->right, depth + 1);
}

// Each BST node stores an integer and its child links
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
};

// Insert a value into its correct position in the BST
BSTNode* insertBST(BSTNode* root, int value) {
    if (root == nullptr)
        return new BSTNode{value, nullptr, nullptr};

    // Smaller values go left and larger values go right
    if (value < root->data)
        root->left = insertBST(root->left, value);
    else if (value > root->data)
        root->right = insertBST(root->right, value);

    return root;
}

// Inorder traversal displays BST values in ascending order
void inorderBST(BSTNode* root) {
    if (root == nullptr)
        return;
    inorderBST(root->left);
    cout << root->data << " ";
    inorderBST(root->right);
}

int main() {
    // This string describes the binary tree
    string treeString = "a(b(d,e),c(,f(g,)))";
    // Check the format before building the tree
    if (!validateTree(treeString)) {
        cout << "Invalid tree format" << endl;
        return 0; }

    int i = 0;
    Node* root = buildTree(treeString, i);

    cout << "Preorder: ";
    preorder(root);
    cout << endl;

    cout << "Inorder: ";
    inorder(root);
    cout << endl;

    cout << "Postorder: ";
    postorder(root);
    cout << endl;

    cout << "Tree height: " << height(root) << endl;

    cout << "Node depths:" << endl;
    printDepth(root);

    // Insert some values to create a binary search tree
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    BSTNode* bstRoot = nullptr;

    for (int value : values)
        bstRoot = insertBST(bstRoot, value);

    cout << "BST inorder: ";
    inorderBST(bstRoot);
    cout << endl;

    return 0;
}
