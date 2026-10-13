#include <iostream>
using namespace std;

struct Request {
    int id;
    int arrival;
    int process;
};

class CircularQueue {
    Request *arr;
    int capacity;
    int front;
    int rear;
    int count;

public:
    CircularQueue() {
        capacity = 3;
        arr = new Request[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~CircularQueue() {
        delete[] arr;
    }

    bool isEmpty() {
        return count == 0;
    }

    void resize(int newCapacity) {
        if (newCapacity < 3)
            newCapacity = 3;

        Request *temp = new Request[newCapacity];

        for (int i = 0; i < count; i++)
            temp[i] = arr[(front + i) % capacity];

        delete[] arr;
        arr = temp;

        capacity = newCapacity;
        front = 0;
        rear = count - 1;

        cout << "Queue resized to " << capacity << ".\n";
    }

    void enqueue(Request r) {
        if (count == capacity)
            resize(capacity * 2);

        rear = (rear + 1) % capacity;
        arr[rear] = r;
        count++;

        cout << "Added request " << r.id << endl;
    }

    Request dequeue() {
        Request r = arr[front];

        front = (front + 1) % capacity;
        count--;

        if (capacity > 3 && count <= capacity / 4)
            resize(capacity / 2);

        return r;
    }

    void display() {
        cout << "Queue: ";

        for (int i = 0; i < count; i++) {
            Request r = arr[(front + i) % capacity];
            cout << r.id << " ";
        }

        cout << endl;
    }
};

int main() {
    CircularQueue q;

    Request requests[] = {
        {101, 0, 4},
        {102, 1, 3},
        {103, 2, 5},
        {104, 3, 2},
        {105, 4, 1},
        {106, 5, 3}
    };

    int n = sizeof(requests) / sizeof(requests[0]);

    cout << "--- Print Server Queue ---\n";

    for (int i = 0; i < n; i++) {
        q.enqueue(requests[i]);
        q.display();
    }

    cout << "\nProcessing requests...\n";

    int currentTime = 0;
    int totalWaiting = 0;
    int processed = 0;

    while (!q.isEmpty()) {
        Request r = q.dequeue();

        if (currentTime < r.arrival)
            currentTime = r.arrival;

        int waiting = currentTime - r.arrival;

        cout << "Request " << r.id
             << " | Waiting time: " << waiting << endl;

        totalWaiting += waiting;
        currentTime += r.process;
        processed++;
    }

    if (processed > 0) {
        cout << "Average waiting time: "
             << (double)totalWaiting / processed << endl;
    }

    return 0;
}