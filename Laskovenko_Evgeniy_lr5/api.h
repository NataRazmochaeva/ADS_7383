#include <iostream>
#include <istream>
#include <ctime>
#include "bst.h"

#ifndef API_H
#define API_H

template<typename BASE>
BST<BASE>* read_stream(std::istream& is_str, BST<BASE>* root=nullptr)
{
    BASE cur_el;

    if(is_str >> cur_el)
    {
        if(!root)
        {
            root = new BST<BASE>;
            root->set_vl(cur_el);
        }
        else
        {
            srand(cur_el);
            if(!root->find(rand()))
                root->add_rand(cur_el);
        }
        root->fix_size();
        root = read_stream<char>(is_str, root);
    }

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
