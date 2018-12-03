#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
using namespace std;


struct node {    // структура для представления узлов дерева
    int key;     // ключ-значение
    int prior;   // приоритет
    node* left;  // указатель на левое поддерево
    node* right; // указатель на правое поддерево
    node(int k) {
        key = k; // инициализация структуры
        left = right = NULL;
        prior = rand()%100; // рандомные числа от 0 до 99
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

node* Delete(node* p) {
    if (left)
        delete p->left;
    if (right)
        delete p->right;
    delete p;
    return p = NULL;
}

void printPriority(node* root) {
    if (!root)
        return;
    cout<<"Приоритет ключа ["<< root->key <<"] - "<<root->prior<<endl;
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

node* add(node* p, int el) { // добавление нового элемент
    if (find(p,el)) {
        cout << "Ключ [" << el << "] повторяется"<<endl;
	return p;
    }
    else {
        p=insert(el, p);
        cout<<"Приоритет нового ключа ["<< (find(p,el))->key <<"] - "<<(find(p,el))->prior<<endl;
        return p;
    }
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
    int el = 0, c;
    string str;
    char forSwitch;
    cout << "\033[34m\tЗдравствуйте!Выберите что вы хотите:\033[0m\n 1) Нажмите 1, чтобы считать с консоли.\n 2) Нажмите 2, чтобы считать с файла.\n 3) Нажмите 3, чтобы выйти из программы.\n" << endl;
    while(1) {
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
	    if(c==0) { 
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
        cout<<"---------------------------"<<endl<<"Введите ключ, который хотите добавить"<<endl;
        cin >> el;
        treap = add(treap, el);
        printtree(treap,0);
        treap = Delete(treap);
        str.clear();
        delete tok;
        delete[] arr;
        cout<<"Введите следующую команду:\n";
    }
}
