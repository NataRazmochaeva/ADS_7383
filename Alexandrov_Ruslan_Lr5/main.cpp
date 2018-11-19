#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "main.h"

using namespace std;

void Main::menu() {
    cout << "1. Enter a binary codeTree from the console" << endl;
    cout << "2. Enter a binary codeTree from the text file" << endl;
    cout << "0. Exit" << endl;
}

void Main::fileRead() {
    string fileName;
    string message;
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
    ofstream outFile;
    outFile.open("result.txt");
    cout << "--------" << endl;
    while (!inFile.eof()) {
        getline(inFile, message);
        if (message.empty()) continue;
        CodeTree *ct = fanno_shannon(message);
        char *resultCode = encode(ct, message);
        cout << "Your code " << endl;
        cout << resultCode << endl;
        outFile << resultCode << endl;
    }
    cout << "--------" << endl;
    inFile.close();
    outFile.close();
}

void Main::consoleRead() {
    string message;
    cout << "Enter string" << endl;
    cin.ignore();
    getline(cin, message);
    if (message.empty())
        return;
    CodeTree *ct = fanno_shannon(message);
    char *resUlt = encode(ct, message);
    cout << "Your code " << endl;
    cout << resUlt << endl;
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