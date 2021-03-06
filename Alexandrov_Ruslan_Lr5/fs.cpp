#include "fs.h"
#include <algorithm>
#include <climits>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

static int middle(const Symbol *symbols, int l, int sum, int &lsum, int &rsum);

CodeTree *fanno_shannon(const Symbol *symbols, int l, int r, int sum) {
    if (l >= r) return nullptr;
    if (r - l == 1) return make_leaf(symbols[l]);
    int lsum, rsum;
    int m = middle(symbols, l, sum, lsum, rsum);
    CodeTree *ltree = fanno_shannon(symbols, l, m + 1, lsum);
    CodeTree *rtree = fanno_shannon(symbols, m + 1, r, rsum);
    CodeTree *node = make_node(sum, ltree, rtree);
    ltree->parent = node;
    rtree->parent = node;
    return node;
}

CodeTree *fanno_shannon(const Symbol *symbols, int len) {
    int sum = 0;
    for (int i = 0; i < len; ++i)
        sum += symbols[i].weight;
    return fanno_shannon(symbols, 0, len, sum);
}

CodeTree *fanno_shannon(const string &message) {
    Symbol symbols[UCHAR_MAX];
    for (int i = 0; i < UCHAR_MAX; ++i) {
        symbols[i].c = i + CHAR_MIN;
        symbols[i].weight = 0;
    }
    int size = message.size();
    for (int i = 0; i < size; ++i)
        symbols[message[i] - CHAR_MIN].weight++;
    std::sort(symbols, symbols + UCHAR_MAX, symbol_greater);
    int len = 0;
    while (symbols[len].weight > 0 && len < UCHAR_MAX) len++;
    return fanno_shannon(symbols, len);
}

void displayTree(const CodeTree *b, int n) {
    if (b != NULL) {
        const CodeTree *newT = b;
        if (b->s.c != 0) {
            cout << "'" << b->s.c << "' / {";
            cout << b->s.weight << "}";
        } else {
            cout << "'";
            helpToDisplay(newT);
            cout << "' / {";
            cout << b->s.weight << "}";
        }
        cout << endl;
        if (b->right) {
            for (int i = 1; i <= n; i++) cout << "   ";
            cout << " [1] ";
            displayTree(b->right, n + 1);
        }
        if (b->left) {
            for (int i = 1; i <= n; i++) cout << "   ";
            cout << " [0] ";
            displayTree(b->left, n + 1);
        }
        delete newT;
    }
}

void helpToDisplay(const CodeTree *b) {
    if (b->s.c != 0) {
        cout << b->s.c;
    }
    if (b->right) {
        helpToDisplay(b->right);
    }
    if (b->left) {
        helpToDisplay(b->left);
    }
}

int middle(const Symbol *symbols, int l, int sum, int &lsum, int &rsum) {
    int m = l;
    lsum = symbols[m].weight;
    rsum = sum - lsum;
    int delta = lsum - rsum;
    while (delta + symbols[m + 1].weight < 0) {
        m++;
        lsum += symbols[m].weight;
        rsum -= symbols[m].weight;
        delta = lsum - rsum;
    }
    return m;
}
