#include "myexception.h"

#ifndef BTREE_H
#define BTREE_H

typedef char base;

class BinTree
{
private:
    base info;
    BinTree* lt;
    BinTree* rt;
public:
    //-------------------------------------
    BinTree()
    {
        info = '\0';
        lt = nullptr;
        rt = nullptr;
    }
    //-------------------------------------
    base
    RootBT()
    {
        if(!this)
            throw new my_ex("Error: RootBT(null)");
        else
            return this->info;
    }
    //-------------------------------------
    BinTree*
    Left()
    {
        if (!this)
            throw new my_ex("Error: Left(null)");
        else
            return this->lt;
    }
    //-------------------------------------
    BinTree*
    Right()
    {
        if (!this)
            throw new my_ex("Error: Right(null)");
        else
            return this->rt;
    }
    //-------------------------------------
    void
    ConsBT(const base x, BinTree* lst=new BinTree, BinTree* rst=new BinTree)
    {
        if (this)
        {
            this->info = x;
            this->lt = lst;
            this->rt = rst;
        }
        else
            throw new my_ex("Error: ConsBT(null)");
    }
    //-------------------------------------
    ~BinTree()
    {
        if(this)
        {
            if(this->lt)
                delete this->lt;
            if(this->rt)
                delete this->rt;
        }
    }
    //-------------------------------------
};

#endif // BTREE_H
