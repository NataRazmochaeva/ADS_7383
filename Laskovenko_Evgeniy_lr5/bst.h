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

    void rebuild(BST<BASE>* el)
    {
        BASE tmp_vl = this->value();
        this->set_vl(el->value());
        el->set_vl(tmp_vl);
        el->set_lf(this->left());
        el->set_rt(this->right());
        if(tmp_vl < this->value())
        {
            this->set_lf(el);
            this->set_rt(nullptr);
        }
        else
        {
            this->set_rt(el);
            this->set_lf(nullptr);
        }
    }
public:
    BST()
    {
        val = 0;
        k = -1;
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

    bool find(int key)
    {
        bool flag=false;
        if(this)
        {
            if(key == this->key())
                return true;

            flag += this->left()->find(key);
            flag += this->right()->find(key);
        }
        else
            return flag;
    }

    void add_rand(BASE val)
    {
        BST<BASE>* bst_el = new BST<BASE>;
        bst_el->set_vl(val);

        srand(val);
        if(!this->find(rand()))
        {
            this->fix_size();
            srand(time(nullptr));
            if(rand()%(this->size()+1) == this->size())
                    this->rebuild(bst_el);
            else
            {
                if(this->value() > bst_el->value())
                {
                    if(!this->left())
                        this->set_lf(bst_el);
                    this->left()->add_rand(val);
                }
                else
                {
                    if(!this->right())
                        this->set_rt(bst_el);
                    this->right()->add_rand(val);
                }
            }
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
