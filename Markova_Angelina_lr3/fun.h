#include<iostream>
#include<stack>
#include<string>
#include <cstdlib>
#include <fstream>

using namespace std;

namespace STACK {
typedef char T;

class Stack { // определение класса
private:
    struct mstack;
    mstack *head;
public:
    Stack() {
        head=NULL;
    };
    void pop();
    void push(T a);
    T top();
    bool stempty();
    void clear();
    ~Stack();
};
}

// Функция сравнения приоритета операторов
bool HasHigherPrecedence(char operator1, char operator2);
// Функция проверки является ли символ оператором
bool IsOperator(char C);
// Функция проверки является ли символ буквой или цифрой
bool IsOperand(char C);
int GetOperatorWeight(char op);
bool HasHigherPrecedence(char op1, char op2);
// Функция преобразования
string InfixToPostfix(const string expression);
