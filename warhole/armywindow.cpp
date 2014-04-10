#include "armywindow.h"
#include "ui_armywindow.h"

using namespace QLogger;

const QString ArmyWindow::LOG_ID_INFO = "ArmyWindow_info";
const QString ArmyWindow::LOG_ID_TRACE = "ArmyWindow_trace";
const QString ArmyWindow::LOG_ID_WARN = "ArmyWindow_warm";
const QString ArmyWindow::LOG_ID_ERR = "ArmyWindow_err";

ArmyWindow::ArmyWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmyWindow)
{

    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

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
         QMessageBox::warning(this, tr("Erreur"), tr("Aucune race existante ; commencez par créer des figurines"));
    }

    existingRaces.removeOne(".");
    existingRaces.removeOne("..");

    currentSelectedPath = "";

    ui->comboBoxRace->addItems(existingRaces);

    // Associate model to view
    model = new QDirModel();

    options = new QStandardItemModel();
    options->setHorizontalHeaderLabels(OPTION_HEADER);

    ui->viewOptions->setModel(options);
    // TODO : This is a hack to fix the fact that options rows are collapsable for an unknown readon
    // investigate and fix properly.
    ui->viewOptions->setItemsExpandable(false);
    ui->viewOptions->setRootIsDecorated(false);

    reg = new QStandardItemModel();

    ui->armyView->setModel(reg);

    models = new QStandardItemModel();
    ui->regimentView->setModel(models);

    ui->labelPointsArmy->setText("0");
    ui->spinBoxPtsBanner->setEnabled(false);
    ui->spinBoxPtsMusician->setEnabled(false);

    changeRace = true;

    setEnableChampionStats(false);
}

ArmyWindow::ArmyWindow(QString fileName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmyWindow)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

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
         QMessageBox::warning(this, tr("Erreur"), tr("Aucune race existante ; commencez par créer des figurines"));
    }

    existingRaces.removeOne(".");
    existingRaces.removeOne("..");

    currentSelectedPath = "";

    ui->comboBoxRace->addItems(existingRaces);

    // Associate model to view
    model = new QDirModel();


    options = new QStandardItemModel();

    options = new QStandardItemModel();
    options->setHorizontalHeaderLabels(OPTION_HEADER);

    ui->viewOptions->setModel(options);
    // TODO : This is a hack to fix the fact that options rows are collapsable for an unknown readon
    // investigate and fix properly.
    ui->viewOptions->setItemsExpandable(false);
    ui->viewOptions->setRootIsDecorated(false);

    reg = new QStandardItemModel();

    ui->armyView->setModel(reg);

    models = new QStandardItemModel();
    ui->regimentView->setModel(models);

    ui->labelPointsArmy->setText("0");
    ui->spinBoxPtsBanner->setEnabled(false);
    ui->spinBoxPtsMusician->setEnabled(false);

    changeRace = false;

    setEnableChampionStats(false);
    load(fileName);
}

ArmyWindow::~ArmyWindow()
{
    delete model;
    delete ma;
    delete ui;
}


void ArmyWindow::on_comboBoxRace_currentIndexChanged(const QString &raceDir)
{
    bool updateDir = true;
    if(reg->rowCount() > 0)
    {
        if(!changeRace)
        {
            changeRace = true;
            updateDir = true;
        }
        else
        {
            int rep = QMessageBox::question(this,tr("Race"),
                                        tr("Une armée ne peut se composer que d'une seule race. Voulez-vous changer de race ? (Attention, cela supprimera les régiments déjà ajoutés.)"),
                                        QMessageBox::Yes | QMessageBox::No);
            if (rep == QMessageBox::No)
            {
                QString s = currentArmy.getUnits().first().getGroups().first().getPath().section('/',-3,-3);
                changeRace = false;
                ui->comboBoxRace->setCurrentText(s);
                updateDir = false;
            }
            else if(rep == QMessageBox::Yes)
            {
                currentArmy.getUnits().clear();
                updateRegModel();
            }
        }
    }
    if(changeRace && updateDir)
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
             QMessageBox::warning(this, tr("Erreur"), tr("Aucune race existante ; commencez par créer des figurines"));
        }

        existingModels.removeOne(".");
        existingModels.removeOne("..");

        int i;
        for (i=4;i==model->columnCount();i++)
        {
             ui->treeViewExistingModels->hideColumn(i);
        }

        ui->treeViewExistingModels->setModel(model);
        ui->treeViewExistingModels->setRootIndex(model->index(MODEL_PATH + "/" + raceDir));
    }
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
            QStandardItem* checkBox = new QStandardItem(true);
            checkBox->setCheckable(true);

            newOption<< checkBox
                     << new QStandardItem(ma->getOptions()[i].getName())
                    <<new QStandardItem(QString::number(ma->getOptions()[i].getNbPoints()))
                   <<new QStandardItem(ma->getOptions()[i].getSpecialRules());

            options->appendRow(newOption);
        }
        options->setHorizontalHeaderLabels(OPTION_HEADER);
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
        QMessageBox::warning(this, tr("Info"), tr("Le nombre de modèles ajoutés doit être suppérieur à 0."));
    }
}

