#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;
//template <class T>
class BST{
private:
    int key;
    int size;
    BST* right;
    BST* left;

public:
    BST(int k){key = k; left = right = nullptr; size = 1;}
    int Root(BST* b)
    {
        if (b == NULL)
            exit(1);
        else
            return b->key;
    }


    BST* Left(BST* b)
    {
        if (b == NULL) { exit(1); }
        else return b->left;
    }

    BST* Right(BST* b)
    {
        if (b == NULL) { exit(1); }
        else return b->right;
    }
    BST* find( BST* p, int k){
        if(!p)
            return nullptr;
        if(k==Root(p))
            return p;
        if(k<Root(p))
            return find(Left(p), k);
        else
            return find(Right(p), k);
    }

    int getsize(BST* p) // обертка для поля size, работает с пустыми деревьями (t=NULL)
    {
        if(!p)
            return 0;
        return p->size;
    }

    void fixsize(BST* p) // установление корректного размера дерева
    {
        p->size = getsize(Left(p))+getsize(Right(p))+1;
    }

    BST* rotateright(BST* p) // правый поворот вокруг узла p
    {
        BST* q = p->left;
        if( !q ) return p;
        p->left = q->right;
        q->right = p;
        q->size = p->size;
        fixsize(p);
        return q;
    }

    BST* rotateleft(BST* q) // левый поворот вокруг узла q
    {
        BST* p = q->right;
        if( !p ) return q;
        q->right = p->left;
        p->left = q;
        p->size = q->size;
        fixsize(q);
        return p;
    }

    BST* insertroot(BST* p, int k) // вставка нового узла с ключом k в корень дерева p
    {
        if( !p )
            return new BST(k);
        if( k<p->key )
        {
            p->left = insertroot(p->left,k);
            return rotateright(p);
        }
        else
        {
            p->right = insertroot(p->right,k);
            return rotateleft(p);
        }
    }

    BST* insertrandom(BST* p, int k) // рандомизированная вставка нового узла с ключом k в дерево p
    {
        if( !p ) return new BST(k);
            if( rand()%(getsize(p)+1)==getsize(p) ){
              //  cout<<"COMBS: "<<rand()%(getsize(p)+1) <<endl;
                return insertroot(p,k);
            }
            if( p->key>k )
                p->left = insertrandom(Left(p),k);
            else
                p->right = insertrandom(Right(p),k);
            fixsize(p);
            return p;

    }

    BST* join(BST* p, BST* q) // объединение двух деревьев
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

    BST* remove(BST* p, int k) // удаление из дерева p первого найденного узла с ключом k
    {
        if( !p ) return p;
        if( p->key==k )
        {
            BST* q = join(p->left,p->right);
            p=q;
            return p;
        }
        else if( k<p->key )
            p->left = remove(p->left,k);
        else
            p->right = remove(p->right,k);
        return p;
    }

    BST* Delete(BST* p){
        if (left)
            delete p->left;
        if (right)
            delete p->right;
        delete p;
        return p = NULL;
    }
};

void printtree(BST* treenode, int l){
   if(treenode==NULL){
       for(int i = 0;i<l;++i)
           cout<<"\t";
       cout<<'#'<<endl;
       return;
   }
   printtree(treenode->Right(treenode), l+1);
   for(int i = 0; i < l; i++)
       cout << "\t";
   cout << treenode->Root(treenode)<< endl;
   printtree(treenode->Left(treenode),l+1);
}


int main(){
    BST* b = NULL;
    int key = 0;
    string str;
    char forSwitch;
    while(1){
       cout<<"Press 1 to read from console, press 2 to read from 1.txt file, press 0 to exit."<<endl;
       cin >> forSwitch;
       getchar();
       switch (forSwitch) {
           case '2':{
               ifstream infile("1.txt");
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
           b = b->insertrandom(b, atoi(tok));
           tok = strtok(NULL, " ");

       }
       cout<<endl;
       printtree(b,0);
   cout<<"Enter the key"<<endl<<"============================"<<endl;
       cin >> key;
       b = b->remove(b, key);
       printtree(b,0);
       b = b->Delete(b);
   str.clear();
   delete tok;
   delete[] arr;
   }

}
