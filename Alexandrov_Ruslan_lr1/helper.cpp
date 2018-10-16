#include <fstream>
#include <iostream>
#include "helper.h"

using namespace std;

/* Check for negative numbers and the even sum of digits */
bool Helper::validateFile(ifstream &inFile) {
    long value;
    long count = 0;
    while (inFile >> value) {
        count++;
        if (value < 0) return false;
    }
    cout << count << endl;
    inFile.clear();
    inFile.seekg(0);
    return count % 2 == 0;
}

void Helper::outputToFile(std::vector<uint64_t> &resValues) {
    ofstream outFile;
    outFile.open("result.txt");
    for (uint64_t resValue : resValues) {
        outFile << resValue;
        if (resValue == 0) outFile << " - The answer is 0 because m was more than n";
        outFile << endl;
    }
    outFile.close();
}

void Helper::outputToConsole(std::vector<uint64_t> &resValues) {
    cout << "Vector consists of " << resValues.size() << " numbers" << endl;
    for (uint64_t resValue : resValues) {
        cout << resValue << endl;
    }
}