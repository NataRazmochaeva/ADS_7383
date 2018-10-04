#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void pr_menu(){
	cout << endl << "Выберите действие:" << endl;
    cout << "1 - ввод с клавиатуры" << endl;
    cout << "2 - ввод из файла" << endl;
    cout << "0 - выход" << endl;
}

int sort_v(int *arr, int n){
    if (n == 1){
        return 0;
    }
    if (n == 2)
        if ((*arr - *(arr+1)) > 0){
            int i = *arr;
            *arr = *(arr+1);
            *(arr+1) = i;
            return 0;
        } else
        return 0;
    int n1 = n/2;
    if(2*n1 == n){
        sort_v(arr, n1);
        sort_v(arr+n1, n1);
    }
    else{
        sort_v(arr, n-n1);
        sort_v(arr+n1+1, n1);
    }
}

void work_with_console(){
    int n;
    int *arr = new int[n];
    cout << "введите количество элементов массива" << endl;
    cin >> n;
    if (n<=0){
        cout << "неверное количество" << endl;
        return;
    }
    cout << "введите массив" << endl;
    for(int i = 0; i < n; i++)
        cin >> *(arr+i);
    sort_v(arr, n);
    for(int i = 0; i < n; i++)
        cout << *(arr+i) << " ";
}

void work_with_file(){
    string file_name;
    int *arr_f = new int[200];
    int tmp = 0;
    cout << "Введите имя файла" << endl;
    cin >> file_name;
    ifstream f;
    f.open(file_name.c_str());
    if (!f){
        cout << "Файл не открыт!" << endl;
        return;
    }
    for(f >> *(arr_f+tmp); !f.eof(); ++tmp, f >> *(arr_f+tmp));
    
    sort_v(arr_f, tmp+1);
    for(int i = 0; i < tmp+1; i++)
        cout << *(arr_f+i) << " ";
    delete(arr_f);
    f.close();
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
