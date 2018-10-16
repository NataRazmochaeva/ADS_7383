#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>

using namespace std;

class Stack {
private:
    int st_p;
    char *st;
public:
    Stack(string str);
    void push(char ch);
    char pop();
    bool isEmpty();
    ~Stack();
};

Stack::Stack(string str)
{
    if (str.size() == 0)
        return;
    st = new char[str.size() + 1];
    st_p = 0;
    st[st_p] = '\n';
    st_p++;
    for (auto ch : str)
    {
        st[st_p] = ch;
        st_p++;
    }
}

void Stack::push(char ch)
{
    st[st_p] = ch;
    st_p++;
}

char Stack::pop()
{
    st_p--;
    return st[st_p];
}

bool Stack::isEmpty()
{
    return (st_p > 0 ? false : true);
}


bool write(string str_o, Stack &st)
{
    fstream f(str_o, ios_base::out | ios_base::app);
    if (!f)
    {
        cout << "Unable to open the output file!" << endl;
        return false;
    }
    while (!st.isEmpty())
        f.put(st.pop());
    f.close();
    return true;
}

Stack::~Stack()
{
    if (st)
        delete[] st;
}

int main()
{
    int n, c;
    int *el;
    string str_i, str_o;
    while(true)
    {
        cout << "Press 1 to reverse letters in strings in a file\n" <<
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
                cout << "Something went wrong. try again!" << endl;
                continue;
        }
        if(c == 1)
        {
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
            f.open(str_i);
            if (!f)
            {
                cout << "Unable to open the input file!" << endl;
                continue;
            }
            while(!f.eof())
            {
                getline(f, str_i);
                Stack el(str_i);
                if (write(str_o, el) == false);
                    break;
            }
            f.close();
        }
    }
}
