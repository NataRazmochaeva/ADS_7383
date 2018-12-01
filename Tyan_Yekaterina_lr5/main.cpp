#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>

#define N 100

using namespace std;

typedef struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
}T;

int imax(int a,int b){
    return (a-b>0) ? a : b;
}

void delete_avltree(T*tree){
    if(tree==NULL)
        return;
    delete_avltree(tree->left);
    delete_avltree(tree->right);
    delete(tree);
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
    tree->height = imax(avltree_height(tree->left),avltree_height(tree->right)) + 1;
    left->height = imax(avltree_height(left->left),tree->height) + 1;
    return left;
}

T*avltree_left_rotate(T*tree){
    T *right;
    right = tree->right;
    tree->right = right->left;
    right->left = tree;
    tree->height = imax(avltree_height(tree->left),avltree_height(tree->right)) + 1;
    right->height = imax(avltree_height(right->right),tree->height) + 1;
    return right;
}

int avltree_balance(T *tree){
    return ((avltree_height(tree->right) - avltree_height(tree->left)));
}

T* balance(T* tree){
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

T* avltree_add(T *&tree, int key,bool &flag){
    if (tree == NULL){
        return avltree_create(key);
    }
    if(key==tree->key){
        flag=false;
    }
    if (key < tree->key) {
        tree->left = avltree_add(tree->left,key,flag);
    }else if (key > tree->key) {
        tree->right = avltree_add(tree->right,key,flag);
    }
    tree->height = imax(avltree_height(tree->left),avltree_height(tree->right)) + 1;
    return balance(tree);
}

void outBT(T* b,int i,bool left, T* ptr){
    if (b!=NULL){
        outBT(b->right,i+4,true,b);
        if(ptr==NULL){
            for(int k=0;k<i;k++)
                cout<<" ";
            cout<<"---";
            cout << "("<<b->key<<")"<<endl;
        }else if(left){
            for(int k=0;k<i;k++)
                cout<<" ";
            cout<<".---";
            cout << "("<<b->key<<")"<<endl;
        }else{
            for(int k=0;k<i;k++)
                cout<<" ";
            cout<<"`---";
            cout << "("<<b->key<<")"<<endl;
        }
        outBT(b->left,i+4,false,b);
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
    tree->height = imax(avltree_height(tree->left),avltree_height(tree->right)) + 1;
    return balance(tree);
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
                cout<<"Input quantity of nodes: ";
                cin>>q;
                cout<<"Input nodes: ";
                T* root=NULL;
                T*b=NULL;
                for(int i=0;i<q;i++){
                    cin>>num;
                    bool flag=true;
                    root=avltree_add(root,num,flag);
                    if(flag==false){
                        cout<<"This symbol exists. Try again."<<endl;
                        i--;
                    }
                    if(flag==true){
                        b=NULL;
                        cout<<"Was inputed: "<<num<<endl;
                        outBT(root,0,false,b);
                    }
                }
                b=NULL;
                cout<<"Built AVL-tree:"<<endl;
                outBT(root,0,false,b);
                q=0;
                cout<<"How many nodes will be deleted: ";
                cin>>q;
                if(q!=0){
                    getchar();
                    int a[q],val=0;
                    cout<<"Input values to be deleted: ";
                    char str[N];
                    fgets(str,N,stdin);
                    char * pch = strtok (str,",");
                    while (pch != NULL){
                        val=atoi(pch);
                        b=NULL;
                        cout<<"Value to be deleted: "<<val<<endl;
                        root=dele(root,val);
                        outBT(root,0,false,b);
                        val=0;
                        pch = strtok (NULL, ",");
                    }
                }
                delete_avltree(root);
                break;
            }
            case 2:{
                int num,q;
                getchar();
                char fname[N];
                printf("Choose file\n");
                fgets(fname,N,stdin);
                fname[strlen(fname)-1]='\0';
                fstream myfile(fname,ios_base::in);
                T*root=NULL;
                T* b;
                while (myfile >> num){
                    bool flag=true;
                    root=avltree_add(root,num,flag);
                    if(flag==false){
                        cout<<"This symbol exists: "<<num<<endl;
                    }else{
                        b=NULL;
                        cout<<"Was inputed: "<<num<<endl;
                        outBT(root,0,false,b);
                    }
                }
                b=NULL;
                cout<<"Built AVL-tree:"<<endl;
                outBT(root,0,false,b);
                q=0;
                cout<<"How many nodes will be deleted: ";
                cin>>q;
                if(q!=0){
                    getchar();
                    int a[q],val=0;
                    cout<<"Input values to be deleted: ";
                    char str[N];
                    fgets(str,N,stdin);
                    char * pch = strtok (str,",");
                    while (pch != NULL){
                        val=atoi(pch);
                        b=NULL;
                        cout<<"Value to be deleted: "<<val<<endl;
                        root=dele(root,val);
                        outBT(root,0,false,b);
                        val=0;
                        pch = strtok (NULL, ",");
                    }
                }
                delete_avltree(root);
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
