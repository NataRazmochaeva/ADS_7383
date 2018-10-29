#include "func.hpp"



    int main ()
    {
        string a;
        int run = 1;
        int m;
        while(run){
            cout<<"Введите 1, если хотите ввести выражение из консоли, введите 2, если хотите ввести выражение из файла, 3 - выход из программы."<<endl;
            cin>>m;
            cin.ignore();
            switch(m){
                case 1:{
                    cout << "Введите выражение:" << endl;
                    getline(cin, a);
                    a=except(a);
                    if (a=="null")
                        cout<<"Недопустимый символ ',' "<<endl;
                    else
                        forstack(a);
                break;
                }
                case 2:{
                        ifstream infile("input.txt");
                        if(!infile){
                            cout<<"File not open for reading"<<endl;
                            break;
                        }
                        getline(infile, a);
                        a=except(a);
                        forstack(a);
                        break;
                        }
                case 3:
                    cout<<"End!"<<endl;
                    return 0;
                default:
                    break;
            }
        }
        return 0;
}

