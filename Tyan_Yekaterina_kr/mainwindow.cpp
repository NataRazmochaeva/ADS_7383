#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstring>
#include <iostream>
#include <QTextStream>
#include <iostream>
#include <cctype>
#include <fstream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <ctime>
#include <stdlib.h>
#include <QtCharts>
#include <QLogValueAxis>

#define N 100

using namespace std;

typedef struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
}T;

T* root=NULL;
T* avl_tree=NULL;
string out_str="";

int num=0;
int *key_ptr=NULL;
int qnt_oper=0;

int imax(int a,int b){
    return (a-b>0) ? a : b;
}

void delete_avltree(T*tree){
    if(tree==NULL)
        return;
    delete_avltree(tree->left);
    delete_avltree(tree->right);
    delete(tree);
}

T *avltree_create(int key){
    T *node=new T;
    if (node != NULL) {
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->height = 0;
    }
    return node;
}

int avltree_height(T *tree){
    return (tree != NULL) ? tree->height : -1;
}

T *avltree_right_rotate(T *tree){
    //qnt_oper=qnt_oper+1;
    T *left;
    left = tree->left;
    tree->left = left->right;
    left->right = tree;
    tree->height = imax(avltree_height(tree->left),avltree_height(tree->right)) + 1;
    left->height = imax(avltree_height(left->left),tree->height) + 1;
    return left;
}

T*avltree_left_rotate(T*tree){
    //qnt_oper=qnt_oper+1;
    T *right;
    right = tree->right;
    tree->right = right->left;
    right->left = tree;
    tree->height = imax(avltree_height(tree->left),avltree_height(tree->right)) + 1;
    right->height = imax(avltree_height(right->right),tree->height) + 1;
    return right;
}

int avltree_balance(T *tree){
//    qnt_oper+=1;
    return ((avltree_height(tree->right) - avltree_height(tree->left)));
}

T* balance(T* tree){
    qnt_oper=qnt_oper+1;
    if(avltree_balance(tree) == 2){
        if(avltree_balance(tree->right)<0)
            tree->right=avltree_right_rotate(tree->right);
        return avltree_left_rotate(tree);
    }
    if(avltree_balance(tree)==-2){
        if(avltree_balance(tree->left)>0)
            tree->left=avltree_left_rotate(tree->left);
        return avltree_right_rotate(tree);
    }
    return tree;
}

T* avltree_add(T *&tree, int key,bool &flag){
    if (tree == NULL){
        return avltree_create(key);
    }
    if(key==tree->key){
        flag=false;
    }
    if (key < tree->key) {
        tree->left = avltree_add(tree->left,key,flag);
    }else if (key > tree->key) {
        tree->right = avltree_add(tree->right,key,flag);
    }
    tree->height = imax(avltree_height(tree->left),avltree_height(tree->right)) + 1;
    return balance(tree);
}

void outBT(T* b,int i,bool left, T* ptr,string& out_str){
    if (b!=NULL){
        outBT(b->right,i+4,true,b,out_str);
        if(ptr==NULL){
            for(int k=0;k<i;k++)
                out_str=out_str+" ";
            out_str=out_str+"---"+"(";
            out_str=out_str+to_string(b->key);
            out_str=out_str+")\n";
        }else if(left){
            for(int k=0;k<i;k++)
                out_str=out_str+" ";
            out_str=out_str+".---"+"(";
            out_str=out_str+to_string(b->key);
            out_str=out_str+")"+'\n';
        }else{
            for(int k=0;k<i;k++)
                out_str=out_str+" ";
            out_str=out_str+"`---"+"(";
            out_str=out_str+to_string(b->key);
            out_str=out_str+")\n";
        }
        outBT(b->left,i+4,false,b,out_str);
    }else
        return;
}

T* find_min(T*tree){
    return tree->left ? find_min(tree->left) : tree;
}

T* remove_min(T* tree){
    if(tree->left==NULL)
        return tree->right;
    tree->left=remove_min(tree->left);
    return balance(tree);
}

