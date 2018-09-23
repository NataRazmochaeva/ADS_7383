#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <cstring>
#pragma once
using namespace std;

int oper(istream &files, int op);
bool write(istream &files, bool cur);
bool rec(istream &files, bool cur, int flag);
