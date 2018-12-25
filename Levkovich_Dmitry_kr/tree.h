#ifndef TREE_H
#define TREE_H
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

class BST{
public:
    BST(int k);
    int Root(BST* b);
    BST *Left(BST* b);
    BST *Right(BST* b);
    int getsize(BST* p);
    void fixsize(BST* p);
    BST *rotateright(BST* p);
    BST *rotateleft(BST* q) ;
    BST* insert(BST*, int);
    BST *insertroot(BST* p, int k);
    BST  *insertrandom(BST *p, int k);
    BST* join(BST* p, BST* q);
    BST* remove(BST* p, int k);
    BST* Delete(BST* p);
    BST* find( BST* tree, int key);
    void random_init();
    int counter(BST* tree);
    bool isNull(BST* b);
    int max(BST*);
    int height(BST*);
    int count();
    void zero();
    int count1();
    void zero1();
    ~BST();
private:
    int key;
    int size;
    BST* right;
    BST* left;
};

#endif // TREE_H
