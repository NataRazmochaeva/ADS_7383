#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#define V_MAX 50

struct Trunk {
    Trunk *prev;
    std::string str;
    Trunk(Trunk *prev, std::string str) {
        this->prev = prev;
        this->str = str;
    }
};


template <typename Type>
class btElem{
public:
    void read_elem();
public:
    Type value; //корень, используем любой тип
    int left;   //индекс левого сына
    int right;  //индекс правого сына
};

template <class Type>                //шаблон класса
struct binTree {                     //бинарное дерево
    binTree(int n = 0): size(n)     //количество элементов в массиве(дереве)
    { 
        storage = new btElem<Type>[size];     //создание массива
        for (int i = 0; i < size; i++) {        //инициализация полей струкуры
            storage[i].left = -1;  //значение правого сына(индекс в массиве)
            storage[i].right = -1; //значение левого сына(индекс в массиве)
        }
    }
    ~binTree() //деструктор
    {
        delete [] storage;              //очистка массива(освобождение памяти, выделенной командой new[])
    }
    int fill_from_input(int&);
    void printTree(int index,Trunk *prev, bool isLeft);
    int depth(int root);
    int size;              //размер массива структур
    btElem<Type> * storage;  //объявление массива структур
};

template <class Type> //шаблон класса
struct Forest {
    Forest(int n = 0, int num_sons = 3, int fdepth = 0): size(n), max_sons(num_sons + 1), depth(fdepth) //инициализация объекта класса, по умолчанию будут 0... или пользовательские значения
    {
        storage = new bt_element[size];               //создание массива сруктур
        for (int i=0; i < size; i++) {                  //заполнение значений
            storage[i].value=0;                       //инициаизация корня
            storage[i].sons = new int[max_sons];      //массив указателей(индексов) на сыновей
            for (int j=0; j < max_sons; j++)            //инициализация сыновей
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
            print_forest(storage[i].sons[j],depth-1);      //выводим сына
            j++;                                                   //перемещаемся по массиву сыновей
        }
        std::string tabs(depth+1,'-');         //с увеличением глубины увеличиваем "-"                              //кол-во сыновей(кол-во напечатанных)
        if (storage[i].value) {                //если корень
            std::cout.width(this->depth+3);                        //задаем ширину поля
            std::cout << storage[i].value << tabs << std::endl;     //выводим значение элемента дерева
        }

    }

    void print_horizontal(std::string * out, int i, int level) {    //функция обхода леса в ширину, указатель на массив строк(каждый уровень отдельно)
        int j = 0;                                                   //кол-во сыновей
        while (storage[i].sons[j] > -1) {                            //пока есть элементы леса
            out[level]+=storage[storage[i].sons[j]].value;         //выводим значения
            j++;
        }
        j = 0;
        while (storage[i].sons[j] > -1) {                                    //пока есть деревья в лесу
            Forest::print_horizontal(out, storage[i].sons[j], level+1);      //выводим
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

template <typename T>
void btElem<T>::read_elem(){
    char c;
    for(c = getchar(); c == ' ' && c != '\n' && c != EOF; c = getchar());
    if(c == '\n' || c == EOF){
        std::cout << "Incorrect input!" << std::endl;
        exit(1);
    }
    else
        ungetc(c, stdin);
    std::cin >> value;
    if(std::cin.fail()){
        std::cout << "Input error!" << std::endl;
        exit(1);
    }
    return;
}

template <typename T>
int binTree<T>::fill_from_input(int& root) { //заполнение дерева, исходя их входных данных, указатель на объект класса, входная строка, указатель на элемент строки, индекс отца
    int curr_pos = 0;                                              //текущая позиция внутри массива структур
    int left_son = 2*root + 1;                                       //в какой индекс записываем сыновей(левый)
    int right_son = 2*root + 2;                                      //правый
    if (root > -1) {                                               //указатель на отца
        if (storage[root].left == -1)                           //сначала записываем левого сына
            curr_pos = left_son;                                   //потом правого
        else
            curr_pos = right_son;

    }
    char c;

    if (curr_pos >= size) return 0;                             //проверка на переполнение
    while(1) {
        for(c = getchar(); c == ' ' && c != '\n' && c != EOF; c = getchar());
        if (c == ')') {
            if (storage[curr_pos].left == 0)                    //нет сыновей
                storage[curr_pos].left = -1;
            if (storage[curr_pos].right == 0)
                storage[curr_pos].right = -1;
            break;
        }
        if (c == '#') {                             //пустой левый сын по умолчанию
            storage[curr_pos].left = -1;
            continue;
        }
        if (c == '(') {
            fill_from_input(curr_pos);    //новая глубина
            continue;
        }
        ungetc(c, stdin);
        storage[curr_pos].read_elem();
        if (root == -1) continue;                        //если нет отца, то не заполняем
        if (curr_pos == left_son)                        //если текущий элемент является левым сыном текущего отца (root)
            storage[root].left = left_son;
        if (curr_pos == right_son)
            storage[root].right = right_son;                              //пропуск разделительных знаков
    }
    return 0;
}

void showTrunks(Trunk *p) {
    if (p == nullptr)
        return;
    showTrunks(p->prev);
    std::cout << p->str;
}

template <class Type>
void binTree<Type>::printTree(int index, Trunk *prev, bool isLeft){
    if (index == -1)
        return;

    std::string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);
    printTree(storage[index].right ,trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isLeft){
        trunk->str = ".---";
        prev_str = "  |";
    }
    else{
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    std::cout << storage[index].value << std::endl;
    if (prev)
        prev->str = prev_str;

    trunk->str = "  |";
    printTree(storage[index].left, trunk, false);
}

int max(int a, int b){
    if (a > b)
        return a;
    else
        return b;
}

template <class Type>
int binTree<Type>::depth(int root){
    if(root == -1)
        return 0;
    return max(depth(storage[root].right), depth(storage[root].left)) + 1;
}

template <class Type>
void convert_bt_to_forest(const binTree<Type> * bt, Forest<Type> * bt_forest,int father,int num_son,int * posf,int pos) { //функция конвертирования дерева в лес, num_son - кол-во сыновой, указатель на позицию в лесе/в бинарном дереве
    bt_forest->storage[*posf].value=bt->storage[pos].value;                             //заполняем значение элемента леса корнем дерева(по индексу pos)
    bt_forest->storage[father].sons[num_son]=*posf;                                     //записываем индекс сына для отца
    if (bt->storage[pos].left>-1) {                                                     //сначала идем по всем левым сыновьям вглубь
        (*posf)++;                                                                      //
        convert_bt_to_forest(bt,bt_forest,(*posf)-1,0,posf,bt->storage[pos].left);      //индекс сыновей = 0, тк они всегда первые идут при обходе, ...left - переход к левому сыну
    }
    if (bt->storage[pos].right>-1) {                                                    //проверка на правого сына, в обратном ходе рекурсии
        (*posf)++;
        convert_bt_to_forest(bt,bt_forest,father,num_son+1,posf,bt->storage[pos].right);//father у братьев один, num_son двигаемся по сыновьям
    }
    return;
}
