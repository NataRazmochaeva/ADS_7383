#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;
//template <class T>
class BST{
private:
    int key;
    BST* right;
    BST* left;
public:

	BST(int k){
		key = k;
		left = right = nullptr;
	}

	int Root(BST* b){
        if (b == NULL)
        	exit(1);
        else
        	return b->key;
	}


	BST* destroy(BST* tree){
        	if (left)
       		     delete tree->left;
       		if (right)
            		delete tree->right;
       		delete tree;
       		return tree = NULL;
	}

	BST* Left(BST* b){
        if (b == NULL) 
		exit(1);
        else 
		return b->left;
	}
	
	BST* Right(BST* b){
        if (b == NULL) 
		exit(1); 
        else 
		return b->right;
	}


	BST* BuildBST(BST* tree, int keyint){
		if (!tree)
			return new BST(keyint);
		if( tree->key > keyint )
                	tree->left = BuildBST(Left(tree), keyint);
           	else
                	tree->right = BuildBST(Right(tree), keyint);
		return tree;
	}
	
	BST* find( BST* tree, int key){
        if(!tree)
            return NULL;
        if(key == tree->key)
            return tree;
        if(key < tree->key)
            return find(tree->left, key);
        else
            return find(tree->right, key);
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


int comp (const int *i, const int *j)
{
return *i - *j;
}

int main(){
	BST *b = NULL;
	BST *p = NULL;
	string exp;
	stringbuf temp;
	int k;
	int arrsize;
	while(1){
		int out = 0;
		cout<<"\nВведите 1 - если хотите считат/ь из файла, 2 - если хотите выполнить ввод с консоли, 0 - если хотите завершить программу\n"<<endl;
		cin>>k;
		switch(k){
			case 1:{
				ifstream infile("1.txt");
   			        if(!infile){
   			        	cout<<"There is no file"<<endl;
   	        		        continue;
   	                  	}
   	        		getline(infile, exp);}
				break;
			case 2:{
				cout << "Введите список:" << endl;
				cin.ignore();
				getline(cin, exp);}
				break;
			case 0:{
				cout<<"Программа завершилась"<<endl;
				out = 1;}
				break;
			default:
				cout<<"Вы ввели какую-то херню, попробуйте еще раз"<<endl;
				break;
		}
		if (out == 1)
			break;
		int keyint;
		int count=0;
		int* arr = new int;
		char* OneKey;
		char* StrKeys = new char[exp.size()+1];
		strcpy(StrKeys, exp.c_str());
		OneKey = strtok(StrKeys, " ");
		while (OneKey != NULL){
			
			keyint = atoi(OneKey);
			
			arr[count] = keyint;
			count++;
			cout<<arr[count-1]<<endl;
			if(b->find(b, keyint)){
				OneKey=strtok(NULL, " ");
				continue;
			}

			b = b->BuildBST(b, keyint);
  
     			OneKey = strtok (NULL, " ");
   		}
		printtree(b, 0);	
		qsort(arr, count, sizeof (int), (int(*) (const void *, const void *)) comp);
		int i;
		for (i=0; i<count; i++){
			p = p->BuildBST(p, arr[i]);		
		}
		cout<<"Дерево отсортировано по возрастанию\n"<<endl;
		printtree(p, 0);
		p = p->destroy(p);
		delete arr;
		exp.clear();
		b = b->destroy(b);
		delete [] StrKeys;
		delete OneKey;
		
	}
return 0;
}
		
		
