#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <cmath>
#include <exception>

using namespace std;
using base = int;

struct bracket{
    int open;
    int close;
};

template <class T>
class Stack
{
private:
        T * arr;
        int size;
        int len;
public:
        Stack();
        ~Stack();
        int Size();
        void Push(T x);
        T Pop();
        T Top();
        void Clear();
        bool IsEmpty();
        void new_size(T s);
};
        template <class T>
        Stack<T>::Stack()
        {
                len = 0;
                arr = new T[size = 5];
        }

        template <class T>
        Stack<T>::~Stack()
        {
                delete[] arr;
        }

        template <class T>
        int Stack<T>::Size()
        {
                return len;
        }

        template <class T>
        void Stack<T>:: Push(T x)
        {
                if (len == size)
                   new_size(size<<1);
                arr[len++] = x;
        }
        template <class T>
        T Stack<T>::Pop()
        {
            if (len == 0)
            return arr[len];
            return arr[--len];
        }
        template <class T>
        T Stack<T>::Top()
        {
            return arr[len];
        }
        template <class T>
        void Stack<T>::Clear()
        {
            delete arr;
        }

        template <class T>
        bool Stack<T>::IsEmpty()
        {
            return len == 0;
        }
        template <class T>
        void Stack<T>::new_size(T s)
        {
                if (s<=0)
            return;
                T * new_arr = new T[s];
                for (int i = 0; i<s; i++)
            new_arr[i] = arr[i];
                delete[] arr;
                size = s;
                arr = new_arr;
        cout<<"NEW SIZE "<<size<<endl;

        }



void written(int k, struct bracket* obj);

void forstack(string a);

int comp1(const void* a, const void* b);

int comp2(const void* a, const void* b);

string except(string str0);
