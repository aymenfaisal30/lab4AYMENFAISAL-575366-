#include <iostream>
using namespace std;

const int SIZE = 100;

class WaitingRoom {
    int patients[SIZE];
    int front;
    int rear;
    int count;
    int nextID;

public:
    WaitingRoom() {
        front = 0;
        rear = -1;
        count = 0;
        nextID = 1;
    }

    bool isEmpty() {
        return count == 0;
    }

    void RegisterPatient() {
        if (count == SIZE) {
            cout << "Waiting room is full.\n";
            return;
        }

        rear = (rear + 1) % SIZE;
        patients[rear] = nextID;

        cout << "Patient registered. ID: "
             << nextID << endl;

        nextID++;
        count++;
    }

    void ServePatient() {
        if (isEmpty()) {
            cout << "No patient is waiting.\n";
            return;
        }

        cout << "Now serving patient ID: "
             << patients[front] << endl;

        front = (front + 1) % SIZE;
        count--;
    }

    void CancelAll() {
        if (isEmpty()) {
            cout << "No appointments to cancel.\n";
            return;
        }

        cout << "All waiting appointments cancelled.\n";

        front = 0;
        rear = -1;
        count = 0;
    }

    bool CanDoctorGoHome() {
        return count == 0;
    }

    void ShowAllPatient() {
        if (isEmpty()) {
            cout << "No patients are waiting.\n";
            return;
        }

        cout << "Waiting patient IDs: ";

        for (int i = 0; i < count; i++)
            cout << patients[(front + i) % SIZE] << " ";

        cout << endl;
    }
};

int main() {
    WaitingRoom room;
    int choice;

    do {
        cout << "\n--- Waiting Room Management ---\n";
        cout << "1. Register Patient\n";
        cout << "2. Serve Patient\n";
        cout << "3. Cancel All Appointments\n";
        cout << "4. Can Doctor Go Home?\n";
        cout << "5. Show Waiting Patients\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                room.RegisterPatient();
                break;

            case 2:
                room.ServePatient();
                break;

            case 3:
                room.CancelAll();
                break;

            case 4:
                if (room.CanDoctorGoHome())
                    cout << "Yes, no patients are waiting.\n";
                else
                    cout << "No, patients are still waiting.\n";
                break;

            case 5:
                room.ShowAllPatient();
                break;

            case 0:
                cout << "Program ended.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}