#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "task.h"
#include "coding.h"
#include "opendialog.h"
#include <vector>
#include <set>
#include <fstream>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->FreqTable->setRowCount(1);
    ui->FreqTable->setColumnCount(2);
    QColor color;
    color.setRgb(239, 234, 234);
    /*for(int i=1; i<10; ++i){
        ui->FreqTable->setItem(i, 0, new QTableWidgetItem());
        ui->FreqTable->item(i, 0)->setFlags(Qt::NoItemFlags);
        ui->FreqTable->item(i, 0)->setBackgroundColor(color);
        ui->FreqTable->setItem(i, 1, new QTableWidgetItem());
        ui->FreqTable->item(i, 1)->setFlags(Qt::NoItemFlags);
        ui->FreqTable->item(i, 1)->setBackgroundColor(color);
    }*/
    ui->FreqTable->setHorizontalHeaderLabels(QStringList() << "Symbol" << "Frequency");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_FreqTableCheck_toggled(bool checked)
{
     ui->FreqTable->setEnabled(checked);
}

void MainWindow::on_FreqTable_cellChanged(int row, int column)
{
    auto item = ui->FreqTable->item(row, column);
    item->setTextAlignment(Qt::AlignCenter);
    if(item->text().length() == 0){
        if(ui->FreqTable->item(row+1, column) != nullptr){
            ui->FreqTable->setRowCount(row+1);
            /*QColor color;
            color.setRgb(239, 234, 234);
            for(int i=1; i<ui->FreqTable->rowCount()-row; ++i){
                ui->FreqTable->item(row+i, 0)->setFlags(Qt::NoItemFlags);
                ui->FreqTable->item(row+i, 0)->setBackground(color);
                ui->FreqTable->item(row+i, 0)->setText(tr(""));
                ui->FreqTable->item(row+i, 1)->setFlags(Qt::NoItemFlags);
                ui->FreqTable->item(row+i, 1)->setBackground(color);
                ui->FreqTable->item(row+i, 1)->setText(tr(""));
            }*/
        }
        return;
    }
    if(column == 0){
        if(item->text().length() > 1){
            QMessageBox::information(this, tr("Isn't a character"), tr("There must be one character"));
            item->setText(tr(""));
            return;
        }
        else{
            for(int i=0; i<ui->FreqTable->rowCount(); ++i)
                if(ui->FreqTable->item(i, 0) != nullptr && row != i && ui->FreqTable->item(i, 0)->text().length() != 0 && ui->FreqTable->item(i,0)->text() == item->text()){
                    QMessageBox::information(this, tr("Already in table"), tr("This character is already in table"));
                    item->setText(tr(""));
                    return;
                }
        }
    }
    else{
        for(auto i : item->text().toStdString())
            if(!isdigit(i)){
                QMessageBox::information(this, tr("Not a number"),tr("Frequency must be a number"));
                item->setText(tr(""));
                return;
            }
    }
    if(ui->FreqTable->item(row, 1-column) != nullptr && ui->FreqTable->item(row, 1-column)->text().length() != 0){
        QColor color;
        color.setRgb(255, 255, 255);
        if(ui->FreqTable->item(row+1, 0) == nullptr){
            ui->FreqTable->setRowCount(row+2);
            ui->FreqTable->setItem(row+1, 0, new QTableWidgetItem());
            ui->FreqTable->setItem(row+1, 1, new QTableWidgetItem());
        }
        ui->FreqTable->item(row+1, 0)->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        ui->FreqTable->item(row+1, 0)->setBackground(color);
        ui->FreqTable->item(row+1, 1)->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        ui->FreqTable->item(row+1, 1)->setBackground(color);
    }
}

void MainWindow::on_encodingButton_clicked()
{
    ui->FreqTableCheck->setEnabled(true);
}

void MainWindow::on_decodingButton_clicked()
{
    if(!ui->FreqTableCheck->isChecked())
        ui->FreqTableCheck->toggle();
    ui->FreqTable->setEnabled(true);
    ui->FreqTableCheck->setEnabled(false);
}

void MainWindow::on_toFileButton_clicked(bool checked)
{
    if(checked){
        ofilename = QFileDialog::getOpenFileName(this, tr("Choose output file"), QDir::homePath(), "Text Files(*.txt);;All Files(*.*)").toStdString();
        ui->OutputFilename->setText(tr(ofilename.c_str()));
    }else ui->OutputFilename->setText(tr(""));
}

void MainWindow::on_randomButton_clicked()
{
    ui->InputLine->setEnabled(false);
}

