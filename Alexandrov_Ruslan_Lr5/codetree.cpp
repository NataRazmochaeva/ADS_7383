#include "codetree.h"
#include <climits>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;


bool symbol_greater(const Symbol &l, const Symbol &r) {
    return l.weight > r.weight;
}

CodeTree *make_leaf(const Symbol &s) {
    return new CodeTree{s, nullptr, nullptr, nullptr};
}

CodeTree *make_node(int weight, CodeTree *left, CodeTree *right) {
    Symbol s{0, weight};
    return new CodeTree{s, nullptr, left, right};
}

bool is_leaf(const CodeTree *node) {
    return node->left == nullptr && node->right == nullptr;
}

bool is_root(const CodeTree *node) {
    return node->parent == nullptr;
}

static void fill_symbols_map(const CodeTree *node, const CodeTree **symbols_map);

bool checkString(const string &message) {
	for (int i = 1; i < message.size(); i++) {
		if (message[0] != message[i]) return false;
	}
	return true;
}

char *encode(const CodeTree *tree, const string &message) {
    unsigned int firstLength = 1000;
    char *code = new char[firstLength];
    const CodeTree **symbols_map = new const CodeTree *[UCHAR_MAX];
    for (int i = 0; i < UCHAR_MAX; ++i) {
        symbols_map[i] = nullptr;
    }
    fill_symbols_map(tree, symbols_map);
    int len = message.size();
    unsigned int index = 0;
    char path[UCHAR_MAX];
	if (!checkString(message)) {
    for (int i = 0; i < len; ++i) {
        const CodeTree *node = symbols_map[message[i] - CHAR_MIN];
        int j = 0;
        while (!is_root(node)) {
            if (node->parent->left == node)
                path[j++] = '0';
            else
                path[j++] = '1';
            node = node->parent;
        }
        while (j > 0) {
            if (index >= firstLength) {
                code = resize(code, firstLength);
            }
            code[index++] = path[--j];
        }
    } } else {
		while (index < message.size()) {
			code[index++] = '0';
		}
	}
    code[index] = 0;
    delete[] symbols_map;
    return code;
}



char *resize(char *prevArr, unsigned int &sizeOfCode) {
    unsigned int newSize = sizeOfCode * 2;
    char *newArr = new char[newSize];
    for (int i = 0; i < sizeOfCode; i++) {
        newArr[i] = prevArr[i];
    }
    sizeOfCode = newSize;
    return newArr;
}

void destroy(CodeTree *tree) {
    if (tree == nullptr) return;
    destroy(tree->left);
    destroy(tree->right);
    delete tree;
    tree = nullptr;
}

void fill_symbols_map(const CodeTree *node, const CodeTree **symbols_map) {
    if (is_leaf(node))
        symbols_map[node->s.c - CHAR_MIN] = node;
    else {
        fill_symbols_map(node->left, symbols_map);
        fill_symbols_map(node->right, symbols_map);
    }
}
