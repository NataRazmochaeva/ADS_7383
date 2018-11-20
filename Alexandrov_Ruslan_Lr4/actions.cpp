#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "actions.h"
// empty list #, +
// print tree as structure -
// enter skip +
// and (aa    b) - one el +
using namespace std;

void Actions::start(string btree) {
    if (!validate(btree)) {
        cout << "Wrong brackets" << endl;
        return;
    }
    BT<string> binaryTree;
    cout << "Your btree - " << btree << endl;
    int i = 0;
    unsigned int choice;
    binaryTree.createBT(btree, i);
    while (true) {
        showMenu();
        cin >> choice;
        string element;
        int count = 0;
        switch (choice) {
            case 1:
                cout << "Your element..." << endl;
                cin.ignore();
                getline(cin, element);
                if (element.empty()) return;

                if (binaryTree.findElem(element, &binaryTree)) {
                    cout << "-----" << endl;
                    cout << "Your element [" << element << "] was found" << endl;
                    cout << "Number of this element = " << binaryTree.countElems(element, &binaryTree, count) << endl;
                    cout << "The least length from the root to this element = " << binaryTree.getLeastLength(element,
                                                                                                             &binaryTree)
                         << endl;
                    cout << "-----" << endl;
                    binaryTree.displayBT(&binaryTree, 1);
                } else {
                    cout << "Your element [" << element << "] wasn`t found" << endl;
                }
                break;
            case 0:
                return;
        }
    }
}

bool Actions::validate(string &str) {
    vector<char> brackets;
    string res;
    unsigned int countBrackets = 0;
    for (int i = 0; i < str.size(); i++) {
        if (isspace(str[i])) {
            continue;
        } else if (str[i] == '(') {
            brackets.push_back(str[i]);
            res.push_back(str[i]);
            countBrackets++;
            i++;
            while (str[i + 1] != ')' && str[i + 1] != '(') {
                res.push_back(str[i]);
                i++;
            }
            res.push_back(str[i]);
        } else if (str[i] == ')') {
            res.push_back(str[i]);
            countBrackets++;
            try {
                brackets.pop_back();
            } catch (exception &e) {
                return false;
            }
        } else {
            res.push_back(str[i]);
        }
    }
    str = res;
    if (str[0] != '(' || str[str.size() - 1] != ')')
        return false;
    return brackets.empty() && (countBrackets > 0);
}

void Actions::showMenu() {
    cout << "1. Enter an element" << endl;
    cout << "0. Return" << endl;
}