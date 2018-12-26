#include <iostream>
#include "tree.h"
#include <ctime>
#include <cstdlib>
#include "mainwindow.h"
using namespace std;

int N = 0, M = 0;

BST::BST(int k){
    key = k;
    left = right = nullptr;
    size = 1;
}

int BST::Root(BST* b)
{
    if (b == nullptr)
         exit(1);
    else
        return b->key;
}

BST* BST::Left(BST* b)
{
    if (b == nullptr)
        exit(1);
    else
        return b->left;
}

BST* BST::Right(BST* b)
{
    if (b == nullptr)
        exit(1);
    else
        return b->right;
}

int BST::getsize(BST* p){
    if(!p)
        return 0;
    return p->size;
}

void BST::fixsize(BST* p){
    p->size = getsize(Left(p))+getsize(Right(p))+1;
}

BST* BST::rotateright(BST* p){
    BST* q = p->left;
    if( !q )
        return p;
    p->left = q->right;
    q->right = p;
    q->size = p->size;
    fixsize(p);
    return q;
    }

BST* BST::rotateleft(BST* q){
    BST* p = q->right;
    if( !p )
        return q;
    q->right = p->left;
    p->left = q;
    p->size = q->size;
    fixsize(q);
    return p;
}

BST* BST::insert(BST* p, int k) // классическая вставка нового узла с ключом k в дерево p
{

    if(!p) return new BST(k);
    if( p->key>k )
        p->left = insert(p->left,k);
    else
        p->right = insert(p->right,k);
    fixsize(p);
    return p;
}

BST* BST::insertroot(BST* p, int k){

    if( !p ){
        return new BST(k);
    }

    if( k<p->key ){
        p->left = insertroot(p->left,k);
        return rotateright(p);
    }
    else{
        p->right = insertroot(p->right,k);
        return rotateleft(p);
    }
}

BST * BST::insertrandom(BST *p, int k){
   M++;
    if(!p)
        return new BST(k);
    if(rand()%(getsize(p)+1)== 0)
        return insertroot(p,k);
    if( p->key>k )
        p->left = insert(Left(p),k);
    else
        p->right = insert(Right(p),k);
    fixsize(p);
    return p;
}

bool BST::isNull(BST* b){
    return b==nullptr;
}
BST* BST::join(BST* p, BST* q){

    if( !p )
        return q;
    if( !q )
        return p;
    if( rand()%(p->size+q->size) < p->size ){
        p->right = join(p->right,q);
        fixsize(p);
        return p;
    }
    else{
        q->left = join(p,q->left);
        fixsize(q);
        return q;
    }
}

int BST::max(BST* p){
    if(p->right==nullptr)
        return p->key;
    else max(p->right);
}

BST* BST::remove(BST* p, int k){
    N++;
    if( !p )
        return p;
    if( p->key==k ){
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


void BST::zero(){
    N = 0;
    return;
}

void BST::zero1(){
    M = 0;
    return;
}

int BST::count(){

    return N;
}

int BST::count1(){

    return M;
}


BST* BST::Delete(BST* p){
    if (p->left)
        delete p->left;
    if (p->right)
        delete p->right;
    delete p;
    return p = nullptr;
}

BST* BST::find( BST* tree, int key){
    if(!tree)
        return nullptr;
    if(key == tree->key)
        return tree;
    if(key < tree->key)
        return find(tree->left, key);
    else
        return find(tree->right, key);
}

void BST::random_init(){
    srand(time(nullptr));
}


int BST::counter(BST* tree){
    int x = 1;
    if(tree == nullptr)
        return 0;
     x+=counter(tree->left);
     x+=counter(tree->right);
     return x;
}

int BST::height(BST* b) {
    if(b==nullptr)
        return 0;
       if(height(b->left)>height(b->right))
           return height(b->left)+1;
    else
        return height(b->right)+1;
}

BST::~BST(){
    delete left;
    delete right;
}
