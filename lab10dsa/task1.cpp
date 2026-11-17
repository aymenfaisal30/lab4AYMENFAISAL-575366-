#include <iostream>
#include <queue>
using namespace std;

const int MAX = 100;

// Linked List Node
struct Node
{
    int id;
    int weight;
    Node* next;

    Node(int i, int w)
    {
        id = i;
        weight = w;
        next = NULL;
    }
};

     // insert container
void insert(Node*& head, int id, int weight)
{
    Node* newNode = new Node(id, weight);

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    Node* temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

// calculate remaining weight
int calculateWeight(Node* current)
{
    int total = 0;

    while (current != NULL)
    {
        total += current->weight;
        current = current->next;
    }

    return total;
}

// Backtracking
bool backtrack(
    Node* current,
    int truckCapacities[],
    int truckCount,
    int truckIndex,
    int assigned[][MAX])
{
    // Base case
    if (current == NULL)
    {
        return true;
    }

    // No trucks left
    if (truckIndex == truckCount)
    {
        return false;
    }

    // Calculate remaining truck capacity
    int totalCapacity = 0;

    for (int i = truckIndex; i < truckCount; i++)
    {
        totalCapacity += truckCapacities[i];
    }

    // Pruning condition 1
    if (calculateWeight(current) > totalCapacity)
    {
        return false;
    }

    int usedWeight = 0;
    int count = 0;

    Node* temp = current;

    // Try different container combinations
    while (temp != NULL)
    {
        usedWeight += temp->weight;

        // Pruning condition 2
        if (usedWeight > truckCapacities[truckIndex])
        {
            break;
        }

        assigned[truckIndex][count] = temp->id;

        count++;

        // Recursive call for next truck
        if (backtrack(
            temp->next,
            truckCapacities,
            truckCount,
            truckIndex + 1,
            assigned))
        {
            return true;
        }

        // Undo previous assignment
        assigned[truckIndex][count - 1] = 0;

        temp = temp->next;
    }

    return false;
}

int main()
{
    Node* head = NULL;

    // Insert containers
    insert(head, 101, 4);
    insert(head, 102, 6);
    insert(head, 103, 3);
    insert(head, 104, 5);

    // Queue of trucks
    queue<int> trucks;

    trucks.push(10);
    trucks.push(8);
    trucks.push(6);

    // copy queue capacities into array
    int capacities[MAX];
    int truckCount = 0;

    while (!trucks.empty())
    {
        capacities[truckCount] = trucks.front();

        trucks.pop();

        truckCount++;
    }

    // Store assignments
    int assigned[MAX][MAX] = {};

    if (backtrack(
        head,
        capacities,
        truckCount,
        0,
        assigned))
    {
        cout << "Containers successfully loaded YAYYY\n";

        for (int i = 0; i < truckCount; i++)
        {
            cout << "\nTruck " << i + 1 << ": ";

            for (int j = 0; j < MAX; j++)
            {
                if (assigned[i][j] != 0)
                {
                    cout << assigned[i][j] << " ";
                }
            }
        }
    }
    else
    {
        cout << "Insufficient truck capacity.";
    }

    return 0;
}