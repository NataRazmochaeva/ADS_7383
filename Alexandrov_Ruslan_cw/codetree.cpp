#include "codetree.h"
#include <climits>
#include <cstring>
#include <iostream>

bool greaterSymbol(const Symbol &l, const Symbol &r) {
    return l.weight > r.weight;
}

CodeTree *makeLeaf(const Symbol &s) {
    return new CodeTree{s, nullptr, nullptr, nullptr};
}

CodeTree *makeNode(int weight, CodeTree *left, CodeTree *right) {
    Symbol s{0, weight};
    return new CodeTree{s, nullptr, left, right};
}

bool isLeaf(const CodeTree *node) {
    return node->left == nullptr && node->right == nullptr;
}

bool isRoot(const CodeTree *node) {
    return node->parent == nullptr;
}

static void fillSymbolsMap(const CodeTree *node, const CodeTree **symbols_map);

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
    fillSymbolsMap(tree, symbols_map);
    int len = message.size();
    unsigned int index = 0;
    char path[UCHAR_MAX];
    if (!checkString(message)) {
        for (int i = 0; i < len; ++i) {
            const CodeTree *node = symbols_map[message[i] - CHAR_MIN];
            int j = 0;
            while (!isRoot(node)) {
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
        }
    } else {
        while (index < message.size()) {
            if (index >= firstLength) {
                code = resize(code, firstLength);
            }
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

char *decode(const CodeTree *tree, const char *code, vector<string> &rows) {
    unsigned int firstLength = 1000;
    char *message = new char[firstLength];
    int index = 0;
    int len = strlen(code);
    const CodeTree *v = tree;
    string binaryCodes;
    string rowString;
    int rowCounter = 0;
    // check if we have only root
    if (tree->parent || tree->left || tree->right) {
        for (int i = 0; i < len; ++i) {
            if (code[i] == '0') {
                v = v->left;
                binaryCodes.push_back(code[i]);
            } else {
                v = v->right;
                binaryCodes.push_back(code[i]);
            }
            if (isLeaf(v)) {
                if (index >= firstLength) {
                    message = resize(message, firstLength);
                }
                message[index++] = v->s.c;
                rowString += (v->s.c);
                rowString += " = " + binaryCodes;
                rows.push_back(rowString);
                rowString.clear();
                binaryCodes.clear();
                v = tree;
            }
        }
    } else {
        for (int i = 0; i < len; ++i) {
            binaryCodes.push_back(code[i]);
            if (index >= firstLength) {
                message = resize(message, firstLength);
            }
            message[index++] = v->s.c;
            rowString += (v->s.c);
            rowString += " = " + binaryCodes;
            rows.push_back(rowString);
            rowString.clear();
            rowCounter++;
            binaryCodes.clear();
        }
    }
    message[index] = 0;
    return message;
}


void destroy(CodeTree *tree) {
    if (tree == nullptr) return;
    destroy(tree->left);
    destroy(tree->right);
    delete tree;
    tree = nullptr;
}

void fillSymbolsMap(const CodeTree *node, const CodeTree **symbols_map) {
    if (isLeaf(node))
        symbols_map[node->s.c - CHAR_MIN] = node;
    else {
        fillSymbolsMap(node->left, symbols_map);
        fillSymbolsMap(node->right, symbols_map);
    }
}