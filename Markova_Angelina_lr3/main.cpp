#include "fun.h"
using namespace STACK;

int main() {
    string expression, postfix;
    int run = 1, check;
    cout << "\033[34m\tЗдравствуйте!Выберите что вы хотите:\033[0m\n 1) Нажмите 1, чтобы считать с файла.\n 2) Нажмите 2, чтобы считать с консоли.\n 3) Нажмите 3, чтобы выйти из программы.\n" << endl; 
    while(run) {
        cin >> check;
        cin.ignore();
        switch(check) {
        case (1): {
            ifstream infile("test.txt");
            if(!infile)cout<<"Входной файл не может быть открыт!"<<endl;
            else { 
                getline(infile, expression);
                postfix = InfixToPostfix(expression);
                cout<<"Output = "<<postfix<<"\n";
            }
            break;
        }
        case(2): {
            cout<<"Enter Infix Expression \n";
            getline(cin,expression);
            postfix = InfixToPostfix(expression);
            cout<<"Output = "<<postfix<<"\n";
            cout<<" Введите следующую команду:\n";
	    break;
        }
        case(3): {
            cout<<"End!"<<endl;
            run = 0;
            break;
        }
        default: {
            cout<<"Incorrect pick!"<<endl;
            run = 0;
            break;
        }
    }
    }
    return 0;
}
