#ifndef BTREE_H
#define BTREE_H
#include <iostream>
#include <fstream>
using namespace std;


template <typename T>
class Tree 	//Структура дерева
{
private:
    T info = 0;
    int lt; //индекс левого узла
    int rt; //индекс правого узла
public:
    bool flag = false;

    bool isNull(){
        return flag;
    }
    void SetInfo(T i){
        info = i;
    }
    void SetLeft(int l){
        lt = l;
    }
    void SetRight(int r){
        rt = r;
    }
    T GetInfo() //взятие корня поддерева
    {
        return info;
    }

    int Left() //взятие индекса левого узла
    {
        return lt;
    }

    int Right() //взятие индекса правого узла
    {
                return rt;
    }



};

template <typename T>
int enterBT(int index, Tree<T>** b, istream &input) // считывание данных из файла
{
    int cur = index;
    T ch;
    input >> ch;
    b[index]->SetInfo(ch);
    if (ch == 0)
    {
        b[cur]->flag = true;
        return index;
    }
    else
    {
        index++;
        (b[cur])->SetLeft(index);
        index = enterBT(index, b, input);
        index++;
        (b[cur])->SetRight(index);
        index = enterBT(index, b, input);
        return index;
    }
}
//template <typename T>
int enterBT(int index, Tree<char>** b, istream &input) // считывание данных из файла
{
    int cur = index;
    char ch;
    ch = input.get();
    //input >> ch;
    (b[cur])->SetInfo(ch);
    if (ch == '/')
    {
        b[cur]->flag = true;
        return index;
    }
    else
    {
        index++;
        (b[cur])->SetLeft(index);
        index = enterBT(index, b, input);
        index++;
        (b[cur])->SetRight(index);
        index = enterBT(index, b, input);
        return index;
    }
}

#endif // BTREE_H
