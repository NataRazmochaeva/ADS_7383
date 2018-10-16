#ifndef LIST_H
#define LIST_H

typedef char base;

class List
{
public:
    List();
    void set_atom(base atom);
    base get_atom();
    void set_pair(class Pair* ptr);
    class Pair* get_pair();
    bool is_atom();
    ~List();
private:
    bool flag; //true: atom, false: pair
    union {
        base atom;
        class Pair* p_ptr;
    }node{};
};

#endif
