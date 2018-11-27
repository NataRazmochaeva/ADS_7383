#include <iostream>
#include <fstream>
#include <string>
#include "main.h"

using namespace std;

void Main::menu() {
    cout << "1. Enter a binary tree from the console" << endl;
    cout << "2. Enter a binary tree from the text file" << endl;
    cout << "0. Exit" << endl;
}

void Main::fileRead() {
    string fileName;
    string bt;
    cout << "What`s the file name?" << endl;
    cin >> fileName;
    cout << "--------------" << endl;
    cout << "Reading from " << fileName << endl;
    cout << "--------------" << endl;
    ifstream inFile;
    inFile.open(fileName);
    if (!inFile) {
        cout << "Cannot find this file" << endl;
        cout << endl;
        return;
    }
    while (!inFile.eof()) {
        getline(inFile, bt);
        actions.start(bt);
    }
    inFile.close();
}

void Main::consoleRead() {
    string btree;
    cout << "Enter btree" << endl;
    cin.ignore();
    getline(cin, btree);
    actions.start(btree);
}

int main() {
    Main main;
    while (true) {
        main.menu();
        cin >> main.choice;
        switch (main.choice) {
            case 1:
                main.consoleRead();
                break;
            case 2:
                main.fileRead();
                break;
            case 0:
                exit(1);
        }
    }
}