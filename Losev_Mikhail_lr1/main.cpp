#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>


using namespace std;

bool Bracket(ifstream &infile);
bool Round (ifstream &infile, char s);
bool Square (ifstream &infile, char s );
bool Figure (ifstream &infile, char s );
void Error (short k);
/*
void UserInterface ()
{
    int key;
    while (true) {
        cout << "Выбери действие:" << endl;
        cout << "0. Завершить выполнение;" << endl;
        cout << "1. Загрузить выражение из файла;" << endl;
        cout << "2. Ввести выражение с клавиатуры;" << endl;
        cout << "3. Анализировать выражение;" << endl;
        cin >> key;
        switch (key) {
            case 0: 
                return;
                break;
            case 1:{
                    cout << "input file name: ";
                    char filename[20];
                    cin >> filename;
                    ifstream infile (filename);
                    if (!infile) cout << "Входной файл не открыт" << endl;
                    else cout << "Входной файл открыт" << endl;
                } 
                break;
            case 2:{
                    cout << "Анализатор скобок:" << endl;
                    ifdef (infile) {
                        bool b = Bracket (infile);
                        if (b) cout << endl << "ЭТО СКОБКИ!" << endl;
                        else cout <<"НЕТ, ЭТО НЕ СКОБКИ!" << endl;
                    }
                    else cout << "Выражение не определено" << endl;
                } 
                break;
            //
        
            default : cout << "! - ...";
            break;    
            // ?
        };
    }
}
*/

int main ( )
{
    setlocale (0,"Rus"); // для MVC++ 2010
    ifstream infile ("in_seq5.txt");
    if (!infile) cout << "Входной файл не открыт!" << endl;
    cout << "Анализатор скобок:" << endl;
    bool b = Bracket (infile);
    if (b) cout << endl << "ЭТО СКОБКИ!" << endl;
    else cout <<"НЕТ, ЭТО НЕ СКОБКИ!" << endl;
 
    return 0;
}

bool Square (ifstream &infile, char s)
// квадратные::=[круглые фигурные] | +
// s － текущий символ входной строки
{   bool k;
    if (s == '+') { return true;}
    else if ( s == '[' )
        {   if (infile >> s)
            {   cout << s;
                k = Round (infile,s);
                if (k)
                {   if (infile >> s)
                    {   cout << s;
                        k = Figure (infile,s);}
                    else {Error (5); return false;} // квадр - пуст!
                }
                else return false; //первый квадр ошибочен
                if (k) // оба квадр правильны
                    if (infile >> s)
                    {   if (s != ']') {Error(3 ); return false;}
                        cout << s;
                        return true;
                    }
                    else {Error (3); return false;}
                else return false;
            }
            else { Error (5); return false;} // квадр － пуст!
        }
    else { Error(4); return false;} // не + и не [ 
}
// end of Square

bool Round (ifstream &infile, char s)
// круглые::=(фигурные квадратные) | -
// s － текущий символ входной строки
{   bool k;
    if (s == '-') { return true;}
    else if ( s == '(' )
        {   if (infile >> s)
            {   cout << s;
                k = Figure (infile,s);
                if (k)
                {   if (infile >> s)
                    {   cout << s;
                        k = Square (infile,s);}
                    else {Error (8); return false;} // кругл - пуст!
                }
                else return false; //первый квадр ошибочен
                if (k) // оба квадр правильны
                    if (infile >> s)
                    {   if (s != ')') {Error(6); return false;}
                        cout << s;
                        return true;
                    }
                    else {Error (6); return false;} 
                else return false;
            }
        else { Error (8); return false;} // кругл － пуст!
        }
    else { Error(7); return false;} // не – и не ( 
}
// end of Round


bool Figure (ifstream &infile, char s)
// фигурные::={квадратные круглые} | 0
// s － текущий символ входной строки
{   bool k;
    if (s == '0') { return true;}
    else if ( s == '{' )
        {   if (infile >> s)
            {   cout << s;
                k = Square (infile,s);
                if (k)
                {   if (infile >> s)
                    {   cout << s;
                        k = Round (infile,s);}
                    else {Error (11); return false;} // фиг - пуст!
                }
                else return false; //первый квадр ошибочен
                if (k) // оба квадр правильны
                    if (infile >> s)
                    {   if (s != '}') {Error(9); return false;}
                        cout << s;
                        return true;
                    }
                    else {Error (9); return false;}
                else return false;
            }
            else { Error (11); return false;} // фиг － пуст!
        }
    else { Error(10); return false;} // не – и не ( }
}
// end of Square

bool Bracket(ifstream &infile)
{   char s;
    bool b;
    b = false;
    if (infile >> s)
    {   cout << s;
        if ((s == '+') || (s == '[')) b = Square (infile, s);
        else if ((s == '-') || (s == '(')) b = Round (infile, s);
            else if ((s == '0') || (s == '{')) b = Figure (infile, s);
                else Error(2); //недопустимый начальный символ
        infile >> s;
        if (b && !infile.eof()) Error(1); // лишние символы
        b = (b && infile.eof());
    }
    else Error (0); // пустая входная строка
    return b;
}

void Error (short k)
{
    cout << endl << "err#" << k << endl;
    switch (k) {
        case 0: cout << "! - Пустая входная строка" << endl; break;
        //{Bracket}
        case 1: cout << "! - Лишние символы во входной строке" << endl; break;
        //{Bracket}
        case 2: cout << "! - Недопустимый начальный символ" << endl; break;
        //{Bracket}
        case 3: cout << "! - Отсутствует ']'." << endl; break;
        //{Square}
        case 4: cout << "! - Отсутствует '+' или '['." << endl; break;
        //{Square}
        case 5: cout << "! - Очередной квадр － пуст." << endl; break;
        //{Round}
        case 6: cout << "! - Отсутствует ')'." << endl; break;
        //{Round}
        case 7: cout << "! - Отсутствует – или (." << endl; break;
        //{Round}
        case 8: cout << "! - Очередной кругл － пуст." << endl; break;
        //{Round}
         case 9: cout << "! - Отсутствует '}'." << endl; break;
        //{Figure}
        case 10: cout << "! - Отсутствует 0 или {." << endl; break;
        //{Figure}
        case 11: cout << "! - Очередной фиг － пуст." << endl; break;
        //{Figure}
        default : cout << "! - ...";break;
        // ?
    };
}
// end of Error
