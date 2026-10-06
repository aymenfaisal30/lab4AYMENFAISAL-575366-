#include <iostream>
#include <string>
using namespace std;

struct Node {
    int id;
    string name;
    string date;
    string location;
    Node* next;
    Node* prev;
};

class PhotoAlbum {
private:
    Node* current;
public:
    PhotoAlbum() {
        current = nullptr;
    }
    // 1. Add Photo at the end
    void addPhoto(int id, string name, string date, string location) {
        Node* newNode = new Node{id, name, date, location, nullptr, nullptr};

        if (current == nullptr) {
            newNode->next = newNode;
            newNode->prev = newNode;
            current = newNode;
        }
        else {
            Node* last = current->prev;

            newNode->next = current;
            newNode->prev = last;
            last->next = newNode;
            current->prev = newNode;
        }
    }

    // 2. Insert Photo After Current
    void insertAfterCurrent(int id, string name, string date, string location) {
        if (current == nullptr) {
            addPhoto(id, name, date, location);
            return;
        }

        Node* newNode = new Node{id, name, date, location, nullptr, nullptr};

        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
    }

    // 3. Remove Photo using ID
    void removePhoto(int id) {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }

        Node* start = current;
        Node* temp = current;

        do {
            if (temp->id == id) {

                // Only one node (photo)
                if (temp->next == temp) {
                    delete temp;
                    current = nullptr;
                    return;
                }

                // If deleting current
                if (temp == current) {
                    current = current->next;
                }

                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                delete temp;

                cout << "Photo removed.\n";
                return;
            }

            temp = temp->next;

        } while (temp != start);

        cout << "Photo not found.\n";
    }

    // 4. Remove Current Photo
    void removeCurrentPhoto() {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }

        Node* temp = current;

        // Only one photo
        if (current->next == current) {
            delete current;
            current = nullptr;
            return;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;
        current = current->next;
        delete temp;
    }

    // 5. Move Next
    void moveNext() {
        if (current != nullptr)
            current = current->next;
    }

    // 6. Move Previous
    void movePrevious() {
        if (current != nullptr)
            current = current->prev;
    }

    // 7. Display Forward
    void displayForward() {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }

        Node* start = current;
        Node* temp = current;

        do {
            displayPhoto(temp);
            temp = temp->next;
        } while (temp != start);
    }

    // 8. Display Backward
    void displayBackward() {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }

        Node* start = current;
        Node* temp = current;

        do {
            displayPhoto(temp);
            temp = temp->prev;
        } while (temp != start);
    }

    // 9. Search Photo
    void searchPhoto(int id) {
        if (current == nullptr) {
            cout << "Album is empty.\n";
            return;
        }

        Node* start = current;
        Node* temp = current;

        do {
            if (temp->id == id) {
                cout << "\nPhoto Found!\n";
                displayPhoto(temp);
                return;
            }

            temp = temp->next;

        } while (temp != start);

        cout << "Photo not found.\n";
    }

    // 10. Count Photos
    void countPhotos() {
        if (current == nullptr) {
            cout << "Total Photos: 0\n";
            return;
        }

        int count = 0;
        Node* start = current;
        Node* temp = current;

        do {
            count++;
            temp = temp->next;
        } while (temp != start);

        cout << "Total Photos: " << count << endl;
    }

    // Display one photo
    void displayPhoto(Node* photo) {
        cout << "\nPhoto ID: " << photo->id << endl;
        cout << "Photo Name: " << photo->name << endl;
        cout << "Date Taken: " << photo->date << endl;
        cout << "Location: " << photo->location << endl;
    }
};

int main() {
    PhotoAlbum album;
    int n;
    cout << "Enter number of photos: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int id;
        string name;
        string date;
        string location;

        cout << "\nEnter Photo " << i + 1 << " ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Photo Name: ";
        getline(cin, name);
        cout << "Enter Date Taken: ";
        getline(cin, date);
        cout << "Enter Location: ";
        getline(cin, location);
        album.addPhoto(id, name, date, location);
    }

    cout << "\n\n===== ALBUM FORWARD =====\n";
    album.displayForward();
    cout << "\n===== ALBUM BACKWARD =====\n";
    album.displayBackward();
    cout << "\n===== TOTAL PHOTOS =====\n";
    album.countPhotos();

    int searchID;

    cout << "\nEnter Photo ID to search: ";
    cin >> searchID;
    album.searchPhoto(searchID);
    cout << "\n===== MOVING NEXT =====\n";
    album.moveNext();
    album.displayForward();
    cout << "\n===== MOVING PREVIOUS =====\n";
    album.movePrevious();
    album.displayForward();

    return 0;
}