#include <iostream>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
};

Node* makeNode(char c, int f) {
    Node* n = new Node;
    n->ch = c;
    n->freq = f;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// min heap that stores Node pointers
class MinHeap {
    Node* arr[100];
    int size;

public:
    MinHeap() { size = 0; }

    int getSize() { return size; }

    void insert(Node* n) {
        int i = size;
        arr[size] = n;
        size++;
        // move up while parent is bigger
        while (i > 0 && arr[(i - 1) / 2]->freq > arr[i]->freq) {
            Node* temp = arr[i];
            arr[i] = arr[(i - 1) / 2];
            arr[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }
    }

    Node* extractMin() {
        Node* minNode = arr[0];
        size--;
        arr[0] = arr[size];
        heapify(0);
        return minNode;
    }

    void heapify(int i) {
        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < size && arr[l]->freq < arr[smallest]->freq)
            smallest = l;
        if (r < size && arr[r]->freq < arr[smallest]->freq)
            smallest = r;

        if (smallest != i) {
            Node* temp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = temp;
            heapify(smallest);
        }
    }
};

Node* buildHuffman(char s[], int f[], int n) {
    MinHeap heap;
    for (int i = 0; i < n; i++)
        heap.insert(makeNode(s[i], f[i]));

    while (heap.getSize() > 1) {
        Node* a = heap.extractMin();
        Node* b = heap.extractMin();
        Node* parent = makeNode('$', a->freq + b->freq);
        parent->left = a;
        parent->right = b;
        heap.insert(parent);
    }
    return heap.extractMin();
}

// preorder: node, left, right. code is printed when we reach a leaf
void printCodes(Node* root, char code[], int depth) {
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL) {
        code[depth] = '\0';
        cout << root->ch << ": " << code << endl;
        return;
    }

    code[depth] = '0';
    printCodes(root->left, code, depth + 1);

    code[depth] = '1';
    printCodes(root->right, code, depth + 1);
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    char s[100];
    int f[100];

    for (int i = 0; i < n; i++) {
        cout << "Character " << i + 1 << ": ";
        cin >> s[i];
        cout << "Frequency of " << s[i] << ": ";
        cin >> f[i];
    }

    Node* root = buildHuffman(s, f, n);

    char code[100];
    cout << "\nHuffman codes (preorder):\n";
    if (n == 1)
        cout << s[0] << ": 0" << endl;   // only one char, give it code 0
    else
        printCodes(root, code, 0);

    return 0;
}
