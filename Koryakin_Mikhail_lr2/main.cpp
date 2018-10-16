#include "func.hpp"

int main ( )
{
    filebuf file;
    string file_name;
    stringbuf exp;
    string temp_str;
    int run = 1;
    string k;
    int m;
    while(run){
        cout<<"Введите 1, если хотите ввести выражение из консоли, введите 2, если хотите ввести выражение из файла, 3 - выход из программы."<<endl;
        getline(cin, k);
        try{
        m=stoi(k);
        }
        catch(exception& a){
        cout<<"Fewfwe"<<endl;
        }
    try{
        switch(m){
            case 1:{
                cout << "введите list1:" << endl;
                getline(cin, temp_str);
                istream is(&exp);
                exp.str(temp_str);
                starter(is);
            break;
            }
            case 2:{
                    ifstream infile("a.txt");
                    getline(infile, temp_str);
                    istream is(&exp);
                    exp.str(temp_str);
                    starter(is);
                break;
        }
            case 3:
                cout<<"End!"<<endl;
                return 0;
            default:
                break;
        }
    }
    catch(exception& a){
        cout << a.what() << endl;
    }
    }
    return 0;
}

