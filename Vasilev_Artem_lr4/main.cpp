#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <sstream>
#include <bintr.h>
#include <func.h>

using namespace std;

int main()
{
    BinTree<char> *bTree1 = new BinTree<char>;
    BinTree<char> *bTree2 = new BinTree<char>;

    stringbuf str_buf;
    istream is_str(&str_buf);

    ifstream file1 ("bt1.txt");
    string bt1;
    getline (file1, bt1);
    file1.close();

    if (analyzer(bt1, bt1.length()))
    {
        cerr << endl << "Ошибка в вводе бинарного дерева № 1. Программа аварийно завершила свою работу." << endl;
        return 0;
    }

    str_buf.str(bt1);
    create_binTree(is_str, bTree1);
    is_str.clear();

    cout << "Первое бинарное дерево:" << endl << endl;

    print_binTree(bTree1);

    ifstream file2 ("bt2.txt");
    string bt2;
    getline (file2, bt2);
    file2.close();

    if (analyzer(bt2, bt2.length()))
    {
        cerr << endl << "Ошибка в вводе бинарного дерева № 2. Программа аварийно завершила свою работу." << endl;
        return 0;
    }

    str_buf.str(bt2);
    create_binTree(is_str, bTree2);
    is_str.clear();

    cout << endl << "Второе бинарное дерево:" << endl << endl;
    print_binTree(bTree2);

    cout << endl << endl;


    if (similar(bTree1, bTree2))             //подобие
        cout << "Деревья подобны." << endl;
    else
        cout << "Деревья не подобны." << endl;

    if (equal(bTree1, bTree2))                  //равенство
        cout << "Деревья равны." << endl;
    else
        cout << "Деревья не равны." << endl;

    if (speculary_similar(bTree1, bTree2))     //зеркально подобны
        cout << "Деревья зеркально подобны." << endl;
    else
        cout << "Деревья не зеркально подобны." << endl;

    if (symmetry(bTree1, bTree2))     //симметричны
        cout << "Деревья симметричны." << endl;
    else
        cout << "Деревья не симметричны." << endl;

    return 0;
}