void ArmyWindow::updateGlobalArmyPoints()
{
    ui->labelPointsArmy->setText(QString::number(currentArmy.computePoints()));
}

void ArmyWindow::updateRegModel()
{
    reg->clear();
    for(int i=0; i<currentArmy.getUnits().size(); ++i)
    {
        QList<QStandardItem *> newRegiment;
        newRegiment<<new QStandardItem(QString::number(currentArmy.getUnits()[i].getStartingCount()))
                <<new QStandardItem(currentArmy.getUnits()[i].getName())
                <<new QStandardItem(QString::number(currentArmy.getUnits()[i].computePoints()));
        reg->appendRow(newRegiment);
    }
    updateGlobalArmyPoints();
}

void ArmyWindow::on_addRegButton_clicked()
{
    RegimentAbstract ra;
    QString modelName;
    int sp = 0;

    if(!models->rowCount())
    {
        QMessageBox::warning(this, tr("Info"), tr("Le régiment est vide, veuillez ajouter des modèles."));
    }
    else
    {
        QList<RecruitsGroup> group;
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
            group.append(o);
        }
        ra.setGroups(group);
        ra.setBanner(ui->checkBoxBanner->isChecked());
        if(ui->checkBoxBanner->isChecked())
            ra.setBannerPoints(ui->spinBoxPtsBanner->value());
        ra.setChampion(ui->checkBoxChampion->isChecked());
        ra.setMusician(ui->checkBoxMusician->isChecked());
        if(ui->checkBoxMusician->isChecked())
            ra.setMusicianPoints(ui->spinBoxPtsMusician->value());
        if(ui->checkBoxChampion->isChecked())
        {
            // Load champion stats
            ra.getChampionStats().setPoints(ui->spinPoints->value());
            ra.getChampionStats().setM(ui->lineEditM->text());
            ra.getChampionStats().setWs(ui->lineEditCC->text());
            ra.getChampionStats().setBs(ui->lineEditCT->text());
            ra.getChampionStats().setS(ui->lineEditF->text());
            ra.getChampionStats().setT(ui->lineEditE->text());
            ra.getChampionStats().setI(ui->lineEditI->text());
            ra.getChampionStats().setA(ui->lineEditA->text());
            ra.getChampionStats().setW(ui->lineEditPV->text());
            ra.getChampionStats().setLd(ui->lineEditCdt->text());
            ra.getChampionStats().setSvg(ui->lineEditSvg->text());
            ra.getChampionStats().setSvgInv(ui->lineEditSvgInv->text());
        }
        ra.setSkirmishers(ui->checkBoxSkirmish->isChecked());
        ra.setStartingCount(sp);
        ra.setName(ui->regName->text());

        currentArmy.addUnit(ra);

        updateRegModel();

        models->clear();
        ui->regName->clear();
        clearRegimentDisplay();
    }
}

