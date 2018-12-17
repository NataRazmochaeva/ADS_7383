#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

struct node {          // структура для представления узлов дерева
    int key;           // ключ-значение
    long prior;   // приоритет
    node* left;        // указатель на левое поддерево
    node* right;       // указатель на правое поддерево
    node(int k) {
        key = k;       // инициализация структуры
        left = right = NULL;
        prior = rand()%100; // рандомные числа
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

void printelements(node* root, ofstream &fout) {
    if (!root)
        return;
  printelements(root->left, fout);
  cout<<root->key<<" ";
  fout <<root->key<< " ";
  printelements(root->right, fout);
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
    char forSwitch;
        while(1) {
          cout << "Выберите команду:"<< endl;
          cout<<"1) Нажмите 1, чтобы считать с консоли."<< endl;
          cout<<"2) Нажмите 2, чтобы считать с файла." << endl;
          cout<<"3) Нажмите 3, чтобы выйти из программы." << endl;
          ofstream fout("Output.txt");
        cin >> forSwitch;
        getchar();
        switch (forSwitch) {
        case '2': {
            ifstream infile("Test.txt");
            if(!infile) {
                cout<<"Файл не может быть открыт!"<<endl;
                cout<<"Введите следующую команду:\n";
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
        case '3': {
            cout<<"До свидания!"<<endl;
            return 0;
        }
        default: {
            cout<<"Некорректные данные!"<<endl;
            return 0;
        }
        }
        char* arr = new char[str.size()+1];
        strcpy(arr, str.c_str()); // запись строки в массив, который содержит последовательность символов с нулевым завершением
        char* tok;
        tok = strtok(arr, " "); // разделяем строку на цифры - ключи
        while(tok != NULL) {
            c = atoi(tok);      // конвертируем строку в величину типа int
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
        printelements(treap, fout);
        cout<<endl;
            Delete(treap);
            str.clear();
            delete tok;
            delete[] arr;
            cout<<"Введите следующую команду:\n";
}
}
