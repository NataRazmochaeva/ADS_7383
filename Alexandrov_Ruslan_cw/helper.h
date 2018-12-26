#ifndef COURSEWORK_HELPER_H
#define COURSEWORK_HELPER_H

#include "codetree.h"
#include <iostream>
#include <string>

#pragma once

void printChWeights(CodeTree *ltree, CodeTree *rtree, int weight, string &testRows);

void helpToPrintChW(CodeTree *b, string &side);

void throughRecursive(CodeTree *b, string &side);

void displayTree(const CodeTree *b, int n);

void helpToDisplay(const CodeTree *b);



#endif //COURSEWORK_HELPER_H
