#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>


template <typename base>
class BST{
private:
	base key;
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

	 BST* insertrandom(BST* p, int k) // ðàíäîìèçèðîâàííàÿ âñòàâêà íîâîãî óçëà ñ êëþ÷îì k â äåðåâî p
	{
		if( !p ) return new BST(k);
			if( rand()%(getsize(p)+1)==getsize(p)){
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

	 BST* Delete(BST* p){
		if (left)
			delete p->left;
		if (right)
			delete p->right;
		delete p;
		return p = NULL;
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