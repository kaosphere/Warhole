#include "armywindow.h"
#include "ui_armywindow.h"

ArmyWindow::ArmyWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmyWindow)
{
    // Put list of existing races in comboBox
    ui->setupUi(this);
    // get list of existing races
    QDir* modelDir = new QDir(MODEL_PATH);

    if (modelDir->exists())    
    {
        existingRaces = modelDir->entryList();
    }


    if(existingRaces.isEmpty())
    {
         QMessageBox::warning(this, "Erreur", "Aucune race existante ; commencez par créer des figurines");
    }

    existingRaces.removeOne(".");
    existingRaces.removeOne("..");

    ui->comboBoxRace->addItems(existingRaces);

    // Associate model to view
    model = new QDirModel();



}

ArmyWindow::ArmyWindow(QString fileName)
{

}

ArmyWindow::~ArmyWindow()
{
    delete ui;
}


void ArmyWindow::on_comboBoxRace_currentIndexChanged(const QString &raceDir)
{
    // get list of existing models
    QDir* modelDir = new QDir(MODEL_PATH + "/" + raceDir);
    QStringList existingModels;
    if (modelDir->exists())
    {
        existingModels = modelDir->entryList();
    }


    if(existingModels.isEmpty())
    {
         QMessageBox::warning(this, "Erreur", "Aucune race existante ; commencez par créer des figurines");
    }

    existingModels.removeOne(".");
    existingModels.removeOne("..");

    qDebug() << existingModels;

    int i;
    for (i=4;i==model->columnCount();i++)
    {
         ui->treeViewExistingModels->hideColumn(i);
    }

    ui->treeViewExistingModels->setModel(model);
    ui->treeViewExistingModels->setRootIndex(model->index(MODEL_PATH + "/" + raceDir));
}


void ArmyWindow::on_treeViewExistingModels_clicked(const QModelIndex &index)
{
    QString name = index.data().toString();
    QStringList pieces = name.split(".");

    if(pieces.last() == "unit")
    {
        QString path(model->filePath(index));
        ModelFactory fac;
        ModelAbstract* ma = fac.create(index.parent().data().toString(), path);
    }


}
