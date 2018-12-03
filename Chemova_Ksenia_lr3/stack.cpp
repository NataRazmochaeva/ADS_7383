#include "stack.hpp"

void Stack::pop() { // удаляем верхний элемент
  if (head == NULL) {
    cerr<<"Stack is empty"<<endl;
    return;
  }
  Stack *temp = head;
  head = head->prev;
  delete temp;
}

void Stack::push(char b) { // добавляем новый элемент
  Stack *temp;
  temp = new Stack;
  temp->br = b;
  temp->prev = head;
  head = temp;
}

char Stack::top() { // возвращаем значение верхнего элемента
  if (head == NULL) {
    cerr<<"Stack is empty"<<endl;
    return '\0';
  }
  return head->br;
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

int Check(string str,Stack s){
  int flag = 0;
  for (int i=0;str[i]!='\0';i++){
    if (str[i] == '[' || str[i] == '{' || str[i] == '('){
      s.push(str[i]);
      flag = i;
    }
    if (str[i] == ']' || str[i] == '}' || str[i] == ')'){
          if (s.top() == '[' && str[i] == ']')
            s.pop();
          else if (s.top() == '{' && str[i] == '}')
                s.pop();
                else if(s.top() == '(' && str[i] == ')')
                      s.pop();
                     else return i;
      }
    }
    if (s.stempty())
      return -1;
    else return flag;
  }
