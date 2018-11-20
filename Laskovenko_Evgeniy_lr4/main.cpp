#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include "btree.h"
#include "api.h"
//#include "myexception.h"

using namespace std;

int main()
{
    string filename;
    string temp_str;
    filebuf file;
    stringbuf str_buf;
    istream is_str(&str_buf);

    while(true)
    {
        try
        {
            cout << "Enter a name of the data-file or press ENTER to exit:" << endl;
            getline(cin, filename);
            if(filename.empty())
                break;

            if(!file.open(filename, ios::in))
            {
                file.close();
                throw "Incorrect filename.";
            }

            auto size = file.in_avail();
            char temp_ch;
            cout << "File contains: ";
            for(auto c_size = 0; c_size<size; c_size++)
            {
                temp_ch=file.sbumpc();
                cout << temp_ch;
                if(temp_ch != ' ' && temp_ch != '\n')
                    temp_str.append(1, temp_ch);
            }
            cout << endl;
            file.close();
            if(!temp_str.size())
                throw "Input file is empty.";

            str_buf.str(temp_str);
            temp_str.clear();
            auto root = new BinTree;
            buildBT_RLR(is_str, root);

            cout << "Binary tree:" << endl;
            printBT(root);

            cout << "Infix form:" << endl <<'(';
            prefix_to_infix(root);
            cout << ')';
            cout << endl;

            fixBT(root);
            cout << "Fixed binary tree:" << endl;
            printBT(root);

        }
        catch (const char* msg)
        { cout << msg << endl; }
    }
    return 0;
}
