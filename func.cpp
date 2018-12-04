#include <iostream>
#include <fstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Btree.h"
using namespace std;
using namespace binTree_modul;

	bool isSymbol( const char c ){
		return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
	}

	bool isSignal( const char c ){
		return c == '-' || c == '+' || c == '*';
	}

	binTree MakeLeaf( base c ){
		return ConsBT(c, nullptr, nullptr);
	}

	void DelSpace(istream &in){

		base c;
		do 
		{
			c = in.peek();
			if (c == ' ')
				c = in.get();
		} while (c == ' ');
	}

	string MakeForm(binTree b){

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
		str += MakeForm(b->lt);
		str += ' ';
		str += b->info;
		str += ' ';
		str += MakeForm(b->rt);
		str += " )";
	}

	binTree MakeTree(istream &in, int k){
		
		base c, sign;
		binTree left, right;
		DelSpace(in);
		c = in.get();
		if (c=='\n'){
			cout<<"Expression not wrote"<<endl;
			return NULL;
		}
		if (isSymbol(c) && k==0){ // если формула является символом
			base h;
			k++;
			DelSpace(in);
			h = in.get();
			if (h=='\n')						
				return MakeLeaf(c);
			else{ 
				cout<<"Exp error"<<endl;
				return NULL;
			}
		}
		if (isSymbol(c)){
			k=1;
			return MakeLeaf(c);
		} 
		if (c == '('){ // если формула имеет вид (<симв><знак><симв>)
			DelSpace(in);
			k++;
			left = MakeTree(in, k++); // первая формула 
			DelSpace(in);
			c = in.get();
			if (isSignal(c))
				sign = c; // знак
			else { cerr << "error: sign expected" << endl; return NULL; }
			// если после первой формулы нет знака
			DelSpace(in);
			right = MakeTree(in, k++); // вторая формула 
			DelSpace(in); // проверка скобок
			c = in.get(); 
			if (c != ')') { cerr << "error: ')' expected" << endl; return NULL; }
			// формула вида (<терм><знак><терм>) заканчивается скобкой
			left = ConsBT(sign, left, right); // делаем из знака и двух формул формулу
			return left;
		}
		else {
			if (isSignal(c)) cerr << "error: extra sign in formula" << endl;
			else cerr << "error: external symbol if formula" << endl;
			return MakeTree(in, k++);
		 } 
	}

	void Remake(binTree b){

		//(f1 * (f2 + f3))
		binTree f1, f2, f3, f4, k;
		if (b->rt->info=='+'){
			f1 = b->rt;
			f2 = b->lt;
			f3 = b->rt->rt;
			f4 = b->rt->lt;			
			b->lt = ConsBT('*', f2, f4);
			
			b->info = '+';
			b->rt->info = '*';
			b->rt->lt=b->lt->lt;
			return;
		}
		// ((f2 + f3)*f1)
		if (b->lt->info=='+'){
			f1 = b->lt;
			f2 = b->rt;
			f3 = b->lt->lt;
			f4 = b->lt->rt;
			b->rt = ConsBT('*', f3, f2);
			b->lt->info = '*';
			b->info = '+';
			b->lt->lt = f4;
			b->lt->rt = b->rt->rt;
			
			return;
		}
	}

	void Invariant(binTree b){	
		
		if (b == NULL)
			return;
		Invariant(b->lt);
		Invariant(b->rt);
		if (b == NULL || b->lt == NULL || b->rt == NULL)
			return; 
		if ((b->lt->info != '+' && b->rt->info != '+') || b->info != '*')
			return; 
		Remake(b);
		return;
	}

	string ToPrefix(binTree b){
	
		string str = "";
		if (b == NULL)
			return str;
		str += ' ';
		str += b->info;
		str += ' ';
		if (b->lt != NULL){
			str += ' ';
			str += ToPrefix(b->lt);
			str += ' ';
		}
		if (b->rt != NULL){
			str += ' ';
			str += ToPrefix(b->rt);
			str += ' ';
		}
	}

	void PrintTree(binTree f, int l){
	
		if(f == nullptr){
			for(int i = 0; i < l; i++)
				cout << "\t";
			cout << '#' << endl;
			return;
		}
		PrintTree(f->rt, l+1);
		for(int i = 0; i < l; i++)
			cout << "\t";
		cout << f->info << endl;
		PrintTree(f->lt, l+1);
    }

