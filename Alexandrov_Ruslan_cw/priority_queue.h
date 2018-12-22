#ifndef COURSEWORK_PRIORITY_QUEUE_H
#define COURSEWORK_PRIORITY_QUEUE_H

#include <utility>

template<typename T>
struct PriorityQueueItem {
    int key;
    T data;
};
template<typename T>
struct PriorityQueue {
    int size_;
    int capacity_;
    PriorityQueueItem<T> *heap_;
};

template<typename T>
PriorityQueue<T> *createPQ(int capacity) {
    PriorityQueue<T> *pq = new PriorityQueue<T>;
    pq->heap_ = new PriorityQueueItem<T>[capacity];
    pq->capacity_ = capacity;
    pq->size_ = 0;
    return pq;
}

template<typename T>
int size(PriorityQueue<T> *pq) {
    return pq->size_;
}

template<typename T>
void siftUp(PriorityQueue<T> *pq, int index) {
    int parent = (index - 1) / 2;
    while (parent >= 0 && pq->heap_[index].key < pq->heap_[parent].key) {
        std::swap(pq->heap_[index], pq->heap_[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

template<typename T>
bool push(PriorityQueue<T> *pq, int key, const T &data) {
    if (pq->size_ >= pq->capacity_) return false;
    pq->heap_[pq->size_].key = key;
    pq->heap_[pq->size_].data = data;
    pq->size_++;
    siftUp(pq, pq->size_ - 1);
    return true;
}

template<typename T>
void siftDown(PriorityQueue<T> *pq, int index) {
    int l = 2 * index + 1;
    int r = 2 * index + 2;
    int min = index;
    if (l < pq->size_ && pq->heap_[l].key < pq->heap_[min].key)
        min = l;
    if (r < pq->size_ && pq->heap_[r].key < pq->heap_[min].key)
        min = r;
    if (min != index) {
        std::swap(pq->heap_[index], pq->heap_[min]);
        siftDown(pq, min);
    }
}

template<typename T>
T pop(PriorityQueue<T> *pq) {
    std::swap(pq->heap_[0], pq->heap_[pq->size_ - 1]);
    pq->size_--;
    siftDown(pq, 0);
    return pq->heap_[pq->size_].data;
}

template<typename T>
void destroyPq(PriorityQueue<T> *pq) {
    delete[] pq->heap_;
    delete pq;
}

#endif //COURSEWORK_PRIORITY_QUEUE_H
