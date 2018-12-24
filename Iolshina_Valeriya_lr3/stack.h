#pragma once

namespace stack
{
	typedef int base;
	class Stack 
	{
		private:
		struct node;
		node *topOfStack;
		public:
		Stack()
		{
			topOfStack = NULL;
		};
		base top();
		void pop();
		base pop2();
		void push(const base &x);
		bool isNull();
		void destroy();
	};
}
