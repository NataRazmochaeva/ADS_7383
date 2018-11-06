#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>

using namespace std;

template <class T>
class Queue;

template <class T>
class BT{
private:
    BT* left;
    BT* right;
    T value;

public:
    BT(stringstream& s);
    void print (Queue<T> &q);
    ~BT();
};

template <class T>
struct El{
    BT<T>* elem;
    El* next;
    El(BT<T>* elem)
    {
        this->elem = elem;
        next = NULL;
    };
};

template <class T>
class Queue{
private:
    El<T>* out;
    El<T>* in;
public:
    Queue();
    bool isEmpty();
    void push(BT<T>* el);
    BT<T>* pop();
};

template <class T>
Queue<T>::Queue()
{
    out = NULL;
    in = NULL;
}

template <class T>
bool Queue<T>::isEmpty()
{
    return (out ? false : true);
}

template <class T>
void Queue<T>::push(BT<T>* el)
{
    if (in)
    {
        in->next = new El<T>(el);
        in = in->next;
    }
    else
    {
        in = new El<T>(el);
    }
    if (!out)
        out = in;
}

template <class T>
BT<T>* Queue<T>::pop()
{
    El<T>* tmp = out;
    BT<T>* ans = out->elem;
    if (out == in)
        in = NULL;
    out = out->next;
    delete tmp;
    return ans;
}

template <class T>
void BT<T>::print (Queue<T> &q)
{
    if (left)
        q.push(left);
    if (right)
        q.push(right);
    cout << value;
}

template <class T>
BT<T>::BT(stringstream& s)
{
    left = NULL;
    right = NULL;
    char ch;
    if (s.peek() == '(')
        s >> ch; // remove '('
    s >> value;
    switch(s.peek())
    {
        case '(':
            left = new BT(s);
            break;
        case '#':
            s >> ch; // remove '#'
            break;
    }
    if (s.peek() == '(')
        {
            right = new BT(s);
            s >> ch; // remove ')'
        }
    else if (s.peek() == '#')
        s >> ch; // remove '#'
    if (s.peek() == ')')
        s >> ch; // remove ')'
}

template <class T>
BT<T>::~BT()
{
    if (left)
        delete left;
    if (right)
        delete right;
}

void run(string str)
{
    stringstream s;
    string str1;
    if (str.size() == 0)
    {
        cout << "The string is empty!" << endl;
        return;
    }
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '(')
        {
            str1.push_back(str[i]);
        }

        else if (str[i] == ')')
        {
            str1.push_back(str[i]);
        }
        else if (isdigit(str[i]))
        {
            str1.push_back(str[i]);
        }
        else if (str[i] == '#')
        {
            str1.push_back(str[i]);
        }
        else
        {
            cout << "There are some unexpected characters in the string: " << str << endl;
            return;
        }
    }
    cout << str1 << endl;
    s << str;
    BT<int>* el = new BT<int>(s);
    Queue<int> q;
    q.push(el);
    while (!q.isEmpty())
    {
        BT<int>* tmp = q.pop();
        tmp->print(q);
    }
    cout << endl;
}


int main()
{
    int n, c;
    string inp;
    int *el;
    string str, str1;
    while(true)
    {
        cout << "Press 1 to get input from a file\n" <<
                "Press 2 to enter binary tree by yourself\n" <<
                "Press 3 to exit." << endl;
        cin >> inp;
        if (!isdigit(inp[0]))
            continue;
        c = stoi(inp);
        inp.clear();
        switch (c)
        {
            case 1:
                break;
            case 2:
                getline(cin, str); // remove '\n'
                getline(cin, str);
                run(str);
                break;
            case 3:
                return 0;
            default:
                cout << "Something went wrong. try again!" << endl;
                continue;
        }
        if(c == 1)
        {
            cout << "Enter file name: ";
            cin >> str;
            ifstream f;
            f.open(str);
            if (!f)
            {
                cout << "Unable to open the file!" << endl;
                continue;
            }
            while(!f.eof())
            {
                getline(f, str);
                if (str.size())
                    run(str);
            }
            f.close();
        }
    }
}
