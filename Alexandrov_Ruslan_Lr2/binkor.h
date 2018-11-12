#pragma once

#include <sstream>
#include <vector>

using namespace std;

class BinKor {
public:
    typedef int base;
    struct s_expr;
    struct two_ptr {
        s_expr *hd;
        s_expr *tl;
    };
    struct s_expr {
        bool tag;
        union {
            base weight;
            two_ptr pair;
        } node;
    };
    typedef s_expr *lisp;

    lisp head(const lisp s);

    lisp tail(const lisp s);

    lisp cons(const lisp h, const lisp t);

    lisp makeAtom(const base x);

    bool isAtom(const lisp s);

    bool isNull(const lisp s);

    void destroy(lisp s);

    void readLisp(lisp &y, string &str);

    void readSExp(lisp &y, string &str, int &iterator);

    void readSeq(lisp &y, string &str, int &iterator);

    int getWeight(const lisp x);

    void getWeighHelper(const lisp x);

    bool checkEl(base x);

    const string &getOutputString();

private:
    string outputString;
    int count = 0;
    vector<base> weights;
};

