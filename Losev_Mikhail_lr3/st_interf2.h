
#ifndef ST_INTERF2_H_INCLUDED
#define ST_INTERF2_H_INCLUDED

// Интерфейс АТД "Стек" (ссылочная реализация в динамической памяти)с шаблоном класса
// И интерфейс, и реализация в одном заголовочном файле 

#include <iostream>
#include <cstdlib>

using namespace std;

namespace st_modul2
{

//-------------------------------------
	template <class Elem>
	class Stack 
	{
		private:
		struct node 
		{ //
			Elem *hd;
			node *tl;
			// constructor
			node ()
				{
					hd = NULL; 
					tl = NULL; 
				};
		};// end node
	
		node *topOfStack;

		public:
		Stack ()
			{ topOfStack = NULL;
			}//;
		
//-------------------------------------
	Elem top (void) //
	{// PreCondition: not null	
		if (topOfStack == NULL) { cerr << "Error: top(null) \n"; exit(1); }
		else return *topOfStack->hd;
	}
//-------------------------------------
	void pop (void)//
	{// PreCondition: not null
		if (topOfStack == NULL) { cerr << "Error: pop(null) \n"; exit(1); }
		else 
		{	node *oldTop = topOfStack;
			topOfStack = topOfStack->tl;
			delete oldTop->hd;
			delete oldTop;
		}
	}
//-------------------------------------
	Elem pop2(void)//
	{// PreCondition: not null
		if (topOfStack == NULL) { cerr << "Error: pop(null) \n"; exit(1); }
		else 
		{	node *oldTop = topOfStack;
			Elem r = *topOfStack->hd;
			topOfStack = topOfStack->tl;
			delete oldTop->hd;
			delete oldTop;
			return r;
		}
	}
//-------------------------------------
	void push (const Elem &x)//
	{	node *p;
		p = topOfStack;
		topOfStack = new node; 
		if ( topOfStack != NULL)	{ 	
			topOfStack->hd = new Elem;
			*topOfStack->hd = x;
			
			topOfStack->tl = p;
		}
		else {cerr << "Memory not enough\n"; exit(1);}
	}

	bool  two_numbers( void )
	{ // если последние два тега соответствуют числам, то возвращается true
		if ((*topOfStack).tl == NULL)
			return 0;
		return (*(*topOfStack).hd && *(*topOfStack).tl->hd);

	}
//-------------------------------------
	bool isNull(void)//
	{	return (topOfStack == NULL) ;
	}
//-------------------------------------
	void destroy (void)//
	{	while ( topOfStack != NULL) {
			pop();	
		}
	}
	};
} 

#endif