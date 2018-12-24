#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QMainWindow>

using namespace std;

struct Elem{
    QChar c;
    QString value;
    Elem* parent;
    Elem* left;
    Elem* right;
};

struct Node{
    int num;
    Elem* ptr;
    QChar value;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void MakeList(Elem* t);

private slots:
    void ChooseANDencode();

    void on_close();

    void MakeDecode();

    void PrintTree();

    void PrintBinary();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
