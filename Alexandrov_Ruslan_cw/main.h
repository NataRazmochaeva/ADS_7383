#ifndef COURSEWORK_MAIN_H
#define COURSEWORK_MAIN_H
#include "fs.h"
#include "huffman.h"

class Main {
public:
    Main() {}

    unsigned int choice;

    string fileRead();

    void getHuffman();

    void getFanoShannon();

    void menu();
};

#endif //COURSEWORK_MAIN_H
