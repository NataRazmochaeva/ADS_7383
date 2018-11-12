#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

namespace STACK {
typedef char T;

class Stack { // определение класса
private:
    struct stack;
    stack *head;
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

enum key {
  empty = -1,
  closing_bracket = -2,
  is_text = -3,
  is_elem = -4,
};

int Text(string str, int i);
int Elem(string str, int i);
