#pragma once

#include "action.h"

class Main {
private:
    Action action;
public:
    unsigned int choice;

    void consoleRead();

    void fileRead();

    void menu();
};