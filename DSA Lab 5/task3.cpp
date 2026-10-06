#include <iostream>
#include <string>
using namespace std;

struct Node {
    int coachNumber;
    string coachType;
    int capacity;
    int passengers;

    Node* next;
    Node* prev;
};

class Train {
private:
    Node* current;

public:
    Train() {
        current = nullptr;
    }

    // 1. Add Coach at the end
    void addCoach(int number, string type, int capacity, int passengers) {
        Node* newNode =
            new Node{number, type, capacity, passengers, nullptr, nullptr};

        if (current == nullptr) {
            newNode->next = newNode;
            newNode->prev = newNode;
            current = newNode;
        }
        else {
            Node* first = current;
            Node* last = current->prev;

            newNode->next = first;
            newNode->prev = last;

            last->next = newNode;
            first->prev = newNode;
        }
    }

    // 2. Insert Coach after a specified coach number
    void insertCoach(int afterNumber, int number, string type,
                     int capacity, int passengers) {

        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }

        Node* start = current;
        Node* temp = current;

        do {
            if (temp->coachNumber == afterNumber) {

                Node* newNode =
                    new Node{number, type, capacity, passengers,
                             nullptr, nullptr};

                newNode->next = temp->next;
                newNode->prev = temp;

                temp->next->prev = newNode;
                temp->next = newNode;

                cout << "Coach inserted.\n";
                return;
            }

            temp = temp->next;

        } while (temp != start);

        cout << "Coach not found.\n";
    }

    // 3. Remove Coach by coach number
    void removeCoach(int number) {

        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }

        Node* start = current;
        Node* temp = current;

        do {
            if (temp->coachNumber == number) {

                // Only one coach
                if (temp->next == temp) {
                    delete temp;
                    current = nullptr;
                    return;
                }

                // If current coach is removed
                if (temp == current) {
                    current = current->next;
                }

                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                delete temp;

                cout << "Coach removed.\n";
                return;
            }

            temp = temp->next;

        } while (temp != start);

        cout << "Coach not found.\n";
    }

    // 4. Move Forward
    void moveForward() {
        if (current != nullptr)
            current = current->next;
    }

    // 5. Move Backward
    void moveBackward() {
        if (current != nullptr)
            current = current->prev;
    }

    // 6. Display Train Clockwise
    void displayClockwise() {

        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }

        Node* start = current;
        Node* temp = current;

        do {
            displayCoach(temp);
            temp = temp->next;

        } while (temp != start);
    }

    // 7. Display Train Anti-clockwise
    void displayAntiClockwise() {

        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }

        Node* start = current;
        Node* temp = current;

        do {
            displayCoach(temp);
            temp = temp->prev;

        } while (temp != start);
    }

    // 8. Search Coach
    void searchCoach(int number) {

        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }

        Node* start = current;
        Node* temp = current;

        do {
            if (temp->coachNumber == number) {
                cout << "\nCoach Found!\n";
                displayCoach(temp);
                return;
            }

            temp = temp->next;

        } while (temp != start);

        cout << "Coach not found.\n";
    }

    // 9. Find Maximum Available Capacity
    void maximumAvailableCapacity() {

        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }

        Node* start = current;
        Node* temp = current;
        Node* maximum = current;

        do {
            int available = temp->capacity - temp->passengers;
            int maxAvailable =
                maximum->capacity - maximum->passengers;

            if (available > maxAvailable) {
                maximum = temp;
            }

            temp = temp->next;

        } while (temp != start);

        cout << "\nCoach with Maximum Available Capacity:\n";
        displayCoach(maximum);
        cout << "Available Seats: "
             << maximum->capacity - maximum->passengers << endl;
    }

    // 10. Display Current Coach
    void displayCurrent() {

        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }

        cout << "\nCurrent Coach:\n";
        displayCoach(current);
    }

    // 11. Reverse Train Direction
    void reverseTrain() {

        if (current == nullptr) {
            cout << "Train is empty.\n";
            return;
        }

        Node* start = current;
        Node* temp = current;

        do {
            Node* swap = temp->next;
            temp->next = temp->prev;
            temp->prev = swap;

            temp = swap;

        } while (temp != start);

        cout << "Train direction reversed.\n";
    }

    // Display one coach
    void displayCoach(Node* coach) {

        cout << "\nCoach Number: " << coach->coachNumber << endl;
        cout << "Coach Type: " << coach->coachType << endl;
        cout << "Passenger Capacity: "
             << coach->capacity << endl;
        cout << "Current Passengers: "
             << coach->passengers << endl;
        cout << "Available Seats: "
             << coach->capacity - coach->passengers << endl;
    }
};

int main() {

    Train train;

    int n;

    cout << "Enter number of coaches: ";
    cin >> n;

    for (int i = 0; i < n; i++) {

        int number;
        string type;
        int capacity;
        int passengers;

        cout << "\nEnter Coach " << i + 1 << " Number: ";
        cin >> number;

        cin.ignore();

        cout << "Enter Coach Type: ";
        getline(cin, type);

        cout << "Enter Passenger Capacity: ";
        cin >> capacity;

        cout << "Enter Current Passengers: ";
        cin >> passengers;

        train.addCoach(number, type, capacity, passengers);
    }

    cout << "\n TRAIN CLOCKWISE \n";
    train.displayClockwise();

    cout << "\n TRAIN ANTI-CLOCKWISE \n";
    train.displayAntiClockwise();

    cout << "\n CURRENT COACH \n";
    train.displayCurrent();

    int searchNumber;

    cout << "\nEnter coach number to search: ";
    cin >> searchNumber;

    train.searchCoach(searchNumber);

    cout << "\n MAXIMUM AVAILABLE CAPACITY \n";
    train.maximumAvailableCapacity();

    cout << "\n MOVING FORWARD \n";
    train.moveForward();
    train.displayCurrent();

    cout << "\n MOVING BACKWARD \n";
    train.moveBackward();
    train.displayCurrent();

    cout << "\n AFTER REVERSING \n";
    train.reverseTrain();

    cout << "\nClockwise after reverse:\n";
    train.displayClockwise();

    cout << "\nAnti-clockwise after reverse:\n";
    train.displayAntiClockwise();

    return 0;
}