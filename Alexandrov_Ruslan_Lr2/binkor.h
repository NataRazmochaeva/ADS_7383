#pragma once

#include <sstream>

using namespace std;

class BinKor {
    struct Atom {
        BinKor *atomicEl;
        BinKor *next;
    };

    struct Elem {
        int level;
        int weight;
        BinKor *deep;
    };

    union Content {
        Atom atom;
        Elem elem;
    };
private:
    bool flag; //true: element, false: atom
    union Content content;
    static int countWeight;

public:
    explicit BinKor(stringstream &sstream, int pos = 1);

    int levelBk(stringstream &sstream);

    int getWeight();

    ~BinKor();
};