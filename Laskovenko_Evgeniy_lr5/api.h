#include <iostream>
#include <istream>
#include <ctime>
#include "bst.h"

#ifndef API_H
#define API_H

template<typename BASE>
BST<BASE>* find(BST<BASE>* root, int key, BST<BASE>* res=nullptr)
{
    if(root)
    {
        if(key == root->key())
            res = root;

        res = find(root->left(), key, res);
        res = find(root->right(), key, res);
    }
    else
        return res;
}

template<typename BASE>
BST<BASE>* build_rand(BASE val, BST<BASE>* root=nullptr, BST<BASE>* cur_root=nullptr, BST<BASE>* prev_root=nullptr, BST<BASE>* bst_el=new BST<BASE>)
{
    bst_el->set_vl(val);

    if(!root)
        return bst_el;
    else
    {
        root->fix_size();
        srand(time(nullptr));
        if(std::rand()%(cur_root->size()+1) == cur_root->size())
        {
            if(cur_root->value() > bst_el->value())
            {
                bst_el->set_rt(cur_root);
            }
            else
            {
                bst_el->set_lf(cur_root);
            }

            if(!prev_root)
                return bst_el;
            else
            {
                if(prev_root->left() == cur_root)
                    prev_root->set_lf(bst_el);
                else
                    prev_root->set_rt(bst_el);
                return root;
            }
        }
        else
        {
            if(cur_root->value() > bst_el->value())
            {
                if(!cur_root->left())
                {
                    cur_root->set_lf(bst_el);
                    return root;
                }
                root = build_rand(val, root, cur_root->left(), cur_root);
            }
            else
            {
                if(!cur_root->right())
                {
                    cur_root->set_rt(bst_el);
                    return root;
                }
                root = build_rand(val, root, cur_root->right(), cur_root);
            }
        }
    }

    return root;
}

template<typename BASE>
BST<BASE>* read_stream(std::istream& is_str, BST<BASE>* root=nullptr)
{
    BASE cur_el;

    if(is_str >> cur_el)
    {
        srand(cur_el);
        if(find(root, rand()))
        {
            root = read_stream<char>(is_str, root);
            return root;
        }

        root = build_rand(cur_el, root, root);
        root = read_stream<char>(is_str, root);
    }
    return root;
}

template<typename BASE>
BST<BASE>* add_el(BASE val, BST<BASE>* root)
{
    srand(val);
    if(!find(root, rand()))
        root = build_rand(val, root, root);
    return root;
}

template<typename BASE>
void printBST(BST<BASE>* root, unsigned int l=0)
{
   if(!root)
   {
       for(unsigned int i=0; i<l; ++i)
           std::cout << '\t';
       std::cout << '#' << std::endl;
       return;
   }

   printBST(root->right(), l+1);

   for(unsigned int i=0; i<l; i++)
       std::cout << '\t';
   std::cout << root->value() << std::endl;

   printBST(root->left(), l+1);
}

#endif // API_H
