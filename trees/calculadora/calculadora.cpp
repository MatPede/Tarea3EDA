#include <iostream>
#include <cstring>
#include <stack>
#include "trees/tree.hpp"
#include <math.h>
using namespace std;

// algoritmo usado de la pagina que se nos dio para hacerlo, con fuertes inspiraciones en el codigo en especial en la parte del orden de los operadores
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
        return -1;
    }
}

string intopost(string s){
    string post = "";
    stack<char> resolvedor; 
    char actual = '2';
    
    for(int i=0;i < s.length();i++){
        actual = s[i];

        if (
            actual == '+' || 
            actual == '-' || 
            actual == '^' || 
            actual == '*' || 
            actual == '/')
        {
          if (resolvedor.empty()){
            resolvedor.push(actual);
          }
          else {
            while(orden(resolvedor.top()) >= orden(actual)){
                post += resolvedor.top();
                resolvedor.pop();
                if (resolvedor.empty()){
                    break;
                }
            }
            resolvedor.push(actual);
          } 
        }

        else if (actual == '('){
            resolvedor.push('(');
        }

        else if (actual == ')'){
            char valor_pila = resolvedor.top();
            resolvedor.pop();
            while (!(valor_pila == '(')){
                post += valor_pila;
                valor_pila = resolvedor.top();
                resolvedor.pop();
            }
        }
        else if (actual >= '0' && actual <= '9'){
            post += actual;
        }
    }

    while (!resolvedor.empty()){
        post += resolvedor.top();
        resolvedor.pop();
    }
	return post;
}

// algoritmo control 2
// tonto pero mas facil
int valor(char i){
    return i - '0';
}

int calculos(char operando, int v1, int v2){
    if (operando == '+'){
        return v1 + v2;
    }
    else if (operando == '-'){
        return v1 - v2;
    }
    else if (operando == '^'){
        return pow(v1, v2);
    }
    else if (operando == '*'){
        return v1 * v2;
    }
    else if (operando == '/'){
        return v1 / v2;
    }
}

int operatoria(string s){
    int resultado = 0;
    stack<int> calculador;
    char actual;
    char valor1;
    char valor2;

    for(int i=0;i < s.length();i++){
        actual = s[i];
        if (
            actual == '+' || 
            actual == '-' || 
            actual == '^' || 
            actual == '*' || 
            actual == '/')
        {
            valor1 = calculador.top();
            calculador.pop();
            valor2 = calculador.top();
            calculador.pop();
            calculador.push(calculos(actual, valor2, valor1));
        }

        else{
            calculador.push(valor(actual));
        }
    }
    return calculador.top();

}

int main (){
    string xd = intopost("5^2+3*(3*2-2)");
    int xd2 = operatoria(xd);
    cout << "valor: " << xd2 << endl;
    return 0;
}