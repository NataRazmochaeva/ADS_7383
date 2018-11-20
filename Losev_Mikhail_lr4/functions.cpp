// Пример работы с АТД "Бинарное дерево" (в процедурно-модульной парадигме)
#include <iostream>
#include <fstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Btree.h"

using namespace std;
using namespace binTree_modul;

// вывод дерева как дерева
// более информативные ошибки

namespace Losev_Mikhail_lab4_namespace
{
	bool isTerminal( const char c )
	{
		return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
	}

	bool isSign( const char c )
	{
		return c == '-' || c == '+' || c == '*';
	}

	binTree MakeLeaf( base c )
	{
		return ConsBT(c, nullptr, nullptr);
	}

	void PrintBt(binTree b)
	{
		if (b == NULL)
			return; 

		if (b->lt == NULL && b->rt == NULL){
			cout << ' ' << b->info << ' ';
			return;
		}

		cout << "( ";
		PrintBt(b->lt);
		cout << ' ' << b->info << ' ';
		PrintBt(b->rt);
		cout << " )";
	}

	void SkipSpaces(istream &in)
	{
		base c;
		do 
		{
			c = in.peek();
			if (c == ' ')
				c = in.get();
		} while (c == ' ');
	}

	string TreeToForm(binTree b)
	{
		string str = "";
		if (b == NULL)
			return str; 

		if (b->lt == NULL && b->rt == NULL){
			str += ' ';
			str += b->info;
			str += ' ';
			return str;
		}

		str += "( ";
		str += TreeToForm(b->lt);
		str += ' ';
		str += b->info;
		str += ' ';
		str += TreeToForm(b->rt);
		str += " )";
	}

	binTree FormToTree(istream &in)
	{
		base c, sign;
		binTree left, right;

		SkipSpaces(in);
		c = in.get();

		if (isTerminal(c)) // если формула является терминалом
			return MakeLeaf(c); 

		if (c == '('){ // если формула имеет вид (<терм><знак><терм>)
			SkipSpaces(in);
			left = FormToTree(in); // первая формула 

			SkipSpaces(in);
			c = in.get();
			if (isSign(c))
				sign = c; // знак
			else { cerr << "error: sign expected" << endl; return NULL; }
			// если после первой формулы нет знака

			SkipSpaces(in);
			right = FormToTree(in); // вторая формула 

			SkipSpaces(in); // проверка скобок
			c = in.get(); 
			if (c != ')') { cerr << "error: ')' expected" << endl; return NULL; }
			// формула вида (<терм><знак><терм>) заканчивается скобкой

			left = ConsBT(sign, left, right); // делаем из знака и двух формул формулу
			return left;
		}
		else {
			if (isSign(c)) cerr << "error: extra sign in formula" << endl;
			else cerr << "error: external symbol if formula" << endl;
			return FormToTree(in);
		 	//return NULL;
		 } // формула является либо термом либо имеет вид (<терм><знак><терм>) и должна начинаться скобкой
	}


	void Transform(binTree b)
	{	// ((f1 * f2) + (f1 * f3)) -> (f1 * (f2 + f3))
		if (isEqual(b->lt->lt, b->rt->lt)){
			binTree f1, f2, f3;

			f1 = b->lt->lt;
			f2 = b->lt->rt;
			f3 = b->rt->rt;

			b->info = '*';
			b->lt = f1;
			b->rt->info = '+';
			b->rt->lt = f2;
			b->rt->rt = f3;

			return;
		}
		// ((f1 * f2) + (f3 * f1)) -> (f1 * (f2 + f3))
		if (isEqual(b->lt->lt, b->rt->rt)){
			binTree f1, f2, f3;

			f1 = b->lt->lt;
			f2 = b->lt->rt;
			f3 = b->rt->lt;

			b->info = '*';
			b->lt = f1;
			b->rt->info = '+';
			b->rt->lt = f2;
			b->rt->rt = f3;

			return;
		}
		// ((f2 * f1) + (f1 * f3)) -> (f1 * (f2 + f3))
		if (isEqual(b->lt->rt, b->rt->lt)){
			binTree f1, f2, f3;

			f1 = b->lt->rt;
			f2 = b->lt->lt;
			f3 = b->rt->rt;

			b->info = '*';
			b->lt = f1;
			b->rt->info = '+';
			b->rt->lt = f2;
			b->rt->rt = f3;

			return;
		}
		// ((f2 * f1) + (f3 * f1)) -> (f1 * (f2 + f3))
		if (isEqual(b->lt->rt, b->rt->rt)){
			binTree f1, f2, f3;

			f1 = b->lt->rt;
			f2 = b->lt->lt;
			f3 = b->rt->lt;

			b->info = '*';
			b->lt = f1;
			b->rt->info = '+';
			b->rt->lt = f2;
			b->rt->rt = f3;

			return;
		}
		
	}


	void ProcTree(binTree b)
	{
		if (b == NULL)
			return;
		ProcTree(b->lt);
		ProcTree(b->rt);

		if (b == NULL || 
			b->lt == NULL || b->lt->lt == NULL || b->lt->rt == NULL ||
			b->rt == NULL || b->rt->lt == NULL || b->rt->rt == NULL)
			return; // проверяем достаточное количество потомков узла

		if (b->lt->info != '*' || b->rt->info != '*' || b->info != '+')
			return; // проверяем знаки

		// не проверяем, что есть множитель, который можно вынести
		// Transform сама проверит это
		Transform(b);

	}

	string Translate(binTree b)
	{
		string str = "";

		if (b == NULL)
			return str;
		str += ' ';
		str += b->info;
		str += ' ';
		if (b->lt != NULL){
			str += ' ';
			str += Translate(b->lt);
			str += ' ';
		}
		if (b->rt != NULL){
			str += ' ';
			str += Translate(b->rt);
			str += ' ';
		}
	}

	void print(binTree f, int l)
	{
		if(f == nullptr){
			for(int i = 0; i < l; i++)
				cout << "\t";
			cout << '#' << endl;
			return;
		}

		print(f->rt, l+1);

		for(int i = 0; i < l; i++)
			cout << "\t";

		cout << f->info << endl;

		print(f->lt, l+1);
    }
}