#include <iostream>
#include <istream>
#include "btree.h"

using namespace std;

#ifndef API_H
#define API_H

bool
isSign(char ch)
{ return ch=='*' || ch=='+' || ch=='-'; }

bool
isTerm(char ch)
{ return isdigit(ch) || (ch>='a' && ch<='z'); }

void
buildBT_RLR(istream& is_str, BinTree* root=new BinTree, bool flag=false)
{
    char cur_ch;

    if(is_str>>cur_ch)
    {
        if(isSign(cur_ch))
        {
            root->ConsBT(cur_ch);
            buildBT_RLR(is_str, root->Left(), true);
            buildBT_RLR(is_str, root->Right(), true);
        }
        else if(isTerm(cur_ch))
        {
            root->ConsBT(cur_ch, nullptr, nullptr);
            flag = false;
        }
        else
            throw new my_ex("Error: Invalid character.");
    }
    else if(flag)
        throw new my_ex("Error: Argument expected.");
}

void
printBT(BinTree* root, unsigned int i=0)
{
    if(root)
    {
        if(root->Right())
            printBT(root->Right(), ++i);
        else
        {
            for(unsigned j=0; j<i; j++)
                cout << '\t';
            cout << root->RootBT() << endl;
            return;
        }

        for(unsigned j=0; j<i-1; j++)
            cout << '\t';
        cout << root->RootBT() << endl;

        if(root->Left())
            printBT(root->Left(), i);
    }
}

void
prefix_to_infix(BinTree* root, BinTree* prev=nullptr)
{
    if(root->Left())
    {
        if(root->Right() && isTerm(root->Right()->RootBT()))
            cout << '(';
        prefix_to_infix(root->Left(), root);
    }
    else
    {
        cout << root->RootBT();
        if(prev && root==prev->Right())
            cout << ')';
        return;
    }

    cout << root->RootBT();

    if(root->Right())
        prefix_to_infix(root->Right(), root);
}

void
fixBT(BinTree* root, BinTree* pv_rt=nullptr)
{
    if(root->Left())
        fixBT(root->Left(), root);
    else
    {
        switch(pv_rt->RootBT())
        {
        case '*':
            if(pv_rt->Left()->RootBT()=='0' || pv_rt->Right()->RootBT()=='0')
                pv_rt->ConsBT('0', nullptr, nullptr);
            else if(pv_rt->Left()->RootBT()=='1' || pv_rt->Right()->RootBT()=='1')
            {
                if(pv_rt->Left()==root)
                    pv_rt->ConsBT(pv_rt->Right()->RootBT(), nullptr, nullptr);
                else if(pv_rt->Right()==root)
                    pv_rt->ConsBT(pv_rt->Left()->RootBT(), nullptr, nullptr);
            }
            break;
        case '+':
            if(pv_rt->Left()->RootBT()=='0')
                pv_rt->ConsBT(pv_rt->Right()->RootBT(), nullptr, nullptr);
            else if(pv_rt->Right()->RootBT()=='0')
                pv_rt->ConsBT(pv_rt->Left()->RootBT(), nullptr, nullptr);
            break;
        case '-':
            if(root->RootBT()=='0' && pv_rt->Right()==root)
                pv_rt->ConsBT(pv_rt->Left()->RootBT(), nullptr, nullptr);
            break;
        }
    }

    if(root->Right())
        fixBT(root->Right(), root);
}

#endif // API_H
