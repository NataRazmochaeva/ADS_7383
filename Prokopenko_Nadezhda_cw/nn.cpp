#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

long long int maxc = pow(2,32);

struct node {          // структура для представления узлов дерева
    int key;           // ключ-значение
    long long prior;   // приоритет
    node* left;        // указатель на левое поддерево
    node* right;       // указатель на правое поддерево
    node(int k) {
        key = k;       // инициализация структуры
        left = right = NULL;
        prior = 1+rand() % 99; // рандомные числа от 0 до 2^32
    }
};

node* rotateright(node* p) { // правый поворот вокруг узла p
    node* q = p->left;
    if( !q )
        return p;
    p->left = q->right;
    q->right = p;
    return q;
}

node* rotateleft(node* q) { // левый поворот вокруг узла q
    node* p = q->right;
    if( !p )
        return q;
    q->right = p->left;
    p->left = q;
    return p;
}

node* insert(int key, node* root) { // вставка
    if(!root) {
        node* p = new node(key);
        return (p);
    }
    if(key <= root->key)
    {
        root->left = insert(key, root->left);
        if(root->left->prior < root->prior)
            root = rotateright(root);
    }
    else {
        root->right = insert(key, root->right);
        if(root->right->prior < root->prior)
            root = rotateleft(root);
    }
    return root;
}

node* find( node* tree, int key) {
    if(!tree)
        return NULL;
    if(key == tree->key)
        return tree;
    if(key < tree->key)
        return find(tree->left, key);
    else
        return find(tree->right, key);
}

node* Delete(node* p){
    if (left)
        delete p->left;
    if (right)
        delete p->right;
    delete p;
    return p = NULL;
}

node* merge(node *p, node *q) {
    if (p == NULL) return q;
    if (q == NULL) return p;

    if (p->prior > q->prior) {
        p->right = merge(p->right, q);
        return p;
    }
    else {
        q->left = merge(p, q->left);
        return q;
    }
}

node* remove(node* p, int k){ // удаление из дерева p первого найденного узла с ключом k
    if( !p )
        return p;
    if( p->key == k ) {
        node* q = merge(p->left,p->right);
        delete p;
        return q;
    }
    else if( k < p->key )
        p->left = remove(p->left,k);
    else
        p->right = remove(p->right,k);
    return p;
}

void printPriority(node* root,ofstream &file) {
    if (!root)
        return;
    file<<"\tПриоритет ключа["<<setw(5)<<right<< root->key <<"] - "<<setw(5)<<right<<root->prior<<endl;
    printPriority(root->right,file);
    printPriority(root->left,file);
}

void printtree(node* treenode, int l, ofstream &file) {
    if(treenode==NULL) {
        for(int i = 0; i<l; ++i)
            file<<"\t";
       file<<'#'<<endl;
        return;
    }
    printtree(treenode->right, l+1,file);
    for(int i = 0; i < l; i++)
        file << "\t";
    file << treenode->key<<endl;
    printtree(treenode->left,l+1,file);
}

int main() {
    node* treap = NULL; // пирамида поиска
    int call, j=0, i=0;
    int ch=0;
    int iskl=0, vstav=0;
    int vozr, foriskl, forvstav;
    ofstream file;
    file.open("1.txt");
    ofstream answ;
    answ.open("answ.txt");
	cout<<"Введите кол-во вариантов заданий"<<endl;
	cin>>call;
	if (!call)
		return 0;
    if (!ch){
        cout<<"\nВведите кол-во узлов пирамиды"<<endl;
          cin>>ch;
          cin.ignore();
          srand(ch);
      }
    while(call>j) {
          j++;
	int arr[ch];
	srand( time(0)+j );
  if (ch){
     if (iskl==0){
        cout<<"\nЕсли вы хотите задание с исключением какого-либо элекмента - введите 1"<<endl;
        cin>>iskl;
       }
     }
     if (vstav==0){
       cout<<"\nЕсли вы хотите задание с вставкой какого-либо элемент - введите 2"<<endl;
         cin>>vstav;
     }
	cout<<"\n\tПирамида #"<<j<<" сгенерирована"<<endl;
	for(i=0; i<ch; i++){
        arr[i]=1+rand() % 99;
    }
	file<<"\n\tВариант №"<<j;
    file<<"\nВаша случайная пирамида:\n";
	answ<<"__________________________________________________________\n";
	answ<<"\n\tВариант №"<<j;
	answ<<"\nИллюстрация сгенерированной пирамиды\n\n";
	for(i=0; i<ch; i++){
		if(find(treap,arr[i])){
            continue;
        }
        treap = insert(arr[i], treap);
	}
	printPriority(treap,file);
	printtree(treap,0,answ);
	if(iskl==1){
		foriskl=arr[0+rand() % ch];
		file<<"Исключить из пирамиды "<<foriskl<<" элемент и нарисовать пирамиду\n";
		treap = remove(treap, foriskl);
		answ<<"\nПирамида перестроена c исключением элемента: "<<foriskl<<"\n\n";
		printtree(treap, 0, answ);
	 }

	if(vstav==2){
		srand(time(NULL)+arr[j]);
		forvstav=1+rand() % 99;
		file<<"Вставить в пирамиду "<<forvstav<<" элемент и нарисовать пирамиду\n";
		treap = insert(forvstav, treap);
		answ<<"\nПирамида перестроена c добавлением элемента: "<<forvstav<<"\n\n";
		printtree(treap, 0, answ);
  	}
	treap = Delete(treap);
}
return 0;
}
