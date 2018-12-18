#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <string>
#include <QThread>
#include "research_thread.h"

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

    void on_exit_clicked();

    void on_push_encode_clicked();

    void on_push_decode_clicked();

    void on_choose_decoded_file_clicked();

    void on_choose_encoded_file_clicked();

    void on_decoded_textChanged();

    void on_encoded_textChanged();

    void on_research_clicked();

    void on_actionAbout_triggered();

    void on_actionTechnical_information_triggered();

    void on_actionManual_triggered();

    void done();

private:
    bool check = false;
    std::string encoded_text;
    std::string decoded_text;
    Ui::MainWindow *ui;
    QThread thread;
    research_thread new_thread;

};

#endif // MAINWINDOW_H
