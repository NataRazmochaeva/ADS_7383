#include <iostream>
#include <cstdlib>
using namespace std;
struct Nod 		//Структура для очереди
{
	char znach;
	Nod *Next;
};

class Queue		//Очередь
{
	Nod *First, *Last;
	int kol;
public:
	Queue() :First(NULL), Last(NULL) { kol = 0; }; //конструкор
	~Queue(); //деструктор
	void Put(char x);//добавление нового элемента в конец очереди
	char Get();//возвращение значения первого элемента и его удаление
	int Kol();//возвращает количество элементов в очереди
	bool Empty();//возвращает True если очередь пуста
};
void Queue::Put(char x) //добавление нового элемента в конец очереди
{
	Nod *temp = new Nod;//создание указателя на структуру Nod и выделение под него памяти
	temp->znach = x;
	temp->Next = NULL;
	if (First == NULL)
	{
		First = temp;
		Last = temp;
		kol++;
	}
	else
	{
		Last->Next = temp;
		Last = temp;
		kol++;
	}
};

Queue::~Queue() //удаление всех эелементов
{
	Nod *temp;
	kol = 0;
	while (First != NULL)
	{
		Nod *temp;
		temp = First;
		First = First->Next; //переходим на следующий элемент
		delete temp;
	}
};

char Queue::Get() //возвращение значения первого элемента и его удаление
{
	if (First == NULL) { printf("Очередь пуста \n"); exit(1); }
	Nod *temp;
	char x;
	x = First->znach;
	temp = First;
	First = First->Next;
	delete temp;
	kol--;
	return x;
};

int Queue::Kol() //возвращает количество элементов в очереди
{
	return kol;
};

bool Queue::Empty() //возвращает True если очередь пуста
{
	return First == NULL;
};
