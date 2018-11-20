#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include "Btree.h"
#include "Queue.h"
using namespace std;


int main() {
	binTree b;
	int input;
	string file_name;
	fstream file;
	cout << "------------------------------\n";
	cout << "Входные данные \n";
	cout << "1: из файла \n0: выход \n";
	cin >> input;
	ofstream fout("output.txt");
	if (!fout.is_open()) {
		cout << "Error opening file.\n";
	}
	while(input){
	switch (input)
	{
	case 1:
	cout << "Enter the name of the file:" << '\n';
	cin >> file_name;
	cin.ignore();
	file.open(file_name, fstream::in);
	if (!file.is_open()) {
		cout << "Error opening file.\n";
	}
	else{
		enterBT(0, b, file);
		goriz(0, b, fout);
		cout << endl << "вывод ответа в файле\n";}
		input=2;
		break;

	case 0:
			break;

	default:
	cout << "Enter again.\n";
	cin >> input;
		 break;
	}
	file.close(); fout.close();
}
return 0;
}


void goriz(int index, binTree b, ofstream &fout)
{
	Queue q;
	q.Put(index);//заношу в очередь индекс корневого элемента дерева
	while (!q.Empty())// пока очередь не пуста
	{
		index = q.Get();//Выдераем из очереди индекс элемента дерева
		fout << RootBT(index, b) << " ";
if (!isNull(b, Left(index, b))) //если слева есть элемент то заносим его индекс в очередь
{
	q.Put(Left(index, b));
}
if (!isNull(b, Right(index, b)))//если справа есть элемент то заносим его индекс в очередь
{
	q.Put(Right(index, b));
}
}
}
