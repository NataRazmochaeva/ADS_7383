#include <iostream>
#include "binkor.h"

// static count for sum weight
int BinKor::countWeight = 0;

BinKor::BinKor(stringstream &sstream, int pos) {
    char ch;
    switch (pos) {
        case 0:
            flag = true;
            content.elem.deep = nullptr;
            content.elem.weight = 0;
            if (sstream.peek() == '(')
                sstream >> ch;
            levelBk(sstream);
            sstream >> ch;
            break;
        case 1:
            flag = false;
            content.atom.atomicEl = new BinKor(sstream, 0);
            content.atom.next = new BinKor(sstream, 2);
            break;
        case 2:
            flag = false;
            content.atom.atomicEl = new BinKor(sstream, 0);
            content.atom.next = nullptr;
            break;
    }
}

int BinKor::levelBk(stringstream &sstream) {
    char ch;
    if (sstream.peek() == '(')
        sstream >> ch;
    sstream >> content.elem.level;
    if (sstream.peek() == '(') {
        content.elem.deep = new BinKor(sstream);
    } else {
        sstream >> content.elem.weight;
    }
    sstream >> ch;
}

int BinKor::getWeight() {
    if (!flag) {
        if (content.atom.next) {
            (content.atom.next)->getWeight();
            (content.atom.atomicEl)->getWeight();
        } else
            (content.atom.atomicEl)->getWeight();
    } else {
        countWeight += content.elem.weight;
        if (content.elem.deep) {
            (content.elem.deep)->getWeight();
        } else {
            return (countWeight);
        }
    }
}

BinKor::~BinKor() {
    if (!flag) {
        delete content.atom.atomicEl;
        if (content.atom.next)
            delete content.atom.next;
    } else if (content.elem.deep)
        delete content.elem.deep;

    countWeight = 0;
}
