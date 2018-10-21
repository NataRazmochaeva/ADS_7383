/*  использование модуля с АТД "Иерархический Список" .
Интерфейс модуля в заголовочном файле "l_intrfc.h" 
и его реализация (в отдельном файле l_impl.cpp) образуют
пространство имен namespace h_list
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "l_intrfc.h"


using namespace std;
using namespace h_list;


void UserInterface ()
{
    int key;
    lisp s1, s2;

    while (true) {
        cout << "Выбери действие:" << endl;
        cout << "0. Завершить выполнение;" << endl;
        cout << "1. Загрузить списки из пользовательского файла;" << endl;
        cout << "2. Загрузить списки из файла по умолчанию;" << endl;
        cout << "3. Ввести списки с клавиатуры;" << endl;
        cin >> key;
        switch (key) {
            case 0: 
                return;
                break;
            case 1:
			{
				string filename;
				cout << "input file name: ";
				cin.ignore(256, '\n');// игнорируем оставшиеся в cin после ввода '1' символы
				getline(cin, filename);

				ifstream infile (filename);
				
				read_lisp (&infile, s1);
				cout << "введен list1: " << endl;
				write_lisp (s1);
				cout << endl;
  	  			infile.ignore(256, '\n'); // игнорируем оставшиеся в первой строке файла символы
				read_lisp (&infile, s2);
				cout << "введен list2: " << endl;
				write_lisp (s2);
				cout << endl;

				infile.close();

				if (isEqual(s1, s2))
					cout << "list1 = list2";
				else
					cout << "list1 != list2";
				cout << endl;
            } 
            break;
            case 2:
            {
            	ifstream infile ("input");

				read_lisp (&infile, s1);
				cout << "введен list1: " << endl;
				write_lisp (s1);
				cout << endl;
  	  			infile.ignore(256, '\n'); // игнорируем оставшиеся в первой строке файла символы
				read_lisp (&infile, s2);
				cout << "введен list2: " << endl;
				write_lisp (s2);
				cout << endl;

				infile.close();

				if (isEqual(s1, s2))
					cout << "list1 = list2";
				else
					cout << "list1 != list2";
				cout << endl;
            } 
            break;
            case 3:
            {
				cout << "введите list1:" << endl;
				cin.ignore(256, '\n'); // игнорируем оставшиеся в cin после ввода '3' символы
				read_lisp (&cin, s1);
				cout << "введен list1: " << endl;
				write_lisp (s1);

				cout << endl;
  	  			cout << "введите list2:" << endl;
  	  			cin.ignore(256, '\n'); // игнорируем оставшиеся в cin после ввода '3' символы
				read_lisp (&cin, s2);
				cout << "введен list2: " << endl;
				write_lisp (s2);
				cout << endl;
	
				if (isEqual(s1, s2))
					cout << "list1 = list2";
				else
					cout << "list1 != list2";
				cout << endl;
            } 
            break;
        
            default : cout << "! - ...";
            break;    
        };
    }
}


int main ( )
{ 
	UserInterface();

	cout << "end! " << endl;
	return 0;
}
