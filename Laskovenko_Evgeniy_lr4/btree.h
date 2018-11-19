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
    bool
    isNull(BinTree*)
    { return this == nullptr; }
    //-------------------------------------
    base
    RootBT(BinTree*)
    {
        if(!this)
            throw "Error: RootBT(null)";
        else
            return this->info;
    }
    //-------------------------------------
    BinTree*
    Left (BinTree*)
    {
        if (!this)
            throw "Error: Left(null)";
        else
            return this->lt;
    }
    //-------------------------------------
    BinTree*
    Right (BinTree*)
    {
        if (!this)
            throw "Error: Right(null)";
        else
            return this->rt;
    }
    //-------------------------------------
    BinTree*
    ConsBT(const base x, BinTree* lst, BinTree* rst)
    {
        auto p = new BinTree;
        if (p)
        {
            p->info = x;
            p->lt = lst;
            p->rt = rst;
            return p;
        }
        else
            throw "Memory not enough";
    }
    //-------------------------------------
    ~BinTree()
    {
        if(this)
        {
            delete this->lt;
            delete this->rt;
            delete this;
        }
    }
    //-------------------------------------
};

#endif // BTREE_H