void ArmyWindow::on_removeRegButton_clicked()
{
    QItemSelectionModel *selection = ui->armyView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    if(indexElementSelectionne.isValid())
    {
        int rep = QMessageBox::question(this,tr("Monture"),
                                        tr("Voulez-vous supprimer le régiment de l'armée ?"),
                                        QMessageBox::Yes | QMessageBox::No);
        if (rep == QMessageBox::No)
        {
        }
        else if(rep == QMessageBox::Yes)
        {
            currentArmy.getUnits().removeAt(indexElementSelectionne.row());
            updateRegModel();
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Info"), tr("Veuillez sélectionner un régiment a supprimer."));
    }
}

void ArmyWindow::loadRegimentInUI(RegimentAbstract r)
{
    ui->spinBoxNB->setValue(0);
    ui->regName->setText(r.getName());
    ui->checkBoxBanner->setChecked(r.getBanner());
    ui->checkBoxChampion->setChecked(r.getChampion());
    ui->checkBoxMusician->setChecked(r.getMusician());
    if(r.getMusician())
        ui->spinBoxPtsMusician->setValue(r.getMusicianPoints());
    if(r.getBanner())
        ui->spinBoxPtsBanner->setValue(r.getBannerPoints());
    ui->checkBoxSkirmish->setChecked(r.getSkirmishers());

    for(int i=0; i<r.getGroups().size(); ++i)
    {
        //add group in the group list
        QList<QStandardItem *> newGroup;
        newGroup<<new QStandardItem(QString::number(r.getGroups()[i].getNb()))
                <<new QStandardItem(r.getGroups()[i].getModel()->getStats().getName())
                <<new QStandardItem(QString::number(r.getGroups()[i].computePoints()))
               <<new QStandardItem(r.getGroups()[i].getPath());
        models->appendRow(newGroup);
    }

    if(r.getChampion())
    {
        ui->lineEditA->setText(r.getChampionStats().getA());
        ui->lineEditCC->setText(r.getChampionStats().getWs());
        ui->lineEditCdt->setText(r.getChampionStats().getLd());
        ui->lineEditCT->setText(r.getChampionStats().getBs());
        ui->lineEditE->setText(r.getChampionStats().getT());
        ui->lineEditF->setText(r.getChampionStats().getS());
        ui->lineEditI->setText(r.getChampionStats().getI());
        ui->lineEditM->setText(r.getChampionStats().getM());
        ui->lineEditPV->setText(r.getChampionStats().getW());
        ui->lineEditSvg->setText(r.getChampionStats().getSvg());
        ui->lineEditSvgInv->setText(r.getChampionStats().getSvgInv());
        ui->spinPoints->setValue(r.getChampionStats().getPoints());
    }
}

void ArmyWindow::on_editRegButton_clicked()
{
    RegimentAbstract ra;
    QItemSelectionModel *selection = ui->armyView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(indexElementSelectionne.isValid())
    {
        ra = currentArmy.getUnits()[indexElementSelectionne.row()];
        currentArmy.getUnits().removeAt(indexElementSelectionne.row());
        updateRegModel();

        loadRegimentInUI(ra);
    }
    else
    {
        QMessageBox::warning(this, tr("Info"), tr("Veuillez sélectionner un régiment a éditer."));
    }
}

void ArmyWindow::on_checkBoxBanner_toggled(bool checked)
{
    ui->spinBoxPtsBanner->setEnabled(checked);
}

void ArmyWindow::on_checkBoxMusician_toggled(bool checked)
{
    ui->spinBoxPtsMusician->setEnabled(checked);
}

void ArmyWindow::on_pushButtonDuplicate_clicked()
{
    RegimentAbstract ra;
    QItemSelectionModel *selection = ui->armyView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(indexElementSelectionne.isValid())
    {
        ra = currentArmy.getUnits()[indexElementSelectionne.row()];
        currentArmy.addUnit(ra);
        updateRegModel();
    }
    else
    {
        QMessageBox::warning(this, tr("Info"), tr("Veuillez sélectionner un régiment a dupliquer."));
    }
}

void ArmyWindow::on_pushButtonQuit_clicked()
{
    this->close();
    this->deleteLater();
}

void ArmyWindow::on_pushButtonSave_clicked()
{
    if(ui->lineEditName->text().isEmpty() ||
       reg->rowCount() == 0)
    {
        QMessageBox::warning(this, tr("Info"),
                tr("Vous devez donner un nom à l'armée et y ajouter des régiments."));
        return;
    }

    currentArmy.setName(ui->lineEditName->text());

    QString path = "armies/" + ui->comboBoxRace->itemText(ui->comboBoxRace->currentIndex()) +
            "/" + ui->lineEditName->text() +".army";

    QFile f;
    f.setFileName(path);

    if(f.exists())
    {
        int rep = QMessageBox::question(this,tr("Ecraser"),
                                        tr("Une armée avec le même nom existe déjà, voulez vous l'écraser?"),
                                        QMessageBox::Yes | QMessageBox::No);
        if (rep == QMessageBox::Yes)
        {
            currentArmy.save(path);
            QMessageBox::information(this, tr("Info"), tr("Armée sauvegardée avec succès."));
        }
        else if (rep == QMessageBox::No)
        {
            QMessageBox::critical(this, tr("Annulation"), tr("Sauvegarde annulée"));
        }
    }
    else{
        currentArmy.save(path);
        QMessageBox::information(this, tr("Info"), tr("Armée sauvegardée avec succès."));
    }
}

void ArmyWindow::load(QString path)
{
    if(!path.isEmpty())
    {
        currentArmy.load(path);
        QLog_Info(LOG_ID_INFO, "Army loaded : ");
        QLog_Info(LOG_ID_INFO, currentArmy.displayInfo());
        updateRegModel();

        QString s = path.section('/',-2,-2);
        ui->comboBoxRace->setCurrentText(s);
        ui->lineEditName->setText(currentArmy.getName());
    }
}

void ArmyWindow::on_pushButtonLoad_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Model"),
            "./armies", tr("Model files (*.army)"));

    load(fileName);
}

void ArmyWindow::on_pushButtonExport_clicked()
{
    currentArmy.setName(ui->lineEditName->text());
    QLog_Info(LOG_ID_INFO, "on_pushButtonExport_clicked : Exporting army to PDF file.");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Sauvegarde du fichier"), "./export.pdf", tr("fichiers pdf(*.pdf)"));

    if(PdfExporter::exportHtmlToPdfFile(fileName, currentArmy.getHtml()))
    {
        QMessageBox::information(this, tr("Info"), tr("PDF exporté avec succès."));
    }
    else
    {
        QMessageBox::warning(this, tr("Info"), tr("L'export du pdf a échoué. Vérifiez le nom du fichier."));
    }
}

void ArmyWindow::on_removeGroupButton_clicked()
{

}
