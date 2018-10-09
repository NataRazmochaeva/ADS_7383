#pragma once

template <class T>
class Queue{
public:
    Queue(unsigned int);
    unsigned int get_size();
    void push(T);
    void resize(unsigned int);
    bool isEmpty();
    T pop();
    ~Queue();
private:
    unsigned int vsize;
    unsigned int qsize;
    T* vstart;
    T* qstart;
    T* qend;
};

template <class T>
Queue<T>::Queue(unsigned int size) : vsize(size), qsize(0) {
    vstart = new T[size];
    qstart = vstart;
    qend = vstart;
}

template <class T>
unsigned int Queue<T>::get_size(){
    return qsize;
}

template <class T>
void Queue<T>::push(T value) {
    if(qend != qstart || (qsize == 0 && vsize != 0))
        *qend = value;
    else {
        resize(vsize*2);
        *qend = value;
    }
    if(qend < (vstart + vsize - 1))
        ++qend;
    else
        qend = vstart;
    ++qsize;
}

template <class T>
void Queue<T>::resize(unsigned int new_size) {
    T* new_vect = new T[new_size];
    int i;
    for(i=0; i<(vsize-(qstart-vstart)); ++i)
        new_vect[i] = qstart[i];
    for(int j=0; i < vsize; ++i, ++j)
        new_vect[i] = vstart[j];
    qstart = new_vect;
    qend = new_vect + qsize;
    delete vstart;
    vstart = new_vect;
    vsize = new_size;
}

template <class T>
bool Queue<T>::isEmpty() {
    return qsize == 0;
}

template <class T>
T Queue<T>::pop() {
    T ret = *qstart;
    if(qstart != (vstart + vsize - 1))
        ++qstart;
    else
        qstart = vstart;
    --qsize;
    return ret;
}

template <class T>
Queue<T>::~Queue() {
    delete vstart;
}

