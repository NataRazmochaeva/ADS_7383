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

int main() {
	st_modul1::Stack stack;
	string c;
	string file_name;
	fstream file;
	int i=0;
	char* str = new char[2];
	int sw_var;
	cout << "Menu" << '\n';
	cout << "0-exit from the program" << '\n';
	cout << "1-input a line from a file" << '\n';
	cin >> sw_var;
	cin.ignore();
	while(sw_var){
		switch (sw_var)
		{
	case 1:{ cout << "Enter the name of the file:" << '\n';
	cin >> file_name;
	cin.ignore();
	file.open(file_name, fstream::in);
	if (!file.is_open()) {
		cout << "Error opening file.\n";
	}
	else {
		getline(file, c);
		int N=c.length();
		c[N]='\0';
		char* res = new char[2*N];
		char* operand1 = new char[2*N];
		char* operand2 = new char[2*N];
		char* ptr=new char[2*N];
		while (i!=N) {
			st_modul1:: base *p = (st_modul1::base*)malloc(2*N * sizeof(st_modul1:: base));
    	*p = (st_modul1::base)malloc(2*N * sizeof(char));
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
		strncpy(*p, res, 2*N);
	}else 	strncpy(*p, str, 2*N);
		stack.push(*p);
		i++;
	}
	file.close();
	if(!stack.isNull())
		operand1 = stack.pop2();
	if(stack.isNull())
		cout<< operand1<< endl;
	else 	{
		cout << "Error. Stak is not empty.\n";
		break;
	}
}
sw_var=2;
break;
	}
	case 0:
		break;
	default: {
		cout << "Enter again.\n";
		cin >> sw_var;
		cin.ignore();
			 break;
	}
}
}
}
