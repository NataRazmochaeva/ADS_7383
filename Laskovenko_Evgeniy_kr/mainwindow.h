#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <vector>
#include "bst.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void drawTree(QPointF point, BST* root, double offset, QPen pen, QBrush brush); // отрисовывает дерево на сцене
    void drawCircle(QPointF center, QPen pen, QBrush brush);
    void addItemOnScene(QPointF point, BST* node);
    void setPointsOfChildren(QPointF father, double offset, QPointF &pointLeft, QPointF &pointRight);
    void setPaintStyle(QPen & pen, QBrush & brush);
    void set_scene();

    BST* copy_bst(BST* root, BST* cp_root);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_lineEdit_returnPressed();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow* ui;
    QGraphicsScene* scene;

    QString str;
    std::vector<char> arr;
    BST* root = new BST;
    std::vector<BST*> arr_pv_rts;
    unsigned counter = 0;
};

#endif // MAINWINDOW_H
