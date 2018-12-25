#pragma once
typedef int base;
#define N 100

struct BST
{
  base key;
  BST* left;
  BST* right;
  BST(int k)
  {
    key = k;
    left = nullptr;
    right = nullptr;
  }
};
base Root(BST* tree);
BST* Left(BST* tree);
BST* Right(BST* tree);
BST* createBST(BST* tree, int el);
void printBST(BST* tree, int n);
bool find_add (BST* tree, base &x);
BST* destroy(BST* tree);
