#include "connecttoserverdialog.h"
#include "ui_connecttoserverdialog.h"

ConnectToServerDialog::ConnectToServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectToServerDialog)
{
    ui->setupUi(this);
}

ConnectToServerDialog::~ConnectToServerDialog()
{
    delete ui;
}

void ConnectToServerDialog::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty() ||
            ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Pseudo"), tr("Veuillez remplir tous les champs"));
        return;
    }
    if(g)
    {
        g->setMe(ui->lineEdit->text());
        info->ip = ui->lineEdit_2->text();
        this->accept();
    }
}

void ConnectToServerDialog::on_pushButton_2_clicked()
{
    this->reject();
}

Game *ConnectToServerDialog::getG() const
{
    return g;
}

void ConnectToServerDialog::setG(Game *value)
{
    g = value;
}

ClientInfo *ConnectToServerDialog::getInfo() const
{
    return info;
}

void ConnectToServerDialog::setInfo(ClientInfo *value)
{
    info = value;
}
