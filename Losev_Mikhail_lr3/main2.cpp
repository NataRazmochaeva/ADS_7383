// Программа клиент вычисляет арифметическое выражение, заданное в постфиксной форме
// Ссылочная реализация в динамической (связанной) памяти
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cstring>

#include "st_interf2.h"

using namespace std;
using namespace st_modul2;

bool IsDigit( char c )
{
	return ( (c <= '9') && (c >= '0'));
}

int CalcPrefixExp(char *expr)
{
	Stack <int> numbers;
	Stack <char> operators;
	Stack <bool> tags; // 0 - operator; 1 - number
	int n = strlen(expr);

	for (int i = 0; i < n; i++)
	{	
		if (expr[i] == '+' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^') {
			operators.push(expr[i]);
			tags.push(false);
		}

		if (expr[i] == '-')
			if (IsDigit(expr[i + 1])){
				i += 1;
				numbers.push(0);
				while ((expr[i] >= '0') && (expr[i] <= '9')) 
				{
					numbers.push(10*numbers.pop2() + (expr[i++]-'0'));
				} 
				numbers.push(numbers.pop2() * -1);
				tags.push(true);
			}
			else{
				operators.push(expr[i]);
				tags.push(false);
			}

		if (IsDigit(expr[i]))
		{
			numbers.push(0);
			while ((expr[i] >= '0') && (expr[i] <= '9')) 
			{
				numbers.push(10*numbers.pop2() + (expr[i++]-'0'));
			} 
			tags.push(true);

			while (tags.two_numbers()){
				char op = operators.pop2();
				tags.pop();
				int x = numbers.pop2();
		  		int y = numbers.pop2();
				
				if (op == '+')
					numbers.push(y + x);
				if (op == '*') 
					numbers.push(y * x);
				if (op == '-')
					numbers.push(y - x);
				if (op == '/') 
					numbers.push(y / x);
		  		if (op == '^') 
		  			numbers.push(pow(y, x));
		  		tags.pop();
		  		tags.pop();	
		  		tags.push(true);
			}
		}
	}

	int answ = numbers.pop2(); // сохраение ответа

	numbers.destroy();
	operators.destroy();
	tags.destroy();

	return answ;
}

template <typename t>
char *Read_str (t *stream)
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

void UserInterface ()
{
    int key;
	char *a; 

    while (true) {
        cout << "Выбери действие:" << endl;
        cout << "0. Завершить выполнение;" << endl;
        cout << "1. Загрузить префиксное выражение из пользовательского файла;" << endl;
        cout << "2. Загрузить префиксное выражение из файла по умолчанию;" << endl;
        cout << "3. Ввести префиксное выражение с клавиатуры;" << endl;
        cin >> key;
        switch (key) {
            case 0: 
                return;
                break;
            case 1:
			{
				char *filename; 

				cout << "Введите имя файла: ";
				cin.ignore(256, '\n');// игнорируем оставшиеся в cin после ввода '1' символы
				filename = Read_str(&cin);
				ifstream fin(filename);
				fin >> noskipws;	// не пропускать пробелы 
				if (fin){
					a = Read_str(&fin);
					cout << a << " = " << CalcPrefixExp(a) << endl;
				}
				else cout << "Файл не открыт\n"; 
			}	
            break;
            case 2:
            {
				ifstream fin("prefix.txt");
				fin >> noskipws;	// не пропускать пробелы 
				if (fin){
					a = Read_str(&fin);
					cout << a << " = " << CalcPrefixExp(a) << endl;
				}
				else cout << "Файл не открыт\n";
            } 
            break;

            case 3:
            {
            	cout << "Введите выражение: ";
            	cin.ignore(256, '\n');// игнорируем оставшиеся в cin после ввода '3' символы
				a = Read_str(&cin);
				cout << a << " = " << CalcPrefixExp(a) << endl;
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
