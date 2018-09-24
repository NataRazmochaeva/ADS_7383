/* Вариант 21
    Построить синтаксический анализатор для понятия скобки.
    скобки::=квадратные | круглые
    квадратные::=[[кваратные](круглые)] | B
    круглые::=((круглые)[квадратные]) | A
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

bool Bracket(ifstream &infile);
bool Round(ifstream &infile, char ch);
bool Square(ifstream &infile, char ch);
void Error(short k);

int main() {

    int n;
    bool br;
    char data[1000];
    FILE *f;
    cout<<"\nВас приветствует анализатор скобок!\n\nВыберите способ ввода данных:\n1 - Для ввода данных с клавиатуры\n2 - Для использования данных из файла\n0 - Для выхода из программы"<<endl;
    cin>>n;

    switch(n) {

    case 0:

        return 0;

    case 1:
    {
        /*        f = fopen("test.txt", "w"); //создание файла
                cin»data;
                fputs(data, f);
                fclose(f);

                ifstream infile("test.txt");
                if(!infile) cout«"Входной файл не может быть открыт!"«endl;
                else {
                    br = Bracket(infile);
                    cout«endl;
                    if (br) cout«"Это скобки"«endl;
                    else cout«"Это НЕ скобки!"«endl;
                }
        */

        f = fopen("test.txt", "w");
        cin>>data;
        fputs(data,f);
        fclose(f);

        ifstream infile("test.txt");
        if(!infile) {
            cout<< "Входной файл не открыт!"<<endl;
            return 0;
        }

        br = Bracket(infile);
        infile.close();

        cout<<endl;

        if (br) cout<<"Это скобки!"<<endl;
        else cout<<"Это НЕ скобки!"<<endl;

        remove("test1.txt"); // удаление файла
        return 0;
    }
    case 2:
    {
        ifstream infile("test1.txt");
        if(!infile) {
            cout<< "Входной файл не открыт!"<<endl;
            break;
        }

        br = Bracket(infile);
        infile.close();

        cout<<endl;

        if (br) cout<<"Это скобки!"<<endl;
        else cout<<"Это НЕ скобки!"<<endl;

        return 0;
    }
    }
}

bool Square(ifstream &infile, char ch) {

// квадратные::=[[кваратные](круглые)] | B
// ch - текущий символ входной строки

    if (ch == 'B') {
        cout<<ch;
        return true;
    }

    else if (ch == '[') {
        cout<<ch;
        infile>>ch;
        if (ch == '[') {
            cout<<ch;
            infile>>ch;
            if (Square(infile,ch)) {
                infile>>ch;
                if (ch == ']') {
                    cout<<ch;
                    infile>>ch;
                    if (ch == '(') {
                        cout<<ch;
                        infile>>ch;
                        if (Round(infile, ch)) {
                            infile>>ch;
                            if (ch == ')') {
                                cout<<ch;
                                infile>> ch;
                                if (ch == ']') {
                                    cout<<ch;
                                    return true;
                                }
                                else {
                                    Error(2);
                                    return false;
                                }
                            }
                            else {
                                Error(4);
                                return false;
                            }
                        }
                        else return false;
                    }
                    else {
                        Error(3);
                        return false;
                    }
                }
                else {
                    Error(2);
                    return false;
                }
            }
            else return false;
        }
        else {
            Error(1);
            return false;
        }
    }
    else {
        return false;
    }
}

bool Round(ifstream &infile, char ch) {

// круглые::=((круглые)[квадратные]) | A
// ch - текущий символ входной строки

    if (ch == 'A') {
        cout<<ch;
        return true;
    }

    else if (ch == '(') {
        cout<<ch;
        infile>>ch;
        if (ch == '(') {
            cout<<ch;
            infile>>ch;
            if (Round(infile, ch)) {
                infile>>ch;
                if (ch == ')') {
                    cout<<ch;
                    infile>>ch;
                    if (ch == '[') {
                        cout<<ch;
                        infile>>ch;
                        if (Square(infile, ch)) {
                            infile>>ch;
                            if (ch == ']') {
                                cout<<ch;
                                infile>>ch;
                                if (ch == ')') {
                                    cout<<ch;
                                    return true;
                                }
                                else {
                                    Error (4);
                                    return false;
                                }
                            }
                            else {
                                Error(2);
                                return false;
                            }
                        }
                        else return false;
                    }
                    else {
                        Error(1);
                        return false;
                    }
                }
                else {
                    Error(4);
                    return false;
                }
            }
            else return false;
        }
        else {
            Error(3);
            return false;
        }
    }
    else {
        //      Error(3);
        return false;
    }
}

bool Bracket(ifstream &infile) {

// скобки::= квадратные | круглые

    char ch;

    if (infile>>ch) {
        if (Square(infile, ch)) return true;
        else if (Round(infile, ch)) return true;
        else return false;
    }
    else Error(0);

}

void Error(short k) {

    cout<< endl << "Ошибка №" << k << ": ";

    switch(k) {
    case 0:
        cout<< "Пустая входная строка." <<endl;
        break;
    case 1:
        cout<< "Не хватает '['." <<endl;
        break;
    case 2:
        cout<< "Не хватает ']'." <<endl;
        break;
    case 3:
        cout<< "Не хватает '('."<<endl;
        break;
    case 4:
        cout<< "Не хватает ')'." <<endl;
        break;
    }
    return;
}
