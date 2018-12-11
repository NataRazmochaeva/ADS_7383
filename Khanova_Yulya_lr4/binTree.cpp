#include <iostream>
#include <cstdlib>
#include "binTree.h"
using namespace std;

namespace binTree_modul
{
	node* Mem = new node;
	bool isNull(int b){
		return (b == 0);
	}
	char RootBT(int b){
		if (b == 0) {
			cerr << "Error: RootBT(null) \n";
			system("pause > nul");
		}
		else return Mem[b].info;
	}
	int Left(int b){
		if (b == 0) {
			cerr << "Error: Left(null) \n";
			system("pause > nul");
		}
		else return Mem[b].lt;
	}
	int Right(int b)	{
		if (b == 0) {
			cerr << "Error: Right(null) \n";
			system("pause > nul");
		}
		else return Mem[b].rt;
	}

	int freeND(){
		for(int i=1; i<100; i++){
			if(Mem[i].info == 0) return i;
		}
		return -1;
	}
	int ConsBT(const char &x, int lt, int rt){
		int k = freeND();
		if (k > 0) {
			Mem[k].info = x;
			Mem[k].lt = lt;
			Mem[k].rt = rt;
			return k;
		}
		else { cerr << "Memory not enough\n"; exit(1); }
	}
}
