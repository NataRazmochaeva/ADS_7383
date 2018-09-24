/* Вариант 13: Построить синтаксический анализатор для понятия скобки
   скобки::=А|скобка скобки
   скобка::=(В скобки)

   упрощение: Скобки ::= А|(В скобки) скобки
*/

#include <iostream>
#include <fstream>
#include <iomanip>

#define N 500

using namespace std;

bool Brackets(ifstream &infile);
void Error(short s); //символ короткой длины, короткий "int"

int main(){
	bool a, run=true;
	char arr[N];
	FILE* f;
	int pick;
	cout<<"\033[34m\tЗдравствуй! Я анализатор скобок, выбери что ты хочешь:\033[0m\n 1) Нажми 1, если хочешь проверить скобки в файле.\n 2) Нажми 2, если хочешь ввести скобки в консоль сам.\n 3) Нажми 3, если хочешь выйти из программы.\n";

	while(run){
		cin>>pick; //выбор

		switch(pick){

			case 1:{
				ifstream infile("test.txt");
				if(!infile)cout<<"Входной файл не может быть открыт!"<<endl;			
				else{
					a=Brackets(infile);
					cout<<endl;
					if(a) cout<<"\033[32mЭТО СКОБКИ:)\033[0m"<<endl;
					else cout<<"\033[31mНет, это не скобки:(\033[0m"<<endl;
				}
				break;
			}

			case 2:{
				f=fopen("test1.txt", "w"); //создание файла 
				cin>>arr;
				fputs(arr,f);
				fclose(f);
				ifstream infile("test1.txt");
				if(!infile)cout<<"Входной файл не может быть открыт!"<<endl;
				else{
					a=Brackets(infile);
					cout<<endl;
					if(a) cout<<"\033[32mЭТО СКОБКИ:)\033[0m"<<endl;
					else cout<<"\033[31mНет, это не скобки:(\033[0m"<<endl;
				}
	 			remove("test1.txt"); // удаление файла 
				break;
			}

			case 3:{
				run=false;
				break;
			}

			default:{
				run=false;
				cout<<"\033[31mНекорректный выбор!\033[0m\n"<<endl;
				break;
			}
		}
	}

	cout<<"\033[34mДо свидания!\033[0m\n"<<endl;
	return 0;
}

bool Brackets(ifstream &infile){
	char sim;
	infile>>sim;
	if(sim=='A'){
	        cout<<sim;
		if(infile>>sim ){
			if(sim==')'){
				cout<<sim;
				if(Brackets(infile)) return true;
				else {Error(3);return false;} //нет скобок	
				return true;
			}
			else {Error(4);return false;} //нет ')'
		}	
		else return true;
	}

	if(sim=='('){ 
		cout<<sim; 
		infile>>sim;//считывание следующего символа
		if(sim=='B'){
			cout<<sim;
			if(Brackets(infile));
			else return false; //нет скобок
		}
		else {Error(2);return false;} //нет "В"
	}
	else return false;//нет 'A' или '('
}

void Error(short s) {
	cout<<endl<<"Ошибка №"<<s<<endl;

	switch(s){

	case 2:
		cout<<"Не хватает 'B'"<<endl;
		break;
	case 3:
		cout<<"Нет скобок"<<endl;
		break;
	case 4:
		cout<<"Не хватает ')' или присутсвуют лишние символы после скобок"<<endl;
		break;
	}
}

