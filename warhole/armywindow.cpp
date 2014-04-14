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
    model = new QFileSystemModel(this);

    options = new QStandardItemModel();
    regOptions = new QStandardItemModel();

    connect(options,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(evaluateOptionsPoints()));
    connect(regOptions,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(evaluateRegimentOptionsPoints()));
    options->setHorizontalHeaderLabels(OPTION_HEADER);
    regOptions->setHorizontalHeaderLabels(OPTION_HEADER);

    ui->viewOptions->setModel(options);
    ui->viewOptions2->setModel(regOptions);
    // TODO : This is a hack to fix the fact that options rows are collapsable for an unknown readon
    // investigate and fix properly.
    ui->viewOptions->setItemsExpandable(false);
    ui->viewOptions->setRootIsDecorated(false);
    ui->viewOptions2->setItemsExpandable(false);
    ui->viewOptions2->setRootIsDecorated(false);

    reg = new QStandardItemModel();

    ui->armyView->setModel(reg);

    ui->labelPointsArmy->setText("0");
    ui->spinBoxPtsBanner->setEnabled(false);
    ui->spinBoxPtsMusician->setEnabled(false);

    changeRace = true;
    editing = false;

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
    model = new QFileSystemModel(this);

    options = new QStandardItemModel();
    options->setHorizontalHeaderLabels(OPTION_HEADER);

    regOptions = new QStandardItemModel();
    regOptions->setHorizontalHeaderLabels(OPTION_HEADER);

    ui->viewOptions->setModel(options);
    ui->viewOptions2->setModel(regOptions);
    // TODO : This is a hack to fix the fact that options rows are collapsable for an unknown readon
    // investigate and fix properly.
    ui->viewOptions->setItemsExpandable(false);
    ui->viewOptions->setRootIsDecorated(false);
    ui->viewOptions2->setItemsExpandable(false);
    ui->viewOptions2->setRootIsDecorated(false);

    reg = new QStandardItemModel();

    ui->armyView->setModel(reg);

    ui->labelPointsArmy->setText("0");
    ui->spinBoxPtsBanner->setEnabled(false);
    ui->spinBoxPtsMusician->setEnabled(false);

    changeRace = false;
    editing = false;

    setEnableChampionStats(false);
    load(fileName);
}

ArmyWindow::~ArmyWindow()
{
    delete model;
    delete options;
    delete regOptions;
    delete ma;
    delete ui;
}


void ArmyWindow::on_comboBoxRace_currentIndexChanged(const QString &raceDir)
{
    bool updateDir = true;
    if(reg->rowCount() > 0)
    {
        // The changeRace member prevents infinite loop when changing
        // race and saying no when confirming is asked
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
        // get list of existing models to verify if some exist
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

        // set the root path of the tree view
        ui->treeViewExistingModels->setModel(model);
        ui->treeViewExistingModels->setRootIndex(model->setRootPath(MODEL_PATH + "/" + raceDir));
        // hide size, type and date collumns
        ui->treeViewExistingModels->hideColumn(1);
        ui->treeViewExistingModels->hideColumn(2);
        ui->treeViewExistingModels->hideColumn(3);
    }
}


void ArmyWindow::on_treeViewExistingModels_clicked(const QModelIndex &index)
{
    QString name = index.data().toString();
    QStringList pieces = name.split(".");
    if(pieces.last() == "unit")
    {
        bool ok = true;
        // check if the user was currently editing a regiment
        if(editing)
        {
            int rep = QMessageBox::question(this,tr("Edition"),
                                        tr("Vous etes en train d'éditer un des régiments. Voulez vous charger une nouvelle figurine ? le régiment édité sera perdu. Sinon, ajoutez le régiment a l'armée."),
                                        QMessageBox::Yes | QMessageBox::No);
            if (rep == QMessageBox::No)
            {
                ok = false;
            }
            else if(rep == QMessageBox::Yes)
            {
                editing = false;
            }
        }
        if(ok)
        {
            currentSelectedPath = model->filePath(index);

            QStringList pieces = currentSelectedPath.split(".");
            if(pieces.last() == "unit")
            {
                clearRegimentDisplay();
                RegimentAbstract r;
                RecruitsGroup rg(ui->spinBoxNB->value(),0,currentSelectedPath);
                r.addGroup(rg);
                loadRegimentInUI(r);
            }
        }
    }
}

