#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cctype>
using namespace std;

struct atom;

struct pairs{
    atom* left;
    atom* right;
};

struct atom{
    bool isleft;
    int action;     // 1-OR, 2-AND, 3-XOR, 4-NOT
    bool flag;
    union{
        int a;
        pairs* next;
    }un;
};

void pr_menu(){
	cout << "Выберите действие:" << endl;
    cout << "1 - ввод с клавиатуры" << endl;
    cout << "2 - ввод из файла" << endl;
    cout << "0 - выход" << endl;
}
    
int find_arg(string str1){
    if(str1[0] == 'O')
        return 1;
    if(str1[0] == 'A')
        return 2;
    if(str1[0] == 'X')
        return 3;
    if(str1[0] == 'N')
        return 4;
    return 0;
}

int full_elem(pairs* knot, string str1, string str2){ // OR, AND, XOR, NOT
    int FFF = 0;
    int F_LOC = 0;
    knot->left = new atom;
    knot->left->isleft = true;
    knot->left->action = find_arg(str1);
    string tmp;
    switch(knot->left->action){
        case 1:
            F_LOC = 3;
            tmp = str1.substr(3);
            str1 = tmp;
            break;
        default:
            F_LOC = 4;
            tmp = str1.substr(4);
            str1 = tmp;
    }
    if((str1[0] > 64) && (str1[0] < 91)){
        knot->left->flag = true;
        knot->left->un.next = new pairs;
        FFF += full_elem(knot->left->un.next, str1, str2);
        if(knot->left->action != 4){
            tmp = str1.substr(FFF);
            str1 = tmp;
        }
    } else {
        for(int i = 0; i < str2.length(); i++)
            if(str1[0] == str2[i])
                knot->left->un.a = str2[i+2] - 48;
        if(knot->left->action != 4){
            tmp = str1.substr(2);
            str1 = tmp;
        }
        FFF += 2;
    }
    if(knot->left->action != 4){
        if((str1[0] > 64) && (str1[0] < 91)){
            knot->right = new atom;
            knot->right->isleft = false;
            knot->right->flag = true;
            knot->right->un.next = new pairs;
            FFF += full_elem(knot->right->un.next, str1, str2);
        } else {
            knot->right = new atom;
            for(int i = 0; i < str2.length(); i++)
                if(str1[0] == str2[i]){
                    knot->right->un.a = str2[i+2] - 48;
                    knot->right->flag = false;
                }
            FFF += 2;
        }
    } else {
        knot->right = NULL;
    }
    FFF += F_LOC;
    return FFF;
}

int find_ans(pairs* knot){
    if(knot->left->flag){
        int tmp1 = find_ans(knot->left->un.next);
        delete(knot->left->un.next);
        knot->left->un.next = NULL;
        knot->left->un.a = tmp1;
        knot->left->flag = false;
    }
    if(knot->left->action != 4)
        if(knot->right->flag){
            int tmp2 = find_ans(knot->right->un.next);
            delete(knot->right->un.next);
            knot->right->un.next = NULL;
            knot->right->un.a = tmp2;
            knot->right->flag = false;
        }
    switch(knot->left->action){
        case 1:
            return (knot->left->un.a | knot->right->un.a);
            break;
        case 2:
            return (knot->left->un.a & knot->right->un.a);
            break;
        case 3:
            return (knot->left->un.a ^ knot->right->un.a);
            break;
        case 4:
            return (!knot->left->un.a);
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
    pairs* knot = new pairs;
    full_elem(knot, str1, str2);
    cout << find_ans(knot) << endl;
    delete(knot);
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
    pairs* knot = new pairs;
    full_elem(knot, str1, str2);
    cout << find_ans(knot) << endl;
    delete(knot);
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