#include "pair.h"
#include "list.h"

Pair::Pair()
{
    hd = nullptr;
    tl = nullptr;
}

void Pair::set(List* head, List* tail)
{
    hd = head;
    tl = tail;
}

List* Pair::get_head()
{
    return hd;
}

List* Pair::get_tail()
{
    return tl;
}

bool Pair::is_null()
{
    return this == nullptr;
}

Pair::~Pair()
{
    delete hd;
    delete tl;
}