T* dele(T *&tree, int key){
    cout<<"key: "<<key<<endl;
    if (tree == NULL){
        return NULL;
    }
    qnt_oper+=1;cout<<"in dele: "<<qnt_oper<<endl;
    if(key==tree->key){
        T*q=tree->left;
        T*r=tree->right;
        delete tree;
        if(!r){
            return q;
        }
        T* min;
        min=find_min(tree->right);
        min->right=remove_min(r);
        min->left=q;
        return balance(min);
    }
    if (key < tree->key) {
        tree->left=dele(tree->left,key);
    }else if (key > tree->key) {
        tree->right=tree->right=dele(tree->right,key);
    }
    tree->height = imax(avltree_height(tree->left),avltree_height(tree->right)) + 1;
    return balance(tree);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString str_in;
    bool flag=true;
    int i=0,val=0;
    T* b=NULL;
    root=NULL;
    str_in = ui->lineEdit->text();
    char str[str_in.size()];
    strcpy(str,str_in.toLocal8Bit().constData());
    char * pch = strtok (str," ,");
    while (pch != NULL){
        val=atoi(pch);
        root=avltree_add(root,val,flag);
        if(flag==false){
            QString error;
            error=QString::number(val);
            error=error+"symbol exists. Add one more symbol.";
            ui->lineEdit_3->setText(error);
        }
        i++;
        pch = strtok (NULL, " ,.");
    }
    out_str="";
    out_str=out_str+"Built AVL-tree:";
    out_str=out_str+'\n';
    outBT(root,0,false,b,out_str);
    QString ostring=QString::fromStdString(out_str);
    if(root!=NULL)
        ui->lineEdit_2->setText(ostring);
    else
        ui->lineEdit_2->setText("AVL-tree is empty.");
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString filter="Text File (*.txt)";
    QString file_name = QFileDialog::getOpenFileName(this, "Считать дерево\n из файла", "/Users/user://",filter);
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"title","file not opened");
    }
    QTextStream in(&file);
    QString text=in.readAll();
    T* b=NULL;
    bool flag=true;
    int i=0,val=0;
    char str[text.size()];
    strcpy(str,text.toLocal8Bit().constData());
    char * pch = strtok (str," ,.");
    root=NULL;
    while (pch != NULL){
        val=atoi(pch);
        root=avltree_add(root,val,flag);
        if(flag==false){
            QString error;
            error=QString::number(val);
            error=error+" symbol exists. Add one more symbol.";
            ui->lineEdit_3->setText(error);
            flag=true;
        }
        i++;
        pch = strtok (NULL, " ,.");
    }
    out_str="";
    out_str=out_str+"Built AVL-tree:\n";
    outBT(root,0,false,b,out_str);
    QString ostring=QString::fromStdString(out_str);
    if(root!=NULL)
        ui->lineEdit_2->setText(ostring);
    else
        ui->lineEdit_2->setText("AVL-tree is empty.");
    file.close();
}

void generated_avl(int num,string& out_str){
    int val=0;
    T*b=NULL;
    bool flag=true;
    srand(time(NULL));
    int key_arr[num];
    for(int i=0;i<num;i++){
        val=rand()%99+1;
        key_arr[i]=val;
        root=avltree_add(root,val,flag);
        if(flag==false){
            i--;
            flag=true;
        }
    }
    key_ptr=key_arr;
    outBT(root,0,false,b,out_str);
    for(int i=0;i<num;i++){
        cout<<key_ptr[i]<<" ";
    }
    cout<<endl;
}

string create_gen_avl(){
    out_str="";
    out_str="Quantity of nodes: ";
    num=0;
    num=rand()% 99+1;
    out_str=out_str+to_string(num)+"\nBuilt AVL-tree:\n";
    generated_avl(num,out_str);
    return out_str;
}

void MainWindow::on_pushButton_3_clicked()
{
    delete_avltree(root);
    root=NULL;
    QString ostring=QString::fromStdString(create_gen_avl());
    if(root!=NULL)
        ui->lineEdit_2->setText(ostring);
    else
        ui->lineEdit_2->setText("AVL-tree is empty.");
}



void MainWindow::on_pushButton_4_clicked()
{
    int val;
    QString str_in= ui->lineEdit_4->text();
    val=str_in.toInt();
    QString a=QString::number(val);
    ui->lineEdit_3->setText(a);
    T*b=NULL;
    unsigned int start_time=clock();
    root=dele(root,val);
    unsigned int end_time=clock();
    double dif;
    dif=end_time-start_time;
    QString tim=QString::number(dif);
    ui->lineEdit_5->setText(tim);
    QString name="/Users/user/Desktop/output.txt";
    QFile fileout;
    fileout.setFileName(name);
    if(fileout.open(QIODevice::Append)){
        QTextStream stream( &fileout );
            stream << val<<" "<<tim << endl;
    }
    out_str="AVL-tree after deleting:\n";
    outBT(root,0,false,b,out_str);
    QString ostring=QString::fromStdString(out_str);
    if(root!=NULL)
        ui->lineEdit_2->setText(ostring);
    else
        ui->lineEdit_2->setText("AVL-tree is empty.");

    fileout.close();
    ui->lineEdit_4->clear();
}

void destroy_avl(T* tree, int** key_ptr,int& num1){
    if(tree==NULL){
        return;
    }
    destroy_avl(tree->left,key_ptr,num1);
    destroy_avl(tree->right,key_ptr,num1);
    if(num1!=0){
        (*key_ptr)[num1-1]= tree->key;
        num1--;
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    out_str="";
    QtCharts::QChart *chart=new QtCharts::QChart();
    QChartView* chartView=new QChartView(chart);
    QLineSeries* build=new QLineSeries();
    build->setName("Build AVL-tree");
    int* key_ptr = (int*)calloc(num,sizeof(int));
    int num1=num;
    int qnt_pred=0;
    destroy_avl(root,&key_ptr,num1);
    for(int i=num-1;i>=0;i--){
        qnt_pred=qnt_oper;
        qnt_oper=-1;
        root=dele(root,key_ptr[i]);
        build->append(i,qnt_oper);
    }

    chart->addSeries(build);
    chart->setTitle("Quantity of operations depending on numbers of nodes");
    QValueAxis* axisX=new QValueAxis;
    axisX->setLabelFormat("%d");
    axisX->setTitleText("Numbers of nodes");
    axisX->setRange(0,100);
    chart->addAxis(axisX,Qt::AlignBottom);
    build->attachAxis(axisX);

    QValueAxis* axisY=new QValueAxis();
    axisY->setLabelFormat("%d");
    axisY->setTitleText("Quantity of operations");
    axisY->setRange(0,15);
    chart->addAxis(axisY, Qt::AlignLeft);
    build->attachAxis(axisY);

    free(key_ptr);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,1000);
    chartView->show();
}
