#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>

using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int priority(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

string expToRPN(const string& exp) {
    stack<char> operators;
    string postfix;

    for (char c : exp) {

        if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else if (isOperator(c)) {
            while (!operators.empty() && priority(operators.top()) >= priority(c)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
        else {
            postfix += c;
        }
    }




    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

int calculateRPN(const string& rpn) {
    stack<int> operands;

    for (char c : rpn) {
        if (isdigit(c)) {
            operands.push(c - '0');
        }
        else if (isOperator(c)) {
            if (operands.size() < 2) {
                throw invalid_argument("Invalid postfix expression");
            }
            int operand2 = operands.top();
            operands.pop();
            int operand1 = operands.top();
            operands.pop();

            if (c == '/' && operand2 == 0) {
                throw runtime_error("Division by 0");
            }

            switch (c) {
            case '+':
                operands.push(operand1 + operand2);
                break;
            case '-':
                operands.push(operand1 - operand2);
                break;
            case '*':
                operands.push(operand1 * operand2);
                break;
            case '/':
                operands.push(operand1 / operand2);
                break;
            }
        }
    }

    if (operands.size() != 1) {
        throw invalid_argument("Invalid expression");
    }

    return operands.top();
}

int main() {
    string expression;
    cout << "Enter expression (for example, 3+4*2/(1-5)+2): ";
    cin >> expression;

    string rpnExpression = expToRPN(expression);
    cout << "RPN: " << rpnExpression << endl;

    try {
        int result = calculateRPN(rpnExpression);
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cerr << "Error - ( " << e.what() << ")" << endl;
    }

    

    return 0;
}
