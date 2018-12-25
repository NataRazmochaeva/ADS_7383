#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;
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
	
	BST* remove(BST* p, int k, int gl){
		int poop;
		if (k==gl){
				BST* jopa=p;
				if(jopa->right){
					jopa=jopa->right;
					while(jopa->left)
						jopa=jopa->left;
				}
				poop = jopa->key;
		}
    	if( !p ) return p;
		if( p->key==k){
            BST* q = join(p->left,p->right);
            p=q;
			if (k==gl && p){
				p->key=poop;
			}
            return p;
        }
        else if( k<p->key )
            p->left = remove(p->left,k, gl);
        else
            p->right = remove(p->right,k, gl);
        return p;
	}
	
	BST* join(BST* L, BST* R){
		if( !R ) return L;
		if( !L ) return R;
		BST* h = R;
		BST* k;
		if (!h->left){
			h->left=L;
			return h;
		}
			
		while(h->left){
			k=h;
			h=h->left;		
		}
		if (h->right){
			k->left=h->right;			
		}
		else k->left=NULL;
		h->right=R;
		h->left=L;
		return h;
	
	}

};




void printtree(BST* treenode, int l, ofstream &file){
   if(treenode==NULL){
       for(int i = 0;i<l;++i)
           file<<"\t";
       file<<'#'<<endl;
       return;
   }
   printtree(treenode->Right(treenode), l+1, file);
   for(int i = 0; i < l; i++)
       file << "\t";
   file << treenode->Root(treenode)<< endl;
   printtree(treenode->Left(treenode),l+1, file);
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
    int i;

	int call, j;
	j=0;
	cout<<"Введите кол-во вариантов заданий"<<endl;
	cin>>call;
	cin.ignore();


	int c1=0, c2=0, c3=0;
	int vozr, foriskl, forvstav, iskl, vstav;
	

	ofstream file;
    file.open("1.txt");

	ofstream answ;
	answ.open("answ.txt");

	int arr[100];
	int ch=0;
while(call>j){	
	j++;
	if (!ch){
		cout<<"\nВведите кол-во узлов дерева"<<endl;
    	cin>>ch;
    	cin.ignore();
    	
    	srand(ch);
	}
	srand( time(0)+j );
    cout<<"Дерево #"<<j<<" сгенерировано"<<endl;
	for(i=0; i<ch; i++){
        
        arr[i]=1+rand() % 99;
        
    }

	file<<"\nВариант №"<<j;
    file<<"\nВаше случайное дерево:\t";
    for(i=0; i<ch; i++){
        file<<arr[i]<<"\t";
    }



    
	answ<<"__________________________________________________________\n";
	answ<<"Вариант №"<<j;
	answ<<"\nИллюстрация сгенерированного дерева\n\n";
		

	for(i=0; i<ch; i++){
		if(b->find(b, arr[i])){
        	
            continue;
        }
        b = b->BuildBST(b, arr[i]);
	}
	printtree(b, 0, answ);


	if(c1==0){
    	cout<<"\nЕсли вы хотите отрисовать дерево по возрастанию - введите 1"<<endl;
    	
   		cin>>vozr;
    	cin.ignore();
		c1=1;
	}

	if(vozr==1){
		file<<"\nОтрисуйте дерево по возрастанию";
		qsort(arr, ch, sizeof (int), (int(*) (const void *, const void *)) comp);
		for (i=0; i<ch; i++){
				if(p->find(p, arr[i]))
            		continue;
				p = p->BuildBST(p, arr[i]);
        }
		answ<<"\nДерево перестроено по возрастанию:\n\n";
		printtree(p, 0, answ);
	}

	


	if (c2==0){
    	cout<<"\nЕсли вы хотите исключить какой-либо элекмент - введите 2"<<endl;
   		
    	cin>>iskl;
    	cin.ignore();
		c2=1;
	}

	if(iskl==2){
		
		foriskl=arr[0+rand() % ch];
		file<<"\nИсключить из дерева "<<foriskl<<" элемент и нарисовать дерево";
		b=b->remove(b, foriskl, arr[0]);
		answ<<"\nДерево перестроено c исключением элемента:\n\n";
		printtree(b, 0, answ);
		
	}
	


	if (c3==0){	
		cout<<"\nЕсли вы хотите вставить какой-либо элемент - введите 3"<<endl;
 		
 		cin>>vstav;
  		cin.ignore();
		c3=1;
	}
	if(vstav==3){
		srand(time(NULL)+arr[j]);
		forvstav=1+rand() % 99;
		file<<"\nВставить в дерево "<<forvstav<<" элемент и нарисовать дерево";
		
		BST* k = k->BuildBST(b, forvstav);
		answ<<"\nДерево перестроено c добавлением элемента:\n\n";
		printtree(k, 0, answ);
	}
	b = b->destroy(b);
	p = p->destroy(p);

}
file.close();
answ.close();
return 0;
}
