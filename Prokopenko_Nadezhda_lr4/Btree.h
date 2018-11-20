#include <iostream>
#include <fstream>
#define N 200
using namespace std;
struct Node 	//Структура дерева
{
	char info = 0;
	int lt; //индекс левого узла
	int rt; //индекс правого узла
};
typedef Node binTree[N];


bool isNull(binTree, int); //проверка на нулевой узел
char RootBT(int, binTree); //взятие корня поддерева
int Left(int, binTree); //взятие индекса левого узла
int Right(int, binTree); //взятие индекса правого узла
int ConsBT(char x, int lst, int rst, binTree, int); //добавление узла в список на базе вектора
void destroy(int, binTree); // удаление дерева
int enterBT(int, binTree, istream &input); // считывание данных из файла
int lastIndex = 0; //последний индекс массива

bool isNull(binTree b, int index) //проверка на нулевой узел
{
	return b[index].info == 0;
}

char RootBT(int index, binTree b) //взятие корня поддерева
{
	if (b == NULL)
	{
		cerr << "Error: RootBT(null) \n";
		exit(1);
	}
	else
		return b[index].info;
}

int Left(int index, binTree b) //взятие индекса левого узла
{
	if (b == NULL)
	{
		cerr << "Error: Left(null) \n";
		exit(1);
	}
	else
		return b[index].lt;
}

int Right(int index, binTree b) //взятие индекса правого узла
{
	if (b == NULL)
	{
		cerr << "Error: Right(null) \n";
		exit(1);
	}
	else
		return b[index].rt;
}
int ConsBT(char x, int lst, int rst, binTree b, int index) //добавление узла в список на базе вектора
{
	if (b != NULL)
	{
		b[index].info = x;
		b[index].lt = lst;
		b[index].rt = rst;
		if (lastIndex < rst)
			lastIndex = rst;
		return index;
	}
	else
	{
		cerr << "Memory not enough\n";
		exit(1);
	}
}

void destroy(int index, binTree b) // удаление дерева
{
	if (b != NULL)
	{
		destroy(b[index].lt, b);
		destroy(b[index].rt, b);
		delete b;
		b = NULL;
	}
}


int enterBT(int index, binTree b, istream &input) // считывание данных из файла
{
	char ch;
	int p, q;
	input >> ch;
	lastIndex = index;
	if (ch == '/')
	{
		b[index].info = 0;
		return index;
	}
	else
	{
		p = enterBT(++index, b, input);
		index = lastIndex;
		q = enterBT(++index, b, input);
		index = q;
		return ConsBT(ch, p, q, b, index - (q - p + 1));
	}
}
