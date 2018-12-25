#pragma once
typedef char base;

struct Node
{
  base info = '\0';
  int lt; //индекс левого узла
  int rt; //индекс правого узла
};
typedef Node *binTree;
bool isNull(binTree b, int i); //проверка на нулевой узел
char RootBT(int i, binTree b); //взятие корня поддерева
int Left(int i, binTree b); //взятие индекса левого узла
int Right(int i, binTree b); //взятие индекса правого узла
int ConsBT(char x, int lst, int rst, binTree b, int i); //добавление узла в список на базе вектора
int createBT(base* arrayKLP, base* arrayLKP, int &i, binTree b, int size);
void printBT(binTree b, int i, int n); //печать дерева
void LPK(binTree b, int i); //обход ЛПК
