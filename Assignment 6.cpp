#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

// Method to check if character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

// Method to return precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

// Function to convert infix to postfix
string infixToPostfix(string infix) {
    stack<char> s;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (isalnum(c)) {     // If the character is letter or number 
            postfix += c;     // Append to the postfix string
        } 
        else if (c == '(') {  // push into the stack
            s.push(c);
        } 
        else if (c == ')') {   
            while (!s.empty() && s.top() != '(') {   // Pop all operators from the stack until ( is found.
                postfix += s.top();                  // Append popped operators to postfix.
                s.pop();
            }
            if (!s.empty()) {
			    s.pop();        // pop '('
			}     
        }
        else if (isOperator(c)) { 
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();                   // Pop operators from stack & append them to postfix
                s.pop();                              // with their higher or equal precedence.
            }
            s.push(c);                                // Push current operator onto the stack.
        }
    }

    // Pop remaining operators
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

// Function to convert infix to prefix
string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());

    // Swapping '(' with ')' and ')' with '('
    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == '(') {
        	infix[i] = ')';
		}
        else if (infix[i] == ')') {
        	infix[i] = '(';
		}
    }

    string postfix = infixToPostfix(infix);
    reverse(postfix.begin(), postfix.end());

    return postfix;
}

// Main function
int main() {
    string infix;

    cout << "Enter an infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);

    cout << "Postfix Expression: " << postfix << endl;
    cout << "Prefix Expression: " << prefix << endl;

    return 0;
}

