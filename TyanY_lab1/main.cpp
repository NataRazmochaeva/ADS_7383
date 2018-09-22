#include <iostream>
#include <cctype>
#include <cstdlib>

using namespace std;

int *vector_modify(int* vector,int start,int end){
    int j=0;
    for(int i=start;i<end;i++, j++){
        vector[j]=vector[i];
    }
    return vector;
}

void divide_vector(int* vector,int size,int *myVector,int* pointer,int k){
    k++;
    for(int j=0; j<k;j++){
        cout << '\t';
    }
    for(int i=0;i<size;i++)
        std::cout << vector[i] << " ";
    cout << '\n';
    if(size <= 2){
        for(int i=0;i<size;i++){
                myVector[*(pointer)]=vector[i];
                (*(pointer))++;
        }
    }
    else{
        if((size % 2) == 0){
            divide_vector(vector_modify(vector,0,(size/2)),size/2,myVector,pointer,k);
            divide_vector(vector_modify(vector,(size/2),size),size/2,myVector,pointer,k);
        }else{
            divide_vector(vector_modify(vector,0,(size+1)/2),(size+1)/2,myVector,pointer,k);
            divide_vector(vector_modify(vector,((size+1)/2)-1,size),(size+1)/2,myVector,pointer,k);
        }
    }
}

int main(){
    int num=0;
    while(num != 3){
        cout << "Выберите дальнейшие дествия и введите цифру:\n";
        cout << "1. Ввести координаты вектора вручную.\n";
        cout << "2. Сгенерировать координаты вектора.\n";
        cout << "3. Завершить работу.\n";
        cin >> num;
        switch(num){
            case 1:{
                string c;
                int j=0, k=-1,space=0;
                getchar();
                getline(cin, c);
                for(char i : c){
                    if(isspace(i))
                        space++;
                }
                space++;
                int * vector = new int[space];
                for(char i : c){
                    if(isdigit(i) != 0){
                        vector[j]=int(i)-'0';
                        j++;
                    }
                }
                if(j < 1){
                    cout << "Проверьте введенные данные и повторите попытку." << endl;
                }else{
                int *myVector = new int[space*2];
                int pointer=0;
                divide_vector(vector,j,myVector,&pointer,0);
                cout << "Результат:";
                for(int i=0;i<pointer;i++)
                    std::cout << myVector[i] << " ";
                cout << endl;
                delete [] vector;
                delete [] myVector;
                }
                break;
            }
            case 2:{
                int size = 0, from = 0, to = 0;
                cout << "Введите промежуток через пробел, в котором будет сгенерирована длина вектора и его значения: ";
                cin >> from;
                cin >> to;
                if(from > to)
                    cout << "Проверьте введенные данные и повторите попытку." << endl;
                else{
                    size = from + rand() % to;
                    int* vector = new int[size];
                    cout << "Размер вектора: " << size << endl;
                    for(int i=0;i<size; i++)
                        vector[i] = from + rand() % to;
                    cout << "Был сгенерирован вектор:\n";
                    for(int i=0;i<size; i++)
                        cout << vector[i] << ' ';
                    cout << '\n';
                    int *myVector = new int[size*2];
                    int pointer=0;
                    divide_vector(vector,size,myVector,&pointer,0);
                    cout << "Результат:";
                    for(int i=0;i<pointer;i++)
                        std::cout << myVector[i] << " ";
                    cout << endl;
                    delete [] vector;
                    delete [] myVector;
                }
                break;

            }
            case 3:
                return 0;
            default:
                cout << "Проверьте введенные данные и повторите попытку." << endl;
                break;
        }
        
    }
    return 0;
}
