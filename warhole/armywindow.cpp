#include "armywindow.h"
#include "ui_armywindow.h"

using namespace QLogger;

const QString ArmyWindow::LOG_ID_INFO = "ArmyWindow_info";
const QString ArmyWindow::LOG_ID_TRACE = "ArmyWindow_trace";
const QString ArmyWindow::LOG_ID_WARN = "ArmyWindow_warm";
const QString ArmyWindow::LOG_ID_ERR = "ArmyWindow_err";

const QStringList ArmyWindow::OPTION_HEADER = QStringList()
                            << QObject::tr("Choisir")
                            << QObject::tr("Nom")
                            << QObject::tr("Pts")
                            << QObject::tr("Règles");

ArmyWindow::ArmyWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmyWindow)
{

    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    QLog_Info(LOG_ID_INFO, "ArmyWindow : Entering ArmyWindow by normal constructor.");
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
        QLog_Info(LOG_ID_INFO, "ArmyWindow() : No race found.");
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

    QLog_Info(LOG_ID_INFO, "ArmyWindow() : Entering ArmyWindow by loading constructor.");
    QLog_Info(LOG_ID_INFO, "ArmyWindow() : File name to load : " + fileName);

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
        QLog_Info(LOG_ID_INFO, "ArmyWindow() : No race found.");
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

    changeRace = false;
    editing = false;

    setEnableChampionStats(false);
    load(fileName);
}

ArmyWindow::~ArmyWindow()
{
    QLog_Info(LOG_ID_INFO, "~ArmyWindow() : Exiting ArmyWindow");
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
            QLog_Info(LOG_ID_INFO, "on_comboBoxRace_currentIndexChanged() : No Model found in race : " + raceDir);
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
            clearRegimentDisplay();
            QLog_Info(LOG_ID_INFO, "on_treeViewExistingModels_clicked() : Loading regiment with model : " + currentSelectedPath);
            RegimentAbstract r;
            RecruitsGroup rg(ui->spinBoxNB->value(),0,currentSelectedPath);
            r.addGroup(rg);
            loadRegimentInUI(r);
            QString type = currentSelectedPath.section('/',-2,-2);
            if(type == CAVALERY_STRING || type == INFANTERY_STRING || type == CHARRIOT_STRING)
                enableChampionUI(true);
            else
                enableChampionUI(false);
        }
    }
}

void ArmyWindow::on_checkBoxChampion_toggled(bool checked)
{
    setEnableChampionStats(checked);
    updateRegimentPoints();
}

void ArmyWindow::enableChampionUI(bool checked)
{
    ui->labelModelM2->setEnabled(checked);
    ui->labelModelWS2->setEnabled(checked);
    ui->labelModelBS2->setEnabled(checked);
    ui->labelModelS2->setEnabled(checked);
    ui->labelModelT2->setEnabled(checked);
    ui->labelModelW2->setEnabled(checked);
    ui->labelModelA2->setEnabled(checked);
    ui->labelModelI2->setEnabled(checked);
    ui->labelModelLd2->setEnabled(checked);
    ui->labelBannerPts->setEnabled(checked);
    ui->labelChampionPts->setEnabled(checked);
    ui->labelMusicianPts->setEnabled(checked);

    ui->checkBoxBanner->setEnabled(checked);
    ui->checkBoxChampion->setEnabled(checked);
    ui->checkBoxMusician->setEnabled(checked);
}

