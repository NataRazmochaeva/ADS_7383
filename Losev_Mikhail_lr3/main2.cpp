// Программа клиент вычисляет арифметическое выражение, заданное в постфиксной форме
// Ссылочная реализация в динамической (связанной) памяти
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cstring>

#include "stack_vec.h"

using namespace std;
//using namespace st_modul2;

bool IsDigit( char c )
{
	return ( (c <= '9') && (c >= '0'));
}

bool IsOperator( char c )
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int CalcPrefixExp(string expr)
{
	Stack <int> numbers;
	int n = expr.length();

	for (int i = n - 1; i >= 0; i--) 
	{	// бежим от конца выражения к началу
		if (IsOperator(expr[i]))
		{   // если попался оператор
			int x = numbers.pop();
			int y = numbers.pop(); 
			if (expr[i] == '+')
				numbers.push(x + y);
			if (expr[i] == '*') 
				numbers.push(x * y);
			if (expr[i] == '-')
				numbers.push(x - y);
			if (expr[i] == '/') 
				numbers.push(x / y);
			if (expr[i] == '^') 
				numbers.push(pow(x, y));
		}
		if (IsDigit(expr[i])) //
		{  // если попалось число
			int dec_exp = 10;
			numbers.push(expr[i--] - '0');  // пушим младшую цифру
			while (IsDigit(expr[i])) 
			{	// пока идут цифры числа, продолжаем его ввод
				numbers.push(numbers.pop() + dec_exp * (expr[i--] - '0'));
				dec_exp *= 10;
			}
			if (expr[i] == '-') // если число отрицательное
				numbers.push(-1 * numbers.pop());
		}
		
	}

	int answ = numbers.pop(); // сохраение ответа

	numbers.destroy();

	return answ;
}

void UserInterface ()
{
    int key;
	string expr;

    while (true) {
        cout << "Выбери действие:" << endl;
        cout << "0. Завершить выполнение;" << endl;
        cout << "1. Загрузить префиксное выражение из пользовательского файла;" << endl;
        cout << "2. Загрузить префиксное выражение из файла по умолчанию (prefix.txt);" << endl;
        cout << "3. Ввести префиксное выражение с клавиатуры;" << endl;
        cin >> key;
        switch (key) {
            case 0: 
                return;
                break;
            case 1:
			{
				string filename; 
				cout << "Введите имя файла: ";
				cin.ignore(256, '\n');// игнорируем оставшиеся в cin после ввода '1' символы
				getline(cin, filename);
				ifstream fin(filename);
				fin >> noskipws;	// не пропускать пробелы 
				if (fin){
					getline(fin, expr);
					cout << expr << " = " << CalcPrefixExp(expr) << endl;
				}
				else cout << "Файл не открыт\n"; 
			}	
            break;
            case 2:
            {
				ifstream fin("prefix.txt");
				fin >> noskipws;	// не пропускать пробелы 
				if (fin){
					getline(fin, expr);
					cout << expr << " = " << CalcPrefixExp(expr) << endl;
				}
				else cout << "Файл не открыт\n";
            } 
            break;

            case 3:
            {
            	cout << "Введите выражение: ";
            	cin.ignore(256, '\n');// игнорируем оставшиеся в cin после ввода '3' символы
				getline(cin, expr);
				cout << expr << " = " << CalcPrefixExp(expr) << endl;
            } 
            break;
        
            default : cout << "! - ...";
            break;    
        };
    }
}

int main () 
{
	UserInterface();
	return (0);
}