void ArmyWindow::on_checkBoxChampion_toggled(bool checked)
{
    setEnableChampionStats(checked);
    updateRegimentPoints();
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
    ui->regName->clear();
    ui->regPtsLabel->clear();
    ui->labelPointsOptions->clear();
    ui->labelPointsOptionsReg->clear();
    ui->modelNameLabel->clear();
    ui->modelPtsLabel->clear();
    ui->checkBoxBanner->setChecked(false);
    ui->spinBoxPtsBanner->clear();
    ui->checkBoxChampion->setChecked(false);
    ui->checkBoxMusician->setChecked(false);
    ui->spinBoxPtsMusician->clear();
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

    ui->labelModelM->clear();
    ui->labelModelWS->clear();
    ui->labelModelBS->clear();
    ui->labelModelS->clear();
    ui->labelModelT->clear();
    ui->labelModelW->clear();
    ui->labelModelA->clear();
    ui->labelModelI->clear();
    ui->labelModelLd->clear();

    options->clear();
    regOptions->clear();
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
    editing = false;
    if(currentSelectedPath.isEmpty())
    {
        QMessageBox::warning(this, tr("Info"), tr("Sélectionnez d'abord une figurine."));
    }
    else if(ui->regName->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Info"), tr("Veuillez donner un nom à votre régiment."));
    }
    else if(ui->spinBoxNB->value() == 0)
    {
        QMessageBox::warning(this, tr("Info"), tr("Le nombre de figurine doit etre supérieur à zéro."));
    }
    else
    {
        regiment.setBanner(ui->checkBoxBanner->isChecked());
        if(ui->checkBoxBanner->isChecked())
            regiment.setBannerPoints(ui->spinBoxPtsBanner->value());
        regiment.setChampion(ui->checkBoxChampion->isChecked());
        regiment.setMusician(ui->checkBoxMusician->isChecked());
        if(ui->checkBoxMusician->isChecked())
            regiment.setMusicianPoints(ui->spinBoxPtsMusician->value());
        if(ui->checkBoxChampion->isChecked())
        {
            // Load champion stats
            regiment.getChampionStats().setPoints(ui->spinPoints->value());
            regiment.getChampionStats().setM(ui->lineEditM->text());
            regiment.getChampionStats().setWs(ui->lineEditCC->text());
            regiment.getChampionStats().setBs(ui->lineEditCT->text());
            regiment.getChampionStats().setS(ui->lineEditF->text());
            regiment.getChampionStats().setT(ui->lineEditE->text());
            regiment.getChampionStats().setI(ui->lineEditI->text());
            regiment.getChampionStats().setA(ui->lineEditA->text());
            regiment.getChampionStats().setW(ui->lineEditPV->text());
            regiment.getChampionStats().setLd(ui->lineEditCdt->text());
            regiment.getChampionStats().setSvg(ui->lineEditSvg->text());
            regiment.getChampionStats().setSvgInv(ui->lineEditSvgInv->text());
        }
        regiment.setSkirmishers(ui->checkBoxSkirmish->isChecked());
        regiment.setStartingCount(regiment.getGroups().first().getNb());
        regiment.setName(ui->regName->text());

        regiment.getGroups().first().setNb(ui->spinBoxNB->value());

        regiment.getGroups()[0].getModel()->clearOptions();

        for(int i = 0; i< options->rowCount(); i++)
        {
            OptionModel o;
            for(int j = 0; j < options->columnCount(); j++)
            {
                QStandardItem* item = options->item(i,j);
                switch(j)
                {
                    case 0:
                        if(item->checkState() == Qt::Checked)
                            o.setActivated(true);
                        else
                            o.setActivated(false);
                        break;
                    case 1:
                        o.setName(item->text());
                        break;
                    case 2:
                        o.setNbPoints(item->text().toUInt());
                        break;
                    case 3:
                        o.setSpecialRules(item->text());
                        break;
                    default:
                        break;
                }
            }
            o.setRegimentOptions(false);
            regiment.getGroups().first().getModel()->addOption(o);
        }
        // treat regiment options separately
        for(int i = 0; i< regOptions->rowCount(); i++)
        {
            OptionModel o;
            for(int j = 0; j < regOptions->columnCount(); j++)
            {
                QStandardItem* item = regOptions->item(i,j);
                switch(j)
                {
                    case 0:
                        if(item->checkState() == Qt::Checked)
                            o.setActivated(true);
                        else
                            o.setActivated(false);
                        break;
                    case 1:
                        o.setName(item->text());
                        break;
                    case 2:
                        o.setNbPoints(item->text().toUInt());
                        break;
                    case 3:
                        o.setSpecialRules(item->text());
                        break;
                    default:
                        break;
                }
            }
            o.setRegimentOptions(true);
            regiment.getGroups().first().getModel()->addOption(o);
        }

        currentArmy.addUnit(regiment);

        updateRegModel();

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

void ArmyWindow::evaluateOptionsPoints()
{
    int pts = 0;
    for(int i = 0; i< options->rowCount(); i++)
    {
        if(options->item(i,0)->checkState() == Qt::Checked)
            pts+= options->item(i,2)->text().toUInt();
    }
    ui->labelPointsOptions->setText(QString::number(pts));

    updateRegimentPoints();
}

void ArmyWindow::evaluateRegimentOptionsPoints()
{
    int pts = 0;
    for(int i = 0; i< regOptions->rowCount(); i++)
    {
        if(regOptions->item(i,0)->checkState() == Qt::Checked)
            pts+= regOptions->item(i,2)->text().toUInt();
    }
    ui->labelPointsOptionsReg->setText(QString::number(pts));

    updateRegimentPoints();
}

void ArmyWindow::updateRegimentPoints()
{
    if(regiment.getGroups().size() > 0)
    {
        int pts = 0;
        pts += ui->spinBoxNB->value() * regiment.getGroups().first().getModel()->getStats().getPoints();
        if (ui->checkBoxBanner->isChecked()) pts += ui->spinBoxPtsBanner->value();
        if (ui->checkBoxChampion->isChecked()) pts += ui->spinPoints->value();
        if (ui->checkBoxMusician->isChecked()) pts += ui->spinBoxPtsMusician->value();
        pts += ui->spinBoxNB->value() * ui->labelPointsOptions->text().toUInt();
        pts += ui->labelPointsOptionsReg->text().toUInt();
        ui->regPtsLabel->setText(QString::number(pts));
    }
}

void ArmyWindow::loadRegimentInUI(RegimentAbstract& r)
{
    regiment = r;
    clearRegimentDisplay();

    ui->modelPtsLabel->setText(QString::number(regiment.getGroups().first().getModel()->getStats().getPoints()));
    ui->modelNameLabel->setText(regiment.getGroups().first().getModel()->getStats().getName());
    ui->labelModelM->setText(regiment.getGroups().first().getModel()->getStats().getM());
    ui->labelModelWS->setText(regiment.getGroups().first().getModel()->getStats().getWs());
    ui->labelModelBS->setText(regiment.getGroups().first().getModel()->getStats().getBs());
    ui->labelModelS->setText(regiment.getGroups().first().getModel()->getStats().getS());
    ui->labelModelT->setText(regiment.getGroups().first().getModel()->getStats().getT());
    ui->labelModelW->setText(regiment.getGroups().first().getModel()->getStats().getW());
    ui->labelModelA->setText(regiment.getGroups().first().getModel()->getStats().getA());
    ui->labelModelI->setText(regiment.getGroups().first().getModel()->getStats().getI());
    ui->labelModelLd->setText(regiment.getGroups().first().getModel()->getStats().getLd());

    ui->spinBoxNB->setValue(regiment.getGroups().first().getNb());
    ui->regName->setText(regiment.getName());
    ui->checkBoxBanner->setChecked(regiment.getBanner());
    ui->spinBoxPtsBanner->setValue(0);
    ui->checkBoxChampion->setChecked(regiment.getChampion());
    ui->checkBoxMusician->setChecked(regiment.getMusician());
    ui->spinBoxPtsMusician->setValue(0);
    if(regiment.getMusician())
        ui->spinBoxPtsMusician->setValue(regiment.getMusicianPoints());
    if(regiment.getBanner())
        ui->spinBoxPtsBanner->setValue(regiment.getBannerPoints());
    ui->checkBoxSkirmish->setChecked(regiment.getSkirmishers());

    for(int i = 0 ; i < regiment.getGroups().first().getModel()->getOptions().length() ; i++)
    {
        QList<QStandardItem *> newOption;
        QStandardItem* checkBox = new QStandardItem(true);
        checkBox->setCheckable(true);

        if(regiment.getGroups().first().getModel()->getOptions()[i].isActivated())
        {
            checkBox->setCheckState(Qt::Checked);
        }
        newOption<< checkBox
                 << new QStandardItem(regiment.getGroups().first().getModel()->getOptions()[i].getName())
                <<new QStandardItem(QString::number(regiment.getGroups().first().getModel()->getOptions()[i].getNbPoints()))
               <<new QStandardItem(regiment.getGroups().first().getModel()->getOptions()[i].getSpecialRules());
        if(regiment.getGroups().first().getModel()->getOptions()[i].isRegimentOptions())
            regOptions->appendRow(newOption);
        else
            options->appendRow(newOption);
    }
    options->setHorizontalHeaderLabels(OPTION_HEADER);
    regOptions->setHorizontalHeaderLabels(OPTION_HEADER);

    if(r.getChampion())
    {
        ui->lineEditA->setText(regiment.getChampionStats().getA());
        ui->lineEditCC->setText(regiment.getChampionStats().getWs());
        ui->lineEditCdt->setText(regiment.getChampionStats().getLd());
        ui->lineEditCT->setText(regiment.getChampionStats().getBs());
        ui->lineEditE->setText(regiment.getChampionStats().getT());
        ui->lineEditF->setText(regiment.getChampionStats().getS());
        ui->lineEditI->setText(regiment.getChampionStats().getI());
        ui->lineEditM->setText(regiment.getChampionStats().getM());
        ui->lineEditPV->setText(regiment.getChampionStats().getW());
        ui->lineEditSvg->setText(regiment.getChampionStats().getSvg());
        ui->lineEditSvgInv->setText(regiment.getChampionStats().getSvgInv());
        ui->spinPoints->setValue(regiment.getChampionStats().getPoints());
    }
    evaluateOptionsPoints();
    evaluateRegimentOptionsPoints();
}

void ArmyWindow::on_editRegButton_clicked()
{
    editing = true;
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
    updateRegimentPoints();
}

void ArmyWindow::on_checkBoxMusician_toggled(bool checked)
{
    ui->spinBoxPtsMusician->setEnabled(checked);
    updateRegimentPoints();
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



void ArmyWindow::on_spinBoxNB_valueChanged(int arg1)
{
    updateRegimentPoints();
}

void ArmyWindow::on_spinBoxPtsBanner_valueChanged(const QString &arg1)
{
    updateRegimentPoints();
}

void ArmyWindow::on_spinBoxPtsMusician_valueChanged(int arg1)
{
    updateRegimentPoints();
}

void ArmyWindow::on_spinPoints_valueChanged(const int &arg1)
{
    updateRegimentPoints();
}
