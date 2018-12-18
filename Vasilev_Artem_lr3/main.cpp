#include <iostream>
#include <fstream>
#include <string>

#include "Queue.cpp"

using namespace std;

int index_of_name(string, string *, int);							//Функция нахождения индекса имени
void find_child(int, int, int **, Queue*, int);							//Функция нахождения детей и записи в очередь
void print_queue(int, Queue*, string *, ofstream &);							//Функция печати поколений из очереди

int main()
{

    ofstream fout;										//Открываем файл на запись результата
    fout.open("Result.txt");

    ifstream file ("Names.txt");								//В первый раз открываем файл с именами
    string tmp;										//для нахождения количества имен persons
    int persons;
    for(persons = 0;; persons++)
    {
        file >> tmp;
        if(file.eof()) break;
    }
    file.close();										//end.

    ifstream file1 ("Names.txt");								//Во второй раз открываем тот же файл
    string *names = new string[persons];							//для записи имен в массив строк names.
    cout << "Индекс - имя:" << endl;
    for(int i = 0; i < persons; i++)
    {
        file1 >> names[i];
        cout << i << ' ' << names[i] << endl;
    }
    file1.close();										//end.

    ifstream file2 ("Connections.txt");								//Открываем файл с матрицей родства
    int **concts = new int *[persons];							//и записываем ее в двумерный массив concts.
    for(int i = 0 ; i < persons; i++)
        concts[i] = new int[persons];


    for(int i = 0; i < persons; i++)
    {
        for(int j = 0; j < persons; j++)
        {
            file2 >> concts[i][j];

            if(file2.eof() && j != persons)             //Обработка ошибки нехватки данных из открытого файла
            {
                cout << endl << "Ошибка: недостаточно данных для таблицы родства" << endl;
                exit(1);
            }
        }
    }

    int kk=-1;
    file2 >> kk;
    if (kk!=-1)
    {
        cout << endl << "Ошибка: в файле с таблицей родства присутствуют лишние символы" << endl;
        exit(1);
    }


    cout << endl << "Таблица смежности:" << endl << "\x1b[4m"<< " |";
    for(int i = 0; i < persons; i++)
        cout << " " << i;
    cout << "\x1b[m" << endl;
    for(int i = 0; i < persons; i++)
    {
        cout << i << "| " ;
        for(int j = 0; j < persons; j++)
        {
            file2 >> concts[i][j];
            cout << concts[i][j] << ' ';
        }
        cout << endl;
    }
    file2.close();										//end.
    cout << endl;

    string name;

    cout << "Введите имя: ";								//Запрос имени name для предоставления потомков.
    cin >> name;


    Queue *queue = new Queue;

    find_child(0, index_of_name(name, names, persons), concts, queue, persons);		//Найдем и запишем рекурсивно детей для имени

    print_queue(0, queue, names, fout);								//Выведем список потомков.
    fout.close();
    for(int i = 0; i < persons; i++)							//Освобождение памяти под concts.
        free(concts[i]);
    free(concts);
    return 0;
}

int index_of_name(string name, string *names, int persons)       //Функция определяющая индекс имени.
{
    for(int i = 0; i < persons; i++)
        if(name == names[i])	return i;
    cout << "Ошибка: Имени нет в списке" << endl;						//Вывод ошибки в случае неправильного имени.
    exit(1);
}

void find_child(int remove,int i_name, int **concts, Queue *queue, int persons)         //Функция нахождения детей по индексу имени.
{
    queue->push(i_name, remove);								//Пуш в очередь индекса найденного имени
    for(int i = 0; i < persons; i++)                            //с учетом колена потомка.
    {
        if(concts[i][i_name])                                   //Для найденного имени
        {
            if(concts[i_name][i])
            {
                cout << "Ошибка: ребенок не может быть отцом его родителя" << endl;
                exit(1);
            }
            if(queue->is_in_queue(i, remove))
            {
                cout << "Ошибка: замкнутая цепь родства" << endl;
                exit(1);
            }
            find_child(remove + 1, i, concts, queue, persons);			//поиск детей для детей name.
        }
    }
}

void print_queue(int remove, Queue *queue, string *names, ofstream &fout)       //Функция печати очереди.
{
    if(remove)	fout << "Потомки "<< remove << "-го поколения: ";
    else		fout << "Потомки для ";
    for(int i = 0; i < queue->count_remove(remove); i++)					//По количеству потомков текущего колена remove
        fout << names[queue->pop()] << ' ';						//вывод имени по индексу полученному из очереди.
    fout << endl;
    if(queue->isEmpty())									//Если очередь не пуста
        print_queue(remove+1, queue, names, fout);						//идем печатать следующее колено.
}
