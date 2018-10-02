/* Вариант 13: Построить синтаксический анализатор для понятия скобки
   скобки::=А|скобка скобки
   скобка::=(В скобки)

   упрощение: Скобки ::= А|(В скобки) скобки
*/

#include <iostream>
#include <fstream>
#include <iomanip>

#define N 500

using namespace std;

bool Brackets(ifstream &infile, char sim);
void Error(short s); //символ короткой длины, короткий "int"

int main() {
    bool run=true;
    char arr[N], sim;
    FILE* f;
    int pick;
    cout<<"\033[34m\tЗдравствуйте! Я анализатор скобок, выберите что вы хотите:\033[0m\n 1) Нажмите 1, чтобы проверить скобки в файле.\n 2) Нажмите 2, чтобы ввести скобки в консоль.\n 3) Нажмите 3, чтобы выйти из программы.\n";

    while(run) {
        cin>>pick; //выбор

        switch(pick) {

        case 1: {
            ifstream infile("test.txt");
            if(!infile)cout<<"Входной файл не может быть открыт!"<<endl;
            else {
                if(Brackets(infile, sim) && !(infile>>sim)) {
                    cout<<endl;
                    cout<<"\033[32mЭТО СКОБКИ\033[0m"<<endl;
                }
                else {
                    cout<<endl;
                    cout<<"\033[31mНет, это не скобки\033[0m"<<endl;
                }
            }
            break;
        }

        case 2: {
            f=fopen("test1.txt", "w"); //создание файла
            cin>>arr;
            fputs(arr,f);
            fclose(f);
            ifstream infile("test1.txt");
            if(!infile)cout<<"Входной файл не может быть открыт!"<<endl;
            else {
                if(Brackets(infile, sim) && !(infile>>sim)) {
                    cout<<endl;
                    cout<<"\033[32mЭТО СКОБКИ\033[0m"<<endl;
                }
                else {
                    cout<<endl;
                    cout<<"\033[31mНет, это не скобки\033[0m"<<endl;
                }
            }
            remove("test1.txt"); // удаление файла
            break;
        }

        case 3: {
            run=false;
            break;
        }

        default: {
            run=false;
            cout<<"\033[31mНекорректный выбор!\033[0m\n"<<endl;
            break;
        }
        }
    }

    cout<<"\033[34mДо свидания!\033[0m\n"<<endl;
    return 0;
}


bool Brackets(ifstream &infile, char sim) {
    infile>>sim;
    if(sim=='A') {
        cout<<sim;
        return true;
    }
    if(sim=='(') {
        cout<<sim;
        infile>>sim;
    }
    else return false;
    if(sim=='B') {
        cout<<sim;
        if(Brackets(infile, sim)) infile>>sim;
        else {
            Error(3);
            return false;
        }
        if(sim==')') cout<<sim;
        else {
            Error(4);
            return false;
        }
        if(Brackets(infile, sim)) return true;
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



void Error(short s) {
    cout<<endl<<"Ошибка №"<<s<<endl;

    switch(s) {
    case 2:
        cout<<"Не хватает 'B'"<<endl;
        break;
    case 3:
        cout<<"Нет скобок"<<endl;
        break;
    case 4:
        cout<<"Не хватает ')'"<<endl;
        break;
    }
}

