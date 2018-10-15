#include "list.h"
#include "pair.h"

List::List() {
    flag = false;
}

void List::set_atom(base atom) {
    flag = true;
    node.atom = atom;
}

base List::get_atom() {
    return node.atom;
}

void List::set_pair(Pair* ptr) {
    flag = false;
    node.p_ptr = ptr;
}

Pair* List::get_pair() {
    return node.p_ptr;
}

bool List::is_atom() {
    return this->flag;
}

List::~List() {
    if(!flag && node.p_ptr!=nullptr)
        delete node.p_ptr;
}
