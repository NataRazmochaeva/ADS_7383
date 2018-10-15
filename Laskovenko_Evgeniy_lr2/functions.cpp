#include "header.h"
#include "atoms.h"
#include "list.h"
#include "pair.h"

Pair* set_right_list(istream& is_str, Pair* c_pair, base prev_ch)
{
    char cur_ch;

    if(is_str>>cur_ch)
    {
        if(cur_ch=='(' && prev_ch=='\0')
        {
            set_right_list(is_str, c_pair, cur_ch);
        }
        else
        {
            auto c_hd = new List;
            auto c_tl = new List;
            c_pair->set(c_hd, c_tl);

            if(prev_ch>=97 && prev_ch<=122 && cur_ch=='(')
            {
                auto n_hd_pair = new Pair;
                c_hd->set_pair(set_right_list(is_str, n_hd_pair, cur_ch));
                auto n_tl_pair = new Pair;
                c_tl->set_pair(set_right_list(is_str, n_tl_pair, cur_ch));
                return c_pair;
            }
            else if(prev_ch!='\0' && cur_ch>=97 && cur_ch<=122)
            {
                c_hd->set_atom(cur_ch);
                auto n_pair = new Pair;
                c_tl->set_pair(set_right_list(is_str, n_pair, cur_ch));
                return c_pair;
            }
            else if(cur_ch==')')
            {
                return nullptr;
            }
            else
            {
                throw 0;
            }
        }
    }
    else if(prev_ch!=')')
        throw 0;

    return nullptr;

}

bool syn_analyzer(string str, unsigned int i, unsigned int opened_br, bool flag) {
    if(str.empty())
        return false;

    if(i<str.length()) {
        if(str[i]==' ')
            i++;
        if(!flag && str[i]=='(')
            flag = syn_analyzer(str, ++i, ++opened_br, true);
        else if(opened_br>0 && (str[i]>=97 && str[i]<=122))
            flag = syn_analyzer(str, ++i, opened_br, false);
        else if(str[i]==')')
            flag = syn_analyzer(str, ++i, --opened_br, true);
        else
            return false;
    }
    else if(opened_br==0)
        return true;
    else
        return false;

    return flag;
}

Pair* set_list(istream& is_str, bool st_flag) {
    char ch;
    if(st_flag)
        is_str >> ch;

    if(is_str >> ch) {
        auto c_pair = new Pair;
        auto c_hd = new List;
        auto c_tl = new List;
        c_pair->set(c_hd, c_tl);

        if(ch>=97 && ch<=122) {
            c_hd->set_atom(ch);
            c_tl->set_pair(set_list(is_str, false));
        }
        else if(ch=='(') {
            c_hd->set_pair(set_list(is_str, false));
            c_tl->set_pair(set_list(is_str, false));
        }
        else if(ch==')') {
            return nullptr;
        }

        return c_pair;
    }

    return nullptr;
}

void cout_list(Pair* head) {
    if(!head->is_null()) {
        if(head->get_head()->is_atom()) {
            cout << head->get_head()->get_atom();
            if(!head->get_tail()->get_pair()->is_null() &&
                head->get_tail()->get_pair()->get_head()->is_atom())
                cout << ' ';
        }
        else {
            cout << ' ' << '(';
            cout_list(head->get_head()->get_pair());
            cout << ')' << ' ';
        }
        cout_list(head->get_tail()->get_pair());
    }
}

Atoms* diff_atoms(Pair* head, Atoms* h_res, Atoms* c_res) {
    if(!head->is_null()) {
        if(head->get_head()->is_atom()) {
            base cur_atom = head->get_head()->get_atom();

            bool diff = true;
            Atoms* tmp_c = h_res;
            while(tmp_c!=nullptr){
                if(tmp_c->get_atom() == cur_atom)
                    diff = false;

                tmp_c = tmp_c->get_next();
            }

            if(diff) {
                c_res->set_atom(cur_atom);
                c_res->set_next(new Atoms);
                c_res = c_res->get_next();
//                diff_atoms(head->get_tail()->get_pair(), h_res, c_res);
            }
        }
        else
            c_res = diff_atoms(head->get_head()->get_pair(), h_res, c_res);
        c_res = diff_atoms(head->get_tail()->get_pair(), h_res, c_res);
    }
    return c_res;
}

void cout_diff_list(Atoms* head) {
    int count = 0;
    cout << "Linear list of different atoms: "
         << endl;
    while(head!=nullptr){
        if(head->get_next()!= nullptr) {
            cout << head->get_atom() << " -- ";
            count++;
        }
        head = head->get_next();
    }
    if(count) {
        cout << endl
             << "Number of different atoms: "
             << count
             << endl;
    }
    else
        cout << "EMPTY."
             << endl;
}
