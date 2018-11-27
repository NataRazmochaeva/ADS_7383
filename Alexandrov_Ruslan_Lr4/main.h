#pragma once

#include "actions.h"

class Main {
    Actions actions;
public:

    Main() {}

    unsigned int choice;

    void fileRead();

    void consoleRead();

    void menu();
};

