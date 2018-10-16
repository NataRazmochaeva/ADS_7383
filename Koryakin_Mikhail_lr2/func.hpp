#include <iostream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <exception>
using namespace std;

typedef char base; // базовый тип элементов (атомов)
struct s_expr;
struct two_ptr{
    s_expr *hd;
    s_expr *tl;
}; //end two_ptr;
struct s_expr {
    bool tag; // true: atom, false: pair
    union{
        base atom;
        two_ptr pair;
    }node; //end union node
}; //end s_expr
typedef s_expr *lisp;
//int count = 0;
lisp head (const lisp s);
lisp tail (const lisp s);
lisp cons (const lisp h, const lisp t);
lisp make_atom (const base x);
bool isAtom (const lisp s);
bool isNull (const lisp s);
void del (lisp s);
base getAtom (const lisp s);
// функции ввода:
void read_lisp ( lisp& y, istream &is_str); // основная
void read_s_expr (base prev, lisp& y, istream &is_str);
void read_seq ( lisp& y, istream &is_str);
// функции вывода:
void write_lisp (const lisp x); // основная
void write_seq (const lisp x);
lisp copy_lisp (const lisp x);
lisp concat (const lisp y, const lisp z);
lisp linelist(const lisp s);
//....................................
void starter(istream &is);
int evade(lisp& sp);
