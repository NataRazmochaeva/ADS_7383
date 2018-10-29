#pragma once

#include "binkor.h"

class Main {
private:
    BinKor binKor;
public:
    Main() {}
    unsigned int choice;

    void consoleRead();

    void fileRead();

    void menu();
};