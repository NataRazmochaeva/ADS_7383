/* Вариант 5
Правильная скобочная конструкция с тремя видами скобок определяется как
< текст > ::= < пусто > | < элемент > < текст >
< элемент > ::= < символ > | ( < текст > ) | [ < текст > ] | { < текст > }
где < символ > любой символ, кроме ( , ) , [ , ] , { , }.
Проверить, является ли текст, содержащийся в заданном файле F, правильной скобочной конструкцией;
если нет, то указать номер ошибочной позиции.*/

#include "stack.hpp"

int main() {

  string str;
  char k = 'a';
  Stack S;

  while (k != 'q'){

    cout<<"\nВыберите действие:"<<endl;
    cout<<"\t1 - Считать данные из файла."<<endl;
    cout<<"\t2 - Ввести данные вручную."<<endl;
    cout<<"\tq - Выход из программы."<<endl;

    cin>>k;
    switch (k) {
      case '1': {
        ifstream ifile("test.txt");
        getline(ifile, str);
        str.push_back('\0');
        len = str.size();
        ans = Check(str,S);
        if (ans == -1 && S.stempty()) cout<<"Это текст!" <<endl;
        else {
          cout<<"Это не текст!" <<endl;
          cout<<"Место ошибки: "<<ans<<endl;
        }
        break;
      }
      case '2': {
        getchar();
        getline(cin, str);
        str.push_back('\0');
        len = str.size();
        cout<<"len: "<<len<<endl;
        ans = Check(str,S);
        cout<<"ans: "<<ans<<endl;
        if (ans == -1 && S.stempty()) cout<<"Это текст!" <<endl;
        else {
          cout<<"Это не текст!" <<endl;
          cout<<"Место ошибки: "<<ans<<", "<<str[i]<<endl;
        }
        break;
      }
    }
  }
  return 0;
}
