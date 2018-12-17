#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <sstream>
#include <bintr.h>

using namespace std;

bool is_open_bracket (char ch)
{ return ch=='(';}

bool is_close_bracket (char ch)
{ return ch==')';}

bool is_value (char ch)
{ return ch!='(' && ch!=')' && ch!='#';}

bool is_latt (char ch)
{ return ch=='#';}

template<typename BASE>
bool create_binTree(istream& is_str, BinTree<BASE> *bTree, unsigned i=0, bool flag = false)
{
    char ch;

    if (is_str>>ch)
    {
        if (i==0)
            flag = create_binTree(is_str, bTree, ++i, true);
        else if (is_value(ch))
        {
           bTree->set_vl(ch);
        }
        else if (is_open_bracket(ch) && flag == true)
        {
           bTree->set_left();
           flag = create_binTree(is_str, bTree->get_left(), ++i, true);
        }
        else if (is_close_bracket(ch))
        {
            return false;

        }
        else if (is_open_bracket(ch) && flag == false)
        {
            bTree->set_right();
            flag = create_binTree(is_str, bTree->get_right(), ++i, true);
        }
        else if (is_latt(ch))
        {
            flag = create_binTree(is_str, bTree, ++i, false);
            return flag;
        }
        flag = create_binTree(is_str, bTree, ++i, flag);
    }

}

template<typename BASE>
void print_binTree(BinTree<BASE>* bTree, unsigned l=0)
{
   if(!bTree)
   {
       for(unsigned int i=0; i<l; ++i)
          cout << '\t';
       cout << '#' << endl;
       return;
   }
   print_binTree(bTree->get_right(), l+1);
   for(unsigned int i=0; i<l; i++)
       cout << '\t';
   cout << bTree->get_vl() << endl;
   print_binTree(bTree->get_left(), l+1);
}



template<typename BASE>
bool similar(BinTree<BASE>* bTree1, BinTree<BASE>* bTree2)    //проверка подобия
{
    if (bTree1 == nullptr && bTree2 ==nullptr)
    {
        return true;
    }
    else
    if (bTree1 == nullptr || bTree2 == nullptr)
    {
        return false;
    }

    return similar(bTree1->get_left(), bTree2->get_left()) &&
           similar(bTree1->get_right(), bTree2->get_right());
}

template<typename BASE>
bool equal(BinTree<BASE>* bTree1, BinTree<BASE>* bTree2)      //проверка на равенство
{
    if (bTree1 == nullptr && bTree2 ==nullptr)
    {
        return true;
    }
    else
    if (bTree1 == nullptr || bTree2 == nullptr)
    {
        return false;
    }
    else
    if (bTree1->get_vl() != bTree2->get_vl())
    {
        return false;
    }
    return equal(bTree1->get_left(), bTree2->get_left()) &&
            equal(bTree1->get_right(), bTree2->get_right());
}


template<typename BASE>
bool speculary_similar(BinTree<BASE>* bTree1, BinTree<BASE>* bTree2) //зеркально подобны
{
    if (bTree1 == nullptr && bTree2 ==nullptr)
    {
        return true;
    }
    else
    if (bTree1 == nullptr || bTree2 == nullptr)
    {
        return false;
    }

    return speculary_similar(bTree1->get_left(), bTree2->get_right()) &&
            speculary_similar(bTree1->get_right(), bTree2->get_left());
}

template<typename BASE>
bool symmetry(BinTree<BASE>* bTree1, BinTree<BASE>* bTree2)      //проверка на симметричность
{
    if (bTree1 == nullptr && bTree2 ==nullptr)
    {
        return true;
    }
    else
    if (bTree1 == nullptr || bTree2 == nullptr)
    {
        return false;
    }
    else
    if (bTree1->get_vl() != bTree2->get_vl())
    {
        return false;
    }
    return symmetry(bTree1->get_left(), bTree2->get_right()) &&
            symmetry(bTree1->get_right(), bTree2->get_left());
}

bool analyzer(string bt, int length)
{
    int open_brackets = 0;
    int close_brackets = 0;

    if (length == 3 && bt[0] == '(' && bt[1] == '#' && bt[2] == ')')
        return false;

    if (bt[0] != '(')
    {
        cerr << "Ошибка в символе № " << 1 << ". Первым символом всегда должна быть '('.";
        return true;
    }
    else
        open_brackets++;

    if (bt[length-1] != ')')
    {
        cerr << "Ошибка в символе № " << length << ". Последним всегда должен быть символ ')'.";
        return true;
    }
    else
        close_brackets++;

    for (int i = 1; i < length-1; i++)
    {
        if (bt[i] == '(' && (bt[i+1] < 'a' || bt[i+1] > 'z'))
        {
            cerr << "Ошибка в символе № " << i+2 << ". После '(' должна следовать буква.";
            return true;
        }
        else  if (bt[i] == '(')
            open_brackets++;

        if (bt[i] > 'a' && bt[i] < 'z' && (bt[i+1] != '(' && bt[i+1] != '#' && bt[i+1] != ')'))
        {
            cerr << "Ошибка в символе № " << i+2 << ". После буквы должен следовать один из вариантов: '(', '#', ')'.";
            return true;
        }

        if (bt[i] == '#' && bt[i+1] != '(')
        {
            cerr << "Ошибка в символе № " << i+2 << ". После '#' ожидается ввод '('.";
            return true;
        }

        if (bt[i] == ')' && (bt[i+1] != '(' && bt[i+1] != ')'))
        {
            cerr << "Ошибка в символе № " << i+2 << ". После ')' ожидается ввод '(' или ')'.";
            return true;
        }
        else
        if (bt[i] == ')')
            close_brackets++;
    }

    if (open_brackets != close_brackets)
    {
       cerr << "Количество открытых и закрытых скобок не равны";
       return true;
    }
    else
        return false;
}


#endif // FUNC_H
