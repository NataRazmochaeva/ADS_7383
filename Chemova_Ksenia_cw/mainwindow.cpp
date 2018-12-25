#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <list>
#include <QMessageBox>
using namespace std;

Node* arr = NULL;
Elem* head = NULL;
Nod* he = NULL;
int index = 0;
QString binary = "";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(ui->ChooseEncode,SIGNAL(clicked()),this,SLOT(ChooseANDencode()));
    connect(ui->MakeDecode,SIGNAL(clicked()),this,SLOT(MakeDecode()));
    //connect(ui->PrintTree,SIGNAL(clicked()),this,SLOT(PrintTree()));
    connect(ui->on_close,SIGNAL(clicked()),this,SLOT(on_close()));
}

MainWindow::~MainWindow(){
    delete ui;
}

bool compare_node(const Nod* first,const Nod* second){
    return first->count < second->count;
}

int cmp(const void* a,const void* b){
    return (*(Node*)b).num-(*(Node*)a).num;
}

int comp(const void* a,const void* b){
    if((*(Huff*)b).num == (*(Huff*)a).num){
        if ((*(Huff*)b).val.size() == (*(Huff*)a).val.size()){
            for (int i=0;i<(*(Huff*)b).val.size();i++){
                if ((*(Huff*)b).val[i] > (*(Huff*)a).val[0])
                    return -1;
                else if ((*(Huff*)b).val[i] < (*(Huff*)a).val[0])
                        return 1;
                     else continue;
            }
            return 0;
        }
        else return (*(Huff*)b).val.size() - (*(Huff*)a).val.size();
    }
    else return (*(Huff*)b).num-(*(Huff*)a).num;
}

