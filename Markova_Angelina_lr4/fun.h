#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


template <class Type>                //шаблон класса
struct binTree {                     //бинарное дерево
    binTree(int n = 0): depth(n)     //задаём глубину дерева, для инициализации объекта класса
    {
        size=(int)pow(2.0,(double)depth)-1; //количество элементов в массиве(дереве)
        storage = new bt_element[size];     //создание массива
        for (int i=0; i<size; i++) {        //инициализация полей струкуры
            storage[i].value=0; //значение корня
            storage[i].left=0;  //значение правого сына(индекс в массиве)
            storage[i].right=0; //значение левого сына(индекс в массиве)
        }
    }
    ~binTree() //деструктор
    {
        delete [] storage;              //очистка массива(освобождение памяти, выделенной командой new[])
    }
    void print_tree(int i,int depth) {  //функция печати дерева
        if (storage[i].right>0) { //если есть правый сын
            binTree::print_tree(storage[i].right,depth-1);      //печаает поддерево правого сына и умньшает значение глубины дерева
        }
        std::string tabs(depth,'-');    //с увелечением глубины увеличиваем кол-во "-", конструктор для класса строк
        if (storage[i].value) {         //если корень
            std::cout.width(this->depth+3);                     //задаёт ширину поля, this - переменная, указывающая какой тип данных хранится(объект класса), для выравнивания по правому краю
            std::cout << storage[i].value + tabs << std::endl;  //вывод корня, с учетом ширины(соединяем символ и строку)
        }
        if (storage[i].left>0) { //если есть левый сын
            binTree::print_tree(storage[i].left,depth-1);       //печатает поддерево левого сына и уменьшает значение глубины дерева
        }

    }
    struct bt_element { //структура элемента массива
        Type value; //корень, используем любой тип
        int left;   //индекс левого сына
        int right;  //индекс правого сына
    };
    int size;              //размер массива структур
    bt_element * storage;  //объявление массива структур
    int depth;             //глубина дерева
};

template <class Type> //шаблон класса
struct Forest {
    Forest(int n = 0,int num_sons = 3,int fdepth=0): size(n),max_sons(num_sons+1),depth(fdepth) //инициализация объекта класса, по умолчанию будут 0... или пользовательские значения
    {
        storage = new bt_element[size];               //создание массива сруктур
        for (int i=0; i<size; i++) {                  //заполнение значений
            storage[i].value=0;                       //инициаизация корня
            storage[i].sons = new int[max_sons];      //массив указателей(индексов) на сыновей
            for (int j=0; j<max_sons; j++)            //инициализация сыновей
                storage[i].sons[j]=-1;                //нет сына
        }
    }
    ~Forest() //деструктор
    {
        for (int i=0; i<size; i++)
            delete [] storage[i].sons;         //очистка памяти, выделенной под сыновей
        delete [] storage;                     //очистка структур леса
    }
    void print_forest(int i,int depth) {
        int j=0; //функция печати леса
        while (storage[i].sons[j]>-1) {                            //пока есть сыновья
            Forest::print_forest(storage[i].sons[j],depth-1);      //выводим сына
            j++;                                                   //перемещаемся по массиву сыновей
        }
        std::string tabs(depth+1,'-');         //с увеличением глубины увеличиваем "-"                              //кол-во сыновей(кол-во напечатанных)
        if (storage[i].value) {                //если корень
            std::cout.width(this->depth+3);                        //задаем ширину поля
            std::cout << storage[i].value + tabs << std::endl;     //выводим значение элемента дерева
        }

    }
    void print_horizontal(std::string * out,int i, int level) {    //функция обхода леса в ширину, указатель на массив строк(каждый уровень отдельно)
        int j=0;                                                   //кол-во сыновей
        while (storage[i].sons[j]>-1) {                            //пока есть элементы леса
            out[level]+=storage[storage[i].sons[j]].value;         //выводим значения
            j++;
        }
        j=0;
        while (storage[i].sons[j]>-1) {                                    //пока есть деревья в лесу
            Forest::print_horizontal(out,storage[i].sons[j],level+1);      //выводим
            j++;
        }

    }
    struct bt_element {    //структура элемента массива
        Type value;        //значение корня
        int * sons;        //указатель на массив сыновей
    };
    int size;              //размер массива указателей
    int max_sons;          //максимальное число сыновей(деревьев леса)
    bt_element * storage;  //массив структур
    int depth;             //глубина
};

int fill_from_str(const binTree<char> * bt,const std::string str_bt, int * position, int root); //заполнение дерева, исходя их входных данных, указатель на объект класса, входная строка, указатель на элемент строки, индекс отца
void convert_bt_to_forest(const binTree<char> * bt, Forest<char> * bt_forest,int father,int num_son,int * posf,int pos);  //функция конвертирования дерева в лес, num_son - кол-во сыновой, указатель на позицию в лесе/в бинарном дереве
