#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;
#define N 500

bool Parameter_list(ifstream &infile, bool q = false);
bool Parameter(ifstream &infile, char s);
bool Name(ifstream &infile, char s);
void Error(short k);
void Output(ifstream &infile);
void SkipSpace(ifstream &infile);

int main()
{
    char str[N];
    bool ex = true;
    FILE* f;
    while(ex) {
        cout << "Анализатор поятия список_парамептров:" << endl;
        cout << "1 - Ввод из файла" << endl;
        cout << "2 - Ввод с клавиатуры" << endl;
        cout << "3 - Выход из программы" << endl;
        cout << "Введите номер из меню: ";
        int ch;
        cin >> ch;
        switch(ch) {
        case 1: {
            ifstream infile("test.txt");
	    Output(infile);
            break;
        }
        case 2: {
            f=fopen("test1.txt", "w");
            cin>>str;
            fputs(str,f);
            fclose(f);
            ifstream infile("test1.txt");
	    Output(infile);
            remove("test1.txt");
            break;
        }
        case 3: {
            ex = false;
            break;
        }
        default: {
            ex = false;
            cout << "Ошибка ввода!" << endl;
            break;
        }
        }
    }
    return 0;
}

void Output(ifstream &infile) {
    if(!infile) {
        cout << "Входной файл не открыт!" << endl;
    }
    bool b = Parameter_list(infile);
    cout << endl;
    if(b) cout << "Это список параметров!" << endl;
    else cout << "Это НЕ список параметров!" << endl;
}

void SkipSpace(ifstream &infile) {
    string str;
    int i =0;
    getline(infile,str);
    for(i=0; i<str.length(); i++) {
        if(str[i] == ' '){
            str.erase(i,1);
	}
    }
    for(int i = 0; i<str.length(); i++){
	infile.putback(str[i]);
	}
}

bool Parameter(ifstream &infile, char s) {
    bool isname=false;
    if(isdigit(s) && infile >> s) {
        cout << s;
        if(isdigit(s)) {
            return true;
        }
        else {
            Error(6);
            return false;
        }
    }
    else if (s=='(' && infile >> s) {
        cout << s;
        isname= Name(infile, s);
        if(isname) {
            if(infile>>s) {
                if(s==')') {
                    cout << s;
                    return true;
                }
                else if(s==',') {
                    cout << s;
                    infile >> s;
                    cout << s;
                    isname=Name(infile, s);
                    if(isname) return true;
                }
            }
        }
        else {
            Error(5);
            return false;
        }
    }
    else {
        Error(5);
        return false;
    }
}

bool Name(ifstream &infile, char s) {
    bool isprm=false;
    for (int i =0; i < 3; i++)
    {
        if(isalpha(s) && infile >> s) {
            cout << s;
        }
        else {
            Error(3);
            return false;
        }
    }
    if(s=='=' && infile >> s) {
        cout << s;
        isprm=Parameter(infile, s);
        if(isprm) {
            return true;
        }
    }
    else {
        Error(4);
        return false;
    }
}
bool Parameter_list(ifstream &infile, bool q) {
    char s;
    bool list = false;
    if(infile >> s)
    {
        cout << s;
        if (isalpha(s)) {
            list = Name(infile, s);
            if(infile >>s)
                cout << s;
            Parameter_list(infile, true);
        }
        else if (s == ',') Parameter_list(infile, true);
        else Error(2);
        infile >> s;
    }
    else if (q == false) Error(0);
    return list;
}
void Error(short k) {
    cout << endl << "err#" << k;
    switch (k) {
    case 0:
        cout << "!-Пустая входная строка" << endl;
        break;
    case 1:
        cout << "!-Лишние симоволы во входной строке" << endl;
        break;
    case 2:
        cout << "!-Недопустимый начальный символ" << endl;
        break;
    case 3:
        cout << "!-Не имя" << endl;
        break;
    case 4:
        cout << "!-Нет знака =" << endl;
        break;
    case 5:
        cout << "!-Нет закрывающей скобки" << endl;
        break;
    case 6:
        cout << "!-Не цифра" << endl;
        break;
    default:
        cout << "!-... ";
        break;
    };
}
