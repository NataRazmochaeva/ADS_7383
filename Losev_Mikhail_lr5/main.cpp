#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <cstdlib> // чтобы юзать rand
#include "bst_interf.h"
#include "functions.h"


using namespace std;
using namespace losev_BST;
using namespace losev_functions;


 int main()
 {
 	int a = 0;
	char* tok;
	string str;
	BST <int> *b = NULL;

	rand_init();
	  
	cout << "Введите ключи: " << endl;
	getline(cin, str);

	if (!tok)
		cout << "Введенная строка пуста." << endl;
	else {
		cout << "Построение дерева... " << endl;
		b = build_tree(str);
		if (b)
			cout << "Дерево построено." << endl;
		else
			cout << "Дерево не построено." << endl;
	}
	

	cout << "Отрисовка дерева:" << endl;
	printtree(b,0);

	cout << "Запись в файл..." << endl;
	int f = ascend_write_tree("out.txt", b);
	if (f == 0) cout << "Зпаись завершена." << endl;
	else cout << "Зпаись не сделана." << endl;

	b = b->Delete(b);
	str.clear();
	
	return 0;
}
