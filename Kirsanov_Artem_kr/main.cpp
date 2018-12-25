#include <iostream>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <fstream>

using namespace std;

struct node // структура для представления узлов дерева
{
    int key;
    int size;
    node* left;
    node* right;
    node(int k) { key = k; left = right = 0; size = 1; }
};

int getsize(node* p) // обертка для поля size, работает с пустыми деревьями (t=NULL)
{
    if( !p ) return 0;
    return p->size;
}

void fixsize(node* p) // установление корректного размера дерева
{
    p->size = getsize(p->left)+getsize(p->right)+1;
}

node* insert(node* p, int k) // вставка нового узла с ключом k в дерево p
{
    if( !p ) return new node(k);
    if( p->key>k )
        p->left = insert(p->left,k);
    else
        p->right = insert(p->right,k);
    fixsize(p);
    return p;
}

node* join(node* p, node* q) // объединение двух деревьев
{
    if( !p ) return q;
    if( !q ) return p;
    if( rand()%(p->size+q->size) < p->size )
    {
        p->right = join(p->right,q);
        fixsize(p);
        return p;
    }
    else
    {
        q->left = join(p,q->left);
        fixsize(q);
        return q;
    }
}

node* remove(node* p, int k) // удаление из дерева p первого найденного узла с ключом k
{
    if( !p ) return p;
    if( p->key==k )
    {
        node* q = join(p->left,p->right);
        delete p;
        return q;
    }
    else if( k<p->key )
        p->left = remove(p->left,k);
    else
        p->right = remove(p->right,k);
    return p;
}

node* destroy(node* T){
        if (T->left)
             delete T->left;
        if (T->right)
                delete T->right;
        delete T;
        return T = NULL;
}

int main()
{
    srand(unsigned(time(0)));
    node *T = NULL;
    unsigned int count, range, ins, del, step;
    double seconds;
    ofstream file;
    file.open("output.txt");

    cout << "Enter the number of nodes:" << endl;
    cin >> count;
    cout << "Enter the range: " << endl;
    cin >> range;
    cout << "Enter the number of elements to be inserted: " << endl;
    cin >> ins;
    cout << "Enter the number of elements to be deleted: " << endl;
    cin >> del;
    cout << "Enter the segment step:" << endl;
    cin >> step;

    vector<int> x(count+ins);
    vector<int> temp(count+ins);
    for(int i = 0; i < count+ins; i++){
        x[i] = range/count*i;
    } 
    random_shuffle(x.begin(), x.end());
    for(int i = 0; i < count; i++){
        T = insert(T, x[i]);
    }

    file << "Number of el\tElapsed insertion time in seconds" << endl;
    seconds = 0;
    for(int i = step; i <= ins; i+=step){
        for (int k = count+i; k < count+i+step; k++) {
            clock_t starti = clock();
            T = insert(T, x[k]);
            clock_t endi = clock();
            seconds += (double)(endi - starti) / CLOCKS_PER_SEC;
        }
        file << i << "\t\t\t\t";
        file << setprecision(5) << seconds << endl;
    }

    file << endl;
    if(del > count+ins) del = count + ins;
    file << "Number of el\tElapsed time to delete in seconds" << endl;
    seconds = 0;
    for(int i = step; i <= del; i+=step){
        for (int k = count; k < count + i; k++) {
            clock_t starti = clock();
            T = remove(T, x[k]);
            clock_t endi = clock();
            seconds += (double)(endi - starti) / CLOCKS_PER_SEC;
        }
        file << i << "\t\t\t\t";
        file << setprecision(5) << seconds << endl;
    }

    cout << "The program finished correctly";
    return 0;
}
