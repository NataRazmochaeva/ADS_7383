#include "list.h"

using namespace std;

namespace h_list //используемое пространство имен
{

//....................................
lisp head(const lisp s) //создание головы списка
{
    if (s != NULL)
        if (!isAtom(s))	return s->node.pair.hd;//в начале узел идёт
        else {
            cerr << "\033[31m Error: Head(atom) \n\033[0m";
            exit(1);
        }//cerr - для вывода ошибок
    else {
        cerr << "\033[31m Error: Head(nil) \n\033[0m";
        exit(1);
    }
}
//.......................................
bool isAtom(const lisp s)//проверка на атом
{
    if (s == NULL) return false;//s - указатель на элемент списка
    else return (s->tag);//false - узел, true - атом
}
//.......................................
bool isNull(const lisp s)//проверка на пустоту
{
    return s == NULL;
}
//.......................................
lisp tail(const lisp s)
{
    if (s != NULL) if (!isAtom(s))	return s->node.pair.tl;//в конце узел идёт
        else {
            cerr << "\033[31m Error: Tail(atom) \n\033[0m";
            exit(1);
        }
    else {
        cerr << "\033[31m Error: Tail(nil) \n\033[0m";
        exit(1);
    }
}
//.......................................
lisp cons(const lisp h, const lisp t)//создает новый список из головы и хвоста
{
    lisp p;
    if (isAtom(t)) {
        cerr << "\033[31m Error: Cons(*, atom) \n\033[0m";
        exit(1);
    }
    else {
        p = new s_expr;//создание узла
        if (p == NULL)	{
            cerr << "\033[31m Memory not enough \n\033[0m";
            exit(1);
        }
        else
        {
            p->tag = false;
            p->node.pair.hd = h;
            p->node.pair.tl = t;
            return p;
        }
    }
}
//...........................
lisp make_atom(const base x)//создание атомарного выражения
{
    lisp s;
    s = new s_expr;//оператор, обеспечивающий выделение динамической памяти
    s->tag = true;
    s->node.atom = x;//заполнение элемента списка
    return s;
}

//...........................
void destroy(lisp s)//удаляет весь списо
{
    if (s != NULL) {
        if (!isAtom(s)) {
            destroy(head(s));
            destroy(tail(s));
        }
        delete s;//оператор, возвращающий память, выделенную new, обратно в кучу
    };
    s = NULL;
}
//...........................
base getAtom(const lisp s)//возвращает значение атома
{
    if (!isAtom(s)) {
        cerr << "\033[31m Error: getAtom(s) for !isAtom(s) \n\033[0m";
        exit(1);
    }
    else return (s->node.atom);
}

//...........................
// ввод списка с консоли
void read_lisp(lisp& y, istream& in)//элемент, атом
{
    base x;
    do in >> x;
    while (x == ' ');
    read_s_expr(x, y, in);
}
//...........................
void read_s_expr(base prev, lisp& y, istream& in)
{   //prev   － ранее прочитанный символ}
    if (prev == ')') {
        cerr << "\033[31m ! List.Error(1) \033[0m" << endl; //отсутствует октрывающая скобка
        exit(1);
    }
    else if (prev != '(') y = make_atom(prev);
    else read_seq(y, in);
}
//...........................
void read_seq(lisp& y, istream& in)//создание списка
{
    base x;
    lisp p1, p2;

    if (!(in >> x)) {
        cerr << "\033[31m ! List.Error(2) \033[0m" << endl; //отсутствует закрывающая скобка
        exit(1);
    }
    else {
        while (x == ' ') in >> x;
        if (x == ')') y = NULL;
        else {
            read_s_expr(x, p1, in);
            read_seq(p2, in);
            y = cons(p1, p2);
        }
    }
}
//...........................
void write_lisp(const lisp x, ostream& out)
{   //пустой список выводится как ()
    if (isNull(x)) out << " ()";
    else if (isAtom(x)) out << ' ' << x->node.atom;
    else  { //непустой список}
        out << " (";
        write_seq(x, out);
        out << " )";
    }
}
//...........................
void write_seq(const lisp x, ostream& out)
{   //выводит последовательность элементов списка без обрамляющих его скобок
    if (!isNull(x)) {
        write_lisp(head(x), out);
        write_seq(tail(x), out);
    }
}
//...........................
lisp copy_lisp(const lisp x)//функция копирования списка
{
    if (isNull(x)) return NULL;
    else if (isAtom(x)) return make_atom(x->node.atom);
    else return cons(copy_lisp(head(x)), copy_lisp(tail(x)));
}
//..........................
int max(int a, int b)
{
    if (a > b) return a;
    return b;
}
//.........................
int listDeepth(lisp list)
{
    if (isNull(list)) return 0;
    if (isAtom(list)) return -1;
    return max(listDeepth(head(list)) + 1, listDeepth(tail(list)));
}

} // end of namespace h_list
