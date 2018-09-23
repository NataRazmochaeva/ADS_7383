#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include "permutations.h"

using namespace std;

int get_n ()
{
    string s;
    cout << "Enter amount of elements: ";
    cin >> s;
    if (!isdigit(s[0]) || stoi(s) <= 0)
    {
        cout << "Invalid value: n = " << s << endl;
        getline(cin, s);
        return 0;
    }
    return stoi(s);
}

int get_el()
{
    string s;
    cin >> s;
    if (!isdigit(s[0]) || stoi(s) <= 0)
    {
        return 0;
    }
    return stoi(s);
}

int main()
{
    int n, c;
    int *el;
    while(true)
    {
        cout << "Press 1 to get input from a file\n" <<
                "Press 2 to enter each element by yourself\n" <<
                "Press 3 to enter only amount of elements\n" <<
                "Press 4 to exit." << endl;
        cin >> c;
        switch (c)
        {
            case 1:
                break;
            case 2:
                if ((n = get_n()) == 0)
                    continue;
                el = new int[n];
                cout << "Enter elements:";
                for (int i = 0; i < n; i++)
                {
                    el[i] = get_el();
                }
                break;
            case 3:
                if ((n = get_n()) == 0)
                    continue;
                el = new int[n];
                for (int i = 0; i < n; i++)
                    el[i] = i;
                break;
            case 4:
                return 0;
            default:
                cout << "Something went wrong. try again!" << endl;
                continue;
        }
        if (c == 1)
        {
            string s;
            cout << "Enter file name: ";
            cin >> s;
            ifstream f;
            f.open(s);
            if (!f)
            {
                cout << "Unable to open the file!" << endl;
                continue;
            }
            while(!f.eof())
            {
                bool flag = false;
                n = 0;
                getline(f, s);
                if (!isdigit(s[0]))
                    continue;
                stringstream ss;
                ss << s;
                ss >> s;
                n = stoi(s);
                if (n <= 0)
                    continue;
                el = new int[n];
                for (int i = 0; i < n; i++)
                {
                    ss >> s;
                    if (s.empty() || !isdigit(s[0]))
                    {
                        flag = true;
                        break;
                    }
                    el[i] = stoi(s);
                    s.clear();
                }
                if (flag)
                    continue;
                Permutations p(n, el);
                p.run();
                delete[] el;
            }
            f.close();
        }
        else
        {
            Permutations p(n, el);
            p.run();
            delete[] el;
        }
    }
    cin >> n;
}
