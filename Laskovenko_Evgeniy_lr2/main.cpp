#include <fstream>
#include <exception>
#include "header.h"
#include "atoms.h"
#include "list.h"
#include "pair.h"

using namespace std;

int main()
{
    int int_temp = -1;

    //case 1, 2
    string file_name;
    string temp_str;
    filebuf file;
    //case 3
    stringbuf str_buf;
    istream is_str(&str_buf);

    while(int_temp)
    {
        auto head = new Pair;
        auto result = new Atoms;

        char istr_null ='\0';


        switch(int_temp)
        {
        case 1:
            cout << "Enter a name of the data-file:"
                 << endl;
            getline(cin, file_name);

            if(!file.open(file_name, ios::in))
                cout << "Input file isn't opened."
                     << endl;
            else
            {
                auto size = file.in_avail();

                for(auto c_size = 0; c_size<size; c_size++)
                        temp_str.append(1, file.sbumpc());
                cout << "File contains: "
                     << temp_str
                     << endl;

                file.close();
                int_temp = 3;
            }

            break;
        case 2:
            cout << "Enter an expression:"
                 << endl;
            try
            {
                getline(cin, temp_str);
                if(temp_str=="")
                    throw 0;
            }
            catch (...)
            {
                cout << "Empty string!"
                     << endl;
                break;
            }

            int_temp = 3;

            break;
        case 0:
            break;
        case 3:
            cout << "=============================================="
                 << endl;

            str_buf.str(temp_str);

            try
            {
                set_right_list(is_str, head);
                if(is_str>>istr_null)
                    throw 0;
            }
            catch (...)
            {
                cout << "It isn't an expression!"
                     << endl
                     << "=============================================="
                     << endl;
                delete head;
                delete result;
                temp_str.clear();
                is_str.clear();
                int_temp = -1;
                break;
            }

            cout << "List is set. Result: "
                 << endl
                 << '(';
            cout_list(head);
            cout << ')'
                 << endl;

            diff_atoms(head, result, result);
            cout_diff_list(result);

            cout << "=============================================="
                 << endl;

            delete head;
            delete result;
            temp_str.clear();
            is_str.clear();
            int_temp = -1;

            break;
        default:
            cout << "Enter \"1\" to input data from file."
                 << endl
                 << "Enter \"2\" to input data from console."
                 << endl
                 << "Enter \"0\" to exit."
                 << endl;
            try
            {
                string t_str;
                getline(cin, t_str);
                int_temp = stoi(t_str);
                if(int_temp == 3)
                    int_temp = -1;
            }
            catch(...)
            {
                cout << "It isn't an integer, retard!"
                     << endl;
            }

            break;
        }
    }
    return 0;
}
