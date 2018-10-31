#include <iostream>
#include <cstdlib>
#include <cstring>
#include "st_interf1.h"
#include <fstream>
using namespace std;

namespace st_modul1
{
	struct Stack::node {//
		base *hd;
		node *tl;
		node()
		{
			hd = NULL; tl = NULL;
		}
	};// end node
	  //-------------------------------------
	base Stack::top(void)
	{// PreCondition: not null
		if (topOfStack == NULL) { cerr << "Error: top(null) \n"; exit(1); }
		else return *topOfStack->hd;
	}
	//-------------------------------------
	void Stack::pop(void)
	{// PreCondition: not null
		if (topOfStack == NULL) { cerr << "Error: pop(null) \n"; exit(1); }
		else
		{
			node *oldTop = topOfStack;
			topOfStack = topOfStack->tl;
			delete oldTop->hd;
			delete oldTop;
		}
	}
	//-------------------------------------
	base Stack::pop2(void)
	{// PreCondition: not null
		if (topOfStack == NULL) { cerr << "Error: pop(null) \n"; exit(1); }
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
	//-------------------------------------
	void Stack::push(const base &x)
	{
		node *p;
		p = topOfStack;
		topOfStack = new node;
		if (topOfStack != NULL) {
			topOfStack->hd = new base;
			*topOfStack->hd = x;
			topOfStack->tl = p;
		}
		else { cerr << "Memory not enough\n"; exit(1); }
	}
	//-------------------------------------
	bool Stack::isNull(void)
	{
		return (topOfStack == NULL);
	}
	//-------------------------------------
	void Stack::destroy(void)
	{
		while (topOfStack != NULL) {
			pop();
		}
	}
}

bool isSign(char* c) {

	return !strcmp(c, "+\0") || !strcmp(c, "-\0") || !strcmp(c, "*\0") || !strcmp(c, "^\0");
}

char* postfixToInfix() {
	st_modul1::Stack stack;
	string c;
	int i=0;
	char* str = new char[2];
	char* res = new char[30];
	char* operand1 = new char[30];
	char* operand2 = new char[30];
	char* ptr=new char[30];
	ifstream file("postfix.txt");
	if (!file.is_open()) {
		cout << "Error opening file.\n";
		exit(1);
	}
	else {
		getline(file, c);
	c[c.length()]='\0';
	while (i!=c.length()) {
			st_modul1:: base *p = (st_modul1::base*)malloc(30 * sizeof(st_modul1:: base));
    *p = (st_modul1::base)malloc(30 * sizeof(char));
  	while(c[i] == ' ')
			i++;
		res[0] = '\0';
		str[0] = c[i];
		str[1] = '\0';
		if (isSign(str)) {
			operand2 = stack.pop2();
			operand1 = stack.pop2();
			if(!strcmp(str, "+\0") || !strcmp(str, "-\0")){
			strcat(res, "(");
			strcat(res, operand1);
			strcat(res, str);
			strcat(res, operand2);
			strcat(res, ")");
		}
		else {
			strcat(res, operand1);
			strcat(res, str);
			strcat(res, operand2);
		}
		strncpy(*p, res, 30);
		}else 	strncpy(*p, str, 30);
		stack.push(*p);
		i++;
	}
	file.close();
	if(!stack.isNull())
		operand1 = stack.pop2();
	if(stack.isNull())
		return operand1;
	else 	{
		cout << "Error.\n";
		exit(1);
		}
	}
}

int main()
{
	cout << postfixToInfix() << endl;
	return 0;
}
