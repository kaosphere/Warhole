#include "backgroundselectiondialog.h"
#include "ui_backgroundselectiondialog.h"
#include <QMessageBox>

backGroundSelectionDialog::backGroundSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::backGroundSelectionDialog)
{
    ui->setupUi(this);

    setModal(true);
    setWindowTitle(tr("Selection de l'arrière plan"));

    model = new QStandardItemModel(this);

    ui->listView->setModel(model);
    ui->listView->setIconSize(QSize(64,64));
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStandardItem* grass = new QStandardItem(QIcon(":/tile/ressources/tiles/grass.png"),tr("Herbe"));
    QStandardItem* dirt = new QStandardItem(QIcon(":/tile/ressources/tiles/dirt.jpg"),tr("Terre"));
    QStandardItem* sand = new QStandardItem(QIcon(":/tile/ressources/tiles/sand.jpg"),tr("Sable"));
    QStandardItem* snow = new QStandardItem(QIcon(":/tile/ressources/tiles/snow.jpg"),tr("Neige"));
    QStandardItem* rock = new QStandardItem(QIcon(":/tile/ressources/tiles/rock.jpg"),tr("Roche"));

    model->appendRow(grass);
    model->appendRow(dirt);
    model->appendRow(sand);
    model->appendRow(snow);
    model->appendRow(rock);

    QModelIndex i = model->index(0,0);
    ui->listView->setCurrentIndex(i);
}

backGroundSelectionDialog::~backGroundSelectionDialog()
{
    delete ui;
}

int *backGroundSelectionDialog::getChoice() const
{
    return choice;
}

void backGroundSelectionDialog::setChoice(int *value)
{
    choice = value;
}

void backGroundSelectionDialog::accept()
{
    *choice = ui->listView->currentIndex().row();
    QDialog::accept();
}
