#ifndef COURSEWORK_CODETREE_H
#define COURSEWORK_CODETREE_H

#include <string>
#include <vector>

using namespace std;
struct Symbol {
    char c;
    int weight;
};

bool greaterSymbol(const Symbol &l, const Symbol &r);

struct CodeTree {
    Symbol s;
    CodeTree *parent;
    CodeTree *left;
    CodeTree *right;
};

CodeTree *makeLeaf(const Symbol &s);

CodeTree *makeNode(int weight, CodeTree *left, CodeTree *right);

bool isLeaf(const CodeTree *node);

bool isRoot(const CodeTree *node);

char *encode(const CodeTree *tree, const string &message);
char *decode(const CodeTree *tree, const char *code, vector<string> &rows);

void destroy(CodeTree *tree);
char *resize(char *prevArr, unsigned int &sizeOfCode);


#endif //COURSEWORK_CODETREE_H
