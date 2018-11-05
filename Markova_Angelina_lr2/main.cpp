#include"list.h"

#define N 50

using namespace h_list;

int main()
{
    FILE* f;
    stringbuf exp;//входная последовательность символов
    int run = 1, pick;
    string list;
    int count;
    lisp l1;
    cout << "\033[34m\tЗдравствуйте!Выберите что вы хотите:\033[0m\n 1) Нажмите 1, чтобы считать с файла.\n 2) Нажмите 2, чтобы считать с консоли.\n 3) Нажмите 3, чтобы выйти из программы.\n" << endl;
    while (run) {
        cin >> pick;
        cin.ignore();
        switch(pick) {
        case (1): {
            ifstream infile("test.txt");
            if(!infile)cout<<"Входной файл не может быть открыт!"<<endl;
            else {
                read_lisp(l1, infile);
                cout << "Введённый список:" << endl;
                write_lisp(l1, cout);
                cout << endl;
                count = listDeepth(l1);
                cout << "Максимальный уровень вложенности: " << count << endl;
            }
            break;
        }
        case (2): {
            cout << "введите строку:" << endl;
            getline(cin, list);
            istream is_str(&exp);//проверка на строку
            exp.str(list);
            read_lisp(l1, is_str);
            count = listDeepth(l1);
            cout << "Максимальный уровень вложенности: " << count << endl;
            break;
        }
        case (3): {
            cout<<"\033[34m До свидания!\033[0m"<<endl;
            run=false;
            break;
        }
        default: {
            cout<<"\033[31m НЕВЕРНЫЙ ВВОД!\033[0m"<<endl;
            break;
        }
        }
    }
}

