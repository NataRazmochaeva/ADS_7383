#include <iostream>
#include <fstream>
#include "stack.h"
#include <sstream>
#include <ctype.h>

using namespace std;
using namespace stack;
void calc(stringstream &xstream, Stack *op);

bool read_expr(stringstream &xstream, Stack *op)
{
  bool res = false;
  char c;

  do
  xstream >> c;
  while (c == ' ');

  if (isdigit(c))
  { // если является цифрой
    op->push(c - '0'); //записываем в стек digit
    res = true;
  }
  else if ((c == 'M') || (c == 'm'))
  { //является обозначением операции min или max
    if (c == 'M') //является max
      op->push(-1); //записываем в стек operation - 1
    else if (c == 'm') //является min
      op->push(-2); //записываем в стек operation - 2

    do xstream >> c; while (c == ' ');

    if (c != '(')
    {//если очередной символ НЕ окрывающая скобка - выход
      cout << "\n! - Error1\n";
      exit(1);
    }
    res = read_expr(xstream, op); //рекурсивный вызов
    if (!res)
    {//если предыдущее выражение НЕ формула - выход
      cout << "\n! - Error2\n";
      exit(1);
    }

    do xstream >> c; while (c == ' ');

    if (c != ',')
    {//если очередной символ НЕ запятая - выход
      cout << "\n! - Error3\n";
      exit(1);
    }

    res = read_expr(xstream, op);//рекурсивный вызов
    if (!res)
    {//предыдущее выражение НЕ формула - выход
      cout << "\n! - Error4\n";
      exit(1);
    }

    do xstream >> c; while (c == ' ');

    if (c == ')' && !(op->isNull())) //если очередной символ - закрывающая скобка и стек не пуст, вычисление
    {  
      res = true;
      calc(xstream, op); //вычисление
    }
    if (c != ')')
    {  //если очередной символ НЕ закрывающая скобка - выход
      cout << "! - Error5\n";
      exit(1);
    }
  }
  else
  {
    cout << "\n! - Error6\n";
    exit(1);
  }

return res;
}

void calc(stringstream &xstream, Stack *op)
{
  base a = op->pop2();
  base b = op->pop2();
  int fun = op->pop2();
  cout << fun << endl;
  base res;
  if (a == b)
  {
    cout << "Цифры равны\n";
    res = a;
  }
  else
  {
    if (fun == -1)//max
    {
      (a > b) ? res = a : res = b;
      cout << "M( " << a << " , " << b << " ) = " << res << endl;
    }
    else if (fun == -2)//min
    {
      (a < b) ? res = a : res = b;
      cout << "m( " << a << " , " << b << " ) = " << res << endl;
    }
  }
  op->push(res);
  cout << endl;
}

int main()
{
  stringstream xstream;
  bool b = 1;
  Stack operation; //стек для операций M(max) или m(min) из формулы
  //Stack digit; //стек для цифр из формулы
  char x;
  char str[100];
  int c = 0;
  while(c != 3)
  {
    cout << "Введите 1, если хотите ввести выражение с клавиатуры.\n"
            "Введите 2, если еспользовать выражение из файла test.txt.\n"
            "Введите 3, если хотите закончить работу." << endl;
    cin >> c;
    switch(c)
    {
      case 1:
        {
          cout << "Введите выражение: \n";
          cin.get();
          cin.getline(str, 1000);
          xstream << str;
          read_expr(xstream, &operation);
          break;
        }
      case 2:
        {
          ifstream outfile;
          outfile.open("test.txt");
          if (!outfile)
          {
            cout << "Входной файл не открыт!\n";
            b = 0;
            break;
          }
          outfile.read(str, 1000);
          outfile.close();
          xstream << str;
          read_expr (xstream, &operation);
          break;
        }
      case 3:
        {
          b=0;
          break;
        }
      default:
        {
          cout << "Введите верное число\n";
          break;
        }
    }
    if(b)
    {
      base result = operation.top();
      cout << "Результат работы программы: \n";
      cout << result;
      cout << endl;
    }
}
operation.destroy();
return 0;
}
