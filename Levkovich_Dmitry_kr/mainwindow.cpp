#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "tree.h"
#include <QProcess>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QKeyEvent>
#include <windows.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include<QRegExpValidator>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <QtCharts/QtCharts>
#include <QLogValueAxis>
#include <QLineSeries>
#include <QValueAxis>
#include <QChart>
#include <QChartView>
#include <QChar>
#include <chrono>
QT_CHARTS_USE_NAMESPACE

using namespace std;

BST* tree = 0;
int numberTreeEl;
vector<int> values(numberTreeEl);

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
    if(tree!=nullptr){
        tree=tree->Delete(tree);
        tree==nullptr;
    }
    tree->random_init();
    QString str = ui->textEdit->toPlainText();
    for(int i = 0;i<str.size();i++){
        if(str[i].isDigit() || str[i].isSpace()){
            continue;
        }
        else{
            ui->textEdit->setText(ui->textEdit->toPlainText()+"\nincorrect input in " + QString::number(i+1)+"th position: "+"'"+str[i]+"'");
            ui->textEdit_2->clear();
            return;
        }
    }
    QStringList list = str.split(QRegExp("\\s"), QString::SkipEmptyParts);
    ui->comboBox->clear();
    for (int i=0; i<list.length(); i++)
    {
        QString x;
        x=list[i];

        if(!(tree->find(tree,x.toInt()))){
            ui->comboBox->addItem(x);
            tree = tree->insertrandom(tree, x.toInt());
            numberTreeEl= tree->counter(tree);
        }
    }
    ui->textEdit_2->clear();
    print(tree, 0);
}

void MainWindow::on_pushButton2_clicked()
{
    tree->random_init();
    srand(time(nullptr));
    int len = 10;
    vector<int> x(len);
    for(int i = 0;i<len;i++){
        x[i] = i;
    }
    random_shuffle(x.begin(),x.end());
    ui->textEdit->clear();
    for (int i=0; i < len; i++)
    {
        ui->textEdit->setText(ui->textEdit->toPlainText() + QString::number(x[i]) + " ");

    }

}

void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("kek"), QString(),
                tr("Text Files (*.txt)"));

        if (!fileName.isEmpty())
        {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly))
            {
                QMessageBox::critical(this, tr("lel"), tr("lal"));
                return;
            }
            QTextStream in(&file);
            ui->textEdit->setText(in.readAll());
            file.close();
        }

}

void MainWindow::on_pushButton_2_clicked()
{
    if(tree==nullptr){
        ui->label_3->setText("tree is empty\n");
        return;
    }
    tree->random_init();
    LARGE_INTEGER t1, t2, f;
    QueryPerformanceFrequency(&f);
    QString string = ui->comboBox->currentText();
    QString x = string;
    int y = x.toInt();
    QueryPerformanceCounter(&t1);
    tree = tree->remove(tree,y);
    QueryPerformanceCounter(&t2);
    numberTreeEl= tree->counter(tree);
    double dt =(t2.QuadPart-t1.QuadPart);
    int i = ui->comboBox->findText(x);
    ui->comboBox->removeItem(i);
    ui->label_3->setText("Vremya udaleniya elementa: " + QString::number(dt)+"\nKol-vo: "+QString::number(numberTreeEl)+" "+QString::number(tree->count()));
    tree->zero();
    ui->textEdit_2->clear();
    print(tree, 0);
    ui->textEdit->clear();
    infix(tree);
}

void MainWindow::print(BST* treenode, int l){
    if(treenode==nullptr){
        for(int i = 0;i<l;++i)
            ui->textEdit_2->setText(ui->textEdit_2->toPlainText() + "\t");
        ui->textEdit_2->setText(ui->textEdit_2->toPlainText() + "\r\n");
        return;
    }
    print(treenode->Right(treenode), l+1);
    for(int i = 0; i < l; i++)
        ui->textEdit_2->setText(ui->textEdit_2->toPlainText() + "\t");
    ui->textEdit_2->setText(ui->textEdit_2->toPlainText()+QString::number(treenode->Root(treenode)) + "\t");
    print(treenode->Left(treenode),l+1);
}

void MainWindow::infix(BST* b){
    if(b!=nullptr){

        infix(b->Left(b));
        ui->textEdit->setText(ui->textEdit->toPlainText() + QString::number(b->Root(b))+" ");
        infix(b->Right(b));

    }
}

int k = 0;

