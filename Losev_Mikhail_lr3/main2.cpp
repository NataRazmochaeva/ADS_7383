// Программа клиент вычисляет арифметическое выражение, заданное в постфиксной форме
// Ссылочная реализация в динамической (связанной) памяти

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdint>

#include "stack_vec.h"

using namespace std;

bool IsDigit( char c )
{
	return ( (c <= '9') && (c >= '0'));
}

bool IsOperator( char c )
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

long long int CalcPrefixExp(string expr)
{
	Stack <long long int> numbers;
	int n = expr.length();

	for (int i = n - 1; i >= 0; i--) 
	{	// бежим от конца выражения к началу
		if (IsOperator(expr[i]))
		{   // если попался оператоp
    
    
			long long int x = numbers.pop();
			long long int y = numbers.pop(); 
			if (expr[i] == '+'){
				if ((x > 0 && y > 0 && INT64_MAX - y < x) || 
       				(x < 0 && y < 0 && INT64_MIN - y > x)) {
      			  	cerr << "error overflow" << endl;
   					} // check if overflow
				numbers.push(x + y);
			}
			if (expr[i] == '*') {
				if ((x > 0 && y > 0 && INT64_MAX / x < y) ||
      				(x < 0 && y < 0 && INT64_MAX / x < y) ||
      				(x > 0 && y < 0 && INT64_MIN / x > y) ||
      				(x < 0 && y > 0 && INT64_MIN / x > y)) {
					cerr << "error overflow" << endl;
				} // check if overflow
				numbers.push(x * y);
			}
			if (expr[i] == '-'){
				if ((y > 0 && x < 0 && INT64_MIN + y > x) ||
      				(y < 0 && x > 0 && INT64_MAX + y < x)) {
					cerr << "error overflow" << endl;
				} // check if overflow
				numbers.push(x - y);
			}
			if (expr[i] == '/') {
				// dont check if overflow cause there cant be overflow when div
				numbers.push(x / y);
				
			}
			if (expr[i] == '^'){
				long long int p = pow(x, y);
				cout << x << y << endl;
				if (( x > 0 && y > 0 && log((double)INT64_MAX) / log((double)x) <= (double)y) ||
					( x < 0 && y > 0 && log(-1 * (double)INT64_MIN) / log(-1 * (double)x) <= (double)y)) {
					// ln(INT64_MAX) / ln(x) = log_x(INT64_MAX) <= y <=>  INT64_MAX <= x ^ y => OVERFLOOOOOOOW
					// нестрогое неравенство в целых числах эквивалентно прибавлению единицы к меньшей части
					// a < b <=> a + 1 <= b
					// прибавление единицы к логарифму нужно, потому что он может округлиться в том числе вниз, 
					// если его значение не целое. например, log_2 (2^63 - 1) < 63, но округляется до 63.
					// ln(INT64_MIN) / ln(x) = log_x(INT64_MIN) > y <=>  INT64_MIN > x ^ y => OVERFLOOOOOOOW
					
					cerr << "error overflow" << endl;
				} // check if overflow
				numbers.push(p);
			}
		}
		if (IsDigit(expr[i])) //
		{  // если попалось число
			long long int dec_exp = 10;
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

	long long int answ = numbers.pop(); // сохраение ответа

	numbers.destroy();

	return answ;
}

void UserInterface ()
{
    int key;
    long long int answ;
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
					cout << "computing..." << endl;
					answ = CalcPrefixExp(expr);
					cout << expr << " = " << answ << endl;
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
					cout << "computing..." << endl;
					answ = CalcPrefixExp(expr);
					cout << expr << " = " << answ << endl;
				}
				else cout << "Файл не открыт\n";
            } 
            break;

            case 3:
            {
            	cout << "Введите выражение: ";
            	cin.ignore(256, '\n');// игнорируем оставшиеся в cin после ввода '3' символы
				getline(cin, expr);
				cout << "computing..." << endl;
				answ = CalcPrefixExp(expr);
				cout << expr << " = " << answ << endl;
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
