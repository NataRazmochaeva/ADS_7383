#ifndef ATOMS_H
#define ATOMS_H

typedef char base;

class Atoms
{
public:
    Atoms();
    void set_atom(base am);
    base get_atom();
    void set_next(Atoms* nxt);
    Atoms* get_next();
    ~Atoms();
private:
    base atom;
    Atoms* next;
};

#endif
