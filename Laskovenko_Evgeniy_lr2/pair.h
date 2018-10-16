#ifndef PAIR_H
#define PAIR_H

class Pair
{
public:
    Pair();
    void set(class List* head, class List* tail);
    class List* get_head();
    class List* get_tail();
    bool is_null();
    ~Pair();
private:
    class List* hd;
    class List* tl;
};

#endif
