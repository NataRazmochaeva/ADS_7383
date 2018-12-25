#ifndef HUFFMANDYNAMIC_H
#define HUFFMANDYNAMIC_H
#include <sstream>
#include <string>
#include "codetree.h"
#include <map>
#include <iostream>

template <class D>
class HuffmanDynamic
{
private:
    CodeTree<D>* tree;
    int op = 0;

public:
    HuffmanDynamic() {tree = new CodeTree<D>(0, 0, true);}
    CodeTree<D>* createChild(CodeTree<D>* parent, D ch, int order, bool isZero)
    {
        op++;
        CodeTree<D>* res = new CodeTree<D>(ch, !isZero, isZero);
        res->setParent(parent);
        res->setOrder(order);
        return res;
    }
    void addNew(D ch, CodeTree<D>* cur)
    {
        CodeTree<D>* left = createChild(cur, 0, cur->getOrder() - 2, true);
        CodeTree<D>* right = createChild(cur, ch, cur->getOrder() - 1, false);
        cur->setZero(false);
        cur->setLeaf(false);
        cur->addChildren(left, right);
    }
    void swap(CodeTree<D> *n1, CodeTree<D> *n2)
    {
        op++;
        int tempOrder = n1->getOrder();
            n1->setOrder(n2->getOrder());
            n2->setOrder(tempOrder);

            if (n1->parent->get_left() == n1) {
                n1->parent->setLeft(n2);
            } else {
                n1->parent->setRight(n2);
            }

            if (n2->parent->get_left() == n2) {
                n2->parent->setLeft(n1);
            } else {
                n2->parent->setRight(n1);
            }

            CodeTree<D> *tmp = n1->parent;
            n1->parent = n2->parent;
            n2->parent = tmp;
    }
    CodeTree<D>* findReplace(CodeTree<D>* cur, CodeTree<D>* root)
    {
        CodeTree<D>* res = cur;
        if (root->getWeight() > res->getWeight() && !root->isLeaf())
        {
            CodeTree<D>* fLeft = findReplace(res, root->get_left());
            if (fLeft)
                res = fLeft;
            CodeTree<D>* fRight = findReplace(res, root->get_right());
            if (fRight)
                res = fRight;
        }
        else if (root->getWeight() == res->getWeight() && root->getOrder() > res->getOrder())
        {
            res = root;
        }
        return (res != cur ? res : NULL);
    }
    void updateTree(CodeTree<D> *cur) {
        op++;
        while (cur != tree) {
            CodeTree<D> *replaceNode = findReplace(cur, tree);
            if (replaceNode && cur->parent != replaceNode) {
                swap(cur, replaceNode);
            }
            cur->incWeight();
            cur = cur->parent;
        }
        cur->incWeight();
    }
    std::string encode(std::stringstream &s)
    {
        s << '\0';
        CodeTree<D>* cur;
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
            cur = tree->find(b);
            if (cur)
            {
                tree->getCode(b, code);
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
            else
            {
                tree->getCode(0, code);
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
                for (int i = 7; i >= 0; i--)
                {
                    if (b & 1 << i)
                        ch = ch | (1 << p);
                    p--;
                    if (p < 0)
                    {
                        out.push_back(ch);
                        p = 7;
                        ch = 0;
                    }
                }
                cur = tree->findZero();
                addNew(b, cur);
            }
            op += code.length();
            updateTree(cur);
        }
        if (ch != 0)
            out.push_back(ch);
        return out;
    }
    std::string decode(std::stringstream &s) {
        CodeTree<D>* cur = tree;
        char b, ch = 0;
        std::string code;
        std::string out;
        while (!s.eof())
        {
            code.clear();
            b = s.get();
            if (b == EOF)
                return out;//b = 0;
            for (int i = 7; i >= 0; i--)
            {
                if (cur->isLeaf())
                {
                    if (!cur->isZero())
                    {
                        out.push_back(cur->val());
                    }
                    else
                    {
                        for (int p = 7; p >= 0; p--)
                        {
                            if (b & 1 << i)
                                ch = ch | (1 << p);
                            i--;
                            if (p && i < 0)
                            {
                                b = s.get();
                                if (b == EOF)
                                    return out;//b = 0;
                                i = 7;
                            }
                        }
                        if (ch == 0)
                            return out;
                        out.push_back(ch);
                        addNew(ch, cur);
                        ch = 0;
                    }
                    i++;
                    updateTree(cur);
                    cur = tree;
                    continue;
                }
                if (b & (1 << i))
                    cur = cur->get_right();
                else
                    cur = cur->get_left();
            }
        }
        out.push_back('\0');
        return out;
    }
    int getOp() {return op;}
    ~HuffmanDynamic() {delete tree;}
};


#endif // HUFFMANDYNAMIC_H