void MainWindow::printlevel(BST *t, int level) {
    if (t == nullptr) {
        // Если дерево пустое, то отображать нечего, выходим
        return;
    } else {
        printlevel(t->Left(t), level - 1);  // С помощью рекурсии посещаем левое поддерево
        if (level == 0) {
            // level будет равен нулю на нужной глубине, так как при каждом рекурсивном вызове значение level уменьшается на один
            this->k = t->Root(t);  // Показываем элемент, если он на нужном нам уровне
            return;
        }
        printlevel(t->Right(t), level - 1);  // С помощью рекурсии посещаем правое поддерево
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    int len = 10000;
    vector<int> x(len), w(len), q(len);
    QChart *chart = new QChart();
    QLineSeries *deleteEl = new QLineSeries();
    QLineSeries *insert = new QLineSeries();
    QLineSeries *delete1 = new QLineSeries();
    QLineSeries *insert1 = new QLineSeries();
    insert1->setName("Insert N");
    delete1->setName("remove N");
    for(int i = 0;i<len;i++)
        x[i] = i;
    random_shuffle(x.begin(),x.end());
    int ans1 = 0;
    int N = 0;
    for(int i = 0;i<len;i++){
        tree = tree->insertrandom(tree, x[i]);
        ans1 += tree->counter(tree);
        N =tree->count1();
        insert1->append(ans1, N);
    }
    ans1 = 0;
    N = 0;
    for(int i = 0;i<len;i++){
        tree=tree->remove(tree, x[i]);
        ans1 += tree->counter(tree);
        N = tree->count();

        delete1->append(ans1, N);


    }
    chart->addSeries(deleteEl);
    chart->addSeries(insert);
    chart->addSeries(insert1);
    chart->addSeries(delete1);
    chart->setTitle("plot iterations(N)");
    QValueAxis *axisX = new QValueAxis();
    axisX->setLabelFormat("%d");
    axisX->setTitleText("Number of elements");
    axisX->setRange(0, len);
    chart->addAxis(axisX, Qt::AlignBottom);
    deleteEl->attachAxis(axisX);
    insert->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("inerations");
    axisY->setLabelFormat("%lld");
    axisY->setRange(0, 1000000);
    chart->addAxis(axisY, Qt::AlignLeft);
    deleteEl->attachAxis(axisY);
    insert->attachAxis(axisY);
    QChartView* chartView = new QChartView(chart);
    chartView->resize(920, 600);
    chartView->show();
    plot();
}

void MainWindow::plot()
{
    int len = 10000;
    vector<int> x(len);
    QChart *chart = new QChart();
    QLineSeries *deleteEl = new QLineSeries;
    QLineSeries *insert = new QLineSeries();
    QLineSeries *delete1 = new QLineSeries();
    QLineSeries *insert1 = new QLineSeries();
    delete1->setName("Delete T");
    insert->setName("Insert T");
    for(int i = 0;i<len;i++)
        x[i] = i;
    random_shuffle(x.begin(),x.end());
    auto ans = 0;
    int ans1 = 0;
    for(int i = 0;i<len;i++){
        auto begin = std::chrono::steady_clock::now();
        tree = tree->insertrandom(tree, x[i]);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ns = ( std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count());
        ans += elapsed_ns;
        ans1 += tree->counter(tree);
            insert->append(ans1, 10*ans);
    }
    ans = 0;
    ans1 = 0;
    for(int i = 0;i<len;i++){
        auto begin = std::chrono::steady_clock::now();
        tree=tree->remove(tree, x[i]);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ns = ( std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count());
        ans += elapsed_ns;
        ans1 += tree->counter(tree);
            delete1->append(ans1, 10*ans);

    }
    chart->addSeries(deleteEl);
    chart->addSeries(insert);
    chart->addSeries(insert1);
    chart->addSeries(delete1);
    chart->setTitle("plot T(N)");
    QValueAxis *axisX = new QValueAxis();
    axisX->setLabelFormat("%d");
    axisX->setTitleText("Number of elements");
    axisX->setRange(0, len);
    chart->addAxis(axisX, Qt::AlignBottom);
    deleteEl->attachAxis(axisX);
    insert->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Time, mcs");
    axisY->setLabelFormat("%lld");
    axisY->setRange(0, 1000000);
    chart->addAxis(axisY, Qt::AlignLeft);
    deleteEl->attachAxis(axisY);
    insert->attachAxis(axisY);
    QChartView* chartView = new QChartView(chart);
    chartView->resize(920, 600);
    chartView->show();

}

void MainWindow::on_pushButton_5_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::on_pushButton_6_clicked()
{
    int h = tree->height(tree);
    printlevel(tree, h-1);
    tree->remove(tree, this->k);
    ui->label_4->setText(QString::number(k)+" "+QString::number(tree->count()));
    tree->zero();
    ui->textEdit_2->clear();
    print(tree, 0);
}
