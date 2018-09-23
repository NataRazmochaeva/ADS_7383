#include "func.hpp"

using namespace std;

int main(){
	
	bool res;//Для записи результата 
	bool cur;//Промежуточное переменная для выполнения логической операции
	int is_okey = 0;//Переменная для определения правильности выполнения программы
	int flag=0;//Для ф-ии "rec", отслеживает какой раз я захожу в функцию 
	int choise = 0; //Для выбора потока данных

	cout << "Введите 1, если хотите считать выражение с терминала" << endl;
	cout << "Введите 2, если хотите считать выражение из файла" << endl;
	cout << "Введите 3, если хотите выйти из программы" << endl;	
	cin >> choise;
	cin.ignore();
	switch (choise){
		case 1:
			{	
				cout << "Введите логическое выражение: ";
				is_okey=1;
				stringbuf exp;//буфер под строку, введенную из терминала
				string temp_str;
				getline(cin, temp_str);
				istream is_str(&exp);
                		exp.str(temp_str);
                		res = rec(is_str, cur, flag);
			}
				break;
		case 2:
			{
				is_okey=1;
				filebuf file;//буфер под строку из файла
				file.open("input.txt", ios::in);
				istream files(&file);
				res = rec(files, cur, flag);
				file.close();
			}
				break;
		case 3:
			{
				cout << "Вы вышли из программы" << endl;
			}
				break;
		default:
			{
				cout << "Вы ввели не то значение, попробуйте заново" << endl;
			}			
				break;
	}

	if(is_okey){
		cout << "Ответ: ";
		if(res)
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}

    return 0;
}
