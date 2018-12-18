#ifndef SHENNONFANO_H
#define SHENNONFANO_H
#include <sstream>
#include <string>
#include <cctype>
#include "codetree.h"
#include <map>

template <class F>
class ShennonFano
{
private:
    CodeTree<F>* tree;
    bool error = false;
    int op = 0;

    void buildTree(std::stringstream& s, bool use_abc)
    {
        std::string str;
        std::multimap<double, CodeTree<F>*> dict;
        int n;
        F ch;
        if (use_abc)
        {
            if (!std::isdigit(s.peek()))
            {
                error = true;
                return;
            }
            s >> n;
            s.get();
            abc += std::to_string(n);
            abc.push_back('\n');
            for (int i = 0; i < n; i++)
            {
                op++;
                int val;
                ch = s.get();
                if (std::isspace(s.peek()))
                    s.get();
                if (!std::isdigit(s.peek()))
                {
                    error = true;
                    return;
                }
                s >> val;
                if (s.peek() == '\n')
                    s.get();
                abc.push_back(ch);
                abc.push_back(' ');
                abc += std::to_string(val);
                abc.push_back('\n');
                dict.insert(std::make_pair((double)val + (double)(ch) / 1000.0, new CodeTree<F>(ch)));
            }
            if (s.peek() == '\n')
                s.get();
        }
        else
        {
            std::map<F, int> alphabet;
            while (!s.eof())
            {
                char c = s.get();
                if (c != EOF)
                    str.push_back(c);
            }
            s.clear();
            for (auto c : str)
            {
                op++;
                if (alphabet.find(c) != alphabet.end())
                    alphabet[c] = alphabet[c] + 1;
                else
                    alphabet.insert(std::make_pair(c, 1));
            }
            s << str;
            for (auto it = alphabet.begin(); it != alphabet.end(); it++)
            {
                dict.insert(std::make_pair((double)(it->second) + (double)(it->first) / 1000.0, new CodeTree<F>(it->first)));
            }
            abc = std::to_string(dict.size());
            abc.push_back('\n');
            for (auto it = dict.begin(); it != dict.end(); it++)
            {
                if (it->second->val() == 0)
                    continue;
                abc.push_back(it->second->val());
                abc.push_back(' ');
                abc += std::to_string((int)it->first);
                abc.push_back('\n');
            }
        }
        dict.insert(std::make_pair(0, new CodeTree<F>('\0')));
        tree = buildTree(dict);
    }
    CodeTree<F>* buildTree(std::multimap<double, CodeTree<F> *> &dict)
    {
        int iter = dict.size();
        int count_left = 0, count_right = 0;
        std::multimap<double, CodeTree<F> *> left_dict;
        std::multimap<double, CodeTree<F> *> right_dict;
        typename std::multimap<double, CodeTree<F>*>::iterator  it_left;
        typename std::multimap<double, CodeTree<F>*>::iterator  it_right;
        CodeTree<F>* left_tree, *right_tree;
        if (iter == 1)
        {
            CodeTree<F> *tmp = ((dict.begin())->second);
            return tmp;
        }
        op++;
        it_left = dict.begin();
        it_right = dict.end();
        it_right--;
        count_left = (int)it_left->first;
        count_right = (int)it_right->first;
        left_dict.insert(std::make_pair(it_left->first, it_left->second));
        right_dict.insert(std::make_pair(it_right->first, it_right->second));
        dict.erase(it_left);
        dict.erase(it_right);
        iter -= 2;
        while (iter > 0)
        {
            op++;
            it_left = dict.begin();
            it_right = dict.end();
            it_right--;
            left_dict.insert(std::make_pair(it_left->first, it_left->second));
            count_left += (int)it_left->first;
            dict.erase(it_left);
            iter--;
            if (iter == 0)
                break;
            if (count_left > count_right + (int)it_right->first)
            {
                right_dict.insert(std::make_pair(it_right->first, it_right->second));
                count_right += (int)it_right->first;
                dict.erase(it_right);
                iter--;
            }
        }
        left_tree = buildTree(left_dict);
        right_tree = buildTree(right_dict);
        return new CodeTree<F>(left_tree, right_tree);
    }

public:
    ShennonFano(std::stringstream& s, bool use_abc){buildTree(s, use_abc);}
    ShennonFano(std::multimap<int, CodeTree<F>*>& dict)
    {
        dict.insert(std::make_pair(0, new CodeTree<F>('\0')));
        tree = buildTree(dict);
    }
    bool success() {return !error;}
    int getOp() {return op;}
    std::string decode(std::stringstream& s)
    {
        if (error == true)
            return "";
        char b;
        std::string out;
        CodeTree<F> *tmp = tree;
        while (!s.eof())
        {
            b = s.get();
            if (b == EOF)
                break;
            for (char i = 7; i >= 0; i--)
            {
                if (tmp)
                    tmp = ((b & (1 << i)) == 0 ? tmp->get_left() : tmp->get_right());
                if (tmp && tmp->isLeaf())
                {
                    if (tmp->val() == EOF)
                        return out;
                    out.push_back(tmp->val());
                    tmp = tree;
                }

            }
        }
        return out;
    }
    std::string encode(std::stringstream& s)
    {
        if (error == true)
            return "";
        char b, ch = 0;
        int p = 7;
        std::string code;
        std::string out;
        while (!s.eof())
        {
            code.clear();
            b = s.get();
            if (b == EOF)
                break;
            if (tree->find(b) == NULL)
            {
                error = true;
                return "";
            }
            tree->getCode(b, code);
            op += code.length();
            for (int i = code.length() - 1; i >= 0; i--)
            {
                if (code[i] == '1')
                    ch = ch | (1 << p);
                p--;
                if (p < 0)
                {
                    out.push_back(ch);
                    p = 7;
                    ch = 0;
                }
            }
        }
        if (ch != 0)
            out.push_back(ch);
        return out;
    }
    ~ShennonFano() {delete tree;}

    std::string abc;
};
#endif // SHENNONFANO_H
