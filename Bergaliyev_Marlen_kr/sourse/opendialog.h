#ifndef OPENDIALOG_H
#define OPENDIALOG_H

#include <QDialog>

namespace Ui {
class OpenDialog;
}

class OpenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenDialog(std::string, QWidget *parent = 0);
    ~OpenDialog();

private slots:
    void on_openFileButton_clicked();

    void on_openDirButton_clicked();

private:
    Ui::OpenDialog *ui;
    std::string filepath;
};

#endif // OPENDIALOG_H
