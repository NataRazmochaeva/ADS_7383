#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTableWidget>
#include "mainwindow.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(std::vector<std::pair<int, char>>, std::string given, std::string answer, Options options, QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_enterButton_clicked();

private:
    Ui::Dialog *ui;
    std::string answer;
};

#endif // DIALOG_H
