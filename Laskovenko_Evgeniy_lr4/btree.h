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
            throw "Error: RootBT(null)";
        else
            return this->info;
    }
    //-------------------------------------
    BinTree*
    Left ()
    {
        if (!this)
            throw "Error: Left(null)";
        else
            return this->lt;
    }
    //-------------------------------------
    BinTree*
    Right ()
    {
        if (!this)
            throw "Error: Right(null)";
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
            throw "Error: ConsBT(null)";
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