void ArmyWindow::setEnableChampionStats(bool checked)
{
    // called when champion check box is toggled
    ui->labelModelM2->setEnabled(checked);
    ui->labelModelWS2->setEnabled(checked);
    ui->labelModelBS2->setEnabled(checked);
    ui->labelModelS2->setEnabled(checked);
    ui->labelModelT2->setEnabled(checked);
    ui->labelModelW2->setEnabled(checked);
    ui->labelModelA2->setEnabled(checked);
    ui->labelModelI2->setEnabled(checked);
    ui->labelModelLd2->setEnabled(checked);
    ui->labelChampionPts->setEnabled(checked);
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
    ui->checkBoxChampion->setChecked(false);
    ui->checkBoxMusician->setChecked(false);
    ui->checkBoxSkirmish->setChecked(false);

    ui->labelModelM2->clear();
    ui->labelModelWS2->clear();
    ui->labelModelBS2->clear();
    ui->labelModelS2->clear();
    ui->labelModelT2->clear();
    ui->labelModelW2->clear();
    ui->labelModelA2->clear();
    ui->labelModelI2->clear();
    ui->labelModelLd2->clear();
    ui->labelBannerPts->clear();
    ui->labelChampionPts->clear();
    ui->labelMusicianPts->clear();

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
        newRegiment<<new QStandardItem(QString::number(currentArmy.getUnits()[i].computeTotalNb()))
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
        regiment.getGroups().first().getModel()->setBanner(ui->checkBoxBanner->isChecked());
        regiment.getGroups().first().getModel()->setChampion(ui->checkBoxChampion->isChecked());
        regiment.getGroups().first().getModel()->setMusician(ui->checkBoxMusician->isChecked());
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
        if (ui->checkBoxBanner->isChecked()) pts += ui->labelBannerPts->text().toUInt();
        if (ui->checkBoxChampion->isChecked()) pts += ui->labelChampionPts->text().toUInt();
        if (ui->checkBoxMusician->isChecked()) pts += ui->labelMusicianPts->text().toUInt();
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

    ui->labelChampionPts->setText(QString::number(regiment.getGroups().first().getModel()->getChampionStats().getPoints()));
    ui->labelModelM2->setText(regiment.getGroups().first().getModel()->getChampionStats().getM());
    ui->labelModelWS2->setText(regiment.getGroups().first().getModel()->getChampionStats().getWs());
    ui->labelModelBS2->setText(regiment.getGroups().first().getModel()->getChampionStats().getBs());
    ui->labelModelS2->setText(regiment.getGroups().first().getModel()->getChampionStats().getS());
    ui->labelModelT2->setText(regiment.getGroups().first().getModel()->getChampionStats().getT());
    ui->labelModelW2->setText(regiment.getGroups().first().getModel()->getChampionStats().getW());
    ui->labelModelA2->setText(regiment.getGroups().first().getModel()->getChampionStats().getA());
    ui->labelModelI2->setText(regiment.getGroups().first().getModel()->getChampionStats().getI());
    ui->labelModelLd2->setText(regiment.getGroups().first().getModel()->getChampionStats().getLd());

    ui->spinBoxNB->setValue(regiment.getGroups().first().getNb());
    ui->regName->setText(regiment.getName());
    ui->checkBoxBanner->setChecked(regiment.getGroups().first().getModel()->getBanner());
    ui->checkBoxChampion->setChecked(regiment.getGroups().first().getModel()->getChampion());
    ui->checkBoxMusician->setChecked(regiment.getGroups().first().getModel()->getMusician());
    ui->labelMusicianPts->setText(QString::number(regiment.getGroups().first().getModel()->getMusicianPoints()));
    ui->labelBannerPts->setText(QString::number(regiment.getGroups().first().getModel()->getBannerPoints()));
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
    //ui->labelBannerPts->setEnabled(checked);
    updateRegimentPoints();
}

void ArmyWindow::on_checkBoxMusician_toggled(bool checked)
{
    //ui->labelMusicianPts->setEnabled(checked);
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
    else
    {
        currentArmy.save(path);
        QLog_Info(LOG_ID_INFO, "save() : Saved army : " + path);
        QMessageBox::information(this, tr("Info"), tr("Armée sauvegardée avec succès."));
    }
}

void ArmyWindow::load(QString path)
{
    QLog_Info(LOG_ID_INFO, "load() : Loading army : " + path);
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
    else
    {
        QLog_Error(LOG_ID_INFO, "load() : The path is empyty");
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
