// continue of namespace h_list
#include "l_intrfc.h"
#include <iostream>
#include <cstdlib>

using namespace std;
namespace h_list
{

	bool isEqual (const lisp f, const lisp s)
	{
		if (isNull(f) && isNull(s))
			return true;
		if (isNull(f) != isNull(s))
			return false;


		if (isAtom(f) && isAtom(s))
			return (getAtom(f) == getAtom(s));
		else 
			if (!isAtom(f) && !isAtom(s))
				return ( isEqual(head(s), head(f)) && isEqual(tail(s), tail(f)) );
			else return false; // one is atom and the other is not
	}

	//....................................
	lisp head (const lisp s)
	{// PreCondition: not null (s)
		if (s != NULL) if (!isAtom(s))	return s->node.pair.hd;
			else { cerr << "Error: Head(atom) \n";return NULL; }
		else { cerr << "Error: Head(nil) \n";
			return NULL;
		}
	}
	//.......................................
	bool isAtom (const lisp s)
	{	if(s == NULL) return false;
	else return (s -> tag);
	}
	//.......................................
	bool isNull (const lisp s)
	{ return s==NULL;
	}
	//.......................................
	lisp tail (const lisp s)
	{// PreCondition: not null (s)
		if (s != NULL) if (!isAtom(s))	return s->node.pair.tl;
			else { cerr << "Error: Tail(atom) \n"; return NULL; }
		else { cerr << "Error: Tail(nil) \n";
			return NULL;
		}
	}
	//.......................................
	lisp cons (const lisp h, const lisp t)
	// PreCondition: not isAtom (t)
	{lisp p;
	if (isAtom(t)) { cerr << "Error: Tail(nil) \n"; return NULL;}
	else {	
		p = new s_expr; 
		if ( p == NULL)	{cerr << "Memory not enough\n"; return NULL; } 	
		else {
			p->tag = false;
			p->node.pair.hd = h;
			p->node.pair.tl = t;
			return p;	
		}
	}
	}
	//...........................
	lisp make_atom (const base x)
	{	lisp s;
		s = new s_expr;
		s -> tag = true;
		s->node.atom = x;
		return s;
	}

	//...........................
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
	//...........................
	base getAtom (const lisp s)
	{
		if (!isAtom(s)) { cerr << "Error: getAtom(s) for !isAtom(s) \n"; return 0;}
		else return (s->node.atom);
	}

	
	//...........................
	
	//...........................
	// Процедура вывода списка с обрамляющими его скобками - write_lisp,
	//  а без обрамляющих скобок - write_seq
	void write_lisp (const lisp x)
	{//пустой список выводится как () 
	if (isNull(x)) cout << " ()";
	else if (isAtom(x)) cout << ' ' << x->node.atom;
		else  { //непустой список} 
			cout << " (" ;
			write_seq(x);
			cout << " )";
		}
	} // end write_lisp
	//...........................
	void write_seq (const lisp x)  
	{//выводит последовательность элементов списка без обрамляющих его скобок
		if (!isNull(x)) {
			write_lisp(head (x)); 
			write_seq(tail (x));
		}
	}
	//...........................
	lisp copy_lisp (const lisp x)
	{	if  (isNull(x)) return NULL;
		else if (isAtom(x)) return make_atom (x->node.atom);
		else return cons (copy_lisp (head (x)), copy_lisp (tail(x)));
	} //end copy-lisp

} // end of namespace h_list
