#ifndef LAB1_HELPER_H
#define LAB1_HELPER_H
#pragma once

#include <fstream>
#include <vector>

/*
 * The class helps to do interim actions
 */

class Helper {
public:
    bool validateFile(std::ifstream &inFile);

    void outputToFile(std::vector<uint64_t> &resValues);

    void outputToConsole(std::vector<uint64_t> &resValues);
};


#endif
