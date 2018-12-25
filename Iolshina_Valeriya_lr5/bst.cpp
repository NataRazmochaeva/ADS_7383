#include "bst.h"
#include <iostream>
using namespace std;

BST* destroy(BST* tree)
{
  if (left)
    delete tree->left;
  if (right)
    delete tree->right;
  delete tree;
  return tree = NULL;
	}

base Root(BST* tree)
{
  if (tree == NULL)
    exit(1);
  else
    return tree->key;
}

BST* Left(BST* tree)
{
  if (tree == NULL)
    exit(1);
  else
    return tree->left;
}

BST* Right(BST* tree)
{
  if (tree == NULL)
    exit(1);
  else
    return tree->right;
}

BST* createBST(BST* tree, int el)
{
  if (!tree)
    return new BST(el);
	if(tree->key > el)
    tree->left = createBST(Left(tree), el);
  else
    tree->right = createBST(Right(tree), el);
	return tree;
}

void printBST(BST* tree, int l)
{
   if(tree==NULL)
   {
       for(int i=0; i<l; i++)
           cout << "\t";
       cout << '#' << endl;
       return;
   }
   printBST(Right(tree), l+1);
   for(int i=0; i<l; i++)
       cout << "\t";
   cout << Root(tree) << endl;
   printBST(Left(tree),l+1);
}

bool find_add (BST* tree, base &k)
{
  if (Root(tree) > k)
  {
    if (Left(tree) == NULL)
    {
      tree->left = new BST(k);
      return false;
    }
      return find_add(Left(tree), k);
  }
  if (Root(tree) < k)
  {
    if (Right(tree) == NULL)
    {
      tree->right = new BST(k);
      return false;
    }
    return find_add(Right(tree), k);
  }
  if (Root(tree) == k)
    return true;
}
