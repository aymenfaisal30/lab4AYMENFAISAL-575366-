#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
};

ListNode* newNode(int v) {
    ListNode* n = new ListNode;
    n->val = v;
    n->next = NULL;
    return n;
}

// min heap of list nodes, compared by val
class MinHeap {
    ListNode* arr[100];
    int size;

public:
    MinHeap() { size = 0; }

    bool isEmpty() { return size == 0; }

    void insert(ListNode* n) {
        int i = size;
        arr[size] = n;
        size++;
        while (i > 0 && arr[(i - 1) / 2]->val > arr[i]->val) {
            ListNode* temp = arr[i];
            arr[i] = arr[(i - 1) / 2];
            arr[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }
    }

    ListNode* extractMin() {
        ListNode* minNode = arr[0];
        size--;
        arr[0] = arr[size];
        heapify(0);
        return minNode;
    }

    void heapify(int i) {
        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < size && arr[l]->val < arr[smallest]->val)
            smallest = l;
        if (r < size && arr[r]->val < arr[smallest]->val)
            smallest = r;

        if (smallest != i) {
            ListNode* temp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = temp;
            heapify(smallest);
        }
    }
};

ListNode* mergeLists(ListNode* lists[], int k) {
    MinHeap heap;

    // put the head of every list in the heap
    for (int i = 0; i < k; i++) {
        if (lists[i] != NULL)
            heap.insert(lists[i]);
    }

    ListNode* head = NULL;
    ListNode* tail = NULL;

    while (!heap.isEmpty()) {
        ListNode* smallest = heap.extractMin();

        if (head == NULL) {
            head = smallest;
            tail = smallest;
        } else {
            tail->next = smallest;
            tail = smallest;
        }

        // next node from the same list goes into the heap
        if (smallest->next != NULL)
            heap.insert(smallest->next);
    }
    return head;
}

void printList(ListNode* head) {
    while (head != NULL) {
        cout << head->val;
        if (head->next != NULL)
            cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    int k;
    cout << "Enter number of linked lists: ";
    cin >> k;

    ListNode* lists[100];

    for (int i = 0; i < k; i++) {
        int count;
        cout << "How many nodes in list " << i + 1 << "? ";
        cin >> count;

        lists[i] = NULL;
        ListNode* tail = NULL;

        cout << "Enter values in ascending order: ";
        for (int j = 0; j < count; j++) {
            int x;
            cin >> x;
            ListNode* n = newNode(x);
            if (lists[i] == NULL) {
                lists[i] = n;
                tail = n;
            } else {
                tail->next = n;
                tail = n;
            }
        }
    }

    ListNode* result = mergeLists(lists, k);

    cout << "\nMerged list:\n";
    printList(result);

    return 0;
}
