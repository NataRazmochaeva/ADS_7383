#include "atoms.h"

Atoms::Atoms()
{
    atom = '\0';
    next = nullptr;
}

void Atoms::set_atom(base am)
{
    atom = am;
}

base Atoms::get_atom()
{
    return atom;
}

void Atoms::set_next(Atoms* nxt)
{
    next = nxt;
}

Atoms* Atoms::get_next()
{
    return next;
}

Atoms::~Atoms()
{
    delete next;
}
