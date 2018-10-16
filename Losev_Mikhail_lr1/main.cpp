#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <string.h>

using namespace std;

bool Bracket(char *buf);
bool Round (char **buf, char s);
bool Figure (char **buf, char s);
bool Square (char **buf, char s);
void Error (short k);

char *Read_str (istream *stream)
{
    
    char *str, c;
    int size = 20; // размер стоки str
    str = new char[size];
    for (int i = 0;  (*stream).get(c); i++){
		if (c == '\n') // конец ввода строки
    		break;
    	if (i == size){ // когда i-ый символ уже не влезет в str
    		char *new_str = new char[2 * size];
			for (size_t l = 0; l < size; ++l)
    			new_str[l] = str[l];
    		size *= 2;
  	    	delete [] str;
    	  	str = new_str;
    	}
   		str[i] = c;
   	}
   	return str;
}

char *Read_str (ifstream *stream) // перегружаем функцию, чтобы она работала как для потоков istream, так и для потоков ifstream
{
    
    char *str, c;
    int size = 20; // размер стоки str
    str = new char[size];
    for (int i = 0;  (*stream).get(c); i++){
		if (c == '\n') // конец ввода строки
    		break;
    	if (i == size){ // когда i-ый символ уже не влезет в str
    		char *new_str = new char[2 * size];
			for (size_t l = 0; l < size; ++l)
    			new_str[l] = str[l];
    		size *= 2;
  	    	delete [] str;
    	  	str = new_str;
    	}
   		str[i] = c;
   	}
   	return str;
}

char *Load ( char *filename)
{
    ifstream infile (filename);
    char c, *buf;
    buf = Read_str(&infile);
    infile.close();
    return buf;
   
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
    char *exp;
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
                char *filename, c;
                cin.get(c);
                filename = Read_str(&cin);
                exp = Load(filename);
                PrintAnsw(exp);
                delete [] filename;
            } 
            break;
            case 2:
            {
                exp = Load("in_seq5.txt");
                PrintAnsw(exp);
            } 
            break;
            case 3:
            {
            	char c, *exp;
                cout << "input expression: ";
                cin.get(c);
                exp = Read_str(&cin);
                PrintAnsw(exp);
            } 
            break;
            
            //
        
            default : cout << "! - ...";
            break;    
            // ?
        };
    }
    delete [] exp;
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
    char exp[100] = {0};
    int j = 0;

    for (int i = 0; buf[i] != 0; i++) // убираем пробелы из строки
        if (buf[i] != ' ')
            exp[j++] = buf[i];
    strcpy(buf, exp); 

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