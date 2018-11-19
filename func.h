#pragma once
#include <iostream>
#include "Btree.h"
using namespace std;
using namespace binTree_modul;

	bool isSymbol( const char c );
	bool isSignal( const char c );
	void DelSpace(istream &in);
	string MakeForm(binTree b);
	binTree MakeTree(istream &in);
	void Remake(binTree b);
	void Invariant(binTree b);
	string ToPrefix(binTree b);
	void PrintTree(binTree f, int l);

