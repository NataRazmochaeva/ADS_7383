#include <ctype.h>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <cmath>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bst.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Input the data and press ENTER...\n");
    scene = new QGraphicsScene(this);
    QPixmap pixmap(ui->graphicsView->width(), ui->graphicsView->height());
    pixmap.fill(Qt::white);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

BST* MainWindow::copy_bst(BST* root, BST* cp_root=nullptr)
{
    if(root)
    {
        cp_root = new BST;
        cp_root->set_vl(root->value());
        if(root->left())
            cp_root->set_lf(copy_bst(root->left()));
        if(root->right())
            cp_root->set_rt(copy_bst(root->right()));
        cp_root->fix_size();
    }
    return cp_root;
}

void MainWindow::setPointsOfChildren(QPointF father, double offset, QPointF & pointLeft, QPointF & pointRight)
{
    if(!offset)
        offset=30;
    pointLeft.setX(father.x() - offset*4);
    pointLeft.setY(father.y() + 45);
    pointRight.setX(father.x() + offset*4);
    pointRight.setY(father.y() + 45);
}

void MainWindow::setPaintStyle(QPen & pen, QBrush & brush)
{
    pen.setColor(Qt::black);
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
}

void MainWindow::drawTree(QPointF point, BST* root, double offset, QPen pen, QBrush brush)
{
    if (!root) // если вершина пустой лист
        return;

    if (root->left() || root->right()) // если вершина не лист
    {
        QPointF newPointLeft;  // вершина левого поддерева
        QPointF newPointRight; // вершина правого поддерева
        setPointsOfChildren(point, offset, newPointLeft, newPointRight);

        if (root->left() != nullptr) // если левое поддерево не пусто, рисуем ребро к нему и повторяем
        {
            scene->addLine(point.x(), point.y(), newPointLeft.x(), newPointLeft.y(), pen);
            drawTree(newPointLeft, root->left(), offset / 2, pen, brush);
        }
        if (root->right() != nullptr) // если правое поддерево не пусто, рисуем ребро к нему и повторяем
        {
            scene->addLine(point.x(), point.y(), newPointRight.x(), newPointRight.y(), pen);
            drawTree(newPointRight, root->right(), offset / 2, pen, brush);
        }
        // отрисовка узла окружностью
        drawCircle(point, pen, brush);
        addItemOnScene(point, root);
        return;
    }

    // если вершина лист
    drawCircle(point, pen, brush);
    addItemOnScene(point, root);
}

void MainWindow::drawCircle(QPointF center, QPen pen, QBrush brush)
{
    QRectF rectangle;
    rectangle.setCoords(center.x() + 10, center.y() + 10, center.x() - 10, center.y() - 10);
    scene->addEllipse(rectangle, pen, brush);
}

void MainWindow::addItemOnScene(QPointF point, BST* root)
{
    // перерасчет точки для вывода значения узла, т.к. textItem задаст положение topLeft
    QPointF positionPoint;
    positionPoint.setX(point.x() - 7);
    positionPoint.setY(point.y() - 11);
    // преобразование содержимого узла в строку и добавление на scene
    QString data;
    data.append(root->value());
    QGraphicsTextItem *textItem = new QGraphicsTextItem(data);
    textItem->setPos(positionPoint);
    scene->addItem(textItem);
}

void MainWindow::set_scene()
{
    scene = new QGraphicsScene(this);
    QPixmap pixmap(ui->graphicsView->width(), ui->graphicsView->height());
    pixmap.fill(Qt::white);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);

    QPointF startPoint; // точка, откуда начнет выводиться дерево
    startPoint.setX((double)scene->width() / 2);
    startPoint.setY((double)scene->height() / 8);

    int diametr = 10; // диаметр окружности
    int height = root->size(); // высота дерева
    double offset = 2*(height - 2) * diametr;
    // настройка параметров отрисовки
    QPen pen;
    QBrush brush;
    setPaintStyle(pen, brush);

    drawTree(startPoint, root, offset, pen, brush);
}

void MainWindow::on_lineEdit_returnPressed()
{
    if(!arr.size())
    {
        str = ui->lineEdit->text();
        int i=0;
        while(i<str.size())
        {
            if(str[i].toLatin1()!=' ' && str[i].toLatin1()!='\n')
                arr.push_back(str[i].toLatin1());
            i++;
        }
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Success! Press 'Step in' to make a step.\n "
                                                                + "Press 'Step back' to return previous step.\n "
                                                                + "Press 'Step out' to built full tree.\n "
                                                                + "Press 'Reset' to start again.\n");
    }
    else
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + "First press 'Reset'.\n");
}

void MainWindow::on_pushButton_clicked()
{
    if(!arr.size())
    {
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Input first!\n");
        return;
    }

    if(counter<arr.size())
    {
        arr_pv_rts.push_back(copy_bst(root));
        if(!counter)
            root->set_vl(arr[counter]);
        else
            root->add_rand(arr[counter]);
        root->fix_size();
        counter++;
    }
    else
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Building finished!\n");
    set_scene();

}

void MainWindow::on_pushButton_2_clicked()
{
    if(!arr.size())
    {
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Input first!\n");
        return;
    }
    unsigned i = counter;
    if(i<arr.size())
        arr_pv_rts.push_back(copy_bst(root));

    for(; i<arr.size(); i++)
    {
        if(!i)
            root->set_vl(arr[i]);
        else
            root->add_rand(arr[i]);
    }
    root->fix_size();
    counter = i;
    ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Building finished!\n");
    set_scene();
}


void MainWindow::on_pushButton_3_clicked()
{
    if(!arr.size())
    {
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Input first!\n");
        return;
    }
    arr.clear();
    str.clear();
    if(root)
        delete root;
    root = new BST;
    counter = 0;
    scene->clear();
    ui->textBrowser->clear();
    ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Cleared! Input the data and press ENTER.\n");
}

void MainWindow::on_pushButton_4_clicked()
{
    scene->clear();
    if(!counter)
        return;
    else if(counter==1)
    {
        counter--;
        return;
    }
    else
        counter = arr_pv_rts.back()->size();

    root = arr_pv_rts.back();
    arr_pv_rts.pop_back();
    set_scene();
}
