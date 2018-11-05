#pragma once
#include <string>
#include "queue.h"

using namespace std;

class Actions {
public:
    void readFile(string fileName, int a, int b);

private:
    template<class Item>
    void printResult(Queue<Item> &queue);
};


