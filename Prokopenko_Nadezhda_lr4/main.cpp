/*Скобочное представление бинарного дерева (БД):
< БД > ::= < пусто > | < непустое БД >,
< пусто > ::= /,
< непустое БД > ::= ( < корень > < БД > < БД > )*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include "btree.h"
#include "queue.h"
using namespace std;
template <typename T>
void goriz(int index, Tree<T>** b, ofstream &fout)
{
    Queue <int> q;
    q.Put(index);//заношу в очередь индекс корневого элемента дерева
    while (!q.Empty())// пока очередь не пуста
    {
        index = q.Get();//Убираем из очереди индекс элемента дерева
        if(!b[index]->flag)
        fout << b[index]->GetInfo() << " ";
        if (!b[index]->isNull()) //если слева есть элемент то заносим его индекс в очередь
        {
            q.Put(b[index]->Left());
        }
        if (!b[index]->isNull())//если справа есть элемент то заносим его индекс в очередь
        {
            q.Put(b[index]->Right());
        }
    }
}


int main() {
    Tree<int> *b[100];
    for(int i=0; i<100;i++){
        b[i]= new Tree<int>();
    }
    int input;
    string file_name;
    fstream file;
    ofstream fout;
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
                enterBT(0, b, file);
                goriz(0, b, fout);
                cout << endl << "вывод ответа в файле\n";
            }
            file.close();
            fout.close();
            break;

        case 2:
            for(int i=0; i<100;i++){
                delete b[i];
            }
            return 0;

        default:
            cout << "Enter again.\n";
            break;
        }
    }
return 0;
}
