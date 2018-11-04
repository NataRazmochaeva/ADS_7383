#include <iostream>
#include <cctype>
#include <string>
#include "binkor.h"

using namespace std;

BinKor::s_expr *BinKor::head(const lisp s) {
    if (s != nullptr) {
        return s->node.pair.hd;
    } else {
        return nullptr;
    }
}

BinKor::s_expr *BinKor::tail(const lisp s) {
    if (s != nullptr) {
        return s->node.pair.tl;
    } else {
        return nullptr;
    }
}

bool BinKor::isAtom(const lisp s) {
    if (s == nullptr)
        return false;
    else
        return (s->tag);
}

bool BinKor::isNull(const lisp s) {
    return s == nullptr;
}

BinKor::lisp BinKor::cons(const lisp h, const lisp t) {
    lisp p;
    p = new s_expr;
    p->tag = false;
    p->node.pair.hd = h;
    p->node.pair.tl = t;
    return p;
}

BinKor::lisp BinKor::makeAtom(const base x) {
    lisp s;
    s = new s_expr;
    s->tag = true;
    s->node.weight = x;
    return s;
}

void BinKor::readLisp(lisp &y, string &str) {
    int i = 0;
    do {
        if (str[i] == '(') outputString += '(';
        i++;
    } while (str[i] == ' ' && i < str.length());
    if (str[i])
        readSExp(y, str, i);
}

void BinKor::readSExp(lisp &y, string &str, int &iterator) {
    if (str[iterator] == ')') {
        throw string("Error: the initial brace is closing");
    } else if (str[iterator] == '-') {
        throw invalid_argument("Element less then zero");
    } else if (str[iterator] != '(') {
        if (!isdigit(str[iterator])) {
            throw string("This list has not only numbers or brackets");
        }
        string num;
        int atomWeight;
        if (isdigit(str[iterator + 1])) {
            while (isdigit(str[iterator])) {
                num.push_back(str[iterator]);
                iterator++;
            }
        }
        if (num.empty() && str[iterator + 1] == ')') {
            atomWeight = str[iterator] - '0';
            iterator++;
            outputString += to_string(atomWeight);
            y = makeAtom(atomWeight);
        } else if (str[iterator + 1] == ')') {
            atomWeight = atoi(num.c_str());
            outputString += to_string(atomWeight);
            y = makeAtom(atomWeight);
        } else {
            if (num.empty()) {
                outputString += to_string(str[iterator] - '0');
            } else {
                atomWeight = atoi(num.c_str());
                outputString += to_string(atomWeight);
            }
            // if the number = length, an atom will be -1
            y = makeAtom(-1);
        }
    } else {
        if (str[iterator] == '(') outputString += ('(');
        readSeq(y, str, iterator);
    }
}

void BinKor::readSeq(lisp &y, string &str, int &iterator) {
    char ch;
    lisp p1, p2;
    if (str[iterator] == ')' && iterator < str.length()) {
        outputString += ')';
    } else if (isspace(str[iterator])) {
        outputString += ' ';
    }
    if (!str[++iterator]) {
        throw string("Error: there is no closing bracket");
    } else {
        // skip whitespaces
        while (isspace(str[iterator]) && iterator < str.length()) {
            iterator++;
            if (outputString[outputString.length() - 1] != ' ') {
                outputString += ' ';
            }
        }
        // skip (
        while (str[iterator] == '(' && iterator < str.length()) {
            iterator++;
            outputString += '(';
        }
        if (str[iterator] == ')') {
            while (str[iterator] == ')' && iterator < str.length()) {
                y = nullptr;
                iterator++;
                outputString += ')';
            }
        } else {
            readSExp(p1, str, iterator);
            readSeq(p2, str, iterator);
            y = cons(p1, p2);
        }
    }
}

int BinKor::getWeight(const lisp x) {
    if (isAtom(x)) {
//        resultString.push_back((char)x->node.weight);
//        cout << "X node weight " << x->node.weight << endl;
        if (x->node.weight != -1)
            count += x->node.weight;
    } else {
        getWeighHelper(x);
    }
    return count;
}

void BinKor::getWeighHelper(const lisp x) {
    if (!isNull(x)) {
        getWeight(head(x));
        getWeighHelper(tail(x));
    }
}

void BinKor::destroy(lisp s) {
    outputString.clear();
    count = 0;
    if (s != nullptr) {
        if (!isAtom(s)) {
            destroy(head(s));
            destroy(tail(s));
        }
        delete s;
    }
}

const string &BinKor::getOutputString() {
    return outputString;
}