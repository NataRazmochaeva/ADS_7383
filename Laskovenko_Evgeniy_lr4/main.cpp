#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include "btree.h"
#include "api.h"
#include "myexception.h"

using namespace std;

int main()
{
    string filename;
    string temp_str;
    filebuf file;
    stringbuf str_buf;
    istream is_str(&str_buf);

    int int_t;
    string t_str;
    char temp_ch;
    long size;

    while(true)
    {
        try
        {
            cout << "Enter \"1\" to input data from file." << endl
                 << "Enter \"2\" to input data from console."<< endl
                 << "Press ENTER to exit." << endl;
            getline(cin, t_str);
            if(t_str.empty())
                break;
            int_t = stoi(t_str);
            t_str.clear();

            switch(int_t)
            {
            case 0:
                break;
            case 1:
                cout << "Enter a name of the data-file:" << endl;
                getline(cin, filename);
                if(filename.empty())
                    throw new my_ex("Empty filename.");

                if(!file.open(filename, ios::in))
                {
                    file.close();
                    throw new my_ex("Incorrect filename.");
                }

                size = file.in_avail();
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

                break;
            case 2:
                cout << "Enter an expression:" << endl;
                getline(cin, temp_str);
                if(temp_str.empty())
                    throw new my_ex("Empty.");

                break;
            }

            str_buf.str(temp_str);
            temp_str.clear();
            auto root = new BinTree;
            buildBT_RLR(is_str, root);
            char t_ch = '\0';
            is_str.get(t_ch);
            if(t_ch)
                throw new my_ex("Error: Argument expected. (Odd operation)");
            is_str.clear();

            cout << "Binary tree:" << endl;
            printBT(root);

            cout << "Infix form:" << endl;
            prefix_to_infix(root);
            cout << endl;

            fixBT(root);
            cout << "Fixed binary tree:" << endl;
            printBT(root);
            delete root;
        }
        catch (exception* ex)
        {
            cout << ex->what() << endl;
            temp_str.clear();
            is_str.clear();
        }
        catch (...)
        {
            cout << "It isn't an integer!" << endl;
            continue;
        }
    }
    return 0;
}
