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
    while (!inFile.eof()) {
        getline(inFile, str);
        BinKor::lisp lisp;
        try {
            binKor.readLisp(lisp, str);
        } catch (invalid_argument e) {
            cout << endl;
            cout << "This list has an element less then zero" << endl;
            cout << endl;
            return;
        } catch (string s) {
            cout << endl;
            cout << s << endl;
            cout << endl;
            return;
        }
        cout << endl;
        int weight = binKor.getWeight(lisp);
        cout << "Weight = " << weight << endl;
        if (weight != 0) {
            cout << "Result list " << endl;
            cout << binKor.getOutputString();
            cout << endl;
        }
        cout << endl;
        binKor.destroy(lisp);
    }
    inFile.close();
}

void Main::consoleRead() {
    string str;
    cout << "Enter string:" << endl;
    getline(cin, str); // remove '\n'
    getline(cin, str);
    BinKor::lisp lisp;

    try {
        binKor.readLisp(lisp, str);
    } catch (invalid_argument e) {
        cout << endl;
        cout << "This list has an element less then zero" << endl;
        cout << endl;
        return;
    } catch (string s) {
        cout << endl;
        cout << s << endl;
        cout << endl;
        return;
    }
    cout << endl;
    int weight = binKor.getWeight(lisp);
    cout << "Weight = " << weight << endl;
    if (weight != 0) {
        cout << "Result list " << endl;
        cout << binKor.getOutputString();
        cout << endl;
    }
    cout << endl;
    binKor.destroy(lisp);
}

void Main::menu() {
    cout << "1. Enter numbers from the txt" << endl;
    cout << "2. Enter numbers from the console" << endl;
    cout << "0. Exit" << endl;
}

int main() {
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