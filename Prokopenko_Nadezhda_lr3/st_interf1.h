#include<iostream>

namespace st_modul1
{
            typedef char* base;

	class Stack {
	private:
		struct node;
	node *topOfStack;
	public:
		Stack ()
			{ topOfStack = NULL;
			};
		base top (void);
		void pop (void);
		base pop2(void);
		void push (const base &x);
		bool isNull(void);
		void destroy (void);
	};
}

int signValue (char* c);
