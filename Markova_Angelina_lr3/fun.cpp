#include "fun.h"

using namespace std;
using namespace STACK;

namespace STACK {  // определем пространство имен
struct Stack::mstack { // элемент стека
    char oprt;
    struct mstack*prev;

    mstack() { // инициализируем структуру 
        oprt='\0';
        prev=NULL;
    }
};

void Stack::pop() { // удаляем элемент
    if(head==NULL) {
        cerr<<"stack is empty\n";
        exit(1);
    }
    mstack *temp=head;
    head=head->prev;
    delete temp;
}

void Stack::push(char a) { // добавляем новый элемент
    mstack*temp;
    temp = new mstack;
    temp->oprt=a;
    temp->prev=head;
    head=temp;
}

char Stack::top() { // достаем верхний элемент
    if(head==NULL) {
        cerr<<"stack is empty\n";
        exit(1);
    }
    return head->oprt;
}

bool Stack::stempty() { // проверка на пустоту
    if(head==NULL)
        return true;
    else
        return false;
}

Stack::~Stack() { // очистка
    while(head!=NULL) {
        pop();
    }
}
}

Stack St;

// Функция для проверки считанного символа: является ли он буквой или цифрой
bool IsOperand(char C) {
    if(isalnum(C)||isalpha(C)) return true;
    return false;
}
// Функция для проверки считанного символа: является ли оператором
bool IsOperator(char C) {
    if(C == '+' || C == '-' || C == '*' || C == '/' )
        return true;
    return false;
}
// Функция для проверки приоритетов, чем больше "вес" оператора, тем раньше он выполняется
int GetOperatorWeight(char op) {
    int weight = -1;
    if(op == '+'|| op == '-' )weight = 1;
    if(op == '/'|| op == '*' )weight = 2;
    return weight;
}
// Функция, которая опряделяет какая операции будет выполнена раньше, используя определение "веса"
bool HasHigherPrecedence(char op1, char op2) {
    int op1Weight = GetOperatorWeight(op1);
    int op2Weight = GetOperatorWeight(op2);
    // Если операторы имеют одинаковый "вес", а значит и приорет, то вернется true (ассоциативность
	// Так же используем левую ассоциативность, т.е в выражение A+B-C, "+" больше, чем "-"
    if(op1Weight < op2Weight)
        return false;
    else
        return true;
}
// Функция, которая пробразовывает запись 
string InfixToPostfix(string expression) {
    string postfix = ""; // Инициализируем пустую строку
    for(int i = 0; i< expression.length(); i++) { // Обрабатываем строку до ее конца
// Сканируем посимвольно
// Если символ является разделительным, то пропускаем его
        if(IsOperator(expression[i])) { // проверка на оператор
            int test=i;
            test++;
            while (expression[test]==' ')
                test++;
            if(IsOperator(expression[test])||expression[test]=='\0') {
                cerr << "Error: incorrect input\n"; // два оператора подряд идут
                exit(1);
            }

        }

        if(expression[i] == ' ' || expression[i] == ',') continue; // пропуск разделительных символов
// Если оператор, то проверяем есть ли что в стеке, если да, то смотрим на приоритеты
// Если оператор в стеке больше "весит", то он записывается в преобразованную строку, иначе в стек кладется текущий оператор
        else if(IsOperator(expression[i]))
        {
            while(!St.stempty() && St.top() != '(' && HasHigherPrecedence(St.top(),expression[i])) {
                postfix+= St.top();
                postfix+=" ";
                St.pop();
            }
            St.push(expression[i]);
        }
// Иначе если символ является буквой или цифрой, записываем в преобразованную строку
        else if(IsOperand(expression[i])) {
            postfix +=expression[i];
            postfix+=" ";
        }
        else if (expression[i] == '(') {
            St.push(expression[i]);
        }
        else if(expression[i] == ')') { // Записываем выражение, которое было в скобках
            while(!St.stempty() && St.top() != '(') {
                postfix += St.top();
                postfix+=" ";
                St.pop();
            }
            St.pop(); //убираем из стека "("
        }
    }
    while(!St.stempty()) { // Оставшиеся операторы достаем из стека
        postfix += St.top();
        postfix+=" ";
        St.pop();
    }
    St.~Stack(); // Очистка стека
    return postfix;
}

