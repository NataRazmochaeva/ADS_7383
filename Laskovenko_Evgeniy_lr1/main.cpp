#include <iostream>
#include <fstream>
#include <sstream>
#include "function.hpp"

using namespace std;

int main()
{
    filebuf file;
    string file_name;
    stringbuf exp;
    string temp_str;
    int c_temp = -1;
    bool res = false;
    int visual = 0;
    char vis_ch;

    while(c_temp!=0)
    {
        cout << "Do you want to enable algorithm visualization? [Y/N]" << endl;
        cin >> vis_ch;
        cin.ignore();
        if(vis_ch == 'Y' || vis_ch == 'N')
        {
            c_temp = 0;
            if(vis_ch == 'Y')
                visual = 1;
            else
                visual = 0;
        }
        else
            cout << "Wrong answer. Type 'Y' or 'N'." << endl;
    }

    cout << "Enter \"1\" to input data from file." << endl
         << "Enter \"2\" to input data from console." << endl
         << "Enter \"0\" to exit." << endl;
    cin >> c_temp;
    if(c_temp == 3)
        c_temp = -1;
    cin.ignore(); //Игнорим символ переноса каретки

    while(c_temp!=0)
    {
        switch(c_temp)
        {
        case 1: //Кейс считывания с файла
            cout << "Enter a name of the data-file:" << endl;
            cin >> file_name;
            if(!file.open(file_name, ios::in))
                cout << "Input file isn't opened." << endl;
            else
            {     
                istream is_file(&file); //Объявляем входной поток, инициализируем адресом файл-буфера
                streamsize size = file.in_avail();
                streamsize c_size = 0;
                for(c_size=0; c_size<size - 1; c_size++)
                    temp_str += file.sgetc();
                cout << "File contains: " << temp_str << endl;;
                temp_str = '\0';
                res = const_expression(is_file, visual);
                file.close();
                c_temp = 3;
            }

            break;
        case 2: //Кейс считывания с консоли
            cout << "Enter an expression:" << endl;
            getline(cin, temp_str);
            if(temp_str != "\0")
            {
                istream is_str(&exp); //Объявляем входной поток, инициализируем адресом строки-буфера
                exp.str(temp_str); //Помещаем в строку-буфер считанную строку с входного потока
                res = const_expression(is_str, visual);
                temp_str = '\0';
                c_temp = 3;
            }
            break;
        case 0: //Кейс выхода
            break;
        case 3: //Кейс проверки
            cout << "Result: ";
            if(res)
                cout << "It is an expression." << endl;
            else
                cout << "It isn't an expression." << endl;

            c_temp = -1;
            break;
        default: //Кейс других входных данных
            cout << "Enter \"1\" to read from file, \"2\" to read from console or \"0\" to exit." << endl;
            cin >> c_temp;
            cin.ignore(); //Игнорим '\n'

            break;
        }
    }

    return 0;
}
