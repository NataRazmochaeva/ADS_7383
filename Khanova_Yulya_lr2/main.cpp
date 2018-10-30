#include <fstream>
#include <exception>
#include <sstream>
#include "functions.h"
#include "struct.h"

using namespace std;

int main()
{
    string temp_str;
    stringbuf str_buf;
    istream is_str(&str_buf);
    string file_name;
    filebuf file;
    int t = 3;

    while(true)
    {
        try
        {
            List* head;

            char istr_null ='\0';

            switch(t)
            {
            case 1:
                cout << "Enter a name of the data-file:" << endl;
                getline(cin, file_name);

                if(!file.open(file_name, ios::in))
                    throw "Input file isn't opened.";
                else
                {
                    auto size = file.in_avail();
                    if(!size)
                        throw "File is empty.";

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
                    t = -1;
                }
                break;
            case 2:
                cout << "Enter an expression." << endl;
                getline(cin, temp_str);
                t = -1;
                break;
            case -1:
                str_buf.str(temp_str);
                head = set_list(is_str);
                out_list(head);
                cout << endl;
                mod_list(head, nullptr);
                out_list(head);
                cout << endl;
                if(is_str>>istr_null)
                    throw "Operations < operators.";

                temp_str.clear();
                is_str.clear();
                t = 3;

                break;
            case 0:
                return 0;
            default:
                cout << "Enter \"1\" to input data from file." << endl
                     << "Enter \"2\" to input data from console." << endl
                     << "Enter \"0\" to exit."  << endl;
                string t_str;
                getline(cin, t_str);
                t = stoi(t_str);
                if(t == -1)
                    t = 3;
                break;
            }
        }
        catch (char const* err)
        {
            cout << err << endl;
            t = 3;
        }
    }
}
