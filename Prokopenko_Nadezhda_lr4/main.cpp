/*Скобочное представление бинарного дерева (БД):
< БД > ::= < пусто > | < непустое БД >,
< пусто > ::= /,
< непустое БД > ::= ( < корень > < БД > < БД > )*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "btree.h"
#include "queue.h"
#define TYPE int
using namespace std;
template <typename T>
void goriz(int index, Tree<TYPE>** b, ofstream &fout)
{
    Queue <TYPE> q;
    q.Put(index);//заношу в очередь индекс корневого элемента дерева
    while (!q.Empty())// пока очередь не пуста
    {
        index = q.Get();//Убираем из очереди индекс элемента дерева
        if (!b[index]->isNull()) //если есть элемент то заносим его индекс в очередь
        {
            fout << b[index]->GetInfo() << " ";
            q.Put(b[index]->Left());
            q.Put(b[index]->Right());
        }
    }
}


int main() {
    int input;
    string file_name;
    fstream file;
    ofstream fout;
    string c;
    while(true){
        cout << "------------------------------\n";
        cout << "Входные данные \n";
        cout << "1: из файла \n2: выход \n";
        cin >> input;
        switch (input)
        {
        case 1:
            cout << "Enter the name of the file:" << '\n';
            cin >> file_name;
            file.open(file_name, fstream::in);
            fout.open("output.txt");
            if (!file.is_open() || !fout.is_open()) {
                cout << "Error opening file.\n";
                break;
            }
            else{
                getline(file, c);
                Tree<TYPE> **b = new Tree<TYPE>*[c.length()];
                for(unsigned int i = 0; i < c.length();i++){
                    b[i]= new Tree<TYPE>();
                }
                stringstream s;
                s << c;
                enterBT(0, b, s);
                goriz<TYPE>(0, b, fout);
                cout << endl << "вывод ответа в файле\n";
                for(unsigned int i=0; i<c.length();i++){
                      delete b[i];
                }
           }
           file.close();
           fout.close();
           break;
        case 2:
           return 0;
        default:
           cout << "Enter again.\n";
           break;
        }
    }
return 0;
}
