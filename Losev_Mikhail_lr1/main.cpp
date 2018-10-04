#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>

using namespace std;

bool Bracket(char *buf);
bool Round (char **buf, char s);
bool Figure (char **buf, char s);
bool Square (char **buf, char s);
void Error (short k);

void Load ( char *filename, char *buf )
{
	ifstream infile (filename);
    if (!infile) cout << "Входной файл не открыт" << endl;
    else {
		cout << "Входной файл открыт" << endl;
		infile >> buf;
   }  
}

void PrintAnsw(char *exp)
{
    cout << "Анализатор скобок:" << endl;
    bool b = Bracket(exp);
    if (b) cout << endl << "ЭТО СКОБКИ!" << endl;
    else cout << "НЕТ, ЭТО НЕ СКОБКИ!" << endl;
}

void UserInterface ()
{
    int key;
    char exp[100] = {0};
    while (true) {
        cout << "Выбери действие:" << endl;
        cout << "0. Завершить выполнение;" << endl;
        cout << "1. Загрузить выражение из пользовательского файла;" << endl;
        cout << "2. Загрузить выражение из файла по умолчанию;" << endl;
        cout << "3. Ввести выражение с клавиатуры;" << endl;
        cin >> key;
        switch (key) {
            case 0: 
                return;
                break;
            case 1:
            {
				cout << "input file name: ";
                char filename[20];
                cin >> filename;
                Load(filename, exp);
                PrintAnsw(exp);
            } 
            break;
            case 2:
            {
                Load("in_seq5.txt", exp);
                PrintAnsw(exp);
            } 
            break;
            case 3:
            {
				cout << "input expression: ";
				cin >> exp;
				PrintAnsw(exp);
            } 
            break;
            
            //
        
            default : cout << "! - ...";
            break;    
            // ?
        };
    }
}


int main ( )
{
    UserInterface();
    return 0;
    
}

bool Square (char **buf, char s)
// квадратные::=[круглые фигурные] | +
// s － текущий символ входной строки
{   bool k;
    if (s == '+') { return true;}
    else if ( s == '[' )
        {   if (*((*buf)++))
            {   cout << **buf;
                k = Round (buf, **buf);
                if (k)
                {   if (*((*buf)++))
                    {   cout << **buf;
                        k = Figure (buf, **buf);}
                    else {Error (5); return false;} // квадр - пуст!
                }
                else return false; //первый квадр ошибочен
                if (k) // оба квадр правильны
                    if (*((*buf)++))
                    {   if (**buf != ']') {Error(3 ); return false;}
                        cout << **buf;
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

bool Round (char **buf, char s)
// круглые::=(фигурные квадратные) | -
// s － текущий символ входной строки
{   bool k;
    if (s == '-') { return true;}
    else if ( s == '(' )
        {   if (*((*buf)++))
            {   cout << **buf;
                k = Figure (buf, **buf);
                if (k)
                {   if (*((*buf)++))
                    {   cout << **buf;
                        k = Square (buf, **buf);}
                    else {Error (8); return false;} // кругл - пуст!
                }
                else return false; //первый квадр ошибочен
                if (k) // оба кругл правильны
                    if (*((*buf)++))
                    {   if (**buf != ')') {Error(6); return false;}
                        cout << **buf;
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


bool Figure (char **buf, char s)
// фигурные::={квадратные круглые} | 0
// s － текущий символ входной строки
{   bool k;
    if (s == '0') { return true;}
    else if ( s == '{' )
        {   if (*((*buf)++))
            {   cout << **buf;
                k = Square (buf, **buf);
                if (k)
                {   if (*((*buf)++))
                    {   cout << **buf;
                        k = Round (buf, **buf);}
                    else {Error (11); return false;} // фиг - пуст!
                }
                else return false; //первый квадр ошибочен
                if (k) // оба квадр правильны
                    if (*((*buf)++))
                    {   if (**buf != '}') {Error(9); return false;}
                        cout << **buf;
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

bool Bracket(char *buf)
{   char s;
    bool b;
    b = false;
    s = *(buf);
    if (s)
    {   cout << s;
        if ((s == '+') || (s == '[')) b = Square (&buf, s);
        else if ((s == '-') || (s == '(')) b = Round (&buf, s);
            else if ((s == '0') || (s == '{')) b = Figure (&buf, s);
                else Error(2); //недопустимый начальный символ
        s = ((*buf)++);
        if (b && !(*buf)) Error(1); // лишние символы
        b = (b && *buf);
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
