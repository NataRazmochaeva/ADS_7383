#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <cctype>

using namespace std;
QString Qstr = "";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(ui->inputStr,SIGNAL(clicked()),this,SLOT(inputFromStr()));
    connect(ui->inputFile,SIGNAL(clicked()),this,SLOT(inputFromFile()));
    connect(ui->addKey,SIGNAL(clicked()),this,SLOT(addKey()));
    connect(ui->removeKey,SIGNAL(clicked()),this,SLOT(removeKey()));
}

MainWindow::~MainWindow(){
    delete ui;
}

node* treap = NULL;

void MainWindow::inputFromStr(){
    Qstr = ui->editStr->toPlainText();
    if (Qstr.isEmpty()){
        ui->treeEdit->setText("");
        ui->treapEdit->setText("");
        QMessageBox::warning(this, "Ошибка", "String is Empty!");
    }
    else {
        ui->treeEdit->setText("");
        ui->treapEdit->setText("");
        Calculate();
    }
}

void MainWindow::inputFromFile(){
    QString filename = QFileDialog::getOpenFileName(this,tr("Open file"),"C://Qt//build-kursovik-Dekstop_Qt_5_7_0_MinGW_32bit-Debug//","Text file (*.txt)");
    QFile file(filename.toStdString().data());
    if (!file.open(QIODevice::ReadOnly)){
        ui->treeEdit->setText("");
        ui->treapEdit->setText("");
        QMessageBox::warning(this, "Ошибка", "Can't open file!");
    }
    else{
        QTextStream in(&file);
        Qstr = in.readLine();
        file.close();
        ui->treeEdit->setText("");
        ui->treapEdit->setText("");
        Calculate();
    }
}


 node* rotateright(node* p){ // правый поворот вокруг узла p
     node* q = p->left;
     if( !q )
         return p;
     p->left = q->right;
     q->right = p;
     return q;
 }

 node* rotateleft(node* q){ // левый поворот вокруг узла q
     node* p = q->right;
     if( !p )
         return q;
     q->right = p->left;
     p->left = q;
     return p;
 }


 node* insert(int key, node* root){ // вставка
     if(!root) {
         node* p = new node(key);
         return (p);
     }
     if(key <= root->key){
         root->left = insert(key, root->left);
         if(root->left->prior < root->prior)
             root = rotateright(root);
     }
     else{
         root->right = insert(key, root->right);
         if(root->right->prior < root->prior)
             root = rotateleft(root);
     }
     return root;
 }
 void Delete(node* p){
     if(p==NULL)
         return;
     Delete(p->left);
     Delete(p->right);
     delete p;
 }

 node* merge(node *p, node *q){
     if (p == NULL) return q;
     if (q == NULL) return p;

     if (p->prior > q->prior){
         p->right = merge(p->right, q);
         return p;
     }
     else {
         q->left = merge(p, q->left);
         return q;
     }
 }

 node* remove(node* p, int k){ // удаление из дерева p первого найденного узла
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

 void printPriority(node* root,QString &tr){
    if (!root)
        return;
    char st[10],tm[10];
    tr = tr + "Key Priority [" + itoa(root->key,st,10) + "] - " + itoa(root->prior,tm,10) + "\n";
    printPriority(root->right,tr);
    printPriority(root->left,tr);
}

 node* findKey( node* tree, int key){
     if(!tree)
         return NULL;
     if(key == tree->key)
         return tree;
     if(key < tree->key)
         return findKey(tree->left, key);
     else
         return findKey(tree->right, key);
 }

 node* MainWindow::add(node* p, int el,QString &err){ // добавление нового элемент
     if (findKey(p,el)) {
         char st[10];
         err = err + "Key [" + itoa(el,st,10) + "] repeats" + "\n";
         return p;
     }
     else{
         p=insert(el, p);
         char st[10],tm[10];
         err = err + "Priority of a new key [" + itoa((findKey(p,el))->key,st,10) + "] - " + itoa((findKey(p,el))->prior,tm,10) + "\n";
         return p;
     }
 }

 void printtree(node* treenode, int l,QString &out){
     if(treenode==NULL) {
         for(int i = 0; i<l; ++i)
             out = out + "  ";
         return;
     }
     printtree(treenode->right, l+1,out);
     for(int i = 0; i < l; i++)
         out = out + "\t";
     char st[10];
     out = out + itoa(treenode->key,st,10) + "\n";
     printtree(treenode->left,l+1,out);
 }

void MainWindow::Calculate(){
        delete[] treap;
        treap = NULL;
        int c;
        if (Qstr.isEmpty()){
           QMessageBox::warning(this, "Ошибка", "String is Empty!");
           return;
        }
        string str = Qstr.toUtf8().constData();
        QString err;
        Qstr.clear();
        char* arr = new char[str.size()+1];
        strcpy(arr, str.c_str()); // запись строки в массив, который содержит последовательность символов с нулевым завершением
        char* tok;
        tok = strtok(arr, " "); // разделяем строку на цифры - ключи
        while(tok != NULL) {
           c = atoi(tok);      // конвертируем строку в величину типа int
           if(isalpha(*tok)){
               QMessageBox::warning(this, "Ошибка", "Uncorrect Data!");
                return;
           }
           if (findKey(treap,c) != NULL){
                 char st[10];
                 err = err + "Key [" + itoa(c,st,10) + "] repeats\n"; // повторение ключа не допустимо, тк должен быть уникальным
                 QMessageBox::warning(this, "Ошибка", err);
                 //ui->ErrorEdit->setText(err);
                 tok = strtok(NULL, " ");
                 continue;
             }
           treap = insert(c, treap);
           tok = strtok(NULL, " ");
        }
        QString tr = "";
        printPriority(treap,tr); // печать приоритетов
        ui->treeEdit->setText(tr);
        QString out = "";
        printtree(treap,0,out);
        ui->treapEdit->setText(out);
        delete tok;
        delete[] arr;
   }

void MainWindow::addKey(){
    if (treap == NULL){
        QMessageBox::warning(this, "Ошибка", "Treap is NULL!");
        return;
    }
    QString tmp = ui->addEdit->toPlainText();
    int flag=0;
    for (int i=0; i<tmp.size();i++){
    if (isalpha(tmp.toStdString()[i])){
        flag++;
    }
    }
    if (!flag) {
    int el = atoi(tmp.toStdString().data());
    QString err;
    treap = add(treap, el,err);
    QString out = "";
    printtree(treap,0,out);
    QString tr = "";
    printPriority(treap,tr); // печать приоритетов
    ui->treeEdit->setText(tr);
    ui->treapEdit->setText(out);
    }
    else QMessageBox::warning(this, "Ошибка", "Not a number!");
}
void MainWindow::removeKey(){
    if (treap == NULL){
        ui->treapEdit->setText("Treap is NULL");
        return;
    }
    QString tmp = ui->removeEdit->toPlainText();
    int el = atoi(tmp.toStdString().data());
    treap = remove(treap, el);
    QString out = "";
    printtree(treap,0,out);
    ui->treapEdit->setText(out);
}
