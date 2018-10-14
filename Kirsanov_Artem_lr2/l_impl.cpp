#include <iostream>
#include <strstream>
#include "l_intrfc.h"
using namespace std;
namespace h_list
{
    bool rep(lisp s, base x, base y){
        if(isNull(s)) return false;
        if(isAtom(s)){
             if(getAtom(s) == x){  s->node.atom = y; return true; }
             return false;
        }
        else return  rep(head(s), x, y) + rep(tail(s), x, y);
    }
    lisp head (const lisp s) // PreCondition: not null (s)
    {
		if (s != NULL) if (!isAtom(s))	return s->node.pair.hd;
			else { cerr << "Error: Head(atom) \n"; exit(1); }
		else { cerr << "Error: Head(nil) \n";
			exit(1);
		}
	}

	bool isAtom (const lisp s)
	{	if(s == NULL) return false;
        else return (s -> tag);
        }

        bool isNull (const lisp s)
        { return s==NULL;
	}

    lisp tail (const lisp s)// PreCondition: not null (s)
    {
		if (s != NULL) if (!isAtom(s))	return s->node.pair.tl;
			else { cerr << "Error: Tail(atom) \n"; exit(1); }
		else { cerr << "Error: Tail(nil) \n";
			exit(1);
		}
	}

    lisp cons (const lisp h, const lisp t) // PreCondition: not isAtom (t)
	{lisp p;
	if (isAtom(t)) { cerr << "Error: Tail(nil) \n"; exit(1);}
        else {
            p = new s_expr;
            if ( p == NULL)	{cerr << "Memory not enough\n"; exit(1); }
            else {
                p->tag = false;
                p->node.pair.hd = h;
                p->node.pair.tl = t;
                return p;
            }
        }
	}

	lisp make_atom (const base x)
	{	lisp s;
		s = new s_expr;
		s -> tag = true;
		s->node.atom = x;
		return s;
	}

	void destroy (lisp s) 
	{
        if ( s != NULL) {
            if (!isAtom(s)) {
                destroy ( head (s));
                destroy ( tail(s));
            }
            delete s;
            // s = NULL;
        };
	}

	base getAtom (const lisp s)
	{
		if (!isAtom(s)) { cerr << "Error: getAtom(s) for !isAtom(s) \n"; exit(1);}
		else return (s->node.atom);
	}

    void read_lisp ( lisp& y, strstream &st) // ввод списка с консоли
    {	base x = 0;

        do{ st >> x; } while (x==' ');
        if(x)
            read_s_expr (x, y, st);
    }

    void read_s_expr (base prev, lisp& y, strstream &st)
	{ //prev - ранее прочитанный символ}
		if ( prev == ')' ) {cerr << " ! List.Error 1 " << endl; exit(1); } 
		else if ( prev != '(' ) y = make_atom (prev);
             else read_seq (y, st);
    }

    void read_seq ( lisp& y, strstream &st)
	{	base x; 
		lisp p1, p2;

        if (!(st >> x)) {cerr << " ! List.Error 2 " << endl; exit(1);}
		else {
            while  ( x==' ' ){ st >> x; }
			if ( x == ')' ) y = NULL;
			else {
                read_s_expr ( x, p1, st);
                read_seq ( p2, st);
				y = cons (p1, p2);
			} 
		}
    }

    // ѕроцедура вывода списка с обрамл€ющими его скобками - write_lisp,
    // а без обрамл€ющих скобок - write_seq
	void write_lisp (const lisp x)
    {
    if (isNull(x)) cout << " ()";
	else if (isAtom(x)) cout << ' ' << x->node.atom;
        else  { //непустой список
			cout << " (" ;
			write_seq(x);
			cout << " )";
		}
    }

    void write_seq (const lisp x) //выводит последовательность элементов списка без обрамл€ющих его скобок
    {
        if (!isNull(x)) {
            write_lisp(head (x));
            write_seq(tail (x));
        }
    }
}
