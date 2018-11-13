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
    int beginSize = 5;
    Queue<int> qLessB(beginSize);
    Queue<int> qMoreB(beginSize);
    cout << "Here " << endl;
    while (inFile >> value) {
        if (value <= b) {
            qLessB.enqueue(value);
        }
        if (value > b) {
            qMoreB.enqueue(value);
        }
    }
    inFile.close();

    cout << "-------- Numbers --------" << endl;
    ofstream outFile;
    outFile.open("result.txt");
    printLessB(qLessB, a, b, outFile);
    printMoreB(qMoreB, b, outFile);
    outFile.close();
    cout << endl;
    cout << "--------------" << endl;

}

template<class Item>
void Actions::printLessB(Queue<Item> &queue, int a, int b, ofstream &outFile) {
    while (!queue.isEmpty()) {
        Item front = queue.getFront();
        if (front < a) {
            outFile << front;
            outFile << " ";
            cout << front << " ";
        }
    }
    while (!queue.isEmpty()) {
        Item front = queue.getFront();
        if (front >= a && front <= b) {
            outFile << front;
            outFile << " ";
            cout << front << " ";
        }
    }
}

template<class Item>
void Actions::printMoreB(Queue<Item> &queue, int b, ofstream &outFile) {
    while (!queue.isEmpty()) {
        Item front = queue.getFront();
        if (front > b) {
            outFile << front;
            outFile << " ";
            cout << front << " ";
        }
    }
}
