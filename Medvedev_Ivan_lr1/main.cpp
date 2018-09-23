#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std ;
bool bracket (ifstream &infile, char ch);
void Error (short k);



int main ( ){
	cout<<"ВАС ПРИВЕТСТВУЕТ АНАЛИЗАТОР СКОБОК! ДЛЯ ТОГО ЧТОБЫ СЧИТАТЬ СКОБКИ С ФАЙЛА test.txt НАЖМИТЕ 1, ДЛЯ ВВОДА С КЛАВИАТУРЫ И ЗАПИСИ В ФАЙЛ test1.txt НАЖМИТЕ 2, ДЛЯ ВЫХОДА НАЖМИТЕ 0"<<endl;
	bool exit = true, check;
	char ch;
	char arr[100];
	int forSwitch;
	FILE* fp;
	while (exit){
		cin>>forSwitch;
		switch (forSwitch){
			case 1:{
				ifstream infile ("test.txt");
				if (infile >> ch){ 
					cout << ch;
					if ((ch == 'A') || (ch == '('))
						check = bracket (infile, ch);
				
					else{
						Error(0);
						break;
					}
				}
				else{
					Error(6);
					break;
				}
				cout << endl;
				if (check)
					cout<<"ЭТО СКОБКИ"<<endl;
				break;
			}
			case 2:{
				fp = fopen("test1.txt", "w");
				if (!fp)
					return 0;
				cin>>arr;
				fputs(arr,fp);
				fclose(fp);
				ifstream infile ("test1.txt");
				if (infile >> ch){ 
					cout << ch;
					if ((ch == 'A') || (ch == '('))
						check = bracket (infile, ch);
					else{
						Error(0);
						break;
					}
				}
				else{
					Error(6);
					break;
				}
				cout << endl;
				if (check)
					cout<<"ЭТО СКОБКИ"<<endl;
				break;
			}
			case 0:{
				exit = false;
				break;
			}
			default: {
				cout<<"НЕВЕРНЫЙ ВВОД"<<endl;
				break;
			}
		}
	}
	return 0;
}
bool bracket (ifstream &infile, char ch){ 
	static string tab;
	bool forCheck;
	if (ch == 'A') 
		return true;
	else if ( ch == '(' ){
		if (infile >> ch){
			cout << tab << ch <<endl;
			if (ch == 'B'){
				tab.push_back('\t');
				if (infile >> ch){ 
					cout << tab << ch << endl;
					forCheck = bracket (infile,ch);
				}
				else{
					Error(3);
					return false;
				} 
				if (forCheck){ 
					if (infile >> ch){
						cout << tab << ch <<endl;
						forCheck = bracket (infile,ch);
					}
				}
				else{
					return false; //nepravilnie skobki
				}
				tab.pop_back();
				if (forCheck) {
					if (infile >> ch){ 
						cout << tab << ch << endl;
						if (ch != ')'){
							Error(5);
							return false;
						}
						return (ch == ')');
					}
					else{
						Error(5);
						return false;
						
					}
				}
				else{
					Error (4);
					return false; //net zakrivayuschey skobki
				}
			}
			else{
				Error(2);
				return false;
			}
		}
		else{ 
			Error(1);
			return false; 
		}
	}
	else{ 
		Error(0);
		return false; //ne a i ne skobka
	}
}


void Error (short k){
cout << endl << "err#" << k << endl;
	switch (k) {
	case 0: cout << "! - НЕВЕРНЫЙ СИМВОЛ" << endl; break;

	case 1: cout << "! - ОТКРЫТАЯ СКОБКА" << endl; break;

	case 2: cout << "! - ОТСУТСТВУЕТ СИМВОЛ В" << endl; break;

	case 3: cout << "! - НЕТ СКОБОК ПОСЛЕ В" << endl; break;

	case 4: cout << "! - НЕВЕРНЫЕ СКОБКИ" << endl; break;
	
	case 5: cout << "! - НЕТ ЗАКРЫВАЮЩЕЙ СКОБКИ" << endl; break;
		
	case 6: cout << "! - ПУСТОЙ ФАЙЛ" << endl; break;

	default : cout << "! - ...";break;

	};
}
