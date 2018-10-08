#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>

using namespace std;

// Perform a binary tree as an hierarchical list?
// That's like asking the Incredible Hulk to open a pickle jar!!!
class LIST;

struct ATOM{
    LIST* elem;
    LIST* next;
};

struct ELEM{
    bool balanced;
    int lever_length;
    int mass;
    LIST* down;
};

union CONTENT{
    ATOM atom;
    ELEM elem;
};

class LIST{
private:
    bool flag; //true if element else atom
    union CONTENT content;

public:
    LIST(stringstream& s, int side = 1); // 0 - elem, 1 - left, 2 - right
    int lever (stringstream &s);
    int Balanced();
    ~LIST();
};

LIST::LIST(stringstream& s, int side)
{
    char ch;
    switch (side)
    {
        case 0:
            flag = true;
            content.elem.down = NULL;
            if (s.peek() == '(')
                s >> ch; // remove (
            lever(s);
            s >> ch; // remove )
            break;
        case 1:
            flag = false;
            content.atom.elem = new LIST(s, 0);
            content.atom.next = new LIST(s, 2);
            break;
        case 2:
            flag = false;
            content.atom.elem = new LIST(s, 0);
            content.atom.next = NULL;
            break;
    }
}

int LIST::lever(stringstream& s)
{
    char ch;
    if (s.peek() == '(')
        s >> ch; // remove '('
    s >> content.elem.lever_length;
    if (s.peek() == '(')
    {
        content.elem.down = new LIST(s);
    }
    else
    {
        s >> content.elem.mass;
    }
    s >> ch; // remove ')'
}

int LIST::Balanced()
{
    int m;
    if (flag == false)
    {
        if (content.atom.next)
        {
            return ((m = (content.atom.next)->Balanced()) ==
                        (content.atom.elem)->Balanced() &&
                        m != -1 ? 2*m : -1);
        }
        else
            return (content.atom.elem)->Balanced();
    }
    else
    {
        if (content.elem.down)
        {
            if ((m = (content.elem.down)->Balanced()) != -1)
                return m * content.elem.lever_length;
            else
                return -1;
        }
        else
            return content.elem.lever_length * content.elem.mass;
    }
}

LIST::~LIST()
{
    if (flag == false)
    {
        delete content.atom.elem;
        if (content.atom.next)
            delete content.atom.next;
    }
    else if (content.elem.down)
            delete content.elem.down;
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
    for (auto el : str)
    {
        if (el == '(')
        {
            if (isspace(str1.back()))
                str1.erase(str1.size()-1, 1);
            str1.push_back(el);
        }
        else if (el == ' ')
        {
            if (isdigit(str1.back()))
                str1.push_back(el);
        }
        else if (el == ')')
        {
            if (isspace(str1.back()))
                str1.erase(str1.size()-1, 1);
            str1.push_back(el);
        }
        else if (isdigit(el))
        {
            str1.push_back(el);
        }
        else
        {
            cout << "There are some unexpected characters in the string: " << str << endl;
            return;
        }
    }
    for (int i = 0; i < str1.size(); i++)
    {
        switch (str1[i])
        {
            case '(':
                i++;
                if (str1[i] == '(')
                {
                    i++;
                    if (isdigit(str1[i]))
                        continue;
                }
                cout << "The string doesn't match to the format." << endl;
                return;
            case ')':
                i++;
                if (str1[i] == '(')
                {
                    i++;
                    if (isdigit(str1[i]))
                        continue;
                }
                else if (str[i] == ')')
                    continue;
                cout << "The string doesn't match to the format." << endl;
                return;
        }
    }
    cout << str1;
    s << str1;
    LIST list(s);
    cout << (list.Balanced() != -1 ? "Balanced\n" : "Not balanced\n");
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
                "Press 2 to enter binary beam by yourself\n" <<
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
                run(str);
            }
            f.close();
        }
    }
}
