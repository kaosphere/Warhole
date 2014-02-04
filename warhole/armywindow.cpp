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


    options = new QStandardItemModel();

    ui->viewOptions->setModel(options);
    ui->viewOptions->header()->hide();

    reg = new QStandardItemModel();

    ui->viewRegiments->setModel(reg);
    ui->viewRegiments->header()->hide();

    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);
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
    scene->clear();
    options->clear();
    selectedModel = index;

    QString name = index.data().toString();
    QStringList pieces = name.split(".");

    if(pieces.last() == "unit")
    {
        QString path(model->filePath(index));
        ma = fac.create(index.parent().data().toString(), path);
    }

    for(int i = 0 ; i < ma->getOptions().length() ; i++)
    {
        QList<QStandardItem *> newOption;

        newOption<<new QStandardItem(ma->getOptions()[i].getName())
                <<new QStandardItem(QString::number(ma->getOptions()[i].getNbPoints()))
               <<new QStandardItem(ma->getOptions()[i].getSpecialRules());

        options->appendRow(newOption);
    }
    QPixmap p(ma->getUrlImage());
    scene->addPixmap(p);

}

void ArmyWindow::on_pushButton_clicked()
{
    //add the regiment to the army list
    QList<ModelAbstract*> l;
    StatsModel m;
    UnitAbstract* u = new UnitAbstract(ma->getStats().getName(),
                                       model->filePath(selectedModel),
                                       l,
                                       0,
                                       ui->checkBoxMusician->isChecked(),
                                       ui->checkBoxSkirmish->isChecked(),
                                       ui->checkBoxChampion->isChecked(),
                                       ui->checkBoxBanner->isChecked(),
                                       m,
                                       ui->spinBoxNB->value());

    QList<QStandardItem *> newRegiment;

    newRegiment<<new QStandardItem(QString::number(ui->spinBoxNB->value()))
            <<new QStandardItem(u->getName());

    reg->appendRow(newRegiment);
}
