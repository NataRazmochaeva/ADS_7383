#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

class Queue{
    private:    
    int first;
    int last;
    int *arr;
    int max;
    void resize(){
        max += 5;
        int *tmp = new int[max];
        for(int i = first; i <=last; i++)
            tmp[i] = arr[i];
        delete [] arr;
        arr = tmp;
    }
    public:
    Queue(){
        max = 10;
        arr = new int[max];
        first = 0;
        last = -1;
    }
    void add_elem(int a){
        if(last == max-1)
            resize();
        last++;
        arr[last] = a;
    }
    int rem_elem(){
        if(count()){
            first++;
            return arr[first-1];
        } else
            cout << "массив пуст!" << endl;
    return 0;
    }
    int count(){
        return last-first+1;
    }
    ~Queue(){
        delete [] arr;
    }
};

int main(){
    string tmp;
    string file_name;
    cout << "Введите имя файла" << endl;
    cin >> file_name;
    ifstream f1;
    f1.open(file_name.c_str());
    if (!f1){
        cout << "Файл не открыт!" << endl;
        return 0;
    }
    ofstream f2;
    f2.open("output.txt");
    getline(f1, tmp);
    while(!f1.eof()){
        Queue arr1;
        for(int i = 0; i < tmp.length(); i++){
            if((tmp[i] > 47) && (tmp[i] < 58)){
                arr1.add_elem(tmp[i]);
                for(int j = i; j < tmp.length()-1-arr1.count(); j++)
                    tmp[j] = tmp[j+1];
                    if(i == tmp.length()-1-arr1.count())
                        break;
                    i--;
            }
        }
        while(arr1.count()){
            tmp[tmp.length()-1-arr1.count()] = arr1.rem_elem();
        }
        f2 << tmp << endl;
        getline(f1, tmp);
    }
    f1.close();
    f2.close();
    return 0;
}