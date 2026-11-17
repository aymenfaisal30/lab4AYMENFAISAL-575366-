#include <iostream>
#include <stack>
#include <string>
using namespace std;

// pprint stack in original order
void printStack(stack<string> s)
{
    if (s.empty())
    {
        return;
    }

    string operation = s.top();

    s.pop();

    printStack(s);

    cout << operation << " ";
}

// Backtracking function
void backtrack(
    int current,
    int target,
    int steps,
    int maxOperations,
    int bound,
    stack<string>& operations)
{
    // Base case
    if (current == target)
    {
        cout << "Solution: ";

        printStack(operations);

        cout << endl;

        return;
    }

    // Maximum operations reached
    if (steps == maxOperations)
    {
        return;
    }

    // Operation 1: +3
    long long newValue = current + 3;

    if (newValue >= 0 && newValue <= bound)
    {
        operations.push("+3");

        backtrack(newValue, target, steps + 1, maxOperations, bound, operations);

        operations.pop();
    }

    // Operation 2: *2
    newValue = (long long)current * 2;

    if (newValue >= 0 && newValue <= bound)
    {
        operations.push("*2");

        backtrack(newValue, target, steps + 1, maxOperations, bound, operations);

        operations.pop();
    }

    // Operation 3: -5
    newValue = current - 5;

    if (newValue >= 0 && newValue <= bound)
    {
        operations.push("-5");

        backtrack(newValue, target, steps + 1, maxOperations, bound, operations);

        operations.pop();
    }

    // Operation 4: /2
    if (current % 2 == 0)
    {
        newValue = current / 2;

        if (newValue >= 0 && newValue <= bound)
        {
            operations.push("/2");
            backtrack(newValue, target, steps + 1, maxOperations, bound, operations);
            operations.pop();
        }
    }
}

int main()
{
    int initial = 2;
    int target = 15;
    int maxOperations = 4;
    int bound = 100;

    stack<string> operations;
    cout << "Valid sequences:\n";
    backtrack(initial, target, 0, maxOperations, bound, operations);

    return 0;
}
