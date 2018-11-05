#ifndef STACK_H
#define STACK_H

template<class BASE>
class Stack
{
public:
    Stack(long);
    BASE top();
    BASE pop();
    void resize(long);
    void push(BASE);
    void clear();
    bool is_empty();
    ~Stack();
private:
    BASE* arr;
    int arr_size;
    int end_index;
};

template<class BASE>
Stack<BASE>::Stack(long size)
{
    arr = new BASE[size];
    arr_size = size;
    end_index = 0;
}

template<class BASE>
BASE
Stack<BASE>::top()
{
    return arr[end_index-1];
}

template<class BASE>
BASE
Stack<BASE>::pop()
{
    end_index--;
    return arr[end_index];
}

template<class BASE>
void
Stack<BASE>::resize(long new_size)
{
    auto new_arr = new BASE[new_size];
    for(int i=0; i<arr_size; i++)
        new_arr[i] = arr[i];
    arr_size = new_size;
    delete arr;
    arr = new_arr;
}

template<class BASE>
void
Stack<BASE>::push(BASE el)
{
    if(end_index == arr_size-1)
        resize(arr_size*2);

    arr[end_index] = el;
    end_index++;
}

template<class BASE>
void
Stack<BASE>::clear()
{
    for(int i=0; i<end_index; i++)
        arr[end_index] = 0;
    end_index = 0;
}

template<class BASE>
bool
Stack<BASE>::is_empty()
{
    return end_index == 0;
}

template<class BASE>
Stack<BASE>::~Stack<BASE>()
{
    clear();
    delete[] arr;
}

#endif // STACK_H
