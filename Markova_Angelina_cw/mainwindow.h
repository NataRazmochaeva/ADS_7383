#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <cmath>
#include <stdlib.h>
#include <QMainWindow>

struct node {          // структура для представления узлов дерева
    int key;           // ключ-значение
    long long prior;   // приоритет
    node* left;        // указатель на левое поддерево
    node* right;       // указатель на правое поддерево
    node(int k) {
        key = k;       // инициализация структуры
        left = right = NULL;
        prior = rand()%4294967296; // рандомные числа от 0 до 2^32
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
    node* add(node* p, int el,QString &err);
private slots:
    void inputFromStr();

    void inputFromFile();

    void Calculate();

    void addKey();

    void removeKey();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
