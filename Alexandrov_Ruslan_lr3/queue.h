#pragma once

#include <iostream>

using namespace std;

template<class Item>
class Queue {
private:
    Item *q;
    int N;
    int size;
public:
    Queue(int newSize);

    void enqueue(Item item);

    void dequeue();

    Item getFront();

    bool isFull();

    bool isEmpty();

    Item *resize(Item *prev);

    ~Queue();
};


template<class Item>
Queue<Item>::Queue(int newSize) {
    q = new Item[newSize];
    N = 0;
    size = newSize;
}

template<class Item>
void Queue<Item>::enqueue(Item item) {
    if (isFull()) {
        q = resize(q);
    }
    q[N] = item;
    N++;
}

template<class Item>
void Queue<Item>::dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty" << endl;
        return;
    }
    for (int i = 0; i < size-1; i++) {
        q[i] = q[i+1];
    }
    this->size--;
    this->N--;
}

template<class Item>
Item Queue<Item>::getFront() {
    if (isEmpty()) {
        cout << "Queue is empty" << endl;
        return 0;
    }
    Item returnEl = q[0];
    dequeue();
    return returnEl;
}

template<class Item>
bool Queue<Item>::isEmpty() {
    return this->N == 0;
}

template<class Item>
Item *Queue<Item>::resize(Item *prev) {
    int newSize = size * 2;
    Item *temp = new Item[newSize];
    for (int i = 0; i < size; i++) {
        temp[i] = prev[i];
    }
    size = newSize;
    return temp;
}

template<class Item>
bool Queue<Item>::isFull() {
    return N == size;
}

template<class Item>
Queue<Item>::~Queue() {
    delete[] q;
}