#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_FreqTableCheck_toggled(bool checked);

    void on_PlusButton_clicked();

    void on_MinusButton_clicked();

    void on_FreqTable_cellChanged(int row, int column);


    void on_encodingButton_clicked();

    void on_decodingButton_clicked();

    void on_createButton_clicked();

    void on_randomButton_clicked();

    void on_fromFileButton_clicked();

    void on_fromKeyboardButton_clicked();

    void on_toFileButton_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    std::string ifilename;
    std::string ofilename;
    std::string message;
    std::string encoded;
};

struct Options
{
    Options() {}
    bool isEncode;
    bool isHuffman;
    bool isTable;

};
#endif // MAINWINDOW_H
