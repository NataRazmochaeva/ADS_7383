/* Вариант 21
    Построить синтаксический анализатор для понятия скобки.
    скобки::=квадратные | круглые
    квадратные::=[[кваратные](круглые)] | B
    круглые::=((круглые)[квадратные]) | A
*/

#include <iostream>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <cctype>
#define N 1000
using namespace std;

void File(ifstream &infile, char ch);
bool Bracket(ifstream &infile, char ch);
bool Round(ifstream &infile, char ch, int &err);
bool Square(ifstream &infile, char ch, int &err);
void Error(short k);

int main() {

    int n;
    char ch;
    char data[N];
    FILE *f;
    cout<<"\nВас приветствует анализатор скобок!\n\nВыберите способ ввода данных:\n1 - Для ввода данных с клавиатуры\n2 - Для использования данных из файла\n0 - Для выхода из программы"<<endl;
    cin>>n;

    switch(n) {

    case 0:

        return 0;

    case 1: {

        f = fopen("test1.txt", "w");
        cin>>data;
        fputs(data,f);
        fclose(f);

        ifstream infile("test1.txt");
        File(infile, ch);
        remove("test1.txt");
        return 0;
    }

    case 2: {

        ifstream infile("test.txt");
        File(infile, ch);
        return 0;
    }
    }
}

void File(ifstream &infile, char ch) {

    FILE *file;

    if(!infile) {
        cout<< "Входной файл не открыт!"<<endl;
    }

    file = fopen("tmp.txt", "w");
    ofstream out("tmp.txt");

    while (infile>>ch) {
        while (isspace(ch)) infile>>ch;
        out<<ch;
    }

    fclose(file);

    ifstream inf("tmp.txt");

    if (Bracket(inf, ch) && !(inf>>ch)) cout<<"\nЭто скобки!"<<endl;
    else cout<<"\nЭто НЕ скобки!"<<endl;
//    remove("tmp.txt");
}

bool Bracket(ifstream &infile, char ch) {

// скобки::= квадратные | круглые

    int err = 0, err1;

    infile>>ch;

    if (!infile>>ch) {
        Error(err);
        return false;
    }

    if (Square(infile, ch, err)) return true;
    else { // это не квадратные скобки
        err1 = err; // в err1 записана ошибка из Square

        if (Round(infile, ch, err)) return true;
        else {
            Error(err);    // ошибка в круглых скобках
            return false;
        }
        Error(err1); // ошибка в квадратных скобках
        return false;
    }
}

bool Square(ifstream &infile, char ch, int &err) {

// квадратные::=[[кваратные](круглые)] | B
// ch - текущий символ входной строки

    if (ch == 'B') {
        cout<<ch;
        return true;
    }

    if (ch != '[') {
        err = 6;
        return false;
    }

    cout<<ch;
    infile>>ch;

    if (ch != '[') {
        err = 1;
        return false;
    }

    cout<<ch;
    infile>>ch;

    if (!Square(infile, ch, err)) return false;

    infile>>ch;

    if (ch != ']') {
        err = 2;
        return false;
    }

    cout<<ch;
    infile>>ch;

    if (ch != '(') {
        err = 3;
        return false;
    }

    cout<<ch;
    infile>>ch;

    if (!Round(infile, ch, err)) return false;

    infile>>ch;

    if (ch != ')') {
        err = 4;
        return false;
    }

    cout<<ch;
    infile>>ch;

    if (ch != ']') {
        err = 2;
        return false;
    }

    cout<<ch;
    return true;
}

bool Round(ifstream &infile, char ch, int &err) {

// круглые::=((круглые)[квадратные]) | A
// ch - текущий символ входной строки

    if (ch == 'A') {
        cout<<ch;
        return true;
    }

    if (ch != '(') {
        err = 7;
        return false;
    }

    cout<<ch;
    infile>>ch;

    if (ch != '(') {
        err = 3;
        return false;
    }

    cout<<ch;
    infile>>ch;

    if (!Round(infile, ch, err)) return false;

    infile>>ch;

    if (ch != ')') {
        err = 4;
        return false;
    }

    cout<<ch;
    infile>>ch;

    if (ch != '[') {
        err = 1;
        return false;
    }

    cout<<ch;
    infile>>ch;

    if (!Square(infile, ch, err)) return false;

    infile>>ch;

    if (ch != ']') {
        err = 2;
        return false;
    }

    cout<<ch;
    infile>>ch;

    if (ch != ')') {
        err = 4;
        return false;
    }

    cout<<ch;
    return true;
}

void Error(short k) {

    cout<< endl <<"\nОшибка №"<< k << ": ";

    switch(k) {
    case 0:
        cout<<"Пустая входная строка.";
        break;
    case 1:
        cout<<"Не хватает '['.";
        break;
    case 2:
        cout<<"Не хватает ']'.";
        break;
    case 3:
        cout<<"Не хватает '('.";
        break;
    case 4:
        cout<<"Не хватает ')'.";
        break;
    case 5:
        cout<<"Неправильная последвательность!";
        break;
    case 6:
        cout<<"Не хватает '[' или 'B'.";
        break;
    case 7:
        cout<<"Не хватает '(' или 'A'.";
        break;
    }
    return;
}
