#include "trees/tree.hpp"
#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <math.h>
#include <sstream>

using namespace std;

// mapear las variables
void updateVariable(map<string, double>& variables, const string& input) {
    istringstream iss(input);
    string variableName;
    char equalsSign;
    double value;

    if (iss >> variableName >> equalsSign && equalsSign == '=' && iss >> value) {
        variables[variableName] = value;
        cout << "Variable " << variableName << " set to " << value << endl;
    } else {
        cout << "Invalid input: " << input << endl;
    }
}

// algoritmo usado de la pagina que se nos dio para hacerlo, con fuertes inspiraciones en el codigo en especial en la parte del orden de los operadores
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int orden(char o){
    if (o == '-' || o == '+'){
        return 1;
    }
    else if (o == '*' || o == '/'){
        return 2;
    }
    else if (o == '^'){
        return 3;
    }
    else {
        return 0;
    }
}

string infixToPostfix(const string& infix) {
    stack<char> operatorStack;
    string postfix;
    map<char, int> precedence;

    for (char op : "+-*/^") {
        precedence[op] = orden(op);
    }

    for (char token : infix) {
        if (isalnum(token)) {
            postfix += token;
        } else if (token == '(') {
            operatorStack.push(token);
        } else if (token == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix += ' ';
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top() == '(') {
                operatorStack.pop();
            }
        } else if (isOperator(token)) {
            postfix += ' ';
            while (!operatorStack.empty() &&
                   orden(operatorStack.top()) >= orden(token)) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(token);
        }
    }

    while (!operatorStack.empty()) {
        postfix += ' ';
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    return postfix;
}

int valor(char i) {
    return i - '0';
}

int calculos(char operando, int v1, int v2) {
    if (operando == '+') {
        return v1 + v2;
    } else if (operando == '-') {
        return v1 - v2;
    } else if (operando == '^') {
        return pow(v1, v2);
    } else if (operando == '*') {
        return v1 * v2;
    } else if (operando == '/') {
        return v1 / v2;
    }
    return 0;
}

void mapNumbers(const string& expression, map<string, int>& numberMap) {
    stringstream ss(expression);
    string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            numberMap[token] = stoi(token);
        }
    }
}

int operatoria(const string& s, map<string, double>& variables) {
    int resultado = 0;
    stack<int> calculador;
    map<string, int> numberMap;

    mapNumbers(s, numberMap);

    for (int i = 0; i < s.length(); i++) {
        char actual = s[i];
        if (actual == '+' || actual == '-' || actual == '^' || actual == '*' || actual == '/') {
            int valor1 = calculador.top();
            calculador.pop();
            int valor2 = calculador.top();
            calculador.pop();
            calculador.push(calculos(actual, valor2, valor1));
        } else if (isalnum(actual)) {
            string token(1, actual);
            while (i + 1 < s.length() && isalnum(s[i + 1])) {
                token += s[i + 1];
                i++;
            }
            if (variables.find(token) != variables.end()) {
                calculador.push(variables[token]);
            } else if (numberMap.find(token) != numberMap.end()) {
                calculador.push(numberMap[token]);
            } else {
                cout << "Variable " << token << " is not defined." << endl;
                return 0;
            }
        } else if (isdigit(actual)) {
            calculador.push(valor(actual));
        }
    }
    return calculador.top();
}


int main() {
    map<string, double> variables;
    variables["ans"] = 0;
    string postfixinput;
    int resultado;
    string lastInput = "NULL";
    string input;

    cout << ">---< calculator >---<" << endl;
    
    while (true) {
        cout << "$ ";
        getline(cin, input);

        // para salir
        if (input == "FIN") {
            break;
        } 

        // Arbol de operacion
        else if (input == "tree") {
            if(lastInput == "NULL"){
                cout << "no hay operaciones de las cuales hacer un arbol" << endl;
            }
            else{

            }

        } 
        // definicion de variables
        else if (input.find('=') != string::npos) {
            updateVariable(variables, input);

        } 
        // operaciones
        else {
            postfixinput = infixToPostfix(input);
            cout << "Infix: " << input << endl;
            cout << "Postfix: " << postfixinput<< endl;
            variables["ans"] = operatoria(postfixinput, variables);
            cout << "Result: " << variables["ans"] << endl;
            lastInput = input;
        }
    }  

    // testing
    variables["x"] = 5;
    string infixExpression = "5 ^ 2 + 3 * ( 3 * 2 - 2 )";
    //string infixExpression = "(x + 23 * x) + 4";
    string postfixExpression = infixToPostfix(infixExpression);
    
    cout << "Infix: " << infixExpression << endl;
    cout << "Postfix: " << postfixExpression << endl;
    int result = operatoria(postfixExpression, variables);
    cout << "Result: " << result << endl;

    return 0;
}
