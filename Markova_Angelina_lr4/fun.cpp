#include "fun.h"

int fill_from_str(const binTree<char> * bt,const std::string str_bt, int * position, int root) { //заполнение дерева, исходя их входных данных, указатель на объект класса, входная строка, указатель на элемент строки, индекс отца
    int curr_pos=0;                                              //текущая позиция внутри массива структур
    int left_son=2*root+1;                                       //в какой индекс записываем сыновей(левый)
    int right_son=2*root+2;                                      //правый
    if (root>-1) {                                               //указатель на отца
        if (bt->storage[root].left==0)                           //сначала записываем левого сына
            curr_pos=left_son;                                   //потом правого
        else
            curr_pos=right_son;

    }

    if (curr_pos>=bt->size) return 0;                             //проверка на переполнение
    while(1) {
        if (str_bt[*position]==')') {
            (*position)++;
            if (bt->storage[curr_pos].left==0)                    //нет сыновей
                bt->storage[curr_pos].left=-1;
            if (bt->storage[curr_pos].right==0)
                bt->storage[curr_pos].right=-1;
            break;
        }
        if (str_bt[*position]=='#') {                             //пустой левый сын по умолчанию
            (*position)++;
            bt->storage[curr_pos].left=-1;
            continue;
        }
        if (str_bt[*position]=='(') {
            (*position)++;
            fill_from_str(bt,str_bt,position,curr_pos);    //новая глубина
            continue;
        }
        if (isalpha(str_bt[*position])) {
            bt->storage[curr_pos].value=str_bt[*position]; //запись значения элемента дерева
            (*position)++;
            if (root==-1) continue;                        //если нет отца, то не заполняем
            if (curr_pos==left_son)                        //если текущий элемент является левым сыном текущего отца (root)
                bt->storage[root].left=left_son;
            if (curr_pos==right_son)
                bt->storage[root].right=right_son;
            continue;
        }
        (*position)++;                                         //пропуск разделительных знаков
    }
    return 0;
}

void convert_bt_to_forest(const binTree<char> * bt, Forest<char> * bt_forest,int father,int num_son,int * posf,int pos) { //функция конвертирования дерева в лес, num_son - кол-во сыновой, указатель на позицию в лесе/в бинарном дереве
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
