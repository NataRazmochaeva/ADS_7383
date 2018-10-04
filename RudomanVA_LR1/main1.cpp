#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std ;

bool bracket (ifstream &infile, char ch);
void Error (short k);
bool forFile (ifstream &infile, bool check, char ch);


int main ( ){
	
	cout << "АНАЛИЗАТОР СКОБОК" << endl;
	cout << "ДЛЯ АНАЛИЗА СКОБОК ИЗ test.txt НАЖМИТЕ '1'" << endl;
	cout << "ДЛЯ ПЕРЕЗАПИСИ И АНАЛИЗА СКОБОК ИЗ test.txt НАЖМИТЕ '2'" << endl; 
	cout << "ДЛЯ ПРЕРЫВАНИЯ ПРОГРАММЫ НАЖМИТЕ '0'" << endl;
	
	bool exit = true, check;
	char ch;
	char arr[100];
	int forSwitch;
	
	FILE* fp;
	cin >> forSwitch;
	
	switch (forSwitch){
		case 1:{
			ifstream infile ("test.txt");
			forFile(infile, check, ch);
			break;
		}
		case 2:{
			fp = fopen("test.txt", "w");
			if (!fp)
				return 0;
			cin >> arr;
			fputs(arr,fp);
			fclose(fp);
			ifstream infile ("test.txt");
			forFile(infile, check, ch);
			break;
		}
		case 0:{
			cout << "ВСЕГО ДОБРОГО" << endl;
			return 0;
		}
		default: {
			cout<<"НЕВЕРНЫЙ ВВОД"<<endl;
			break;
		}
	}
	return 0;
}


bool bracket (ifstream &infile, char ch) {
	static string tab;
	bool forCheck;
	if(ch == 'A' || ch == 'B')
		return true;
		
		if(ch == '(') {
			tab.push_back('\t');
			if(infile >> ch) {
				cout << tab << ch << endl;
				forCheck = bracket(infile, ch);
			}
			else {
				Error(2);
				return false;
			}	
			if (forCheck) {
				if (infile >> ch)
					cout << tab << ch << endl;
				forCheck = bracket(infile, ch);
			}
			else {
				Error(2);
				return false;
			}

			if (!forCheck) {
				Error(3);
				return false;
			}	
			
			tab.pop_back();
			if(forCheck) {
				if(infile >> ch) {
					cout << tab << ch << endl;
					if (ch != ')'){
						Error(1);
						return false;
					}
					return (ch == ')');	
				}
				else {
					Error(2);
					return false;
				}
			}
		}

	else {
		Error(6);
		return false;
	}

 	return true;
}

bool forFile (ifstream &infile, bool check, char ch) {
			if (infile >> ch){ 
				cout << ch << endl;
				if ((ch == 'A') || (ch == '(') || (ch == 'B'))
					check = bracket (infile, ch);
			
				else{
					Error(3);
					return 0;
				}
			}
			else{
				Error(4);
			
			}
			if (infile >> ch) {
				cout << ch;
				if (ch != EOF) {
					Error(5);
					return 0;
				}	 
			}
			cout << endl;
			if (check)
				cout<<"ЭТО СКОБКИ"<<endl;
			return true;
}


void Error (short k){

	cout << endl << "   Error № " << k << endl;
	
	switch (k) {

	case 1: cout << "::ОЖИДАЛСЯ: ) ::" << endl; break;

	case 2: cout << "::ОЖИДАЛИСЬ: А, В, ( ::" << endl; break;

	case 3: cout << "::НЕВЕРНЫЙ СИМВОЛ::" << endl; break;

	case 4: cout << "::ПУСТОЙ ФАЙЛ::" << endl; break;
	
	case 5: cout << "::ЛИШНИЙ СИМВОЛ::" << endl; break;

	case 6 : cout << "ERROR..." << endl; break;

	};
}