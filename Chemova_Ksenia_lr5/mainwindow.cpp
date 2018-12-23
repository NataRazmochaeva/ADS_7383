#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
using namespace std;

Node* arr = NULL;
Elem* head = NULL;
int index = 0;
QString binary = "";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(ui->ChooseEncode,SIGNAL(clicked()),this,SLOT(ChooseANDencode()));
    connect(ui->PrintTree,SIGNAL(clicked()),this,SLOT(PrintTree()));
    connect(ui->on_close,SIGNAL(clicked()),this,SLOT(on_close()));
}

MainWindow::~MainWindow(){
    delete ui;
}

int cmp(const void* a,const void* b){
    return (*(Node*)b).num-(*(Node*)a).num;
}

void iteration (Elem** root){
    if (*root){
        iteration(&(*root)->left);
        iteration(&(*root)->right);
                free(*root);
    }
}

Elem* buildTree(QChar el){
    Elem* head = new Elem;
    head->c = el;
    head->parent = NULL;
    head->value = "";
    head->left = NULL;
    head->right = NULL;
    return head;
}

void SearchTree(Elem** t,Node* el,QString &branch,QString &fullBranch,int start,int end,QString &steps,QChar uzel,int &ind,int tab){
    char st[10];
    steps = steps + "Step " + itoa(ind++,st,10) + "  ";
    for (int i=0;i<tab;i++)
        steps = steps + "  ";
    for (int i = start;i<=end;i++){
        if (el[i].value == '\n')
            steps = steps + "\\n";
        else steps = steps + el[i].value;
    }
    steps = steps + "\n";
    if (*t == NULL){
        *t = new Elem;
        (*t)->parent = NULL;
        (*t)->left = NULL;
        (*t)->right = NULL;
        (*t)->value = "";
        (*t)->c = uzel;
    }
    double dS=0;
    int i,S=0;
    QString cBranch="";
    cBranch=fullBranch+branch;
    if (start==end)
    {
        (*t)->value += cBranch;
        (*t)->c = el[start].value;
        el[start].ptr = *t;
        return;
    }
    for (i=start;i<=end;i++)
        dS+=el[i].num;
    dS/=2.;
    i=start+1;
    S+=el[start].num;
    while (fabs(dS-(S+el[i].num))<fabs(dS-S) && (i<end))
    {
        S+=el[i].num;
        i++;
    }
    QChar o = '1';
    QChar z = '0';
    QString zero="0";
    QString one="1";
    SearchTree(&(*t)->left,el,one,cBranch,start,i-1,steps,o,ind,tab-6);
    SearchTree(&(*t)->right,el,zero,cBranch,i,end,steps,z,ind,tab+6);
}

void Encode(Node* arr,int index,QString copy,QString &binary){
    for (int i=0;copy[i]!='\0';i++){
        for (int j=0;j<index;j++){
            if (copy[i] == arr[j].value)
                binary += arr[j].ptr->value;
        }
    }
}

void print(Elem *t,QString &out,int count){
   if (t != NULL){
       print(t->left,out,count+1);
       for (int i = 0;i < count;i++)
           out = out + "   ";
       if (t->c == '\n')
           out = out + "[\\n]" + "   " + t->value + "\n";
       else if (t->c == ' ')
           out = out + "[' ']" + "   " + t->value + "\n";
       else out = out + "[" + t->c + "]   " + t->value + "\n";
       print(t->right,out,count+1);
   }
}

void MainWindow::MakeList(Elem* t){
    if (t == NULL){
        ui->ResultEdit->setText("Tree is empty");
    }
    else{
        QString tr;
        print(t,tr,0);
        ui->ResultEdit->setText(QString(tr.data()));
    }
}

void Decode(Node* arr,QString &answer,QString binary,int index){ //Декодирование дерева
    int len = 0;
    QString ptr = "";
    while (len <= binary.length()){
        ptr += binary[len++];
        for (int i = 0; i < index;i++){
            if(ptr == arr[i].ptr->value) {
                answer += arr[i].value;
                ptr.clear();
            }
        }
    }
}

void MainWindow::ChooseANDencode(){ //Кодирует дерево
    int k;
    QString str = "",copy = "",all = "";
    QString filename = QFileDialog::getOpenFileName(this,tr("Open file"),"D://lab5//text//","Text file (*.txt)");
    QFile file(filename.toStdString().data());
    if (!file.open(QIODevice::ReadOnly))
        ui->ResultEdit->setText("File can not be opened");
    else{
        free(arr);
        iteration(&head);
        head = NULL;
        binary.clear();
        ui->ResultEdit->clear();
        ui->BinaryEdit->clear();
        ui->CodesEdit->clear();
        ui->PreEdit->clear();
        index = 0;
        arr = (Node*) malloc(sizeof(Node));
        QTextStream in(&file);
        all = in.readLine();
        if (in.atEnd()){
            ui->ResultEdit->setText("File is empty");
            ui->BinaryEdit->setText("File is empty");
            ui->CodesEdit->setText("File is empty");
            ui->PreEdit->setText("File is empty");
            return;
        }
        int c=0;
        str += all + "\n";
        while (!in.atEnd()){
            all = in.readLine();
            str += all + "\n";
        }
        ui->PreEdit->setText(str);
        copy += str;
        for (int j=0;str[j] != '\0';j++){
            k = 0;
            for (int i=j+1;str[i] != '\0';i++){
                if (str[j] == str[i]){
                    while (str[j] == str[i]){
                        str.remove(i,1);
                        k++;
                    }
                }
            }
            k++;
            index++;
            arr = (Node*) realloc (arr,index*sizeof(Node));
            if (arr != NULL){
                arr[index-1].num = k;
                arr[index-1].value = str[j];
                arr[index-1].ptr = NULL;
            }
            else {
                free(arr);
                ui->ResultEdit->setText("Error with allocation");
                break;
            }
        }
        if (c != index){
            iteration(&head);
            head = NULL;
        }
        file.close();
        qsort(arr,index,sizeof(Node),cmp);
        int ind = 1;
        QChar sym = '.';
        QString a = "",b = "",symbols = "";
        ind = 1;
        int tab = 25;
        SearchTree(&head,arr,a,b,0,index-1,symbols,sym,ind,tab);
        ui->CodesEdit->setText(symbols);
        Encode(arr,index,copy,binary);
        if (binary.isEmpty())
            ui->BinaryEdit->setText("Binary is empty");
        else ui->BinaryEdit->setText(binary);
   }
}

void MainWindow::on_close(){
    this->close();
}

void MainWindow::PrintTree(){
    MakeList(head);
}
