#include <iostream>
#include <cstdlib>

#ifndef BST_H
#define BST_H

template<typename BASE>
class BST
{
private:
    BASE val;
    int k;
    int sz;
    BST* lf;
    BST* rt;
public:
    BST()
    {
        val = 0;
        k = 0;
        sz = 1;
        lf = nullptr;
        rt = nullptr;
    }

    BASE value()
    { return val; }

    int key()
    { return k; }

    int size()
    { return sz; }

    BST* left()
    { return lf; }

    BST* right()
    { return rt; }

    void set_lf(BST* lft)
    { this->lf = lft; }

    void set_rt(BST* rgt)
    { this->rt = rgt; }

    void set_vl(BASE vl)
    {
        val = vl;
        srand(val);
        k = std::rand();
    }

    void fix_size()
    {
        this->sz = 1;
        if(this->left())
        {
            this->left()->fix_size();
            this->sz += this->left()->size();
        }
        if(this->right())
        {
            this->right()->fix_size();
            this->sz += this->right()->size();
        }
    }

    ~BST()
    {
        if(this->left()!=nullptr)
            delete lf;
        if(this->right()!=nullptr)
            delete rt;
    }
};

#endif // BST_H
