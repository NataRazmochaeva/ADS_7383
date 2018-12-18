#ifndef BINTR_H
#define BINTR_H


template<typename BASE>

class BinTree
{
private:
    BASE root;
    BinTree *left;
    BinTree *right;

public:
    BinTree()
    {
        root = 0;
        left = nullptr;
        right = nullptr;
    }

    BASE get_vl()
    { return root;}

    void set_vl(BASE vl)
    {
        root = vl;
    }

    BinTree *get_left()
    { return left;}

    void set_left()
    { left = new BinTree;}

    BinTree *get_right()
    { return right;}

    void set_right()
    { right = new BinTree;}


    ~BinTree()
    {
        if(left)
            delete left;
        if(right)
            delete right;
    }
};


#endif // BINTR_H
