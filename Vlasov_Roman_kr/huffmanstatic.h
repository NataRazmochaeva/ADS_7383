#ifndef HUFFMANSTATIC_H
#define HUFFMANSTATIC_H
#include <sstream>
#include <string>
#include <cctype>
#include "codetree.h"
#include <map>

template <class S>
class HuffmanStatic
{
private:
    CodeTree<S>* tree;
    bool error = false;
    int op = 0;

    void buildTree(std::stringstream& s, bool use_abc = true)
    {
        std::string str;
        std::multimap<double, CodeTree<S>*> dict;
        int n;
        S ch;
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
                dict.insert(std::make_pair((double)val + (double)(ch) / 1000.0, new CodeTree<S>(ch)));
            }
            if (s.peek() == '\n')
                s.get();
        }
        else
        {
            std::map<S, int> alphabet;
            while (!s.eof())
            {
                op++;
                char c = s.get();
                if (c != EOF)
                    str.push_back(c);
            }
            s.clear();
            for (auto c : str)
            {
                if (alphabet.find(c) != alphabet.end())
                    alphabet[c] = alphabet[c] + 1;
                else
                    alphabet.insert(std::make_pair(c, 1));
            }
            s << str;
            for (auto it = alphabet.begin(); it != alphabet.end(); it++)
            {
                dict.insert(std::make_pair((double)(it->second) + (double)(it->first) / 1000.0, new CodeTree<S>(it->first)));
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
        dict.insert(std::make_pair(0, new CodeTree<S>('\0')));
        buildTree(dict);
    }
    void buildTree(std::multimap<double, CodeTree<S> *> &dict)
    {
        typename std::multimap<double, CodeTree<S>*>::iterator  it;
        while (dict.size() > 1)
        {
            op++;
            double el1, el2;
            CodeTree<S>* t1, *t2;
            it = dict.begin();
            el1 = it->first;
            t1 = it->second;
            dict.erase(it);
            it = dict.begin();
            el2 = it->first;
            t2 = it->second;
            dict.erase(it);
            dict.insert(std::make_pair((double)((int)el1+(int)el2)+0.999, new CodeTree<S>(t1, t2)));
        }
        it = dict.begin();
        tree = it->second;
    }

public:
    HuffmanStatic(std::stringstream& s, bool use_abc){buildTree(s, use_abc);}
    HuffmanStatic(std::multimap<double, CodeTree<S>*>& dict)
    {
        dict.insert(std::make_pair(0, new CodeTree<S>('\0')));
        buildTree(dict);
    }
    bool success() {return !error;}
    int getOp() {return op;}
    std::string decode(std::stringstream& s)
    {
        if (error == true)
            return "";
        char b;
        std::string out;
        CodeTree<S> *tmp = tree;
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
                    out.push_back(tmp->val());
                    if (tmp->val() == 0)
                        return out;
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
    ~HuffmanStatic() {delete tree;}

    std::string abc;
};

#endif // HUFFMANSTATIC_H
