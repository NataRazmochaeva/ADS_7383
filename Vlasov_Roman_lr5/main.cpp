#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>

using namespace std;


template <class T>
class HuffmanTree{
private:
    HuffmanTree* left;   // 0
    HuffmanTree* right;  // 1
    bool flag = false; //true if leaf
    T value;

public:
    HuffmanTree(ifstream& s);
    bool isLeaf() {return flag;}
    HuffmanTree *get_left() {return left;}
    HuffmanTree *get_right() {return right;}
    T val() {return value;}
    ~HuffmanTree();
};

template <class T>
HuffmanTree<T>::HuffmanTree(ifstream& s)
{
    flag = false;
    left = NULL;
    right = NULL;
    char ch;
    if (s.peek() == '(')
        s >> ch; // remove '('
    else
        return;
    if (s.peek() == '(')
        {
            left = new HuffmanTree(s);
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
        right = new HuffmanTree(s);
        s >> ch; // remove ')'
    }
    if (s.peek() == ')')
        s >> ch; // remove ')'
}

template <class T>
HuffmanTree<T>::~HuffmanTree()
{
    if (left)
        delete left;
    if (right)
        delete right;
}

int main()
{
    int n, c;
    int *el;
    string str_i, str_o;
    while(true)
    {
        cout << "Press 1 to decode a file\n" <<
                "Press 2 to exit." << endl;
        cin >> str_i;
        if (!isdigit(str_i[0]))
            continue;
        c = stoi(str_i);
        str_i.clear();
        switch (c)
        {
            case 1:
                break;
            case 2:
                return 0;
            default:
                cout << "Something went wrong. Try again!" << endl;
                continue;
        }
        cout << "Enter input file name: ";
        cin >> str_i;
        cout << "Enter output file name: ";
        cin >> str_o;
        if (str_i == str_o)
        {
            cout << "Input and output files can't be the same." << endl;
            continue;
        }
        ifstream f;
        ofstream o;
        char b;
        f.open(str_i);
        o.open(str_o);
        if (!f)
        {
            cout << "Unable to open the input file!" << endl;
            continue;
        }
        if (!o)
        {
            cout << "Unable to open the output file!" << endl;
            continue;
        }
        HuffmanTree<char> *Dictionary = new HuffmanTree<char>(f);
        HuffmanTree<char> *tmp = Dictionary;
        while (!f.eof())
        {
            b = f.get();
            if (b == '\n')
                if (f.peek() == EOF)
                    break;
            for (char i = 7; i > 0; i--)
            {
                if (tmp)
                    tmp = ((b & (1 << i)) == 0 ? tmp->get_left() : tmp->get_right());
                if (tmp && tmp->isLeaf())
                {
                    o << tmp->val();
                    tmp = Dictionary;
                }

            }
        }
        f.close();
        o.close();
        if (tmp)
            cout << str_i << " was decoded to " << str_o << " succesfully." << endl;
        else
            cout << str_i <<" is broken." << endl;
        delete Dictionary;
    }
}
