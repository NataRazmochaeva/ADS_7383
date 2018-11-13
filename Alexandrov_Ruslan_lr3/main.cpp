#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "main.h"

using namespace std;

void Main::menu() {
    cout << "1. Enter the name of the text file" << endl;
    cout << "0. Exit" << endl;
}

void Main::fileRead() {
    string fileName;
    int a;
    int b;
    cout << "Enter a" << endl;
    cin >> a;
    cout << "Enter b" << endl;
    cin >> b;
    if (a >= b) {
        cout << "a must be less then b" << endl;
        return;
    }
    cout << "Enter the name of the text file" << endl;
    cin >> fileName;
    try {
        actions.readFile(fileName, a, b);
    } catch (string s) {
        cout << s << endl;
    }
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
            case 0:
                exit(1);
        }
    }
}