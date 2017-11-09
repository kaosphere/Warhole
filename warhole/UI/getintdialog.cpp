#include "getintdialog.h"
#include "ui_getintdialog.h"

GetIntDialog::GetIntDialog(QString title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetIntDialog)
{
    ui->setupUi(this);
    ui->label->setText(title);
    setWindowTitle(title);
}

GetIntDialog::~GetIntDialog()
{
    delete ui;
}

void GetIntDialog::setNb(int *value)
{
    nb = value;
}

void GetIntDialog::accept()
{
    *nb = ui->spinBox->value();
    QDialog::accept();
}
