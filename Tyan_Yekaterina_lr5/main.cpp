#include <iostream>
#include <cctype>
#include <fstream>

#define N 100

using namespace std;

typedef struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
}T;

int imax2(int a,int b){
    return (a-b>0) ? a : b;
}

T *avltree_create(int key){
    T *node=new T;
    if (node != NULL) {
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->height = 0;
    }
    return node;
}

int avltree_height(T *tree){
    return (tree != NULL) ? tree->height : -1;
}

T *avltree_right_rotate(T *tree){
    T *left;
    left = tree->left;
    tree->left = left->right;
    left->right = tree;
    tree->height = imax2(avltree_height(tree->left),avltree_height(tree->right)) + 1;
    left->height = imax2(avltree_height(left->left),tree->height) + 1;
    return left;
}

T*avltree_left_rotate(T*tree){
    T *right;
    right = tree->right;
    tree->right = right->left;
    right->left = tree;
    tree->height = imax2(avltree_height(tree->left),avltree_height(tree->right)) + 1;
    right->height = imax2(avltree_height(right->right),tree->height) + 1;
    return right;
}

int avltree_balance(T *tree){
    return ((avltree_height(tree->right) - avltree_height(tree->left)));
}

T* balance(T* tree){
    avltree_height(tree);
    if(avltree_balance(tree) == 2){
        if(avltree_balance(tree->right)<0)
            tree->right=avltree_right_rotate(tree->right);
        return avltree_left_rotate(tree);
    }
    if(avltree_balance(tree)==-2){
        if(avltree_balance(tree->left)>0)
            tree->left=avltree_left_rotate(tree->left);
        return avltree_right_rotate(tree);
    }
    return tree;
}

T* avltree_add(T *&tree, int key,bool flag){
    if (tree == NULL){
        return avltree_create(key);
    }
    if(key==tree->key){
        flag=false;
        return NULL;
    }
    if (key < tree->key) {
        tree->left = avltree_add(tree->left,key,flag);
    }else if (key > tree->key) {
        tree->right = avltree_add(tree->right,key,flag);
    }
    tree->height = imax2(avltree_height(tree->left),avltree_height(tree->right)) + 1;
    return balance(tree);
}

void outBT(T* b,int i,bool left, T* ptr){
    if (b!=NULL){
        outBT(b->left,i+4,true,b);
        if(ptr==NULL){
            for(int k=0;k<i;k++)
                cout<<" ";
            cout<<"---";
            cout << b->key<<endl;
        }else if(left){
            for(int k=0;k<i;k++)
                cout<<" ";
            cout<<".---";
            cout << b->key<<endl;
        }else{
            for(int k=0;k<i;k++)
                cout<<" ";
            cout<<"`---";
            cout << b->key<<endl;
        }
        outBT(b->right,i+4,false,b);
    }else
        return;
}

T* find_min(T*tree){
    return tree->left ? find_min(tree->left) : tree;
}

T* remove_min(T* tree){
    if(tree->left==NULL)
        return tree->right;
    tree->left=remove_min(tree->left);
    return balance(tree);
}

T* dele(T *&tree, int key){
    if (tree == NULL){
        return NULL;
    }
    if(key==tree->key){
        T*q=tree->left;
        T*r=tree->right;
        delete tree;
        if(!r){
            return q;
        }
        T* min;
        min=find_min(tree->right);
        min->right=remove_min(r);
        min->left=q;
        return balance(min);
    }
    if (key < tree->key) {
        tree->left=dele(tree->left,key);
    }else if (key > tree->key) {
        tree->right=tree->right=dele(tree->right,key);
    }
    tree->height = imax2(avltree_height(tree->left),avltree_height(tree->right)) + 1;
    return balance(tree);
}

void avltree_print_dfs(T *tree, int level){
    int i;
    if (tree == NULL)
        return;
    for (i = 0; i < level; i++)
        printf("    ");
    printf("%d\n", tree->key);
    avltree_print_dfs(tree->left, level + 1);
    avltree_print_dfs(tree->right, level + 1);
}

int main(){
    int var=0;
    while(var != 3){
        cout << "Выберите дальнейшие действия и введите цифру:"<<endl;
        cout << "1. Ввести перечисления узлов вручную."<<endl;
        cout << "2. Считать перечисления узлов из выбранного файла <имя файла>.txt."<<endl;
        cout << "3. Завершить работу."<<endl;
        cin >> var;
        switch(var){
            case 1:{
                int q,num;
                cout<<"Input quantity of umbers: ";
                cin>>q;
                T* root=NULL;
                for(int i=0;i<q;i++){
                    cin>>num;
                    bool flag=true;
                    root=avltree_add(root,num,flag);
                    if(flag==false){
                        cout<<"This symbol exists."<<endl;
                        return 1;
                    }
                }
                T* b;
                outBT(root,0,false,b);
                int a;
                cout<<"Input value: ";
                cin>>a;
                b=NULL;
                root=dele(root,a);
                outBT(root,0,false,b);
                break;
            }
            case 2:{
                int num;
                getchar();
                char fname[N];
                printf("Choose file\n");
                fgets(fname,N,stdin);
                fname[strlen(fname)-1]='\0';
                fstream myfile(fname,ios_base::in);
                T*root=NULL;
                while (myfile >> num)
                {
                    bool flag=true;
                    root=avltree_add(root,num,flag);
                    if(flag==false){
                        cout<<"This symbol exists."<<endl;
                        return 1;
                    }
                }
                T* b;
                outBT(root,0,false,b);
                int a;
                cout<<"Input value: ";
                cin>>a;
                b=NULL;
                root=dele(root,a);
                outBT(root,0,false,b);
                break;
            }
            case 3:
                return 0;
            default:
                cerr << "Проверьте введенные данные и повторите попытку." << endl;
                break;
        }
    }
    return 0;
}
