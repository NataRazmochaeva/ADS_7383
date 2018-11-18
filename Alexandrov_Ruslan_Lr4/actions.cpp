#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "actions.h"

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
                cin >> element;
                if (binaryTree.findElem(element, &binaryTree)) {
                    cout << "-----" << endl;
                    cout << "Your element [" << element << "] was found" << endl;
                    cout << "Number of this element = " << binaryTree.countElems(element, &binaryTree, count) << endl;
                    cout << "The least length from the root to this element = " << binaryTree.getLeastLength(element,
                                                                                                             &binaryTree)
                         << endl;
                    cout << "-----" << endl;
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
    for (char i : str) {
        if (isspace(i)) {
            continue;
        } else if (i == '(') {
            res.push_back(i);
            countBrackets++;
            brackets.push_back(i);
        } else if (i == ')') {
            res.push_back(i);
            countBrackets++;
            try {
                brackets.pop_back();
            } catch (exception &e) {
                return false;
            }
        } else {
            res.push_back(i);
        }
    }
    str = res;
    return brackets.empty() && (countBrackets > 0);
}

void Actions::showMenu() {
    cout << "1. Enter an element" << endl;
    cout << "0. Return" << endl;
}
