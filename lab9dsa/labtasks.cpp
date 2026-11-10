#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;


//      TASK 1: BINARY SEARCH TREE 
class BST
{
private:

    struct Node
    {
        int data;
        Node* left;
        Node* right;

        Node(int value)
        {
            data = value;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    // Insert values at their correct positins
    Node* insert(Node* node, int value)
    {
        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);

        else if (value > node->data)
            node->right = insert(node->right, value);

        return node;
    }

    // Inorder traversal recursive function
    void inorder(Node* node)
    {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Recursive range query
    void recursiveRange(Node* node, int low, int high,
                        int& comparisons)
    {
        if (node == nullptr)
            return;
        comparisons++;

        if (node->data > low)
            recursiveRange(node->left, low, high, comparisons);
        if (node->data >= low && node->data <= high)
            cout << node->data << " ";

        comparisons++;

        if (node->data < high)
            recursiveRange(node->right, low, high, comparisons);
    }

public:

    BST()
    {
        root = nullptr;
    }

    void insert(int value)
    {
        root = insert(root, value);
    }

    void displayInorder()
    {
        inorder(root);
        cout << endl;
    }

    // find the nearest smaller and greater values of a key
    void findPredecessorSuccessor(int key)
    {
        Node* current = root;
        Node* predecessor = nullptr;
        Node* successor = nullptr;

        while (current != nullptr)
        {
            if (current->data == key)
            {
                if (current->left != nullptr)
                { Node* temp = current->left;
                    while (temp->right != nullptr)
                        temp = temp->right;
                    predecessor = temp;
                }

                if (current->right != nullptr)
                { Node* temp = current->right;
                    while (temp->left != nullptr)
                        temp = temp->left;

                    successor = temp;
                }

                break;
            }

            else if (key < current->data)
            {
                successor = current;
                current = current->left;
            }

            else
            {
                predecessor = current;
                current = current->right;
            }
        }

        if (current == nullptr)
        { cout << "Key not found." << endl;
            return; }

        if (predecessor != nullptr)
            cout << "Predecessor: " << predecessor->data << endl;
        else
            cout << "Predecessor: None" << endl;

        if (successor != nullptr)
            cout << "Successor: " << successor->data << endl;
        else
            cout << "Successor: None" << endl;
    }

    // Display values in the given range using recursion
    void recursiveRangeQuery(int low, int high)
    {
        int comparisons = 0;

        cout << "Recursive Range Query: ";
        recursiveRange(root, low, high, comparisons);
        cout << endl;
        cout << "Comparisons: " << comparisons << endl;
    }

    // Iterative version using an array as a stack
    void iterativeRangeQuery(int low, int high)
    {
        Node* stack[100];
        int top = -1;
        Node* current = root;
        int comparisons = 0;

        cout << "Iterative Range Query: ";

        while (current != nullptr || top != -1)
        {
            while (current != nullptr)
            {
                comparisons++;

                if (current->data > low)
                {
                    stack[++top] = current;
                    current = current->left;
                }
                else
                {
                    break;
                }
            }

            if (current == nullptr)
            {
                if (top == -1)
                    break;

                current = stack[top--];
            }

            comparisons++;

            if (current->data >= low && current->data <= high)
                cout << current->data << " ";

            if (current->data > high)
                break;

            current = current->right;
        }

        cout << endl;
        cout << "Comparisons: " << comparisons << endl;
    }
};


//  TASK 2: WORD FREQUENCY BST 

class WordBST
{
private:

    struct WordNode
    {
        string word;
        int frequency;

        WordNode* left;
        WordNode* right;

        WordNode(string w)
        {
            word = w;
            frequency = 1;

            left = nullptr;
            right = nullptr;
        }
    };

    WordNode* root;

    // Insert a word or increase its frequency if it already existss
    WordNode* insert(WordNode* node, string word)
    {
        if (node == nullptr)
            return new WordNode(word);
        if (word < node->word)
            node->left = insert(node->left, word);
        else if (word > node->word)
            node->right = insert(node->right, word);
        else
            node->frequency++;

        return node;
    }

    // Print words alphabetically using inorder traversal
    void displayAlphabetical(WordNode* node)
    {
        if (node == nullptr)
            return;

        displayAlphabetical(node->left);

        cout << node->word << " : "
             << node->frequency << endl;

        displayAlphabetical(node->right);
    }

