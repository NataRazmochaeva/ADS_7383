#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include "stack.h"
#include "analyzer.h"

int
main()
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
                throw 1;

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
                throw 2;
            str_buf.str(temp_str);
            temp_str.clear();
            if(syn_analyzer(is_str, str_buf.in_avail()))
                cout << "It is an expression" << endl;
            else
                throw 3;
        }
        catch (int exp)
        {
            switch(exp)
            {
            case 1:
                cout << "Input file isn't opened." << endl;
                break;
            case 2:
                cout << "Input file is empty." << endl;
                break;
            case 3:
                cout << "It isn't an expression!" << endl;
                break;
            }
        }
        catch (char const* exp)
        {
            cout << exp << endl;
        }

    }
    return 0;
}
