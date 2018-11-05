#pragma once
#include "actions.h"

class Main {
private:
    Actions actions;
public:
    Main() {}
    unsigned int choice;

    void fileRead();

    void menu();
};