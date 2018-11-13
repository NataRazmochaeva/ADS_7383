#pragma once
#include <string>
#include "queue.h"

using namespace std;

class Actions {
public:
    void readFile(string fileName, int a, int b);

private:
    template<class Item>
    void printLessB(Queue<Item> &queue, int a, int b, ofstream &outFile);
    template<class Item>
    void printMoreB(Queue<Item> &queue, int b, ofstream &outFile);
};


