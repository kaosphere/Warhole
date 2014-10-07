#include "gameconfiguratordialog.h"
#include "ui_gameconfiguratordialog.h"

GameConfiguratorDialog::GameConfiguratorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameConfiguratorDialog)
{
    ui->setupUi(this);
}

GameConfiguratorDialog::~GameConfiguratorDialog()
{
    delete ui;
    // Don't delete g, because it comes from the gamewindow, and
    // must stay allocated
}

Game *GameConfiguratorDialog::getG() const
{
    return g;
}

void GameConfiguratorDialog::setG(Game *value)
{
    g = value;
}

void GameConfiguratorDialog::on_buttonBox_accepted()
{
    if(g)
    {
        g->setName(ui->lineEdit->text());
        g->setMe(ui->lineEditNickName->text() + "_SERVER");
        g->setInformation(ui->textEdit->toPlainText());
        g->setSpectators(ui->checkBox->isChecked());
        g->setPlayerNumber(ui->spinBoxPlayerNb->value());
        g->setPoints(ui->spinBoxPts->value());
    }
    // TODO error handling
}
