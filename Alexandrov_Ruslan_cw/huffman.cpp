#include "huffman.h"
#include "priority_queue.h"
#include <functional>
#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


CodeTree *huffmanCode(const Symbol *symbols, int len) {
    PriorityQueue<CodeTree *> *queue = createPQ<CodeTree *>(len);
    for (int i = 0; i < len; ++i) {
        cout << symbols[i].c << "[" << symbols[i].weight << "] ";
        push(queue, symbols[i].weight, makeLeaf(symbols[i]));
    }
    cout << endl;
    cout << "2. Join 2 nodes with each other according to their low priority of weights" << endl;
    cout << "------------------------" << endl;
    vector<string> rows;
    while (size(queue) > 1) {
        CodeTree *ltree = pop(queue);
        CodeTree *rtree = pop(queue);
        int weight = ltree->s.weight + rtree->s.weight;
        CodeTree *node = makeNode(weight, ltree, rtree);
        ltree->parent = node;
        rtree->parent = node;
        push(queue, weight, node);
        string testRow;
        printChWeights(ltree, rtree, weight, testRow);
        rows.push_back(testRow);
    }
    for (int i = 0; i < rows.size(); i++) {
        cout << rows[i] << endl;
    }
    CodeTree *result = pop(queue);
    destroyPq(queue);
    return result;
}


CodeTree *huffmanCode(const string &message) {
    Symbol symbols[UCHAR_MAX];
    for (int i = 0; i < UCHAR_MAX; ++i) {
        symbols[i].c = i + CHAR_MIN;
        symbols[i].weight = 0;
    }
    int size = message.size();
    for (int i = 0; i < size; ++i)
        symbols[message[i] - CHAR_MIN].weight++;
    std::sort(symbols, symbols + UCHAR_MAX, greaterSymbol);
    int len = 0;
    while (symbols[len].weight > 0 && len < UCHAR_MAX) len++;
    cout << "1. Count and sort by ascending numbers of each characters in the entered text" << endl;
    cout << message << "[" << message.size() << "]" << endl;
    return huffmanCode(symbols, len);
}