void iteration(Elem** root){
    if (*root){
        iteration(&(*root)->left);
        iteration(&(*root)->right);
                free(*root);
    }
}
 void iteration1(Nod** root) {
     if (*root){
         iteration1(&(*root)->left);
         iteration1(&(*root)->right);
                 delete[] *root;
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

void FillTheTree(Elem* head, QString str,int &count){
    int deep = 0;

    for(unsigned int i = 1; i < str.size(); i++){
        if(str[i] == '('){
        deep++;
        }
        if(str[i] == ')'){
        deep--;
        }
        if(str[i] != '(' && str[i] != ')'){
            Elem* tree = head;
            for(int j = 1; j < deep; j++){
               if(tree->right == NULL){
                   tree = tree->left;
               } else {
                   tree = tree->right;
                   }
         }
        Elem* newElem = new Elem;
        if(tree->left == NULL){
            tree->left = newElem;
        }else {
            tree->right = newElem;
            }
        newElem->value = "";
        newElem->c = str[i];
        if (newElem->c == '1' || newElem->c == '0')
            count--;
        count++;
        newElem->left = NULL;
        newElem->right = NULL;
        }
    }
}

void Huffman(Elem* t,Huff* h,int i,QString &str,int ind,int cycle){
    char st[10];
    str = str + "Step " + itoa(ind++,st,9) + "   ";
    for (int m=0;m<cycle;m++){
        for (int j=0;j<h[m].val.size();j++){
            if ((h[m].val)[j] == '\n')
                str = str + "\\n";
            else str += (h[m].val)[j];
        }
        str = str + "(" + itoa(h[m].num,st,10) + ")     ";
    }
    str+="\n";
    if (i == 0){
        h[i].code = h[i].code + ".";
        return;
    }
    h[i+1].num = h[i].num;
    h[i+1].code.clear();
    h[i+1].code = h[i+1].code + "1";
    h[i+1].val.clear();
    h[i+1].val += h[i].val;
    h[i].num = h[i-1].num;
    h[i].code.clear();
    h[i].code = h[i].code + "0";
    h[i].val.clear();
    h[i].val = h[i-1].val;
    h[i-1].num = h[i].num + h[i+1].num;
    h[i-1].val += h[i+1].val;
    qsort(h,i,sizeof(Huff),comp);
    Huffman(t,h,i-1,str,ind,cycle-1);
}

void SearchTree(Elem** t,Node* el, QString &branch, QString &fullBranch, int start, int end,QString &steps,QChar uzel,int &ind,int tab){
    char st[10];
    steps = steps + "Step " + itoa(ind++,st,10) + "   ";
    for (int i=0;i<tab;i++)
        steps = steps + "   ";
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
    if (start==end){
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
    while (fabs(dS-(S+el[i].num))<fabs(dS-S) && (i<end)){
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
            if (copy[i] == arr[j].value){
                binary += arr[j].ptr->value;
            }
        }
    }
}

void print(Elem *t,QString &out,int count){
   if (t != NULL)   {
       print(t->left,out,count+1);
       for (int i = 0;i < count;i++)
           out = out + "   ";
       if (t->c == '\n')
           out = out + "[\\n]" + "   " + t->value + "\n";
       else out = out + "[" + t->c + "]   " + t->value + "\n";
       print(t->right,out,count+1);
   }
}

void print1(Nod *t,QString &out,int count,char uzel,QString code){
   if (t != NULL)   {
       if (t->left != NULL)
        t->value = uzel;
       uzel = '1';
       print1(t->left,out,count+1,uzel,code+"1");
       for (int i = 0;i < count;i++)
           out = out + "   ";
       if (t->value == '0' || t->value == '1'){
           out = out + "[" + t->value + "]" + "\n";
       }
       else if (t->value == '\n')
                out = out + "[\\n] " + code + "\n";
            else out = out + "[" + t->value + "] " + code + "\n";
       uzel = '0';
       print1(t->right,out,count+1,uzel,code+"0");
   }
}

void MainWindow::MakeHuffList(Nod* t){
    if (t == NULL){
        QMessageBox::warning(this, "Ошибка", "Tree is empty!");
    }
    else{
        QString tr;
        char uzel = '.';
        QString cod = "";
        print1(t,tr,0,uzel,cod);
        ui->HuffTree->setText(QString(tr.data()));
    }
}

void MainWindow::MakeList(Elem* t){
    if (t == NULL){
        QMessageBox::warning(this, "Ошибка", "Tree is empty!");
    }
    else{
        QString tr;
        print(t,tr,0);
        ui->ResultEdit->setText(QString(tr.data()));
    }
}

void Decode(Node* arr,QString &answer,QString binary,int index){
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

void MainWindow::ChooseANDencode(){
    int k;
    QString str = "",copy = "",all = "";
    QString filename = QFileDialog::getOpenFileName(this,tr("Open file"),"D://ADS//kursovik//texts","Text file (*.txt)");
    QFile file(filename.toStdString().data());
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, "Ошибка", "File can not be opened!");
    }
    else{
        free(arr);
        iteration(&head);
        head = NULL;
        iteration1(&he);
        he = NULL;
        binary.clear();
        ui->ResultEdit->clear();
        ui->BinaryEdit->clear();
        ui->CodesEdit->clear();
        ui->DecodeEdit->clear();
        ui->PreEdit->clear();
        index = 0;
        arr = (Node*) malloc(sizeof(Node));
        QTextStream in(&file);
        all = in.readLine();
        int c=0;
        str += all + "\n";
        while (!in.atEnd()){
            all = in.readLine();
            str += all + "\n";
        }
        if (str.size()==1 && (str[0]=='\n' || str[0] =='\0')){
            QMessageBox::warning(this, "Ошибка", "File is empty!");
            return;
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
                QMessageBox::warning(this, "Ошибка", "Error with allocation!");
                break;
            }
        }
        if (c != index){
            //ui->BinaryStroka->setText("Trees are not equal,deleting your tree...");
            iteration(&head);
            head = NULL;
        }
        file.close();
        qsort(arr,index,sizeof(Node),cmp);
        Huff* mass = NULL;
        mass = new Huff[2*index-1];
        for (int i = 0;i<index;i++){
            mass[i].num = arr[i].num;
            mass[i].val = arr[i].value;
        }
        QString hu;
        int ind = 1;
        list<QueueEl> queue;
        for (int i=0;i<index;i++) {
            queue.push_back(QueueEl(mass[i].val[0],mass[i].num));
        }
        queue.sort();
        list<QueueEl>::iterator q_it;
        list<Nod*>listNode;
        for (q_it = queue.begin(); q_it != queue.end(); q_it++) {
            Nod* p = new Nod;
            p->count = q_it->count;
            p->value = q_it->symbol;
            listNode.push_back(p);
        }
        while (listNode.size() > 1) {
            listNode.sort(compare_node);
            Nod* L = listNode.front();
            listNode.pop_front();
            Nod* R = listNode.front();
            listNode.pop_front();
            Nod* parent = new Nod(L, R);
            listNode.push_back(parent);
        }
        he = listNode.front();
        qsort(mass,index,sizeof(Huff),comp);
        Huffman(head,mass,index-1,hu,ind,index);
        QChar sym = '.';
        ui->HuffmanStep->setText(hu);
        delete[] mass;
        QString a = "",b = "",symbols = "";
        ind = 1;
        int tab = 25;
        SearchTree(&head,arr,a,b,0,index-1,symbols,sym,ind,tab);
        ui->CodesEdit->setText(symbols);
        Encode(arr,index,copy,binary);
        if (binary.isEmpty())
            QMessageBox::warning(this, "Ошибка", "Binary is empty!");
        else ui->BinaryEdit->setText(binary);
        PrintTree();
   }
}

void MainWindow::on_close(){
    this->close();
}

void MainWindow::MakeDecode(){
    if (index == 0){
        QMessageBox::warning(this, "Ошибка", "Choose file first!");
        return;
    }
    QString answer = "";
    Decode(arr,answer,binary,index);
    ui->DecodeEdit->setText(answer);
}

void MainWindow::PrintTree(){
    MakeList(head);
    MakeHuffList(he);
}
