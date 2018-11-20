// Пример работы с АТД "Бинарное дерево" (в процедурно-модульной парадигме)
#include <iostream>
#include <fstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Btree.h"
#include "functions.h"


using namespace std ;
using namespace binTree_modul;
using namespace Losev_Mikhail_lab4_namespace;

int main () 
{
	string formula;
	binTree b;
	
	cout << "Водите формулу: ";
	b = FormToTree(cin);
	cout << "Дерево-формула построено:" << endl;
	formula = TreeToForm(b);
	cout << formula << endl;

	cout << "Преобразование дерева-формулы..." << endl;
	ProcTree(b);
	formula = TreeToForm(b);
	cout << formula << endl;

	cout << "Перевод дерева-формулы в префиксную форму..." << endl;
	formula = Translate(b);
	cout << formula << endl;

	cout << "Визуализация дерева-формулы: " << endl;
	print(b, 0);

	destroy (b);
	cout << endl;
	return (0);
}