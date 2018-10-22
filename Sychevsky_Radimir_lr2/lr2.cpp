#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

struct elem{
    int action;      // 1-OR, 2-AND, 3-XOR, 4-NOT
    union{
        int a;
        elem* next;
    }un1;
    union{
        int b;
        elem* next;
    }un2;
};
typedef elem *kek;

void pr_menu(){
	cout << "Выберите действие:" << endl;
    cout << "1 - ввод с клавиатуры" << endl;
    cout << "2 - ввод из файла" << endl;
    cout << "0 - выход" << endl;
}

int find_arg(string str1){
    if(str1[1] == 'O')
        return 1;
    if(str1[1] == 'A')
        return 2;
    if(str1[1] == 'X')
        return 3;
    if(str1[1] == 'N')
        return 4;
    return 0;
}

int full_elem(elem* expression, string str1, string str2){ // OR, AND, XOR, NOT
    expression->action = find_arg(str1);
    switch(expression->action){                            //>
        case 1:                                            // >
            for(int i = 4; i < str1.length()-1; i++)       //  >
                str1[i-4] = str1[i];                       //   >
            str1[str1.length()-1] = ' ';                   //    >
            break;                                         //     > стирание операции
        default:                                           //    >
            for(int i = 5; i < str1.length()-1; i++)       //   >
                str1[i-5] = str1[i];                       //  >
            str1[str1.length()-1] = ' ';                   // >
    }                                                      //>
    if(str1[0] == '('){                                   
        expression->un1.next = new elem;                   
        full_elem(expression->un1.next, str1, str2);       
        int k = 1;                                        
        int count = 1;                                     
        while(count){                                      
            if(str1[k] == '(')                            
                count++;                                  
            if(str1[k] == ')')                            
                count--;                                  
            k++;                                          
        }                                                 
        for(int i = (k+1); i < str1.length();i++)         
            str1[i-k-1] = str1[i];                         
    } else {        
        for(int i = 0; i < str2.length()-1; i++)           //ввод первой переменной
            if(str1[0] == str2[i])
                expression->un1.a = str2[i+2] - 48;
        for(int i = 2; i < str1.length()-1; i++)
            str1[i-2] = str1[i];
    }
    if(expression->action != 4){
        if(str1[0] == '('){
            expression->un2.next = new elem;
            full_elem(expression->un2.next, str1, str2);
        } else {                                           //вторая переменная
            for(int i = 0; i < str2.length()-1; i++)       //ввод второй переменной
                if(str1[0] == str2[i])
                    expression->un2.b = str2[i+2] - 48;
        }
    } else {
        expression->un2.next = NULL;
    }
    return 0;
}

int find_ans(elem* expression){
    if((expression->un1.a != 1) && (expression->un1.a != 0)){
        int tmp1 = find_ans(expression->un1.next);
        delete(expression->un1.next);
        expression->un1.next = NULL;
        expression->un1.a = tmp1;
    }
    if(expression->action != 4)
        if((expression->un2.b != 1) && (expression->un2.b != 0)){
            int tmp2 = find_ans(expression->un2.next);
            delete(expression->un2.next);
            expression->un2.next = NULL;
            expression->un2.b = tmp2;
        }
    switch(expression->action){
        case 1:
            return (expression->un1.a | expression->un2.b);
            break;
        case 2:
            return (expression->un1.a & expression->un2.b);
            break;
        case 3:
            return (expression->un1.a ^ expression->un2.b);
            break;
        case 4:
            return (!expression->un1.a);
            break;
    }
}

int work_with_console(){
    cout << "Введите выражение" << endl;
    string str1;
    getline(cin, str1);
    getline(cin, str1);
    cout << "Введите значеия переменных" << endl;
    string str2;
    getline(cin, str2);
    elem* expression = new elem;
    full_elem(expression, str1, str2);
    cout << find_ans(expression) << endl;
    delete(expression);
    return 0;
}

int work_with_file(){
    cout << "Введите имя файла, в котором записано выражение и значения переменных" << endl;
    string file_name;
    cin >> file_name;
    ifstream f;
    f.open(file_name.c_str());
    if (!f){
        cout << "Файл не открыт!" << endl;
        return 0;
    }
    string str1;
    string str2;
    getline(f, str1);
    getline(f, str2);
    cout << str1 << endl << str2 << endl;
    elem* expression = new elem;
    full_elem(expression, str1, str2);
    cout << find_ans(expression) << endl;
    delete(expression);
    return 0;
}

int main(){
    pr_menu();
    int way = 0;
    cin >> way;
    while(way){
        switch (way){
            case 1:
                work_with_console();
                cout << endl;
                pr_menu();
                cin >> way;
                break;
            case 2:
				work_with_file();
                cout << endl;
                pr_menu();
                cin >> way;
                break;
            default:
                cout << "Неверно введены данные!" << endl;
                pr_menu();
                cin >> way;
        }
    }
    return 0;
}