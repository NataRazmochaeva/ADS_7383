#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "huffmanstatic.h"
#include "huffmandynamic.h"
#include "shennonfano.h"
#include <QString>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <sstream>
#include <string>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QMainWindow::setFixedSize(1031, 611);
    ui->setupUi(this);
    ui->label_inp_file->setWordWrap(true);
    ui->label_out_file->setWordWrap(true);
    ui->label_inp_file->setText("Select a file to encode from");
    ui->label_out_file->setText("Select a file to decode from");
    ui->HS->setChecked(true);
    ui->abc_is_given->setChecked(true);

    connect(&thread, SIGNAL(started()), &new_thread, SLOT(run()), Qt::DirectConnection);
    connect(&new_thread, SIGNAL(finished()), this, SLOT(done()), Qt::DirectConnection);
    new_thread.moveToThread(&thread);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exit_clicked()
{
    exit(0);
}

void MainWindow::on_push_encode_clicked()
{
    for (auto c : decoded_text)
    {
        if ((unsigned int)c > 127)
        {
            ui->encoded->setPlainText("An error has occured!");
            return;
        }
    }
    check = true;
    std::stringstream ss;
    std::string str, abc;
    ss << decoded_text ;//<< '\0';
    if (ui->HS->isChecked())
    {
        HuffmanStatic<char>* hs = new HuffmanStatic<char>(ss, ui->abc_is_given->isChecked());
        abc = hs->abc;
        str = hs->encode(ss);
        if (!hs->success())
        {
            ui->encoded->setPlainText("An error has occured!");
            return;
        }
    }
    else if (ui->HD->isChecked())
    {
        HuffmanDynamic<char>* hd = new HuffmanDynamic<char>();
        str = hd->encode(ss);
    }
    else if (ui->SF->isChecked())
    {
        ShennonFano<char>* sf = new ShennonFano<char>(ss, ui->abc_is_given->isChecked());
        abc = sf->abc;
        str = sf->encode(ss);
        if (!sf->success())
        {
            ui->encoded->setPlainText("An error has occured!");
            return;
        }
    }
    encoded_text.clear();
    encoded_text = abc + str;
    QString s = QString::fromStdString(abc);
    for (uchar c : str)
    {
        s += QString::fromStdString(std::to_string(c));
        s += ' ';
    }
    ui->encoded->setPlainText(s);
    if (ui->checkBox->isChecked())
    {
        QString file = QFileDialog::getSaveFileName(this, "Choose a file", QDir::homePath());
        QFile f(file);
        f.open(QFile::ReadWrite);
        f.write(QString::fromStdString(encoded_text).toUtf8());
        f.close();
    }
    check = false;
}

void MainWindow::on_push_decode_clicked()
{
    check = true;
    std::stringstream ss;
    std::string str;
    encoded_text.erase(std::remove(encoded_text.begin(), encoded_text.end(), '\0'), encoded_text.end());
    ss << encoded_text ;//<< '\0';
    if (ui->HS->isChecked())
    {
        HuffmanStatic<char>* hs = new HuffmanStatic<char>(ss, true);
        str = hs->abc + hs->decode(ss);
        if (!hs->success())
        {
            ui->decoded->setPlainText("An error has occured!");
            return;
        }

    }
    else if (ui->HD->isChecked())
    {
        HuffmanDynamic<char>* hd = new HuffmanDynamic<char>();
        str = hd->decode(ss);
    }
    else if (ui->SF->isChecked())
    {
        ShennonFano<char>* sf = new ShennonFano<char>(ss, true);
        str = sf->abc + sf->decode(ss);
        if (!sf->success())
        {
            ui->decoded->setPlainText("An error has occured!");
            return;
        }
    }
    decoded_text.clear();
    decoded_text = str;
    ui->decoded->setPlainText(QString::fromStdString(str));
    if (ui->checkBox->isChecked())
    {
        QString file = QFileDialog::getSaveFileName(this, "Choose a file", QDir::homePath());
        QFile f(file);
        f.open(QFile::ReadWrite);
        f.write(QString::fromStdString(decoded_text).toUtf8());
        f.close();
    }
    check = false;
}

void MainWindow::on_choose_decoded_file_clicked()
{
    QString decoded_file = QFileDialog::getOpenFileName(this, "Choose a file", QDir::homePath(), "*.txt");
    if (decoded_file.length() > 0)
    {
        QFile file(decoded_file);
        file.open(QFile::ReadOnly);
        QString content = QString::fromUtf8(file.readAll());
        ui->decoded->setPlainText(content);
        file.close();
        ui->label_inp_file->setText(decoded_file);
    }
    else
        ui->label_inp_file->setText("Select a file to encode from");
}

void MainWindow::on_choose_encoded_file_clicked()
{
    QString encoded_file = QFileDialog::getOpenFileName(this, "Choose a file", QDir::homePath(), "*.txt");
    if (encoded_file.length() > 0)
    {
        QFile file(encoded_file);
        file.open(QFile::ReadOnly);
        QString content = QString::fromUtf8(file.readAll());
        ui->encoded ->setPlainText(content);
        file.close();
        ui->label_out_file->setText(encoded_file);
    }
    else
        ui->label_out_file->setText("Select a file to decode from");
}

void MainWindow::on_decoded_textChanged()
{
    if (!check)
    {
        std::string str = ui->decoded->toPlainText().toStdString();
        str.erase(std::remove(str.begin(), str.end(), '\0'), str.end());
        decoded_text = str;
    }
    check = false;
}

void MainWindow::on_encoded_textChanged()
{
    if (!check)
    {
        encoded_text = ui->encoded->toPlainText().toStdString();
    }
    check = false;
}

void MainWindow::on_research_clicked()
{
    ui->research->setEnabled(false);
    thread.start();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About the program"),
                           "<p>"
                           + tr("The program is made by <b>Roman Vlasov</b> as a course work in December 2018.")
                           + "<br><br>"
                           + tr("Version 1.0")
                           + "</p>");
}

void MainWindow::on_actionTechnical_information_triggered()
{
    QMessageBox::aboutQt(this, tr("Technical information"));
}

void MainWindow::on_actionManual_triggered()
{
    QMessageBox::about(this, "Manual",
            tr("<p><b>Q&A</b></p>")
            + tr("<p><b>")
            + tr("What can the program do?")
            + "</b><br>"
            + tr("The program provides encoding or decoding text files using Huffman static, Huffman dynamic or Shennon-Fano algorithms. ")
            + tr("The program also provides automatic comparison of the algorithms efficienty in different cathegories.")
            + "<br><br><b>"
            + tr("How to use the program?")
            + "</b><br>"
            + tr("Choose algorithm you want to use. ")
            + tr("Check the box whether you want to use your own alphabet or not. ")
            + tr("Check the box whether you want the result saved to a file and choose a file if you do.")
            + tr("Press encode to encode the text or decode to decode it.")
            + "<br><br><b>"
            + tr("Notes")
            + "</b><br>"
            + tr("The program works with latin characters only.<br>")
            + tr("Huffman static and Shennon-Fano algorithms use a given alphabet by default.")
                       + "</p>");
}

void MainWindow::done()
{
    ui->research->setEnabled(true);
}
