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

    currentSelectedPath = "";

    ui->comboBoxRace->addItems(existingRaces);

    // Associate model to view
    model = new QDirModel();


    options = new QStandardItemModel();

    ui->viewOptions->setModel(options);
    ui->viewOptions->header()->hide();

    reg = new QStandardItemModel();

    ui->armyView->setModel(reg);

    models = new QStandardItemModel();
    ui->regimentView->setModel(models);

    setEnableChampionStats(false);
}

ArmyWindow::ArmyWindow(QString fileName)
{

}

ArmyWindow::~ArmyWindow()
{
    delete model;
    delete ma;
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
    options->clear();
    selectedModel = index;
    currentSelectedPath = model->filePath(index);

    QString name = index.data().toString();
    QStringList pieces = name.split(".");

    if(pieces.last() == "unit")
    {
        QString path(model->filePath(index));
        ma = fac.createFromFile(path);

        for(int i = 0 ; i < ma->getOptions().length() ; i++)
        {
            QList<QStandardItem *> newOption;

            newOption<<new QStandardItem(ma->getOptions()[i].getName())
                    <<new QStandardItem(QString::number(ma->getOptions()[i].getNbPoints()))
                   <<new QStandardItem(ma->getOptions()[i].getSpecialRules());

            options->appendRow(newOption);
        }
        ui->textInfo->clear();
        ui->textInfo->append(ma->displayStringInfo());
    }
}

void ArmyWindow::on_checkBoxChampion_toggled(bool checked)
{
    setEnableChampionStats(checked);
}

void ArmyWindow::setEnableChampionStats(bool checked)
{
    ui->lineEditA->setEnabled(checked);
    ui->lineEditCC->setEnabled(checked);
    ui->lineEditCdt->setEnabled(checked);
    ui->lineEditCT->setEnabled(checked);
    ui->lineEditE->setEnabled(checked);
    ui->lineEditF->setEnabled(checked);
    ui->lineEditI->setEnabled(checked);
    ui->lineEditM->setEnabled(checked);
    ui->lineEditPV->setEnabled(checked);
    ui->lineEditSvg->setEnabled(checked);
    ui->lineEditSvgInv->setEnabled(checked);
    ui->spinPoints->setEnabled(checked);
}

void ArmyWindow::clearRegimentDisplay()
{
    ui->checkBoxBanner->setChecked(false);
    ui->checkBoxChampion->setChecked(false);
    ui->checkBoxMusician->setChecked(false);
    ui->checkBoxSkirmish->setChecked(false);

    ui->lineEditA->clear();
    ui->lineEditCC->clear();
    ui->lineEditCdt->clear();
    ui->lineEditCT->clear();
    ui->lineEditE->clear();
    ui->lineEditF->clear();
    ui->lineEditI->clear();
    ui->lineEditM->clear();
    ui->lineEditPV->clear();
    ui->lineEditSvg->clear();
    ui->lineEditSvgInv->clear();
    ui->spinPoints->clear();
}

void ArmyWindow::on_addGroupButton_clicked()
{
    if(ui->spinBoxNB->value() != 0)
    {
        clearRegimentDisplay();
        RecruitsGroup rg(ui->spinBoxNB->value(),0,currentSelectedPath);

        //add group in the group list
        QList<QStandardItem *> newGroup;
        newGroup<<new QStandardItem(QString::number(rg.getNb()))
                <<new QStandardItem(rg.getModel()->getStats().getName())
                <<new QStandardItem(QString::number(rg.computePoints()))
               <<new QStandardItem(rg.getPath());
        models->appendRow(newGroup);
    }
    else
    {
        QMessageBox::warning(this, "Info", "Le nombre de modèles ajoutés doit être suppérieur à 0.");
    }
}

void ArmyWindow::on_addRegButton_clicked()
{
    RegimentAbstract ra;
    QString modelName;
    int sp = 0;

    QMap<QString, RecruitsGroup> groupMap;
    for(int i = 0; i< models->rowCount(); i++)
    {
        RecruitsGroup o;
        for(int j = 0; j < models->columnCount(); j++)
        {
            QStandardItem* item = models->item(i,j);
            switch(j)
            {
                case 0:
                    o.setNb(item->text().toUInt());
                    qDebug() << "nombre dans le groupe : " << item->text().toUInt();
                    sp += o.getNb();
                    break;
                case 1:
                    modelName = item->text();
                    break;
                case 3:
                    o.setPath(item->text());
                    break;
                default:
                    break;
            }
        }
        o.setCasualties(0);
        o.loadPath();
        groupMap.insert(modelName,o);
    }
    ra.setGroups(groupMap);
    ra.setBanner(ui->checkBoxBanner->isChecked());
    ra.setChampion(ui->checkBoxChampion->isChecked());
    ra.setSkirmishers(ui->checkBoxSkirmish->isChecked());
    ra.setStartingCount(sp);
    qDebug() << "on se rend tu fucking jusque la ??";
    ra.setName(ui->regName->text());
    qDebug() << "test a la con";
    qDebug() << ra.displayInfo();

    currentArmy.addUnit(ra);

    QList<QStandardItem *> newRegiment;
    newRegiment<<new QStandardItem(QString::number(ra.getStartingCount()))
            <<new QStandardItem(ra.getName())
            <<new QStandardItem(QString::number(ra.computePoints()));
    reg->appendRow(newRegiment);

    models->clear();
    ui->regName->clear();
    clearRegimentDisplay();
}
