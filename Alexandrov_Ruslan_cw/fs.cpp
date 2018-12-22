#include "fs.h"
#include <algorithm>
#include <climits>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
static int middle(const Symbol *symbols, int l, int sum, int &lsum, int &rsum);

CodeTree *fanno_shannon(const Symbol *symbols, int l, int r, int sum, vector<string> &vectorFanoShanon) {
    if (l >= r) return nullptr;
    if (r - l == 1) return makeLeaf(symbols[l]);
    int lsum, rsum;
    int m = middle(symbols, l, sum, lsum, rsum);
    CodeTree *ltree = fanno_shannon(symbols, l, m + 1, lsum, vectorFanoShanon);
    CodeTree *rtree = fanno_shannon(symbols, m + 1, r, rsum, vectorFanoShanon);
    CodeTree *node = makeNode(sum, ltree, rtree);
    string testRow;
    printChWeights(ltree, rtree, sum, testRow);
    vectorFanoShanon.push_back(testRow);
    ltree->parent = node;
    rtree->parent = node;
    return node;
}

CodeTree *fanoShanon(const Symbol *symbols, int len) {
    int sum = 0;
    for (int i = 0; i < len; ++i) {
        cout << symbols[i].c << "[" << symbols[i].weight << "] ";
        sum += symbols[i].weight;
    }
    cout << endl;
    vector<string> vectorFanoShanon;
    CodeTree *returnValue = fanno_shannon(symbols, 0, len, sum, vectorFanoShanon);
    cout << "2. Divide the list into two parts, with the total frequency counts of the left part being as close to the total of the right as possible" << endl;
    cout << "------------------------" << endl;
    if (vectorFanoShanon.size() > 0) {
        for (int i = vectorFanoShanon.size() - 1; i >= 0; i--) {
            cout << vectorFanoShanon[i] << endl;
        }
    }
    cout << "------------------------" << endl;
    return returnValue;
}

CodeTree *fanoShanon(const string &message) {
    Symbol symbols[UCHAR_MAX];
    for (int i = 0; i < UCHAR_MAX; ++i) {
        symbols[i].c = i + CHAR_MIN;
        symbols[i].weight = 0;
    }
    int size = message.size();
    for (int i = 0; i < size; ++i) {
        symbols[message[i] - CHAR_MIN].weight++;
    }
    std::sort(symbols, symbols + UCHAR_MAX, greaterSymbol);
    int len = 0;
    while (symbols[len].weight > 0 && len < UCHAR_MAX) len++;
    cout << "1. Count and sort by ascending numbers of each characters in the entered text" << endl;
    cout << message << "[" << message.size() << "]" << endl;
    return fanoShanon(symbols, len);
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


