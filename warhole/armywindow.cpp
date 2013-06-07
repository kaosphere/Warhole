#include "armywindow.h"
#include "ui_armywindow.h"

ArmyWindow::ArmyWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmyWindow)
{
    ui->setupUi(this);
}

ArmyWindow::ArmyWindow(QString fileName)
{

}

ArmyWindow::~ArmyWindow()
{
    delete ui;
}
