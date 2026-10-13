#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const int MAX = 1000;

// Stack for characters
class CharStack
{
    char arr[MAX];
    int top;

public:
    CharStack()
    { top = -1; }

    bool isEmpty()
    { return top == -1; }

    bool isFull()
    { return top == MAX - 1; }

    void push(char value)
    { if (!isFull())
         arr[++top] = value;
    }

    char pop()
    {
        if (isEmpty())
            return '\0';
        return arr[top--];
    }

    char peek()
    {
        if (isEmpty())
            return '\0';
        return arr[top];
    }
};

// Stack for strings
class StringStack
{
    string arr[MAX];
    int top;

public:
    StringStack()
    { top = -1; }

    bool isEmpty()
    { return top == -1; }

    void push(string value)
    {
        if (top < MAX - 1)
            arr[++top] = value;
    }

    string pop()
    {
        if (isEmpty())
            return "";

        return arr[top--];
    }
};

// Stack for numbers
class NumberStack
{
    double arr[MAX];
    int top;

public:
    NumberStack()
    { top = -1; }

    bool isEmpty()
    {
        return top == -1;
    }

    void push(double value)
    {
        if (top < MAX - 1)
            arr[++top] = value;
    }

    double pop()
    {
        if (isEmpty())
            return 0;

        return arr[top--];
    }
};

// Check whether a character is an operator
bool isOperator(char ch)
{
    return ch == '+' || ch == '-' ||
           ch == '*' || ch == '/' ||
           ch == '%' || ch == '^';
}

// Operator precedence
int precedence(char ch)
{
    if (ch == '^')
        return 3;

    if (ch == '*' || ch == '/' || ch == '%')
        return 2;

    if (ch == '+' || ch == '-')
        return 1;

    return 0;
}

// Reverse a string manually
string reverseString(string s)
{
    string result = "";

    for (int i = (int)s.length() - 1; i >= 0; i--)
        result += s[i];

    return result;
}

// TASK 1: Infix to Postfix
string infix_to_postfix(string expr)
{
    CharStack s;
    string output = "";

    for (int i = 0; i < (int)expr.length(); i++)
    {
        char ch = expr[i];

        if (ch == ' ')
            continue;

        if ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') ||
            (ch >= '0' && ch <= '9'))
        {
            output += ch;
        }
        else if (ch == '(')
        {
            s.push(ch);
        }
        else if (ch == ')')
        {
            while (!s.isEmpty() && s.peek() != '(')
                output += s.pop();

            if (!s.isEmpty())
                s.pop();
        }
        else if (isOperator(ch))
        {
            while (!s.isEmpty() && s.peek() != '(' &&
                   (precedence(s.peek()) > precedence(ch) ||
                   (precedence(s.peek()) == precedence(ch) &&
                    ch != '^')))
            {
                output += s.pop();
            }

            s.push(ch);
        }
    }

    while (!s.isEmpty())
        output += s.pop();

    return output;
}

// TASK 2: Infix to Prefix
string infix_to_prefix(string expr)
{
    string reversed = reverseString(expr);

    for (int i = 0; i < (int)reversed.length(); i++)
    {
        if (reversed[i] == '(')
            reversed[i] = ')';
        else if (reversed[i] == ')')
            reversed[i] = '(';
    }

    CharStack s;
    string output = "";

    for (int i = 0; i < (int)reversed.length(); i++)
    {
        char ch = reversed[i];

        if (ch == ' ')
            continue;

        if ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') ||
            (ch >= '0' && ch <= '9'))
        {
            output += ch;
        }
        else if (ch == '(')
        {
            s.push(ch);
        }
        else if (ch == ')')
        {
            while (!s.isEmpty() && s.peek() != '(')
                output += s.pop();

            if (!s.isEmpty())
                s.pop();
        }
        else if (isOperator(ch))
        {
            while (!s.isEmpty() && s.peek() != '(' &&
                   (precedence(s.peek()) > precedence(ch) ||
                   (precedence(s.peek()) == precedence(ch) &&
                    ch == '^')))
            {
                output += s.pop();
            }

            s.push(ch);
        }
    }

    while (!s.isEmpty())
        output += s.pop();

    return reverseString(output);
}

// TASK 3: Postfix to Infix
string postfix_to_infix(string expr)
{
    StringStack s;

    for (int i = 0; i < (int)expr.length(); i++)
    {
        char ch = expr[i];

        if (ch == ' ')
            continue;

        if (!isOperator(ch))
        {
            string operand = "";
            operand += ch;
            s.push(operand);
        }
        else
        {
            string right = s.pop();
            string left = s.pop();

            string result = "(" + left + ch + right + ")";
            s.push(result);
        }
    }

    return s.pop();
}

// Perform a mathematical operation
double calculate(double left, double right, char op)
{
    if (op == '+')
        return left + right;

    if (op == '-')
        return left - right;

    if (op == '*')
        return left * right;

    if (op == '/')
        return left / right;

    if (op == '%')
        return fmod(left, right);

    if (op == '^')
        return pow(left, right);

    return 0;
}

// TASK 4: Evaluate Postfix
double evaluate_postfix(string expr)
{
    NumberStack s;

    for (int i = 0; i < (int)expr.length(); i++)
    {
        char ch = expr[i];

        if (ch == ' ')
            continue;

        if (ch >= '0' && ch <= '9')
        {
            s.push(ch - '0');
        }
        else if (isOperator(ch))
        {
            double right = s.pop();
            double left = s.pop();

            double result = calculate(left, right, ch);
            s.push(result);
        }
    }

    return s.pop();
}

// TASK 5: Evaluate Prefix
double evaluate_prefix(string expr)
{
    NumberStack s;

    for (int i = (int)expr.length() - 1; i >= 0; i--)
    {
        char ch = expr[i];

        if (ch == ' ')
            continue;

        if (ch >= '0' && ch <= '9')
        {
            s.push(ch - '0');
        }
        else if (isOperator(ch))
        {
            double left = s.pop();
            double right = s.pop();

            double result = calculate(left, right, ch);
            s.push(result);
        }
    }

    return s.pop();
}

// MAIN FUNCTION
int main()
{
    int choice;
    string expr;

    do
    {
        cout << "\n           TASK 1          \n";
        cout << "1. Infix to Postfix\n";
        cout << "2. Infix to Prefix\n";
        cout << "3. Postfix to Infix\n";
        cout << "4. Evaluate Postfix\n";
        cout << "5. Evaluate Prefix\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0)
            break;

        cout << "Enter expression: ";
        cin >> expr;

        switch (choice)
        {
        case 1:
            cout << "Postfix: "
                 << infix_to_postfix(expr) << endl;
            break;

        case 2:
            cout << "Prefix: "
                 << infix_to_prefix(expr) << endl;
            break;

        case 3:
            cout << "Infix: "
                 << postfix_to_infix(expr) << endl;
            break;

        case 4:
            cout << "Result: "
                 << evaluate_postfix(expr) << endl;
            break;

        case 5:
            cout << "Result: "
                 << evaluate_prefix(expr) << endl;
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
