#ifndef CODETREE_H
#define CODETREE_H
#include <sstream>

template <class T>
class CodeTree
{
private:
    CodeTree* left;   // 0
    CodeTree* right;  // 1
    bool flag = false; //true if leaf
    bool zero = false; //true if NYT
    T value;
    int weight = 0;
    int order = 512;

public:
    CodeTree* parent;

public:
    CodeTree(std::stringstream& s)
    {
        flag = false;
        left = NULL;
        right = NULL;
        parent = NULL;
        char ch;
        if (s.peek() == '(')
            s >> ch; // remove '('
        else
            return;
        if (s.peek() == '(')
            {
                left = new CodeTree(s);
                if (s.peek() == ')')
                    s >> ch; // remove ')'
            }
        else
            {
                flag = true;
                s >> value;
                return;
            }
        if (s.peek() == '(')
        {
            right = new CodeTree(s);
            s >> ch; // remove ')'
        }
        if (s.peek() == ')')
            s >> ch; // remove ')'
    }
    CodeTree(T val, int w = 1, bool z = false)
    {
        value = val;
        left = NULL;
        right = NULL;
        flag = true;
        weight = w;
        zero = z;
    }
    CodeTree(CodeTree *left, CodeTree *right)
    {
        value = 0;
        this->left = left;
        this->right = right;
        flag = false;
        zero = false;
    }
    void setOrder(int o) {order = o;}
    int getOrder() {return order;}
    void setZero(bool z) {zero = z;}
    bool isZero() {return zero;}
    void setParent(CodeTree* p) {parent = p;}
    bool isLeaf() {return flag;}
    void setLeaf(bool l) {flag = l;}
    void incWeight() {weight++;}
    int getWeight() {return weight;}
    void addChildren(CodeTree* l, CodeTree* r) {left = l; right = r;}
    CodeTree *get_left() {return left;}
    void setLeft(CodeTree *l) {left = l;}
    CodeTree *get_right() {return right;}
    void setRight(CodeTree *r) {right = r;}
    CodeTree *find(T ch)
    {
        CodeTree *l, *r;
        if (isLeaf())
        {
            if (value == ch && zero == false)
                return this;
            else
                return NULL;
        }
        else
        {
            l = left->find(ch);
            r = right->find(ch);
        }
        if (l || r)
        {
            if (l)
                return l;
            return r;
        }
        return NULL;

    }
    CodeTree *findZero()
    {
        CodeTree *l, *r;
        if (isLeaf())
        {
            if (isZero())
                return this;
            else
                return NULL;
        }
        else
        {
            l = left->findZero();
            r = right->findZero();
        }
        if (l || r)
        {
            if (l)
                return l;
            else
                return r;
        }
        return NULL;

    }
    bool getCode(T ch, std::string &code)
    {
        if (isLeaf())
            if (value == ch)
                return true;
        if (left)
            if (left->getCode(ch, code))
            {
                code.push_back('0');
                return true;
            }
        if (right)
            if (right->getCode(ch, code))
            {
                code.push_back('1');
                return true;
            }
        return false;
    }
    T val() {return value;}
    int weight_upd()
    {
        if (isLeaf())
            return weight;
        int t1 = 0, t2 = 0;
        if (left)
            t1 = left->weight_upd();
        if (right)
            t2 = right->weight_upd();
        weight = t1 + t2;
        return weight;
    }
    ~CodeTree()
    {
        if (left)
            delete left;
        if (right)
            delete right;
    }
};

#endif // CODETREE_H
