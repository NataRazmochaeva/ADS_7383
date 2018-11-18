#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include "bst_interf.h"

using namespace std;
using namespace losev_BST;

namespace losev_functions
{
	BST <int> *build_tree(string str);
	void printtree(BST <int> *treenode, int l);
	void ascend_write_node(ofstream *outfile, BST <int> *tree);
	int ascend_write_tree(string filename, BST <int> *tree);
	void rand_init();
}