// интерфейс АТД "Иерархический Список"
#include <iostream>
#include <cstdlib>

namespace h_list
{
	typedef char base;	// базовый тип элементов (атомов)

	struct s_expr;
	struct  two_ptr
		{
		s_expr *hd;
		s_expr *tl;
	} ;	//end two_ptr;

	struct s_expr {
		bool tag; // true: atom, false: pair
		union  
			{
			base atom;
			two_ptr pair;	
		} node;		//end union node
	};			//end s_expr 
	
	typedef s_expr *lisp;

	// функции 
	bool isEqual (const lisp f, const lisp s);
	// базовые функции:
	lisp head (const lisp s);
	lisp tail (const lisp s);
	lisp cons (const lisp h, const lisp t);
	lisp make_atom (const base x);
	bool isAtom (const lisp s);
	bool isNull (const lisp s);
	void destroy (lisp s);
	
	base getAtom (const lisp s);

	// функции ввода:
	// ввод списка с консоли
	template <typename stream>
	void read_lisp ( stream *s, lisp& y)
	{	base x;
		do (*s).get(x); while (x==' ');
		read_s_expr (s, x, y);
	} //end read_lisp
	//...........................
	template <typename stream>
	void read_s_expr (stream s, base prev, lisp& y)
	{ //prev - ранее прочитанный символ}
		if ( prev == ')' ) { return; } 
		else if ( prev != '(' ) y = make_atom (prev);
			 else read_seq (s, y);
	} //end read_s_expr
	//...........................
	template <typename stream>
	void read_seq (stream *s, lisp& y) 
	{	base x; 
		lisp p1, p2;

		if (!(*s).get(x)) { return;}
		else {
			while  ( x==' ' ) (*s).get(x);
			if ( x == ')' ) y = NULL;
			else {
				read_s_expr (s, x, p1);
				read_seq (s, p2);
				y = cons (p1, p2);
			} 
		}
	} //end read_seq
	
	// функции вывода:
	void write_lisp (const lisp x);		// основная
	void write_seq (const lisp x);  
	
	lisp copy_lisp (const lisp x);

} // end of namespace h_list