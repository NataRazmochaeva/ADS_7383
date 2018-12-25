#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "tree.h"
class SecondWindow;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton2_clicked();

    void on_pushButton_3_clicked();

    void on_label_2_linkActivated();

    void print(BST*, int);

    void printlevel(BST*, int);

    void infix(BST*);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
    void plot();
    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    SecondWindow *window;
    int k;
};


#endif // MAINWINDOW_H
