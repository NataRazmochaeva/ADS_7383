/* Функции Лосева */
#include "bst_interf.h"
#include "functions.h"

using namespace std;
using namespace losev_BST;


namespace losev_functions
{

	BST <int> *build_tree(string str)
	{
		int n;
		char* tok;
		BST <int> *b = NULL;

		char* arr = new char[str.size()+1];
		strcpy(arr, str.c_str());

		tok = strtok(arr, " ");
		
		while(tok){
			n = atoi(tok);
			if(b->find(b, n)){
				tok = strtok(NULL, " ");
			} // не добавляем число в дерево, если оно там уже есть
			if (tok){
				b = b->insertrandom(b, atoi(tok));
				tok = strtok(NULL, " ");
			} // проверка нужна, т.к. если число последовательности было пропущено, то после него может идти конец строки.
		}

		delete[] arr;

		return b;
	}

	void printtree(BST <int> *treenode, int l){
		if(treenode==NULL){
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




	void ascend_write_node(ofstream *outfile, BST <int> *tree)
	{
		if (tree == NULL)
			return;
		ascend_write_node(outfile, tree->Left(tree));
		(*outfile) << tree->Root(tree) << ' ';
		ascend_write_node(outfile, tree->Right(tree));
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
	void rand_init()
	{
		srand(time(NULL));
		// rand надо инициализировать, поскольку иначе он будет выдавать 
		// одну и ту же последовательность псевдослучайных чисел при каждом
		// запуске программы. rand инициализируется временем, потому что 
		// время в каждый момент времени различно, и поэтому последовательность
		// псевдослучайных чисел будет всегда различная.
	}
}
