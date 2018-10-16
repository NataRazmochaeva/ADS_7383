#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "main.h"
#include "binom.h"

using namespace std;

void Main::fileRead() {
    string fileName;
    uint64_t value;
    vector<uint64_t> resValues;

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

    /* Check file for work */
    if (!helper.validateFile(inFile)) {
        cout << "Odd number of digits" << endl;
        inFile.close();
        return;
    }

    /* Read file num by num*/
    cout << "-------- Numbers --------" << endl;
    while (inFile >> value) {
        m = value;
        inFile >> value;
        n = value;
        cout << "m = " << m;
        cout << ", n = " << n << endl;
        x = binom.count(m, n);
        cout << "x = " << x << endl;
        resValues.push_back(x);
    }
    inFile.close();
    cout << "--------------" << endl;

    helper.outputToConsole(resValues);
    helper.outputToFile(resValues);
}

void Main::consoleRead() {
    int64_t m;
    int64_t n;
    try {
        cout << "Input m" << endl;
        cin >> m;
        cout << "Input n" << endl;
        cin >> n;
        cout << "-------- Numbers --------" << endl;
        cout << "m = " << m << endl;
        cout << "n = " << n << endl;
        x = binom.count(m, n);
        cout << "x = " << x << endl;
        cout << "--------------" << endl;
    } catch (invalid_argument iae) {
        cout << "Invalid arguments" << endl;
    }
}

void Main::menu() {
    cout << "1. Enter numbers from the txt" << endl;
    cout << "2. Enter numbers from the console" << endl;
    cout << "0. Exit" << endl;
}

int main() {
    cout << "Hello! This program calculates the Binomial coefficient" << endl;
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