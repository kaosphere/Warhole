#include "magicalobjectwindow.h"
#include "ui_magicalobjectwindow.h"

MagicalObjectWindow::MagicalObjectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MagicalObjectWindow)
{
    ui->setupUi(this);
}

MagicalObjectWindow::~MagicalObjectWindow()
{
    delete ui;
}
