#include <string>
#include <vector>

using namespace std;


struct Symbol {
    char c;
    int weight;
};

bool symbol_greater(const Symbol &l, const Symbol &r);

struct CodeTree {
    Symbol s;
    CodeTree *parent;
    CodeTree *left;
    CodeTree *right;
};

char *resize(char *prevArr, unsigned int &sizeOfCode);

CodeTree *make_leaf(const Symbol &s);

CodeTree *make_node(int weight, CodeTree *left, CodeTree *right);

bool is_leaf(const CodeTree *node);

bool is_root(const CodeTree *node);

char *encode(const CodeTree *tree, const string &message);

void destroy(CodeTree *tree);