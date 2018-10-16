#ifndef LAB1_R_H
#define LAB1_R_H
#pragma once

#include <fstream>
#include "helper.h"
#include "binom.h"

class Main {
private:
    Helper helper;
    Binom binom;
    uint64_t m;
    uint64_t n;
    uint64_t x;

public:
    unsigned int choice;

    void consoleRead();

    void fileRead();

    void menu();
};

#endif