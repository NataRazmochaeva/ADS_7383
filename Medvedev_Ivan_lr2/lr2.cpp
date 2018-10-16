#include "list.h"
int start( lisp& s1, lisp& s2, istream &astr){
    char ch;
    read_lisp (s1, astr);
    cout << "введен list1: " << endl;
    write_lisp (s1);
    cout << endl;
    if(astr >> ch){
        cout<<"! Лишние символы !"<<endl;
        return 0;
    }
    cout << "Список перевернут: " << endl;
    s2 = rev (s1, NULL);
    write_lisp (s2);
    cout << endl;
    delete(s2);
    delete (s1);
    return 0;


}


int main ( ){
    char forSwitch;
    stringbuf exp;
    string list;
    char ch;
    lisp s1, s2;
    while (1){
        cout << "Нажмите 1 для ввода с клавиатуры, 2 для ввода с файла, 0 для выхода"<<endl;
        cin>>forSwitch;
        cin.ignore();
        switch(forSwitch){
            case '1':{
                cout << "введите list1:" << endl;
                getline(cin, list);
                istream str(&exp);
                exp.str(list);
                start(s1,s2,str);
                break;
            }
             case '2':{
                ifstream infile("list.txt");
                 getline(infile, list);
                istream str(&exp);
                exp.str(list);
                start(s1,s2,str);
                break;
            }
            case '0':{
                cout<<"Bye!"<<endl;
                return 0;
            }
            default:{
                cout<<"НЕВЕРНЫЙ ВВОД!"<<endl;
                break;
            }
       }

    }


}
