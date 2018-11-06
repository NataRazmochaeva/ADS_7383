#include <iostream>
#include <cctype>
#include "struct.h"

using namespace std;

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

List* set_list(istream& is_str, List* hd_p=new List)
{
    char cur_ch;
    if(is_str>>cur_ch)
    {
        if(cur_ch=='+' || cur_ch=='-' || cur_ch=='*' || cur_ch=='/')
        {
            hd_p = make_pair(make_atom(cur_ch, '\0'), make_pair(set_list(is_str)));
            if(is_str>>cur_ch)
                get_head(hd_p)->node.atom = cur_ch;
            else
                throw "Operations >= operators.";
        }
        else if(isalnum(cur_ch))
        {
            hd_p = make_pair(make_atom('\0', cur_ch));
            return hd_p;
        }
        else
            throw "Invalid input.";
    }

    return hd_p;
}

void out_list(List* head)
{
    if(head->node.p_ptr.tl)
    {
        out_list(get_head(get_tail(head)));
    }
    if(get_head(head)->operation)
        cout << get_head(head)->operation;
    cout << get_head(head)->node.atom;
}

void mod_list(List* head, List* prev)
{
    if(head->node.p_ptr.tl)
    {
        mod_list(get_head(get_tail(head)), head);
    }
    else
    {
        if((get_head(head)->node.atom=='0' &&(get_head(prev)->operation=='+' || get_head(prev)->operation=='-'))
           || (get_head(head)->node.atom=='1' && get_head(prev)->operation=='*'))
        {
            get_head(prev)->operation = '\0';
            prev->node.p_ptr.tl = nullptr;
            destroy(head);
            return;
        }
    }

    if(prev==nullptr)
    {

    }

    if(head->node.p_ptr.hd->node.atom=='0' && head->node.p_ptr.hd->operation=='/')
        throw "Delenie na 0.";
    else if((get_head(head)->node.atom=='0' && (get_head(head)->operation=='+' || get_head(head)->operation=='-'))
      || (get_head(head)->node.atom=='1' && (get_head(head)->operation=='*' || get_head(head)->operation=='/')))
    {
        if(prev==nullptr)
        {
            auto temp = head;
            head = get_tail(head)->node.p_ptr.hd;
            destroy(temp);
        }
        else
        {
            get_tail(prev)->node.p_ptr.hd=get_head(get_tail(head));
            destroy(head);
            return;
        }
    }

}


#endif // FUNCTIONS_H
