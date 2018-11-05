#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;

namespace h_list//пространство имен
{
typedef char base;	// базовый тип элементов (атомов)

struct s_expr;
struct  two_ptr//содержит два указателя, на голову и хвост
{
    s_expr *hd;
    s_expr *tl;
};

struct s_expr {
    bool tag; // true: atom, false: pair
    union
    {
        base atom;
        two_ptr pair;
    } node;
};

typedef s_expr *lisp;

// функции
void print_s_expr(lisp s);
// базовые функции:
lisp head(const lisp s);
lisp tail(const lisp s);
lisp cons(const lisp h, const lisp t);
lisp make_atom(const base x);
bool isAtom(const lisp s);
bool isNull(const lisp s);
void destroy(lisp s);

base getAtom(const lisp s);

// функции ввода:
void read_lisp(lisp& y, istream& in);			// основная
void read_s_expr(base prev, lisp& y, istream& in);
void read_seq(lisp& y, istream& in);

// функции вывода:
void write_lisp(const lisp x, ostream& out);		// основная
void write_seq(const lisp x, ostream& out);

lisp copy_lisp(const lisp x);

int max(int a, int b); //поиск максимального значения
int listDeepth(lisp list); //счетчик уровней вложенности

} // end of namespace h_list

#endif // LIST_H_INCLUDED
