#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <cstring>
#include <string>
#pragma once
using namespace std;

int oper(istream &files, int op);
bool write(istream &files, bool cur, int flag);
bool rec(istream &files, bool cur, int flag);
bool check(string str, bool flag, unsigned int k);
