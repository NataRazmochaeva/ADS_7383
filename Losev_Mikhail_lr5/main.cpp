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
	string str;
	BST <int> *b = NULL;

	rand_init();
	  
	cout << "Введите ключи: " << endl;
	getline(cin, str);

	if (str.size() == 0)
		cout << "Введенная строка пуста." << endl;
	else {
		cout << "Построение дерева... " << endl;
		b = b->build_tree(str);
		if (b)
			cout << "Дерево построено." << endl;
		else
			cout << "Дерево не построено." << endl;
	}

	

	cout << "Отрисовка дерева:" << endl;
	if (!b)
		cout << "Нет дерева." << endl;
	else
		b->printtree(b,0);

	cout << "Запись в файл..." << endl;
	int f = b->ascend_write_tree("out.txt", b);
	if (f == 0) cout << "Запись завершена." << endl;
	else cout << "Запись не сделана." << endl;


	b = b->Delete(b);
	str.clear();
	
	return 0;
}
