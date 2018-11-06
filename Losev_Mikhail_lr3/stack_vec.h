#ifndef STACK_VEC_H
#define STACK_VEC_H

#include <iostream>


template <class base>
class Stack
{
    private:
        base * arr;
        int size;
        int len;
    public:
        Stack()
        {
            len = 0;
            size = 5;
            arr = new base[size];
        }


        ~Stack()
        {
            delete [] arr;
        }


        int lenth()
        {
            return len;
        }


        void push(base x)
        {
            if (len == size) 
            new_size(size<<1);
            arr[len++] = x;
            //cout << "Push -> " << x << endl;
        }

        base pop()
        {
            if (len == 0){
            	std::cerr << "error: pop(0)" << std::endl;
            	return arr[len];
            }
            
            return arr[--len];
        }

        base top()
        {
            return arr[len];
        }

        void destroy()
        {
            delete [] arr;
        }

        bool isEmpty()
        {
            return len == 0;
        }

        void new_size(int s)
        {
            if (s <= 0) 
                return;
            base *new_arr = new base[s];
            for (int i = 0; i < s; i++) 
                new_arr[i] = arr[i];
            delete[] arr;
            size = s;
            arr = new_arr;
            //cout<<"NEW SIZE "<<size<<endl;
        }
};

#endif
