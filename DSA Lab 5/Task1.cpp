#include <iostream>
#include <string>
using namespace std;

struct Node {
    int id;
    string title;
    string url;
    Node* next;
    Node* prev;
};

class Browser {
private:
    Node* current;

public:
    Browser() {
        current = nullptr;
    }

// 1. Open New Tab
    void openTab(int id, string title, string url) {
        Node* newNode = new Node{id, title, url, nullptr, nullptr};

        if (current == nullptr) {
            newNode->next = newNode;
            newNode->prev = newNode;
            current = newNode;
        }
        else {
            newNode->next = current->next;
            newNode->prev = current;

            current->next->prev = newNode;
            current->next = newNode;
        }
    }

// 2. Close Current Tab
    void closeTab() {
        if (current == nullptr) {
            cout << "No tabs open.\n";
            return;
        }
         //if only one node 
        if (current->next == current) {
            delete current;
            current = nullptr;
        }
        else {
            Node* temp = current;

            current->prev->next = current->next;
            current->next->prev = current->prev;

            current = current->next;
            delete temp;
        }
    }

    // 3. Move Next
    void moveNext() {
        if (current != nullptr)
            current = current->next;
    }

    // 4. Move Previous
    void movePrevious() {
        if (current != nullptr)
            current = current->prev;
    }

    // 5. Display Current Tab
    void displayCurrent() {
        if (current == nullptr) {
            cout << "No tabs open.\n";
            return;
        }

        cout << "ID: " << current->id << endl;
        cout << "Title: " << current->title << endl;
        cout << "URL: " << current->url << endl;
    }

    // 6. Display All Tabs Forward
    void displayForward() {
        if (current == nullptr) {
            cout << "No tabs open.\n";
            return;
        }

        Node* start = current;
        Node* temp = current;

        do {
            cout << temp->id << " - "
                 << temp->title << " - "
                 << temp->url << endl;

            temp = temp->next;

        } while (temp != start);
    }

    // 7. Display All Tabs Backward
    void displayBackward() {
        if (current == nullptr) {
            cout << "No tabs open.\n";
            return;
        }

        Node* start = current;
        Node* temp = current;

        do {
            cout << temp->id << " - "
                 << temp->title << " - "
                 << temp->url << endl;

            temp = temp->prev;

        } while (temp != start);
    }

    // 8. Search Tab
    void searchTab(int id) {
        if (current == nullptr) {
            cout << "No tabs open.\n";
            return;
        }

        Node* start = current;
        Node* temp = current;

        do {
            if (temp->id == id) {
                cout << "Tab Found!\n";
                cout << "ID: " << temp->id << endl;
                cout << "Title: " << temp->title << endl;
                cout << "URL: " << temp->url << endl;
                return;
            }

            temp = temp->next;

        } while (temp != start);

        cout << "Tab not found.\n";
    }
};

int main() {
    Browser browser;

    browser.openTab(1, "Instagram", "https://instagram.com");
    browser.openTab(2, "lms", "https://lms.nust.edu.pkSSSS");
    browser.openTab(3, "GitHub", "https://github.com");

    cout << "Current Tab:\n";
    browser.displayCurrent();

    cout << "\nForward:\n";
    browser.displayForward();

    cout << "\nBackward:\n";
    browser.displayBackward();

    cout << "\nMoving Next:\n";
    browser.moveNext();
    browser.displayCurrent();

    cout << "\nMoving Previous:\n";
    browser.movePrevious();
    browser.displayCurrent();

    cout << "\nSearching for ID 2:\n";
    browser.searchTab(2);

    cout << "\nClosing Current Tab:\n";
    browser.closeTab();

    cout << "\nRemaining Tabs:\n";
    browser.displayForward();

    return 0;
}