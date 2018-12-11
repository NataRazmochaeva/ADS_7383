#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include <set>
#include <cstdlib>
#include <QMessageBox>

Dialog::Dialog(std::vector<std::pair<int, char>> table, std::string given, std::string answer, Options options, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->answer = answer;
    //QMessageBox::information(this, tr(given.c_str()), tr(answer.c_str()));
    if(options.isTable){
        ui->freqTableWidget->setHorizontalHeaderLabels(QStringList() << "Symbol" << "Frequency");
        ui->freqTableWidget->setColumnCount(2);
        ui->freqTableWidget->setRowCount(table.size());
        int j = 0;
        for(auto it : table){
            ui->freqTableWidget->setItem(j, 1, new QTableWidgetItem(QString(std::to_string(std::get<0>(it)).c_str())));
            ui->freqTableWidget->setItem(j, 0, new QTableWidgetItem(QString(std::string(1, std::get<1>(it)).c_str())));
            ui->freqTableWidget->item(j,0)->setTextAlignment(Qt::AlignCenter);
            ui->freqTableWidget->item(j,1)->setTextAlignment(Qt::AlignCenter);
            ++j;
        }
    }
    else ui->freqTableWidget->hide();
    std::string text;
    if(options.isEncode)
        text = "Кодирование ";
    else text = "Декодирование ";
    if(options.isHuffman)
        text += "Хаффмана\n";
    else text += "Шеннона-Фано\n";
    if(options.isTable)
        text += "Дана таблица частот символов. ";
    if(options.isEncode)
        text += "Незакодированное сообщение:\n";
    else text += "Закодированное сообщение:\n";
    text += given;
    text += "\n";

    ui->taskText->setText(QString(text.c_str()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_enterButton_clicked()
{
    if(answer == ui->InputLine->text().toStdString())
        QMessageBox::information(this, tr("Correct"), tr("Correct answer!"));
    else QMessageBox::information(this, tr("Incorrect"), tr("Incorrect answer!"));
}