    // Store all tree nodes in an array for frequency sorting
    void storeWords(WordNode* node, WordNode* words[],
                    int& count)
    {
        if (node == nullptr)
            return;

        storeWords(node->left, words, count);

        if (count < 100)
            words[count++] = node;

        storeWords(node->right, words, count);
    }

    // Find the highest frequency in the tree
    void findMaximum(WordNode* node, int& maximum)
    {
        if (node == nullptr)
            return;
        if (node->frequency > maximum)
            maximum = node->frequency;

        findMaximum(node->left, maximum);
        findMaximum(node->right, maximum);
    }

    // Display all words wth highest frequency
    void displayMaximum(WordNode* node, int maximum)
    {
        if (node == nullptr)
            return;

        displayMaximum(node->left, maximum);

        if (node->frequency == maximum)
        {
            cout << node->word << " : " << node->frequency << endl;
        }

        displayMaximum(node->right, maximum);
    }

public:

    WordBST()
    {
        root = nullptr;
    }

    void insertWord(string word)
    {
        root = insert(root, word);
    }

    void displayAlphabetical()
    {
        displayAlphabetical(root);
    }


    void displayByFrequency()
    {
        WordNode* words[100];

        int count = 0;

        storeWords(root, words, count);

        // Sort from highest frequency to lowest.
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - i - 1; j++)
            {
                if (words[j]->frequency < words[j + 1]->frequency)
                {
                    WordNode* temp = words[j];

                    words[j] = words[j + 1];

                    words[j + 1] = temp;
                }

                // If frequencies are equal then arrange alphabetically.
                else if (words[j]->frequency ==
                         words[j + 1]->frequency &&
                         words[j]->word > words[j + 1]->word)
                {
                    WordNode* temp = words[j];

                    words[j] = words[j + 1];

                    words[j + 1] = temp;
                }
            }
        }

        for (int i = 0; i < count; i++)
        {
            cout << words[i]->word << " : "
                 << words[i]->frequency << endl;
        }
    }

    void findMostFrequentWord()
    {
        int maximum = 0;

        findMaximum(root, maximum);

        cout << "Most Frequent Word(s):" << endl;

        if (maximum > 0)
            displayMaximum(root, maximum);
    }
};


// TASK 3: WEIGHTED M-ARY TREE 

class TravelRoute
{
public:

    // Cost of travelling between two star systems
    float travel_cost;

    TravelRoute(float cost = 0)
    {
        travel_cost = cost;
    }
};


class StarSystem
{
public:

    int system_id;
    string name;
    int num_planets;

    float x, y, z;

    bool is_habitable;

    struct Child
    {
        StarSystem* system;
        TravelRoute route;

        Child* next;

        Child(StarSystem* s, float cost)
        {
            system = s;
            route = TravelRoute(cost);
            next = nullptr;
        }
    };

    Child* firstChild;

    int childCount;

    StarSystem(int id, string n, int planets,
               float a, float b, float c, bool habitable)
    {
        system_id = id;
        name = n;
        num_planets = planets;

        x = a;
        y = b;
        z = c;

        is_habitable = habitable;

        firstChild = nullptr;
        childCount = 0;
    }
};


class Galaxy
{
private:

    int M;
    StarSystem* root;

    // Calculate the number of nodes in a subtree.
    int subtreeSize(StarSystem* node) const
    {
        if (node == nullptr)
            return 0;

        int size = 1;

        StarSystem::Child* current = node->firstChild;

        while (current != nullptr)
        {
            size += subtreeSize(current->system);
            current = current->next;
        }

        return size;
    }

    // Check whether the child subtrees have almost equal sizes.
    bool checkBalance(StarSystem* node) const
    {
        if (node == nullptr)
            return true;

        StarSystem::Child* current = node->firstChild;

        if (current != nullptr)
        {
            int minimum = subtreeSize(current->system);
            int maximum = minimum;

            current = current->next;

            while (current != nullptr)
            {
                int size = subtreeSize(current->system);

                if (size < minimum)
                    minimum = size;

                if (size > maximum)
                    maximum = size;

                current = current->next;
            }

            if (maximum - minimum > 1)
                return false;
        }

        // Check the remaining child subtrees 
        current = node->firstChild;

        while (current != nullptr)
        {
            if (!checkBalance(current->system))
                return false;

            current = current->next;
        }

        return true;
    }

