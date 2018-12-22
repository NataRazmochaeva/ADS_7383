#include "helper.h"

void printChWeights(CodeTree *ltree, CodeTree *rtree, int weight, string &testRows) {
    string left;
    string right;
    if (ltree->s.c != 0 && rtree->s.c != 0) {
        testRows.push_back(rtree->s.c);
        testRows.push_back('[');
        testRows += to_string(rtree->s.weight);
        testRows.push_back(']');
        testRows += " and ";
        testRows.push_back(ltree->s.c);
        testRows.push_back('[');
        testRows += to_string(ltree->s.weight);
        testRows.push_back(']');
    } else if (ltree->s.c == 0 && rtree->s.c == 0) {
        helpToPrintChW(ltree, left);
        helpToPrintChW(rtree, right);
        testRows += right;
        testRows.push_back('[');
        testRows += to_string(rtree->s.weight);
        testRows.push_back(']');
        testRows += " and ";
        testRows += left;
        testRows.push_back('[');
        testRows += to_string(ltree->s.weight);
        testRows.push_back(']');
    } else if (ltree->s.c == 0) {
        helpToPrintChW(ltree, left);
        testRows.push_back(rtree->s.c);
        testRows.push_back('[');
        testRows += to_string(rtree->s.weight);
        testRows.push_back(']');
        testRows += " and ";
        testRows += left;
        testRows.push_back('[');
        testRows += to_string(ltree->s.weight);
        testRows.push_back(']');
    } else if (rtree->s.c == 0) {
        helpToPrintChW(rtree, right);
        testRows += right;
        testRows.push_back('[');
        testRows += to_string(rtree->s.weight);
        testRows.push_back(']');
        testRows += " and ";
        testRows.push_back(ltree->s.c);
        testRows.push_back('[');
        testRows += to_string(ltree->s.weight);
        testRows.push_back(']');
    }
    testRows += " | Full weight =  ";
    testRows += to_string(weight);
}

void helpToPrintChW(CodeTree *b, string &side) {
    if (b->s.c != 0) {
        side += b->s.c;
    }
    if (b->right) {
        helpToPrintChW(b->right, side);
    }
    if (b->left) {
        helpToPrintChW(b->left, side);
    }
}

void throughRecursive(CodeTree *b, string &side) {
    if (b != nullptr) {
        CodeTree *newT = b;
        if (b->s.c == 0) {
            helpToPrintChW(newT, side);
        }
        if (b->right) {
            throughRecursive(b->right, side);
        }
        if (b->left) {
            throughRecursive(b->left, side);
        }
        delete newT;
    }
}

void displayTree(const CodeTree *b, int n) {
    if (b != nullptr) {
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