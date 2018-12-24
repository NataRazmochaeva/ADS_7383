#include <fstream>
#include <iostream>
#include <cstdlib>
#include "stack.h"

using namespace std;
namespace stack
{
	struct Stack::node
	{
		base *hd;
		node *tl;
		node() //constructor
		{
			hd = NULL;
			tl = NULL;
		}
	};

base Stack::top()
{
	if (topOfStack == NULL)
	{
		cerr << "Error: top(null) \n";
		exit(1);
	}
	else
		return *topOfStack->hd;
}

void Stack::pop()
{
	if (topOfStack == NULL)
	{
		cerr << "Error: pop(null) \n";
		exit(1);
	}
	else
	{
		node *oldTop = topOfStack;
		topOfStack = topOfStack->tl;
		delete oldTop->hd;
		delete oldTop;
	}
}

base Stack::pop2()
{
	if (topOfStack == NULL)
	{
		cerr << "Error: pop(null) \n";
		exit(1);
	}
	else
	{
		node *oldTop = topOfStack;
		base r = *topOfStack->hd;
		topOfStack = topOfStack->tl;
		delete oldTop->hd;
		delete oldTop;
		return r;
	}
}

void Stack::push(const base &x)
{
	node *p;
	p = topOfStack;
	topOfStack = new node;
	if (topOfStack != NULL)
	{
		topOfStack->hd = new base;
		*topOfStack->hd = x;
		topOfStack->tl = p;
	}
	else
	{
		cerr << "Memory not enough\n";
		exit(1);
	}
}

bool Stack::isNull()
{
	return (topOfStack == NULL);
}

void Stack::destroy()
{
	while (topOfStack != NULL)
	{
		pop();
	}
}

} // end of namespace stack
