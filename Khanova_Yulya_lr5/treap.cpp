#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

long long int maxc = pow(2,32);

struct node {
    int key;
    long long prior;
    node* left;
    node* right;
    node(int k) {
        key = k;
        left = right = NULL;
        prior = rand()%maxc; // рандомные числа от 0 до 2^32
    }
};



node* rotateright(node* p) { // правый поворот вокруг узла p
    node* q = p->left;
    if( !q )
        return p;
    p->left = q->right;
    q->right = p;
    return q;
}

node* rotateleft(node* q) { // левый поворот вокруг узла q
    node* p = q->right;
    if( !p )
        return q;
    q->right = p->left;
    p->left = q;
    return p;
}


node* insert(int key, node* root) { // вставка
    if(!root) {
        node* p = new node(key);
        return (p);
    }
    if(key <= root->key)
    {
        root->left = insert(key, root->left);
        if(root->left->prior < root->prior)
            root = rotateright(root);
    }
    else {
        root->right = insert(key, root->right);
        if(root->right->prior < root->prior)
            root = rotateleft(root);
    }
    return root;
}

void Delete(node* p) {
    if(p==NULL)
        return;
    Delete(p->left);
    Delete(p->right);
    delete p;
}

void printPriority(node* root) {
    if (!root)
        return;
    cout<<"Приоритет ключа ["<<setw(5)<<right<< root->key <<"] - "<<setw(11)<<right<<root->prior<<endl;
    printPriority(root->right);
    printPriority(root->left);
}

node* find( node* tree, int key) {
    if(!tree)
        return NULL;
    if(key == tree->key)
        return tree;
    if(key < tree->key)
        return find(tree->left, key);
    else
        return find(tree->right, key);
}


void printtree(node* treenode, int l) {
    if(treenode==NULL) {
        for(int i = 0; i<l; ++i)
            cout<<"\t";
        cout<<'#'<<endl;
        return;
    }
    printtree(treenode->right, l+1);
    for(int i = 0; i < l; i++)
        cout << "\t";
    cout << treenode->key<< endl;
    printtree(treenode->left,l+1);
}

int main() {
    node* treap = NULL; // пирамида поиска
    int c, el=0;
    string str;
    bool ex = 1;
    char ch;

    while(ex) {
      cout<<"1 - ввод с клавиатуры"<<endl;
      cout<<"2 - ввод из файла input.txt"<<endl;
      cout<<"0 - выход из программы"<<endl;
      cout<<"Введите номер действия:"<<endl;
        cin >> ch;
        switch (ch) {
        case '2': {
            ifstream infile("input.txt");
            if(!infile) {
                cout<<"Файл не открыт!"<<endl;
                continue;
            }
            getline(infile, str);
            break;
        }
        case '1': {
            cout<<"Введите ключи в строку:"<<endl;
            getline(cin, str);
            break;
        }
        case '0': {
            ex = 0;
            return 0;
        }
        default: {
            cout<<"Некорректные данные!"<<endl;
            return 0;
        }
        }
        char* arr = new char[str.size()+1];
        strcpy(arr, str.c_str());
        char* tok;
        tok = strtok(arr, " ");
        while(tok != NULL) {
            c = atoi(tok);
	    if(isalpha(*tok)) {
	        cout<<"Некорректные данные!"<<endl;
                return 0;
	    }
	    if (find(treap,c)) {
                cout << "Ключ [" << c << "] повторяется"<<endl; // повторение ключа не допустимо, тк должен быть уникальным
                tok = strtok(NULL, " ");
                continue;
            }
            treap = insert(c, treap);
            tok = strtok(NULL, " ");
        }
        printPriority(treap); // печать приоритетов
        cout<<endl;
        printtree(treap,0);

        if(isdigit(cin.peek())) {
            cin.clear();
	          cin.ignore(1000, '\n');
	          cout<<"Введите только число!"<<endl;
	          cin >> el;
            printtree(treap,0);
            Delete(treap);
            str.clear();
            delete tok;
            delete[] arr;
	}
	else {
	    cout<<"Некорректные данные!"<<endl;
	    return 0;
	}
}
}
