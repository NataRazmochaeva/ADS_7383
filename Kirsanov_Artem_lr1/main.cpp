//Вариант 8
// Program SyntaxAnalysisOfBracket;
// вариант с синхронным выводом входной строки (до места ошибки включительно)
/* Определения (синтаксис)
Expression = выражение, Logical = простое логическое, Mark = знак операции, Tilda - знак '~'
простое_логическое::= TRUE | FALSE | простой_идентификатор |
NOT простое_логическое
(простое_логическое знак_операции простое_логическое)
простой-идентификатор::=буква
знак-операции::= AND | OR
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
using namespace std ;
bool Expression(ifstream &infile, bool b, char s);
bool Logical (ifstream &infile, char s);
bool Mark (char s );
char Tilda(ifstream &infile, char s);
void Error (short k);

int main ()
{
    char str[1000];
    char str1[1];
    int k = 0;
    bool b;
    char s;
    setlocale (0,"Rus");

    while(k != 3){
        b = false;
        cout << endl <<"Анализатор выражения:" << endl << "1 - чтение из файла, 2 - ввод с клавиатуры, 3 - выход из программы." << endl;
        cin >> k;
        if(!isalnum(k)){ Error(8); return 0; }

        switch (k) {
        case 1:{
            cout << "Введите имя файла" << endl;
            cin >> str;
            ifstream infile(str);
            if (!infile) { cout << "Входной файл не открыт!" << endl; break; }
            if(infile>>s)
            {
                cout<<s;
                s = Tilda(infile, s);
                b = Logical(infile, s);
            }
            else { Error(0); b = false; }
            if(infile>>s && b){ Error(1); b = false; }
            break;
        }
        case 2:{
            cout << "Введите строку" << endl;
            cin.getline(str1, 1);
            cin.getline(str, 1000);
            ofstream fout("expression");
            fout << str;
            fout.close();
            ifstream infile("expression");
            if (!infile) { cout << "Входной файл не открыт!" << endl; break; }
            if(infile>>s)
            {
                cout<<s;
                s = Tilda(infile, s);
                b = Logical(infile, s);
            }
            else { Error(0); b = false; }
            if(infile>>s && b){ Error(1); b = false; }

            remove("expression");
            break;
        }
        case 3: break;
        default:{ Error(6); break; }
        }
        cout << endl;
        if(k == 1 || k == 2){
            if (b) cout << "ЭТО ВЫРАЖЕНИЕ!" << endl;
            else cout <<"НЕТ, ЭТО НЕ ВЫРАЖЕНИЕ!" << endl;
        }
    }


    return 0;
}


bool Logical (ifstream &infile, char s){
    if(s == '(')
    {
        if(infile>>s)
        {
                cout<<s;
                s = Tilda(infile, s);
                if(!Logical(infile, s))
                    return false;
        }
        else{ Error(7); return false; }

        if(infile>>s)
        {
            cout<<s;
            s = Tilda(infile, s);
            if(!Mark(s)){ Error(5); return false; }
        }
        else{ Error(5); return false; }
        if(infile>>s)
        {
            cout<<s;
            s = Tilda(infile, s);
            if(!Logical(infile, s))
                    return false;
        }
        else{ Error(5); return false; }
        if(infile>>s)
        {
            cout<<s;
            s = Tilda(infile, s);
            if (s == ')')
                return true;
            else{ Error(4); return false; }
        }
        else{ Error(4); return false; }
        }
    else if(isalpha(s) || (s == '0') || (s == '1'))
        return true;
    else{ Error(7); return false; }
}


bool Mark (char s){
    if((s == '^') || (s == '|')) return true;
    else{ Error(5); return false; }
}

char Tilda(ifstream &infile, char s){
    if( s == '~' ){
        if((infile >> s) && (s != '^') && (s != '|') && (s != '~')) { cout << s; return s; }
        else Error(3);
    }
    return s;
}

void Error (short k)
{
    cout << endl << "err#" << k << endl;
    switch (k) {
    case 0: cout << "! - Пустая входная строка" << endl; break;
    case 1: cout << "! - Лишние символы во входной строке" << endl; break;
    case 2: cout << "! - Недопустимый начальный символ" << endl; break;
    case 3: cout << "! - Отсутствует выражение после '~'." << endl; break;
    case 4: cout << "! - Отсутствует ')'" << endl; break;
    case 5: cout << "! - Отсутствует знак операции" << endl; break;
    case 6: cout << "! - Неверный выбор способа ввода." << endl; break;
    case 7: cout << "! - Отсутствует выражение" << endl; break;
    case 8: cout << "! - Неверный выбор способа ввода" << endl; break;
    default : cout << "! - ...";break;
    };
}
