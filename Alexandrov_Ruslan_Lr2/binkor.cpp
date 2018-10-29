#include <iostream>
#include "binkor.h"


BinKor::s_expr *BinKor::head(const lisp s) {
    if (s != NULL) {
        return s->node.pair.hd;
    } else {
        return NULL;
    }
}

BinKor::s_expr *BinKor::tail(const lisp s) {
    if (s != NULL) {
        return s->node.pair.tl;
    } else {
        return NULL;
    }
}

bool BinKor::isAtom(const lisp s) {
    if (s == NULL)
        return false;
    else
        return (s->tag);
}

bool BinKor::isNull(const lisp s) {
    return s == NULL;
}

BinKor::lisp BinKor::cons(const lisp h, const lisp t) {
    lisp p;
    p = new s_expr;
    if (p == NULL) {
        cout << "Memory not enough" << endl;
        return nullptr;
    }
    else {
        p->tag = false;
        p->node.pair.hd = h;
        p->node.pair.tl = t;
        return p;
    }
}

BinKor::lisp BinKor::make_atom(const base x) {
    lisp s;
    s = new s_expr;
    s->tag = true;
    s->node.atom = x;
    return s;
}

void BinKor::read_lisp(lisp &y, stringstream &xstream) {
    base x;
    do
        xstream >> x;
    while (x == ' ');
    if (x)
        read_s_expr(x, y, xstream);
}

void BinKor::read_s_expr(base prev, lisp &y, stringstream &xstream) {
    if (prev == ')')  {
        cout << "Error: the initial brace is closing" << endl;
        return;
    }
    else if (prev != '(') {
        if (!isdigit(prev)) {
            cout << "Element " << prev << " it isn`t a digit, try again";
            exit(1);
        }
        y = make_atom(prev);
    } else read_seq(y, xstream);
}

void BinKor::read_seq(lisp &y, stringstream &xstream) {
    base x;
    lisp p1, p2;

    if (!(xstream >> x)) {
        cout << "Error: there is no closing bracket" << endl;
        return;
    }
    else {
        while (x == ' ')
            xstream >> x;
        if (x == ')') {
            y = NULL;
        } else {
            read_s_expr(x, p1, xstream);
            read_seq(p2, xstream);
            y = cons(p1, p2);
        }
    }
}

void BinKor::write_lisp(const lisp x) {
    if (isNull(x))
        cout << "()";
    else if (isAtom(x))
        cout << x->node.atom;
    else {
        cout << "(";
        write_seq(x);
        cout << ")";
    }
}

void BinKor::write_seq(const lisp x) {
    if (!isNull(x)) {
        write_lisp(head(x));
        write_seq(tail(x));
    }
}

int BinKor::getWeight(const lisp x) {
    if (isAtom(x)) {
        resultString.push_back(x->node.atom);
    } else {
        resultString.push_back('(');
        getWeighHelper(x);
        resultString.push_back(')');
        if (resultString.at(resultString.size() - 1) == ')' && resultString.at(resultString.size() - 2) != ')') {
            count += (resultString.at(resultString.length() - 2)) - '0';
        }
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
    resultString.clear();
    count = 0;
    if (s != NULL) {
        if (!isAtom(s)) {
            destroy(head(s));
            destroy(tail(s));
        }
        delete s;
    }
}
