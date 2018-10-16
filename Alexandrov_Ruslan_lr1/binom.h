#ifndef LAB1_BINOM_H
#define LAB1_BINOM_H
#pragma once

#include <cstdint>

class Binom {
private:
    unsigned short int i = 0; // iterator
    void printUnderscore(unsigned short int i);
    uint64_t eval(uint64_t m, uint64_t n, uint64_t &half, uint64_t &full); // recursive function

public:
    uint64_t count(uint64_t m, uint64_t n); // recursive function
};

#endif
