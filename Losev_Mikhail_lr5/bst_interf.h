#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include "functions.h"

using namespace std;
using namespace losev_functions;

namespace losev_BST
{
	template <class base>
	class BST {
	private:
		int key;
		int size;
		base info;
		BST* right;
		BST* left;
	public:	
		BST *build_tree(string str)
		{
			int n;
			char* tok;
			BST <int> *b = NULL;

			if (check_for_externs(str)){
				cerr << "Ошибка: в строке посторонние символы!" << endl;
				return NULL;
			}

			char* arr = new char[str.size()];
			strcpy(arr, str.c_str());

			tok = strtok(arr, " ");
			
			while(tok){
				n = atoi(tok);
				
				if(!b->find(b, n)){ 
					n = atoi(tok);
					b = b->insertrandom(b, atoi(tok));
				} // добавляем число в дерево, если его там еще нет
				tok = strtok(NULL, " ");
			}

			delete[] arr;
			return b;
		}

		void printtree(BST *treenode, int l)
		{
			if(treenode == NULL){
			   for(int i = 0;i<l;++i)
					cout<<"\t";
				cout<<'#'<<endl;
				return;
			}
			printtree(treenode->Right(treenode), l+1);
			for(int i = 0; i < l; i++)
				cout << "\t";
			cout << treenode->Root(treenode) << endl;
			printtree(treenode->Left(treenode),l+1);
		}

		int ascend_write_tree(string filename, BST <int> *tree)
		{
			if (tree == NULL){
				return 2;
			}

			ofstream fout;
			fout.open(filename, ofstream::trunc);
			if (fout.is_open()){
				ascend_write_node(&fout, tree);
				fout.close();
			}
			else {
				cerr << "Ошибка: файл вывода не открывается" << endl;
				return 1;
			}
			return 0;
		}

		BST* Delete(BST* p)
		{
			if (p == NULL)
				return NULL;
			if (left)
				delete p->left;
			if (right)
				delete p->right;
			delete p;
			return p = NULL;
		}
	protected:
		BST(int k)
		{
			key = k; left = nullptr;
			right = nullptr;
			size = 1;
		}

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
		BST* Right()
		{
			/*if (b == NULL) { exit(1); }
			else*/ return right;
		}

		int getsize(BST* p) // îáåðòêà äëÿ ïîëÿ size, ðàáîòàåò ñ ïóñòûìè äåðåâüÿìè (t=NULL)
		{
			if(!p)
				return 0;
			return p->size;
		}

		void fixsize(BST* p) // óñòàíîâëåíèå êîððåêòíîãî ðàçìåðà äåðåâà
		{
			p->size = getsize(Left(p))+getsize(Right(p))+1;
		}

		BST* rotateright(BST* p) // ïðàâûé ïîâîðîò âîêðóã óçëà p
		{
			BST* q = p->left;
			if( !q ) return p;
			p->left = q->right;
			q->right = p;
			q->size = p->size;
			fixsize(p);
			return q;
		}

		BST* rotateleft(BST* q) // ëåâûé ïîâîðîò âîêðóã óçëà q
		{
			BST* p = q->right;
			if( !p ) return q;
			q->right = p->left;
			p->left = q;
			p->size = q->size;
			fixsize(q);
			return p;
		}

		BST* insertroot(BST* p, int k) // âñòàâêà íîâîãî óçëà ñ êëþ÷îì k â êîðåíü äåðåâà p
		{
			if (!p)
				return new BST(k);
			if (k < p->key){
				p->left = insertroot(p->left, k);
				return rotateright(p);
			}
			else{
				p->right = insertroot(p->right, k);
				return rotateleft(p);
			}
		}

		BST* insertrandom(BST* p, int k) // ðàíäîìèçèðîâàííàÿ âñòàâêà íîâîãî óçëà ñ êëþ÷îì k â äåðåâî p
		{
			if (!p) return new BST(k);
			if (rand() % (getsize(p)+1) == getsize(p)){
				//  cout<<"COMBS: "<<rand()%(getsize(p)+1) <<endl;
				return insertroot(p, k);
			}
			if (p->key > k)
				p->left = insertrandom(Left(p), k);
			else
				p->right = insertrandom(Right(p), k);
			fixsize(p);
			return p;
		 }

		BST* join(BST* p, BST* q) // îáúåäèíåíèå äâóõ äåðåâüåâ
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

		BST* remove(BST* p, int k) // óäàëåíèå èç äåðåâà p ïåðâîãî íàéäåííîãî óçëà ñ êëþ÷îì k
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

		BST* find(BST* tree, int key)
		{
			if (!tree)
				return NULL;
			if (key == tree->key)
				return tree;
			if (key < tree->key)
				return find(tree->left, key);
			else
				return find(tree->right, key);
		}

		void ascend_write_node(ofstream *outfile, BST <base> *tree)
		{
			if (tree == NULL)
				return;
			ascend_write_node(outfile, Left(tree));
			(*outfile) << Root(tree) << ' ';
			ascend_write_node(outfile, Right(tree));
		}
	};


}