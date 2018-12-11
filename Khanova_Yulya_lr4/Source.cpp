#include <iostream>
#include <fstream>
#include <cstdlib>
#include "binTree.h"
#include <string>
using namespace std;
using namespace binTree_modul;
void displayBT(int b, int n)
{	// n  － уровень узла
	if (b != 0) {
		cout << ' ' << RootBT(b);
		if (!isNull(Right(b))) { displayBT(Right(b), n + 1); }
		else cout << endl; // вниз
		if (!isNull(Left(b))) {
			for (int i = 1; i <= n; i++) cout << "  "; // вправо
			displayBT(Left(b), n + 1);
		}
	}
	else {};
}

int build(string a, string b, int x) {
	int k;
	if (a == "") return 0;
	if (a.length() == 1) {
		k = ConsBT(a[0], 0, 0);
		return k;
	}
	if (x < 0) return 0;
	int flag = a.find(b[x]);
	if (flag < 0) {cout << "Error: некорректные данные!"<< endl;return 0; }
	k = ConsBT(b[x], build(a.substr(0, flag), b.substr(0, flag), flag-1), build(a.substr(flag + 1), b.substr(flag, x-1), x-1-flag));
	return k;
}

int main() {
	int ch;
	bool ex = true;
	string str1, str2;
	while(ex){
		cout << "Введите номер действия:"<< endl;
		cout << "0 - выход"<< endl;
		cout << "1 - ввод с клавиатуры"<< endl;
		cout << "2 - ввод из файла"<< endl;
		cin >> ch;
		switch(ch){
			case 0: {
				ex = false;
				break;
			}
			case 1:{
				cout<<"Введите ЛКП запись:"<< endl;
				cin >> str1;
				cout<<"Введите ЛПК запись:"<< endl;
				cin >> str2;
				if(str1.length()!= str2.length()){cout << "Error: строки разной длины!"<< endl;}
				else{
					int MyTree = build(str1, str2, str2.length() - 1);
					displayBT(MyTree, 1);
				}
				break;
			}
			case 2:{
				ifstream fin("input.txt");
				if (!fin) { cout << "File not open for reading!\n"; return 1; }
				cout << "Считывается ЛКП запись..." << endl;
				getline(fin, str1, '\n');
				cout << "Считывается ЛПК запись..." << endl;
				getline(fin, str2, '\n');
				if(str1.length()!= str2.length()){cout << "Error: строки разной длины!"<< endl;}
				else{
					int MyTree = build(str1, str2, str2.length() - 1);
					displayBT(MyTree, 1);
				}
				break;
			}
			default:{
				ex = false;
				cout << "Error of input!";
				break;
			}
		}
	}
	return 0;
}

