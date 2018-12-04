#include <iostream>
#include <fstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Btree.h"
#include "func.h"
using namespace std ;
using namespace binTree_modul;
int main () {
	string exp;
	binTree tr;
	int k = 0;
	cout << "Enter expression: ";
	tr = MakeTree(cin, 0);
	if (tr == NULL){
		//cout<<"Expression not wrote"<<endl;
		return 0;
	}
	cout << "Tree built:" << endl;
	exp = MakeForm(tr);
	cout << exp << endl;
	cout << "Visualization: " << endl;
	PrintTree(tr, 0);
	cout<<endl;
	cout << "Multiplication brackets are opened" << endl;
	Invariant(tr);
	exp = MakeForm(tr);
	cout << exp << endl;
	cout << "Go To Prefix Form" << endl;
	exp = ToPrefix(tr);
	cout << exp << endl;
	cout << "Visualization: " << endl;
	PrintTree(tr, 0);
	destroy (tr);
	cout << endl;
	return 0;
} 
