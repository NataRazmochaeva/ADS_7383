#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "main.h"
#include "binkor.h"

using namespace std;

void Main::fileRead() {
    string fileName, str;
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
    stringstream xstream;
    while (!inFile.eof()) {
        getline(inFile, str);
        xstream << str;
        BinKor::lisp s1;
        binKor.read_lisp(s1, xstream);
        int weight = binKor.getWeight(s1);
        cout << "weight = " << weight << endl;
        cout << "for list " << endl;
        binKor.write_lisp(s1);
        cout << endl;
        cout<<endl;
        binKor.destroy(s1);
    }
    inFile.close();
}

void Main::consoleRead() {
    string str;
    cout << "Enter string:" << endl;
    getline(cin, str); // remove '\n'
    getline(cin, str);
    stringstream xstream;
    xstream << str;
    BinKor::lisp s1;
    binKor.read_lisp(s1, xstream);
    int weight = binKor.getWeight(s1);
    cout << "weight = " << weight << endl;
    cout << "for list " << endl;
    binKor.write_lisp(s1);
    cout << endl;
    cout<<endl;
    binKor.destroy(s1);
}

void Main::menu() {
    cout << "1. Enter numbers from the txt" << endl;
    cout << "2. Enter numbers from the console" << endl;
    cout << "0. Exit" << endl;
}

int main() {
    cout << "Hello! This program calculates the weight of the binary rocket" << endl;
    Main main;

    while (true) {
        main.menu();
        cin >> main.choice;
        switch (main.choice) {
            case 1:
                main.fileRead();
                break;
            case 2:
                main.consoleRead();
                break;
            case 0:
                exit(1);
        }
    }
}