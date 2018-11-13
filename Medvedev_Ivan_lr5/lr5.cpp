#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
using namespace std;


struct node{     // структура для представления узлов дерева
    int key;
    int prior;
    node* left;
    node* right;
    node(int k) { key = k; left = right = NULL; prior = rand()%100;}
};



node* rotateright(node* p){ // правый поворот вокруг узла p
    node* q = p->left;
    if( !q )
        return p;
    p->left = q->right;
    q->right = p;
    return q;
}

node* rotateleft(node* q){ // левый поворот вокруг узла q
    node* p = q->right;
    if( !p )
        return q;
    q->right = p->left;
    p->left = q;
    return p;
}


node* insert(int key, node* root){
    if(!root){
        node* p = new node(key);
        return (p);
    }
    if(key <= root->key)
    {
        root->left = insert(key, root->left);
        if(root->left->prior < root->prior)
            root = rotateright(root);
    }
    else{
        root->right = insert(key, root->right);
        if(root->right->prior < root->prior)
            root = rotateleft(root);
    }
    return root;
}



node* merge(node *p, node *q) {
    if (p == NULL) return q;
    if (q == NULL) return p;

    if (p->prior > q->prior) {
        p->right = merge(p->right, q);
        return p;
    }
    else {
        q->left = merge(p, q->left);
        return q;
    }
}


node* Delete(node* p){
    if (left)
        delete p->left;
    if (right)
        delete p->right;
    delete p;
    return p = NULL;
}

void printPriority(node* root){
    if (!root)
        return;
    cout<<"Priority of key ["<< root->key <<"] is "<<root->prior<<endl;
    printPriority(root->right);
    printPriority(root->left);
}


node* remove(node* p, int k){ // удаление из дерева p первого найденного узла с ключом k
    if( !p )
        return p;
    if( p->key == k ) {
        node* q = merge(p->left,p->right);
        delete p;
        return q;
    }
    else if( k < p->key )
        p->left = remove(p->left,k);
    else
        p->right = remove(p->right,k);
    return p;
}


 void printtree(node* treenode, int l){
    if(treenode==NULL){
        for(int i = 0;i<l;++i)
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

node* find( node* tree, int key){
        if(!tree)
            return NULL;
        if(key == tree->key)
            return tree;
        if(key < tree->key)
            return find(tree->left, key);
        else
            return find(tree->right, key);
    }


 int main(){
     node* treap = NULL;
     int key = 0, c;
     string str;
     char forSwitch;
     while(1){
        cout<<"Press 1 to read from console, press 2 to read from Treap.txt file, press 0 to exit."<<endl;
        cin >> forSwitch;
        getchar();
        switch (forSwitch) {
            case '2':{
                ifstream infile("Treap.txt");
                if(!infile){
                      cout<<"There is no file"<<endl;
                      continue;
                      }
                getline(infile, str);
                break;
            }
            case '1':{
                    cout<<"Enter the keys"<<endl;
                    getline(cin, str);
                    break;
            }
            case '0':{
                    return 0;
            }
            default:{
                    cout<<"Incorrect input"<<endl;
                    break;
            }
        }
        char* arr = new char[str.size()+1];
        strcpy(arr, str.c_str());
        char* tok;
        tok = strtok(arr, " ");
        while(tok != NULL){
	    c = atoi(tok);
	    if (find(treap,c)){
		cout << "key [" << c << "] repeated"<<endl;
		tok = strtok(NULL, " ");
		continue;  
	    }
            treap = insert(c, treap);
            tok = strtok(NULL, " ");
        }
        printPriority(treap);
        cout<<endl;
        printtree(treap,0);
    cout<<"Enter the key"<<endl<<"============================"<<endl;
        cin >> key;
        treap = remove(treap, key);
        printtree(treap,0);
        treap = Delete(treap);
    str.clear();
    delete tok;
    delete[] arr;
    }
 }
