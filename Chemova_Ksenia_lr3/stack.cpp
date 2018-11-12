#include "stack.hpp"
using namespace STACK;

namespace STACK {  // определем пространство имен
struct Stack::stack {
  char oprt;
  struct stack *prev;

  stack() { //конструктор
    oprt = '\0';
    prev = NULL;
  }
};

void Stack::pop() { // удаляем верхний элемент
  if (head == NULL) {
    cerr<<"Stack is empty"<<endl;
    return;//exit(1);
  }
  stack *temp = head;
  head = head->prev;
  delete temp;
}

void Stack::push(char a) { // добавляем новый элемент
  stack *temp;
  temp = new stack;
  temp->oprt = a;
  temp->prev = head;
  head = temp;
}

char Stack::top() { // возвращаем значение верхнего элемента
  if (head == NULL) {
    cerr<<"Stack is empty"<<endl;
    return '\0';//exit(1);
  }
  return head->oprt;
}

bool Stack::stempty() { // проверка на пустой стек
  if (head == NULL)
    return true;
  else
    return false;
}

Stack::~Stack() { // деструктор
  while (head != NULL)
    pop();
}
}
Stack St;

//--------------------------------------------------------------------------

int Text(string str, int i) {

  int ret;
  if (str[i] == '\0' || str[i] == '\n') return empty;//true, file is empty
  if (str[i]==')' || str[i]==']' || str[i]=='}') return closing_bracket;
  if (Elem(str, i) == is_elem)
  ret = Text(str, i+1);
    if (ret == empty || ret == closing_bracket || ret == is_text)
      return is_text;
  return i; //error. It isn't a Text
}

int Elem(string str, int i) {

  char ch = str[i];

  switch (ch) {
    case '(': {
      St.push(ch);
      if (Text (str, i+1) == is_text)
        if (St.top() == '('){
          St.pop();
          return is_elem;
        }
      else return i;
    }
    case '[': {
      St.push(ch);
      if (Text (str, i+1) == is_text)
        if (St.top() == '['){
          St.pop();
          return is_elem;
        }
      else return i;
    }
    case '{': {
      St.push(ch);
      if (Text (str, i+1) == is_text)
        if (St.top() == '{'){
          St.pop();
          return is_elem;
        }
      else return i;
    }
    default: return is_elem;
  }
}
