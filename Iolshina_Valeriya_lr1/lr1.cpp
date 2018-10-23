#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

bool isInt(ifstream &infile, char &ref);

bool isUnsInt(ifstream &infile, char &ref, int i);

void Error(short k);

bool isNumber(ifstream &infile, char s)
{
        bool b;
        if(!(infile >> s))
        {
                Error(2); 
                return false;
        }
        cout << s;
        b = isInt(infile, s);
        if(!b)
        {
                Error(3); 
                return false;
        }
        if(s == '.')
        {
                if(!(infile >> s))
                {
                        Error(4); 
                        return false;
                }
                cout << s;
                int i=0;
                b = isUnsInt(infile, s, i);
                if(!b)
                {
                        Error(6); 
                        return false;
                }
                if (s == 'E' || s == 'e')
                {
                        if(!(infile >> s))
                                return false;
                        cout << s;
                        b = isInt(infile, s);
                        if(b)
                                return true;
                        else
                        {
                                Error(3);
                                return false; 
                        }
                }
                else
                        return true;
        }
        else if (s == 'E' || s == 'e')
        {
                if(!(infile >> s))
                        return false;
                cout << s;
                b = isInt(infile, s);
                if(b)
                        return true;
                else
                {
                        Error(3);
                        return false;
                }
        }
        else
        {
                Error(5);
                return false;
        }
}



bool isInt(ifstream &infile, char &ref)
{
	bool b;
	int i=0;
	if(ref == '+' || ref == '-')
        {
	        if(infile >> ref)
                {
                        cout << ref;
                        b = isUnsInt(infile, ref, i);
		}
        	else return false;
	}
	else b = isUnsInt(infile, ref, i);
	if(b) return true;
	else return false;
}

bool isUnsInt(ifstream &infile, char &ref, int i)
{
	bool b;
	b = isdigit(ref);
	i++;
	if(b)
	{
		if(infile >> ref)
		{
                	cout << ref;
			isUnsInt(infile, ref, i);
		}
		else return true;
	}
	else if (i == 1)
		return false;
	else return true;
}

void Error (short k)
{
	cout << endl << "err#" << k << endl;
	switch (k)
	{

		case 1: cout << "! - Лишние символы во входной строке" << endl; break;

		case 2: cout << "! - Отсутствует  начальный символ" << endl; break;

		case 3: cout << "! - Символ не является целым числом" << endl; break;

		case 4: cout << "! - Отсутствует нужный символ" << endl; break;

		case 5: cout << "! - Отсутствует точка или экспонента" << endl; break;

		case 6: cout << "! - Символ не является целым беззнаковым" << endl; break;

		case 7: cout << "! - Символ не является экспонентой" << endl; break;

		case 8: cout << "! - " << endl; break;

		default : cout << "! - ...";break;

	};
}

bool res (bool b)
{
	char s;
        ifstream infile ("ex.txt");
        if(!infile)
                cout << "Входной файл не открыт" << endl;
        cout << "Анализатор для вещественного числа:" << endl;
        b = isNumber(infile, s);
        if(b && !infile.eof())
        {
                Error(1);
                return false;
        }
        b = (b && infile.eof());
        if(b)
                cout << endl << "Это вещественное число" << endl;
        else
                cout << endl << "Это НЕ вещественное число" << endl;
}

int main()
{
	char s;
	char ss[100];
	char &ref = s;
	bool b, exit = true;
	int n;
	while(exit)
	{
		cout << "Введите 1, если хотите ввести вещественное число" << endl << "Введите 2, если хотите использовать число из файла ex.txt" << endl << "Введите 3, чтобы завершить работу" << endl;
        	cin >> n;
		switch(n)
		{
			case 1:
				{
				ofstream tempfile("ex.txt");
				cout << "Введите вещественное чило:" << endl;
				cin >> ss;
				tempfile << ss;
				tempfile.close();
                        	res(b);
				}
				break;
			case 2:
				{
				res(b);
				}
				break;
			case 3:
				{
				exit = false;
				return 0;
				}
			default:
				cout << "Повторите попытку" << endl;
				break;
		}
	}
return 0;
}

