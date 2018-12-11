#include "opendialog.h"
#include "ui_opendialog.h"

OpenDialog::OpenDialog(std::string filepath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenDialog)
{
    ui->setupUi(this);
    this->filepath = filepath;
}

OpenDialog::~OpenDialog()
{
    delete ui;
}

void OpenDialog::on_openFileButton_clicked()
{
    std::string command("gedit ");
    command += filepath;
    system(command.c_str());
}

void OpenDialog::on_openDirButton_clicked()
{
    std::string command("nautilus ");
    command += filepath;
    system(command.c_str());
}
