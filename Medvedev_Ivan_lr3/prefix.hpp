template <class Type>
class Stack {
Type* arr;
int head,tail, size, maxsize;
public :
   Stack () ;
   void push ( Type sym ) ;
   Type pop();
   int Size();
   void resize(int maxsize);
   Type Top();
} ;
//----------------

template <class Type>
Stack<Type>::Stack()
{
   arr = new char[100];
   head = size = 0 ;
   tail= -1;
   maxsize = 100;
}
//----------------

template <class Type>
void Stack<Type>::push (Type sym){
    if (size == maxsize){
        resize(2*maxsize);

    }

        tail++;
        size++;
        arr[tail] = sym;
}
//----------------
template <class Type>
Type Stack<Type>::pop(){
    char x;
    x = arr[tail];
        tail--;
        size--;
        return(x);
}

//----------------

template <class Type>
int Stack<Type>::Size(){
    return (size);
}


template <class Type>
void Stack<Type>::resize(int new_size){
    Type* new_arr = new Type[new_size];
    int i;
    for (i = 0; i < size; i++){
        new_arr[i] = arr[i];
    }
    delete[] arr;
    maxsize = new_size;
    arr = new_arr;

}

template <class Type>
Type Stack<Type>::Top(){
    return(arr[tail]);

}

