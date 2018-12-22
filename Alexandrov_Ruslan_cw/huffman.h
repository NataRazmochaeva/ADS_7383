#ifndef COURSEWORK_HUFFMAN_H
#define COURSEWORK_HUFFMAN_H
#include "codetree.h"
#include "helper.h"
#include <iostream>

using namespace std;

CodeTree *huffmanCode(const string &message);

CodeTree *huffmanCode(const Symbol *symbols, int len);

#endif //COURSEWORK_HUFFMAN_H
