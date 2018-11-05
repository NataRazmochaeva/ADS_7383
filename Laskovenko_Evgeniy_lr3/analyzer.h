#include <iostream>
#include "stack.h"
#include "myexception.h"

#define ARR_SIZE 10

using namespace std;

#ifndef ANALYZER_H
#define ANALYZER_H

bool
syn_analyzer(istream& is_str, long size)
{
    char ch;
    bool flag = false;
    Stack<char> st(ARR_SIZE);

    for(int i=0; i<size; i++)
    {
        is_str >> ch;
        if(ch=='A' || ch=='B')
            st.push(ch);
        else if(ch=='C')
        {
            if(st.is_empty())
                throw new analyzer_err("Where is x1? (Stack is empty)");
            while(!st.is_empty())
            {
                if(is_str >> ch)
                {
                    if(st.pop()==ch)
                        flag = true;
                    else
                        throw new analyzer_err("x2 is not reversed x1!");
                    i++;
                }
                else
                    throw new analyzer_err("x2 is wrong! (x1 is greater)");
            }
        }
        else if(ch=='D')
        {
            if(!flag)
                throw new analyzer_err("D is before a,b,c,d-elements?");
            flag = false;
        }
        else
            throw new analyzer_err("Wrong character in string! (Not A, B, C or D)");
    }
    if(!st.is_empty())
        throw new analyzer_err("There is no C in a,b,c,d-element!");
    return flag;
}

#endif // ANALYZER_H