void MainWindow::on_fromFileButton_clicked()
{
    ifilename = QFileDialog::getOpenFileName(this, tr("Choose input file"), QDir::homePath(), tr("Text files(*.txt);;All files(*.*)")).toStdString();
    ui->InputLine->setText(tr(ifilename.c_str()));
}

void MainWindow::on_fromKeyboardButton_clicked()
{
    message = QInputDialog::getText(this, tr("Enter "), tr("")).toStdString();
    for(auto it=message.begin(); it<message.end(); ++it)
        if(isspace(*it))
            message.erase(it);
    encoded = "";
    ui->InputLine->setText(tr(message.c_str()));
}

void MainWindow::on_createButton_clicked()
{
    Options options;
    options.isEncode = ui->encodingButton->isChecked();
    options.isHuffman = ui->HuffmanButton->isChecked();
    options.isTable = ui->FreqTableCheck->isChecked();
    if(ui->randomButton->isChecked()){
        encoded = "";
        message = "";
    }
    if(!options.isEncode){
        if(encoded == "")
            std::swap(message, encoded);
        for(auto c : encoded)
            if(c != '1' && c != '0'){
                QMessageBox::information(this, tr("Incorrect encoded message"), tr("Encoded string must contain only '1' and '0' characters"));
                return;
            }
    }

    std::vector<std::pair<int, char>> table;
    std::set<char> alphabet;
    auto freq = ui->FreqTable;
    if(options.isTable)
        for(int i=0; i<freq->rowCount(); ++i){
            if(!freq->item(i, 0) || !freq->item(i, 1) || freq->item(i, 0)->text() == tr("") || freq->item(i, 1)->text() == tr(""))
                continue;
            if(freq->item(i, 0)->text() != "" && freq->item(i, 1)->text() != "" && alphabet.find(freq->item(i, 0)->text().toStdString()[0]) == alphabet.end()){
                table.push_back(std::make_pair(std::stoi(freq->item(i, 1)->text().toStdString()), freq->item(i,0)->text().toStdString()[0]));
                alphabet.insert(freq->item(i, 0)->text().toStdString()[0]);
            }
        }
    if(options.isTable && table.size() < 2){
        QMessageBox::information(this, QString("Incomplete table"), QString("Table must contain at least 2 symbols"));
        return;
    }
    if(ui->fromFileButton->isChecked()){
        std::filebuf file;
        if(file.open(ifilename, std::ios::in)){
            std::istream fin(&file);
            std::getline(fin, message);
        }else{
            QMessageBox::information(this, QString("File doesn't exist"), QString("File doesn't exist"));
            return;
        }
    }
    if(options.isTable && options.isEncode)
        for(auto c : message)
            if(alphabet.find(c) == alphabet.end()){
                QMessageBox::information(this, QString("Incomplete table"), QString("Message contains symbol that table doesn't contain"));
                return;
            }
    CodeTree*(*coding)(std::set<std::pair<int, char>>);
    if(options.isHuffman)
        coding = CodeTree::Huffman;
    else coding = CodeTree::ShannonFano;
    //QMessageBox::information(this, tr(message.c_str()), tr(encoded.c_str()));
    create_task(table, message, encoded, coding);
    std::string given, answer;
    if(options.isEncode){
        given = message;
        answer = encoded;
    }else{
        given = encoded;
        answer = message;
    }
    if(!ui->toFileButton->isChecked()){
        Dialog d(table, given, answer, options);
        d.show();
        d.exec();
    }
    else{
        std::filebuf file;
        if(file.open(ofilename, std::ios::out)){
            std::ostream fout(&file);
            std::string text;
            if(options.isEncode)
                text = "Кодирование ";
            else text = "Декодирование ";
            if(options.isHuffman)
                text += "Хаффмана";
            else text += "Шеннона-Фано";
            fout << text << std::endl;
            if(options.isTable){
                fout << "Дана таблица частот символов:" << std::endl;
                for(auto i : table)
                    fout << std::get<1>(i) << " " << std::get<0>(i) << std::endl;
            }

            if(options.isEncode)
                text = "Незакодированное сообщение:\n";
            else text = "Закодированное сообщение:\n";
            text += given;
            text += "\nAnswer: ";
            text += answer;
            fout << text;
            fout.flush();
            OpenDialog dialog(ofilename, this);
            dialog.show();
            dialog.exec();
        }else{
            QMessageBox::information(this, QString("File doesn't exist"), QString("File doesn't exist"));
            return;
        }
    }
    if(options.isEncode)
        encoded = "";
    else message = "";
}
