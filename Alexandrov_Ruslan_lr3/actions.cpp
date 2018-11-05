#include <iostream>
#include <string>
#include <fstream>
#include "actions.h"
using namespace std;

void Actions::readFile(string fileName, int a, int b) {
    ifstream inFile;
    inFile.open(fileName);
    int value;
    if (!inFile) {
        throw string("Cannot find this file");
    }
    //
    int beginSize = 5;
    Queue<int> qLessA(beginSize);
    Queue<int> qMoreALessB(beginSize);
    Queue<int> qMoreB(beginSize);
    while (inFile >> value) {
        if (value < a) {
            qLessA.enqueue(value);
        }
        if (value >= a && value <= b) {
            qMoreALessB.enqueue(value);
        }
        if (value > b) {
            qMoreB.enqueue(value);
        }
    }
    inFile.close();

    cout << "-------- Numbers --------" << endl;
    printResult(qLessA);
    printResult(qMoreALessB);
    printResult(qMoreB);
    cout << endl;
    cout << "--------------" << endl;
}

template<class Item>
void Actions::printResult(Queue<Item> &queue) {
    while (!queue.isEmpty()) {
        cout << queue.getFront() << " ";
    }
}
