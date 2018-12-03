#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Stack { // определение класса
private:
    char br;
    Stack *prev;
    Stack *head;
public:
    Stack() {
		br = '\0';
		head = NULL;
		prev = NULL;
    };
    void pop();
    void push(char a);
    char top();
    bool stempty();
    ~Stack();
};

int Check(string str, Stack s);