    // Count the nodes that do not have any children
    int leaves(StarSystem* node) const
    {
        if (node == nullptr)
            return 0;

        if (node->firstChild == nullptr)
            return 1;
        int count = 0;

        StarSystem::Child* current = node->firstChild;

        while (current != nullptr)
        {
            count += leaves(current->system);
            current = current->next;
        }

        return count;
    }

public:
    // Constructor with only M
    Galaxy(int m)
    {
        M = m;
        root = nullptr;
    }

    // Constructor with M and an optional root
    Galaxy(int m, StarSystem* r)
    {
        M = m;
        root = r;
    }

    // Connect two systems and save the route cost
    void addRoute(StarSystem* parent,
                  StarSystem* child,
                  float cost)
    {
        if (parent == nullptr || child == nullptr)
            return;

        if (parent->childCount >= M)
        {
            cout << "Maximum children reached!" << endl;
            return;
        }

        StarSystem::Child* newChild =
            new StarSystem::Child(child, cost);

        if (parent->firstChild == nullptr)
        { parent->firstChild = newChild; }
        else
        {
            StarSystem::Child* current = parent->firstChild;
            while (current->next != nullptr)
                current = current->next;

            current->next = newChild;
        }
        parent->childCount++;
    }

    bool is_balanced(StarSystem* x) const
    { return checkBalance(x); }

    int count_leaves(StarSystem* x) const
    { return leaves(x); }

    StarSystem* getRoot() const
    { return root; }
};


//  MAIN FUNCTION 

int main()
{

    cout << "\n          TASK 1-->         \n";

    BST tree;

    // Numbers given in the lab manual.
    int values[] = {50, 30, 70, 20, 40,
                    60, 80, 35, 45, 65, 85};

    for (int i = 0; i < 11; i++)
    {
        tree.insert(values[i]);
    }

    cout << "Inorder Traversal: ";
    tree.displayInorder();

    cout << "\nFor Key = 40\n";
    tree.findPredecessorSuccessor(40);

    cout << "\nRange: 30 to 70\n";

    tree.recursiveRangeQuery(30, 70);

    tree.iterativeRangeQuery(30, 70);

    cout << "\n           TASK 2-->          \n";

    WordBST wordTree;

    // Paragraph given in the lab manual.
    string paragraph =
        "The quick brown fox jumps over the lazy dog. "
        "The fox is quick and smart.";

    string word;

    stringstream ss(paragraph);

    int totalWords = 0;

    // Read and clean each word before inserting it.
    while (ss >> word)
    {
        string cleanWord = "";

        for (char ch : word)
        {
            if (isalpha(static_cast<unsigned char>(ch)))
            {
                cleanWord += static_cast<char>(
                    tolower(static_cast<unsigned char>(ch))
                );
            }
        }

        if (!cleanWord.empty())
        {
            wordTree.insertWord(cleanWord);
            totalWords++;
        }
    }

    cout << "\nWords in Alphabetical Order:\n";

    wordTree.displayAlphabetical();
    cout << "\nWords by Frequency:\n";
    wordTree.displayByFrequency();
    cout << endl;
    wordTree.findMostFrequentWord();
    cout << "\nTotal Words: " << totalWords << endl;

    cout << "\n          TASK 3-->         \n";

    // Create star systems with their information.
    StarSystem* earth = new StarSystem(
        1, "Earth", 1, 0, 0, 0, true
    );
    StarSystem* mars = new StarSystem(
        2, "Mars", 2, 1, 2, 3, false
    );
    StarSystem* jupiter = new StarSystem(
        3, "Jupiter", 4, 4, 5, 6, false
    );
    StarSystem* saturn = new StarSystem(
        4, "Saturn", 3, 7, 8, 9, false
    );
    StarSystem* venus = new StarSystem(
        5, "Venus", 0, 2, 3, 4, false
    );

    // Earth is the starting point of the galaxy
    Galaxy galaxy(3, earth);

    // Add routes between the star systems
    galaxy.addRoute(earth, mars, 5.5);
    galaxy.addRoute(earth, jupiter, 8.2);
    galaxy.addRoute(earth, saturn, 10.5);

    galaxy.addRoute(mars, venus, 3.5);

    cout << "Is Galaxy Balanced? ";

    if (galaxy.is_balanced(galaxy.getRoot()))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    cout << "Number of Leaf Nodes: "
         << galaxy.count_leaves(galaxy.getRoot())
         << endl;

    return 0;
}
