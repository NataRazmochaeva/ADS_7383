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

struct Huff{
    int num;
    Elem* ptr;
    QString val;
    QString code;
};

class QueueEl{
    public:
    QChar symbol;
    int count;

    QueueEl(QChar s, int n) {
        symbol = s;
        count = n;
    }

    bool operator<(QueueEl t) const {
        if(count != t.count)
            return count < t.count;
        return symbol < t.symbol;
    }
};

class Nod{
    public:
    int count;
    QChar value;
    Nod* left, *right;

    Nod(Nod* l, Nod* r) {
        left = l;
        right = r;
        value = NULL;
        count = l->count + r->count;
    }

    Nod() {
        left = NULL;
        right = NULL;
        count = 0;
        value = NULL;
    }
    bool operator<(Nod* t) const {
            return count < t->count;
        }
    };

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void MakeList(Elem* t);
    void MakeHuffList(Nod* t);

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
