#include <iostream>
#include "function.hpp"

using namespace std;

bool const_expression(istream &is, int visual, int step, bool cur)
{
    char c;

    if(is >> c)
    {
        if(!visual)
            cout << c;

        if(c>=48 && c<=57)
        {
            if(visual)
            {
                cout <<"STEP"<<'{'<<step<<"}: "<<c<<" IS DIGIT."<<endl;
                step++;
            }
            cur = true;
            cur = const_expression(is, visual, step, cur);
        }
        else if(cur==true && (c==42 || c==43 || c==45))
        {
            if(visual)
            {
                cout <<"STEP"<<'{'<<step<<"}: "<<c<<" IS OPERATOR."<<endl;
                step++;
            }
            cur = false;
            cur = const_expression(is, visual, step,cur);
        }
        else
        {
            if(visual)
                cout <<"STEP"<<'{'<<step<<"}: "<<c<<" IS INVALID. Algorithm ends."<<endl;
            cout << endl;
            return cur = false;
        }
    }
    else
    {
        cout << endl;
        return cur;
    }
}
