#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

typedef char base;
struct s_expr;
struct  two_ptr
{
	s_expr *hd;
	s_expr *tl;
};

struct s_expr
{
	bool tag;
	union
	{
        	base atom;
        	two_ptr pair;
    	}node;
};

typedef s_expr *lisp;

lisp head (const lisp s);
lisp tail (const lisp s);
lisp cons (const lisp h, const lisp t);
lisp make_atom (const base x);
bool isAtom (const lisp s);
bool isNull (const lisp s);
void destroy (lisp s);
base getAtom (const lisp s);
void read_lisp (lisp& y, stringstream &xstream);
void read_s_expr (base prev, lisp& y, stringstream &xstream);
void read_seq (lisp& y, stringstream &xstream);
void write_lisp (const lisp x);
void write_seq (const lisp x);

lisp  del_atom(lisp s, char x)
{
	if (isNull(s)) return NULL;
	if (isAtom(s))
	{
 		if(s->node.atom != x)
			return s;
        	else
		{
        		delete s;
			return NULL;
        	}
	}
        s->node.pair.hd = del_atom(head(s),x);
	s->node.pair.tl = del_atom(tail(s),x);
	return ((head(s) == NULL)? tail(s) : s);
}

int main()
{
	stringstream xstream;
	bool b = 1;
	lisp s = NULL;
	char x;
	char str[100];
	int c = 0;
	while(c != 3)
	{
        	cout << "Введите 1, если хотите ввести выражение с клавиатуры.\n"
                	"Введите 2, если еспользовать выражение из файла test.txt.\n"
                	"Введите 3, если хотите закончить работу." << endl;
        	cin >> c;
        	switch(c)
		{
        		case 1:
            		{
				cout << "Введите искомый элемент X\n";
        			cin >> x;
                		cout << "Введите выражение: \n";
                		cin.get();
                		cin.getline(str, 1000);
                		xstream << str;
                		read_lisp(s, xstream);
                		break;
            		}
            		case 2:
            		{
                		cout << "Введите искомый элемент X\n";
        			cin >> x;
				ifstream outfile;
                		outfile.open("test.txt");
                		if (!outfile)
                		{
                    			cout << "Входной файл не открыт!\n";
                    			b = 0;
                    			break;
                		}
                		outfile.read(str, 1000);
                		outfile.close();
                		xstream << str;
                		read_lisp (s, xstream);
                		break;
            		}
            		case 3:
            		{
				b=0;
	    			break;
			}
            		default:
            		{
                		cout << "Введите верное число\n";
                		break;
            		}
        	}
        	if(b)
		{
        		cout << "Введен list1: \n";
        		write_lisp (s);
        		cout<<endl;
        		cout << "Произведен поиск элемента: " << x << endl;
			s = del_atom(s,x);
	        	cout << "Результат работы программы \n";
				write_lisp(s);
				cout << endl;
        		destroy(s);
        	}
	}
return 0;
}

lisp head(const lisp s)
{
	if (s != NULL)
        	if (!isAtom(s))
            		return s->node.pair.hd;
        	else
        	{
           		cerr << "Error: Head(atom) \n";
           		exit(1);
        	}
	else
    	{
        	cerr << "Error: Head(nil) \n";
        	exit(1);
    	}
}

bool isAtom(const lisp s)
{
	if(s == NULL)
        	return false;
    	else
        	return (s -> tag);
}

bool isNull (const lisp s)
{
	return s==NULL;
}

lisp tail(const lisp s)
{
	if (s != NULL)
        	if (!isAtom(s))
            		return s->node.pair.tl;
        else
        {
          	cerr << "Error: Tail(atom) \n";
        	exit(1);
        }
    	else
    	{
        	cerr << "Error: Tail(nil) \n";
        	exit(1);
    	}
}

lisp cons(const lisp h, const lisp t)
{
	lisp p;
    	if (isAtom(t))
    	{
        	cerr << "Error: Tail is head \n";
        	exit(1);
    	}
    	else
    	{
        	p = new s_expr;
        	if ( p == NULL)
        	{
            		cerr << "Memory not enough\n";
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

lisp make_atom(const base x)
{
	lisp s;
    	s = new s_expr;
    	s -> tag = true;
    	s->node.atom = x;
    	return s;
}


void destroy (lisp s)
{
	if (s != NULL)
    	{
        	if (!isAtom(s))
        	{
            		destroy (head (s));
            		destroy (tail(s));
        	}
        	delete s;
    	}
}

base getAtom (const lisp s)
{
	if (!isAtom(s))
    	{
        	cerr << "Error: getAtom(s) for !isAtom(s) \n";
        	exit(1);
    	}
    	else
		return (s->node.atom);
}

void read_lisp (lisp& y, stringstream &xstream)
{
	base x;
    	do
        	xstream >> x;
    	while (x==' ');
    		if(x)
        		read_s_expr (x, y, xstream);
}

void read_s_expr (base prev, lisp& y, stringstream &xstream)
{
	if (prev == ')' )
    	{
        	cerr << "Error: the initial brace is closing\n";
        	exit(1);
    	}
    	else
        	if (prev != '(' )
            		y = make_atom (prev);
         	else read_seq (y, xstream);
}

void read_seq (lisp& y, stringstream &xstream)
{
	base x;
	lisp p1, p2;
	if (!(xstream >> x))
    	{
        	cerr << "Error: there is no closing bracket\n";
        	exit(1);
    	}
    	else
    	{
        	while  ( x==' ' )
            		xstream >> x;
        	if ( x == ')' )
            		y = NULL;
        	else
        	{
            		read_s_expr (x, p1, xstream);
            		read_seq (p2, xstream);
            		y = cons (p1, p2);
        	}
    	}
}

void write_lisp (const lisp x)
{
	if (isNull(x))
        	cout << " ()";
    	else
        	if (isAtom(x))
            		cout << ' ' << x->node.atom;
        	else
        	{
            		cout << " (" ;
            		write_seq(x);
            		cout << " )";
        	}
}

void write_seq (const lisp x)
{
	if (!isNull(x))
    	{
        	write_lisp(head (x));
        	write_seq(tail (x));
    	}
}
