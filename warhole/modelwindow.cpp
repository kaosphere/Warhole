#include "modelwindow.h"
#include "ui_modelwindow.h"

using namespace QLogger;

const QString ModelWindow::LOG_ID_INFO = "ModelWindow_info";
const QString ModelWindow::LOG_ID_TRACE = "ModelWindow_trace";
const QString ModelWindow::LOG_ID_WARN = "ModelWindow_warm";
const QString ModelWindow::LOG_ID_ERR = "ModelWindow_err";

const QStringList ModelWindow::OPTION_HEADER = QStringList()
                            << QObject::tr("Nom")
                            << QObject::tr("Pts")
                            << QObject::tr("Règles");

ModelWindow::ModelWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelWindow)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    QLog_Info(LOG_ID_INFO, "ModelWindow() : entered model window with default constructor.");

    ui->setupUi(this);
    image = new QPixmap();
    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);

    options = new QStandardItemModel();
    regOptions = new QStandardItemModel();
    crew = new QStandardItemModel();

    QStringList modelList;
    modelList << CAVALERY_STRING << CHARACTER_STRING << CHARRIOT_STRING <<
    		     INFANTERY_STRING << MONSTER_STRING << WARMACHINE_STRING;
    ui->comboUnitType->addItems(modelList);

    ui->viewOptions->setModel(options);
    ui->viewOptions2->setModel(regOptions);
    options->setHorizontalHeaderLabels(OPTION_HEADER);
    regOptions->setHorizontalHeaderLabels(OPTION_HEADER);

    ui->viewModelCrew->setModel(crew);
    ui->viewModelCrew->header()->hide();

    loadInfanteryWidget();
}

ModelWindow::ModelWindow(QString f, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelWindow)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    QLog_Info(LOG_ID_INFO, "ModelWindow() : entered model window with loading constructor.");

    ui->setupUi(this);
    image = new QPixmap();

    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);

    options = new QStandardItemModel();
    regOptions = new QStandardItemModel();
    crew = new QStandardItemModel();

    QStringList modelList;
    modelList << CAVALERY_STRING << CHARACTER_STRING << CHARRIOT_STRING <<
    		     INFANTERY_STRING << MONSTER_STRING << WARMACHINE_STRING;
    ui->comboUnitType->addItems(modelList);

    ui->viewOptions->setModel(options);
    ui->viewOptions2->setModel(regOptions);
    options->setHorizontalHeaderLabels(OPTION_HEADER);
    regOptions->setHorizontalHeaderLabels(OPTION_HEADER);

    ui->viewModelCrew->setModel(crew);
    ui->viewModelCrew->header()->hide();

    loadInfanteryWidget();

    load(f);
}

ModelWindow::~ModelWindow()
{
    QLog_Info(LOG_ID_INFO, "~ModelWindow() : exited modelWindow.");
    delete poupik;

    delete crew;
    delete options;
    delete regOptions;
    delete scene;

    delete ui;
}

void ModelWindow::closeEvent (QCloseEvent *event)
{
    int rep = QMessageBox::question(this,tr("Quitter"),
            tr("Voulez-vous vraiment quitter ?"), QMessageBox::Yes | QMessageBox::No);
    if (rep == QMessageBox::Yes)
    {
        event->accept();
    }
    else if (rep == QMessageBox::No)
    {
        event->ignore();
    }
}

void ModelWindow::loadWidgets(bool l)
{
    ui->lineEditA2->setEnabled(l);
    ui->lineEditCC2->setEnabled(l);
    ui->lineEditCdt2->setEnabled(l);
    ui->lineEditCT2->setEnabled(l);
    ui->lineEditE2->setEnabled(l);
    ui->lineEditF2->setEnabled(l);
    ui->lineEditF2->setEnabled(l);
    ui->lineEditI2->setEnabled(l);
    ui->lineEditPV2->setEnabled(l);
    ui->lineEditSvgInv2->setEnabled(l);
    ui->lineEditSvg2->setEnabled(l);
    ui->lineEditM2->setEnabled(l);
    ui->lineEditName2->setEnabled(l);
    ui->lineEditPts2->setEnabled(l);

    ui->label_28->setEnabled(l);
    ui->label_54->setEnabled(l);
    ui->label_41->setEnabled(l);
    ui->label_42->setEnabled(l);
    ui->label_43->setEnabled(l);
    ui->label_44->setEnabled(l);
    ui->label_45->setEnabled(l);
    ui->label_46->setEnabled(l);
    ui->label_47->setEnabled(l);
    ui->label_48->setEnabled(l);
    ui->label_49->setEnabled(l);
    ui->label_50->setEnabled(l);
    ui->label_51->setEnabled(l);
    ui->label_66->setEnabled(l);
    ui->label_67->setEnabled(l);

    ui->pushButtonAdd->setEnabled(l);
    ui->pushButtonRmv->setEnabled(l);

    ui->viewModelCrew->setEnabled(l);
}

void ModelWindow::enableChampionUI(bool b)
{
    ui->label_56->setEnabled(b);
    ui->label_57->setEnabled(b);
    ui->label_58->setEnabled(b);
    ui->label_59->setEnabled(b);
    ui->label_60->setEnabled(b);
    ui->label_61->setEnabled(b);
    ui->label_62->setEnabled(b);
    ui->label_63->setEnabled(b);
    ui->label_64->setEnabled(b);
    ui->label_65->setEnabled(b);
    ui->label_68->setEnabled(b);
    ui->label_6->setEnabled(b);
    ui->label_73->setEnabled(b);

    ui->lineEditAChamp->setEnabled(b);
    ui->lineEditCCChamp->setEnabled(b);
    ui->lineEditCdtChamp->setEnabled(b);
    ui->lineEditCTChamp->setEnabled(b);
    ui->lineEditEChamp->setEnabled(b);
    ui->lineEditFChamp->setEnabled(b);
    ui->lineEditFChamp->setEnabled(b);
    ui->lineEditIChamp->setEnabled(b);
    ui->lineEditPVChamp->setEnabled(b);
    ui->lineEditSvgInvChamp->setEnabled(b);
    ui->lineEditSvgChamp->setEnabled(b);
    ui->lineEditMChamp->setEnabled(b);
    ui->spinPointsChamp->setEnabled(b);

    ui->spinBannerPoints->setEnabled(b);
    ui->spinMusicianPoints->setEnabled(b);
    ui->label_69->setEnabled(b);
    ui->label_70->setEnabled(b);
    ui->label_71->setEnabled(b);
    ui->label_72->setEnabled(b);
}

void ModelWindow::loadCavaleryWidget()
{
    //hide character checkboxes
    ui->checkGB->setEnabled(false);
    ui->checkGeneral->setEnabled(false);
    ui->checkLord->setEnabled(false);
    ui->checkMage->setEnabled(false);
    ui->checkMounted->setEnabled(false);

    ui->radioBase->setEnabled(true);
    ui->radioRare->setEnabled(true);
    ui->radioSpecial->setEnabled(true);

    ui->spinWidth->setValue(25);
    ui->spinLength->setValue(50);
    loadWidgets(true);
    enableChampionUI(true);
}

void ModelWindow::loadCharacterWidget()
{
    //character checkboxes
    ui->checkGB->setEnabled(true);
    ui->checkGeneral->setEnabled(true);
    ui->checkLord->setEnabled(true);
    ui->checkMage->setEnabled(true);
    ui->checkMounted->setEnabled(true);

    ui->spinWidth->setValue(25);
    ui->spinLength->setValue(25);

    ui->radioBase->setEnabled(false);
    ui->radioRare->setEnabled(false);
    ui->radioSpecial->setEnabled(false);

    loadWidgets(true);
    enableChampionUI(false);
}

void ModelWindow::loadCharriotWidget()
{
    //hide character checkboxes
    ui->checkGB->setEnabled(false);
    ui->checkGeneral->setEnabled(false);
    ui->checkLord->setEnabled(false);
    ui->checkMage->setEnabled(false);
    ui->checkMounted->setEnabled(false);

    ui->spinWidth->setValue(50);
    ui->spinLength->setValue(100);

    ui->radioBase->setEnabled(true);
    ui->radioRare->setEnabled(true);
    ui->radioSpecial->setEnabled(true);

    loadWidgets(true);
    enableChampionUI(true);
}

void ModelWindow::loadInfanteryWidget()
{
    //hide character checkboxes
    ui->checkGB->setEnabled(false);
    ui->checkGeneral->setEnabled(false);
    ui->checkLord->setEnabled(false);
    ui->checkMage->setEnabled(false);
    ui->checkMounted->setEnabled(false);

    ui->radioBase->setEnabled(true);
    ui->radioRare->setEnabled(true);
    ui->radioSpecial->setEnabled(true);

    ui->spinWidth->setValue(25);
    ui->spinLength->setValue(25);

    loadWidgets(false);
    enableChampionUI(true);
}

void ModelWindow::loadMonsterWidget()
{
    //hide character checkboxes
    ui->checkGB->setEnabled(false);
    ui->checkGeneral->setEnabled(false);
    ui->checkLord->setEnabled(false);
    ui->checkMage->setEnabled(false);
    ui->checkMounted->setEnabled(false);

    ui->radioBase->setEnabled(true);
    ui->radioRare->setEnabled(true);
    ui->radioSpecial->setEnabled(true);

    ui->spinWidth->setValue(50);
    ui->spinLength->setValue(50);

    loadWidgets(true);
    enableChampionUI(false);
}

void ModelWindow::loadWarMachineWidget()
{
    //hide character checkboxes
    ui->checkGB->setEnabled(false);
    ui->checkGeneral->setEnabled(false);
    ui->checkLord->setEnabled(false);
    ui->checkMage->setEnabled(false);
    ui->checkMounted->setEnabled(false);

    ui->radioBase->setEnabled(true);
    ui->radioRare->setEnabled(true);
    ui->radioSpecial->setEnabled(true);

    ui->spinWidth->setValue(25);
    ui->spinLength->setValue(25);

    loadWidgets(true);
    enableChampionUI(false);
}

void ModelWindow::on_comboUnitType_currentIndexChanged(int index)
{
    switch(index)
    {
    //TODO:replace numbers by type enum
        case 1:
            loadCavaleryWidget();
            break;
        case 2:
            loadCharacterWidget();
            break;
        case 3:
            loadCharriotWidget();
            break;
        case 4:
            loadInfanteryWidget();
            break;
        case 5:
            loadMonsterWidget();
            break;
        case 6:
            loadWarMachineWidget();
            break;
        default:
            break;
    }

}

void ModelWindow::on_toolButtonImage_pressed()
{
    QString fileName;

    fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir Image"),
                ".", tr("Fichiers images (*.png *.jpg *.bmp)"));
    ui->lineEditImage->setText(fileName);

    if(image->load(fileName))
    {
    	scene->clear();
    	scene->addPixmap(*image);
    }
    else
    {
        QMessageBox::warning(this, tr("Info"), tr("URL de l'image non valide"));
        QLog_Info(LOG_ID_INFO, "on_toolButtonImage_pressed() : invalid image with path : " + fileName);
    }

}

void ModelWindow::on_pushButtonCancel_clicked()
{
    this->close();
    this->deleteLater();
}

void ModelWindow::on_addOption_clicked()
{
    bool ok;
    //check if the point number for the option is an integer
    ui->lineEditOptionPts->text().toUInt(&ok);

    //save it if nbPoints is integer
    if(ok)
    {
        QList<QStandardItem *> newOption;

        newOption<<new QStandardItem(ui->lineOptionName->text())
                <<new QStandardItem(ui->lineEditOptionPts->text())
               <<new QStandardItem(ui->lineEditOptionSpec->text());

        options->appendRow(newOption);

        ui->lineOptionName->clear();
        ui->lineEditOptionPts->clear();
        ui->lineEditOptionSpec->clear();
    }
    //don't do anything if not
    else
    {
        QMessageBox::warning(this, tr("Erreur"), tr("Le nombre de point doit être un nombre entier."));
        QLog_Info(LOG_ID_INFO, "on_addOption_clicked() : integer needef for option point, got " + ui->lineEditOptionPts->text());
    }
}

void ModelWindow::on_addOption_2_clicked()
{
    bool ok;
    //check if the point number for the option is an integer
    ui->lineEditOptionPts2->text().toUInt(&ok);

    //save it if nbPoints is integer
    if(ok)
    {
        QList<QStandardItem *> newOption;

        newOption<<new QStandardItem(ui->lineOptionName2->text())
                <<new QStandardItem(ui->lineEditOptionPts2->text())
               <<new QStandardItem(ui->lineEditOptionSpec2->text());

        regOptions->appendRow(newOption);

        ui->lineOptionName2->clear();
        ui->lineEditOptionPts2->clear();
        ui->lineEditOptionSpec2->clear();
    }
    //don't do anything if not
    else
    {
        QMessageBox::warning(this, tr("Erreur"), tr("Le nombre de point doit être un nombre entier."));
        QLog_Info(LOG_ID_INFO, "on_addOption_2_clicked() : integer needef for option point, got " + ui->lineEditOptionPts2->text());
    }
}


void ModelWindow::on_deleteOption_clicked()
{
    QItemSelectionModel *selection = ui->viewOptions->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    options->removeRow(indexElementSelectionne.row());
}

void ModelWindow::on_deleteOption_2_clicked()
{
    QItemSelectionModel *selection = ui->viewOptions2->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    regOptions->removeRow(indexElementSelectionne.row());
}

void ModelWindow::on_pushButtonSave_clicked()
{
    //Slot where everything happens !
    //Create a Model depending on the type of model chosen
    //begin to check if everything is ok

    if(ui->lineEditName->text().isEmpty() ||
       ui->lineEditImage->text().isEmpty() ||
       ui->comboRace->currentIndex() == 0 ||
       ui->comboUnitType->currentIndex() == 0 )
    {
        QMessageBox::warning(this, tr("Info"),
                tr("Vous devez obligatoirement choisir une race, un type d'unité et remplir un nom et une image."));
        return;
    }
    // If any type was chosen, abort instead the model is a character because character don't have a type.
    if(!ui->radioBase->isChecked() &&
       !ui->radioRare->isChecked() &&
       !ui->radioSpecial->isChecked() &&
       ui->comboUnitType->itemText(ui->comboUnitType->currentIndex()) != CHARACTER_STRING)
    {
        QMessageBox::warning(this, tr("Info"), tr("Un type (base, special ou rare) doit être choisi."));
        return;
    }
    if(ui->comboUnitType->itemText(ui->comboUnitType->currentIndex()) == CAVALERY_STRING)
    {
        if(crew->rowCount() > 1 || crew->rowCount() == 0)
        {
            QMessageBox::warning(this, tr("Info"), tr("La figurine doit posséder obligatoirement une (seule) monture."));
            return;
        }
    }

    if(ui->comboUnitType->itemText(ui->comboUnitType->currentIndex()) == CHARACTER_STRING)
    {
        if(ui->checkMounted->isChecked() && crew->rowCount() == 0)
        {
            QMessageBox::warning(this, tr("Info"), tr("Vous avez spécifié que le personnage était monté, veuillez ajouter une monture, ou décocher la case \"Monté\""));
            return;
        }
        if(crew->rowCount() > 1)
        {
            QMessageBox::warning(this, tr("Info"), tr("La figurine doit posséder obligatoirement une seule monture."));
            return;
        }
        if(crew->rowCount()!=0 && !ui->checkMounted->isChecked())
        {
            // Check mounted checkbox is forgetten by user
            ui->checkMounted->setChecked(true);
        }
    }

    QString path = "models/" + ui->comboRace->itemText(ui->comboRace->currentIndex()) +
    		"/" + ui->comboUnitType->itemText(ui->comboUnitType->currentIndex()) +
    		"/" + ui->lineEditName->text() +".unit";

    QFile f;
    f.setFileName(path);

    if(f.exists())
    {
        int rep = QMessageBox::question(this,tr("Ecraser"),
                tr("La figurine existe déjà, voulez vous l'écraser?"), QMessageBox::Yes | QMessageBox::No);
        if (rep == QMessageBox::Yes)
        {
            save(path);
            QMessageBox::information(this, tr("Info"), tr("Figurine sauvegardée avec succès."));
        }
        else if (rep == QMessageBox::No)
        {
            QMessageBox::critical(this, tr("Annulation"), tr("Sauvegarde annulée"));
        }
    }
    else{
        save(path);
        QMessageBox::information(this, tr("Info"), tr("Figurine sauvegardée avec succès."));
    }
}

void ModelWindow::fillUI(ModelAbstract* m, QString path)
{
    QString type = path.section('/',-2,-2);
    QString race = path.section('/',-3,-3);

    ui->comboRace->setCurrentText(race);
    ui->comboUnitType->setCurrentText(type);

    ui->lineEditName->setText(m->getStats().getName());
    ui->spinPoints->setValue(m->getStats().getPoints());
    ui->lineEditM->setText(m->getStats().getM());
    ui->lineEditCC->setText(m->getStats().getWs());
    ui->lineEditCT->setText(m->getStats().getBs());
    ui->lineEditF->setText(m->getStats().getS());
    ui->lineEditE->setText(m->getStats().getT());
    ui->lineEditPV->setText(m->getStats().getW());
    ui->lineEditI->setText(m->getStats().getI());
    ui->lineEditA->setText(m->getStats().getA());
    ui->lineEditCdt->setText(m->getStats().getLd());
    ui->lineEditSvg->setText(m->getStats().getSvg());
    ui->lineEditSvgInv->setText(m->getStats().getSvgInv());
    ui->spinWidth->setValue(m->getSquareBaseW());
    ui->spinLength->setValue(m->getSquareBaseL());
    ui->spinPU->setValue(m->getUnitPower());
    ui->lineEditImage->setText(m->getUrlImage());

    if(image->load(m->getUrlImage()))
    {
    	scene->clear();
    	scene->addPixmap(*image);
    }
    else  QMessageBox::warning(this, tr("Info"), tr("URL de l'image non valide"));

    for(int i = 0 ; i < m->getOptions().length() ; i++)
    {
        QList<QStandardItem *> newOption;

        newOption<<new QStandardItem(m->getOptions()[i].getName())
                <<new QStandardItem(QString::number(m->getOptions()[i].getNbPoints()))
               <<new QStandardItem(m->getOptions()[i].getSpecialRules());
        if(m->getOptions()[i].isRegimentOptions())
            regOptions->appendRow(newOption);
        else
            options->appendRow(newOption);
    }
    //fill specifi UI data depending on model type
    if(type == CAVALERY_STRING)
    {
        ModelCavalry* cav = dynamic_cast<ModelCavalry*>(m);
        if (cav){
            QList<QStandardItem *> newCrew;
            newCrew<<new QStandardItem(cav->getMount().getName())
                    <<new QStandardItem(QString::number(cav->getMount().getPoints()))
                    <<new QStandardItem(cav->getMount().getM())
                    <<new QStandardItem(cav->getMount().getWs())
                    <<new QStandardItem(cav->getMount().getBs())
                    <<new QStandardItem(cav->getMount().getS())
                    <<new QStandardItem(cav->getMount().getT())
                    <<new QStandardItem(cav->getMount().getW())
                    <<new QStandardItem(cav->getMount().getI())
                    <<new QStandardItem(cav->getMount().getA())
                    <<new QStandardItem(cav->getMount().getLd())
                    <<new QStandardItem(cav->getMount().getSvg())
                    <<new QStandardItem(cav->getMount().getSvgInv());
            crew->appendRow(newCrew);
            ui->textEdit->append(cav->getSpecialRules());
            switch(cav->getType())
            {
            case BASE:
                ui->radioBase->setChecked(true);
                break;
            case SPECIAL:
                ui->radioSpecial->setChecked(true);
                break;
            case RARE:
                ui->radioRare->setChecked(true);
                break;
            default:
                QLog_Error(LOG_ID_ERR, "fillUI : can't find a valid type.");
                break;
            }
            ui->spinPointsChamp->setValue(cav->getChampionStats().getPoints());
            ui->lineEditMChamp->setText(cav->getChampionStats().getM());
            ui->lineEditCCChamp->setText(cav->getChampionStats().getWs());
            ui->lineEditCTChamp->setText(cav->getChampionStats().getBs());
            ui->lineEditFChamp->setText(cav->getChampionStats().getS());
            ui->lineEditEChamp->setText(cav->getChampionStats().getT());
            ui->lineEditPVChamp->setText(cav->getChampionStats().getW());
            ui->lineEditIChamp->setText(cav->getChampionStats().getI());
            ui->lineEditAChamp->setText(cav->getChampionStats().getA());
            ui->lineEditCdtChamp->setText(cav->getChampionStats().getLd());
            ui->lineEditSvgChamp->setText(cav->getChampionStats().getSvg());
            ui->lineEditSvgInvChamp->setText(cav->getChampionStats().getSvgInv());
            ui->spinBannerPoints->setValue(cav->getBannerPoints());
            ui->spinMusicianPoints->setValue(cav->getMusicianPoints());
        }
        else
            QLog_Error(LOG_ID_ERR, "FillUI : DYNAMIC_CAST ERROR : Can't cast to ModelCavalry.");
    }
    else if(type == CHARACTER_STRING)
    {
        ModelCharacter * ch = dynamic_cast<ModelCharacter*>(m);
        if (ch)
        {
            QList<QStandardItem *> newCrew;
            newCrew<<new QStandardItem(ch->getMount().getName())
                    <<new QStandardItem(QString::number(ch->getMount().getPoints()))
                    <<new QStandardItem(ch->getMount().getM())
                    <<new QStandardItem(ch->getMount().getWs())
                    <<new QStandardItem(ch->getMount().getBs())
                    <<new QStandardItem(ch->getMount().getS())
                    <<new QStandardItem(ch->getMount().getT())
                    <<new QStandardItem(ch->getMount().getW())
                    <<new QStandardItem(ch->getMount().getI())
                    <<new QStandardItem(ch->getMount().getA())
                    <<new QStandardItem(ch->getMount().getLd())
                    <<new QStandardItem(ch->getMount().getSvg())
                    <<new QStandardItem(ch->getMount().getSvgInv());
            crew->appendRow(newCrew);

            ui->textEdit->append(ch->getSpecialRules());
            ui->checkLord->setChecked(ch->getIsALord());
            ui->checkMage->setChecked(ch->getIsAMage());
            ui->checkGeneral->setChecked(ch->getIsTheGeneral());
            ui->checkMounted->setChecked(ch->getIsMounted());
            ui->checkGB->setChecked(ch->getHasGB());
        }
        else
            QLog_Error(LOG_ID_ERR, "FillUI : DYNAMIC_CAST ERROR : Can't cast to ModelCharacter.");
    }
    else if(type == CHARRIOT_STRING)
    {
        ModelCharriot* ch = dynamic_cast<ModelCharriot*>(m);
        if (ch)
        {
            for(int i = 0 ; i < ch->getCrew().size() ; i++)

            {
                QList<QStandardItem *> newCrew;
                newCrew<<new QStandardItem(ch->getCrew()[i].getName())
                        <<new QStandardItem(QString::number(ch->getCrew()[i].getPoints()))
                        <<new QStandardItem(ch->getCrew()[i].getM())
                        <<new QStandardItem(ch->getCrew()[i].getWs())
                        <<new QStandardItem(ch->getCrew()[i].getBs())
                        <<new QStandardItem(ch->getCrew()[i].getS())
                        <<new QStandardItem(ch->getCrew()[i].getT())
                        <<new QStandardItem(ch->getCrew()[i].getW())
                        <<new QStandardItem(ch->getCrew()[i].getI())
                        <<new QStandardItem(ch->getCrew()[i].getA())
                        <<new QStandardItem(ch->getCrew()[i].getLd())
                        <<new QStandardItem(ch->getCrew()[i].getSvg())
                        <<new QStandardItem(ch->getCrew()[i].getSvgInv());
                crew->appendRow(newCrew);
            }
            ui->textEdit->append(ch->getSpecialRules());
            switch(ch->getType())
            {
            case BASE:
                ui->radioBase->setChecked(true);
                break;
            case SPECIAL:
                ui->radioSpecial->setChecked(true);
                break;
            case RARE:
                ui->radioRare->setChecked(true);
                break;
            default:
                QLog_Error(LOG_ID_ERR, "fillUI : can't find a valid type.");
                break;
            }
            ui->spinPointsChamp->setValue(ch->getChampionStats().getPoints());
            ui->lineEditMChamp->setText(ch->getChampionStats().getM());
            ui->lineEditCCChamp->setText(ch->getChampionStats().getWs());
            ui->lineEditCTChamp->setText(ch->getChampionStats().getBs());
            ui->lineEditFChamp->setText(ch->getChampionStats().getS());
            ui->lineEditEChamp->setText(ch->getChampionStats().getT());
            ui->lineEditPVChamp->setText(ch->getChampionStats().getW());
            ui->lineEditIChamp->setText(ch->getChampionStats().getI());
            ui->lineEditAChamp->setText(ch->getChampionStats().getA());
            ui->lineEditCdtChamp->setText(ch->getChampionStats().getLd());
            ui->lineEditSvgChamp->setText(ch->getChampionStats().getSvg());
            ui->lineEditSvgInvChamp->setText(ch->getChampionStats().getSvgInv());
            ui->spinBannerPoints->setValue(ch->getBannerPoints());
            ui->spinMusicianPoints->setValue(ch->getMusicianPoints());
        }
        else
            QLog_Error(LOG_ID_ERR, "FillUI : DYNAMIC_CAST ERROR : Can't cast to ModelCharriot.");
    }
    else if(type == INFANTERY_STRING)
    {
        ModelInfantery* inf = dynamic_cast<ModelInfantery*>(m);
        if (inf)
        {
            ui->textEdit->append(inf->getSpecialRules());
            switch(inf->getType())
            {
            case BASE:
                ui->radioBase->setChecked(true);
                break;
            case SPECIAL:
                ui->radioSpecial->setChecked(true);
                break;
            case RARE:
                ui->radioRare->setChecked(true);
                break;
            default:
                QLog_Error(LOG_ID_ERR, "fillUI : can't find a valid type.");
                break;
            }
            ui->spinPointsChamp->setValue(inf->getChampionStats().getPoints());
            ui->lineEditMChamp->setText(inf->getChampionStats().getM());
            ui->lineEditCCChamp->setText(inf->getChampionStats().getWs());
            ui->lineEditCTChamp->setText(inf->getChampionStats().getBs());
            ui->lineEditFChamp->setText(inf->getChampionStats().getS());
            ui->lineEditEChamp->setText(inf->getChampionStats().getT());
            ui->lineEditPVChamp->setText(inf->getChampionStats().getW());
            ui->lineEditIChamp->setText(inf->getChampionStats().getI());
            ui->lineEditAChamp->setText(inf->getChampionStats().getA());
            ui->lineEditCdtChamp->setText(inf->getChampionStats().getLd());
            ui->lineEditSvgChamp->setText(inf->getChampionStats().getSvg());
            ui->lineEditSvgInvChamp->setText(inf->getChampionStats().getSvgInv());
            ui->spinBannerPoints->setValue(inf->getBannerPoints());
            ui->spinMusicianPoints->setValue(inf->getMusicianPoints());
        }
        else
            QLog_Error(LOG_ID_ERR, "FillUI : DYNAMIC_CAST ERROR : Can't cast to ModelInfantery.");
    }
    else if(type == MONSTER_STRING)
    {
        ModelMonster* mon = dynamic_cast<ModelMonster*>(m);
        if (mon)
        {
            for(int i = 0 ; i < mon->getCrew().size() ; i++)

            {
                QList<QStandardItem *> newCrew;
                newCrew<<new QStandardItem(mon->getCrew()[i].getName())
                        <<new QStandardItem(QString::number(mon->getCrew()[i].getPoints()))
                        <<new QStandardItem(mon->getCrew()[i].getM())
                        <<new QStandardItem(mon->getCrew()[i].getWs())
                        <<new QStandardItem(mon->getCrew()[i].getBs())
                        <<new QStandardItem(mon->getCrew()[i].getS())
                        <<new QStandardItem(mon->getCrew()[i].getT())
                        <<new QStandardItem(mon->getCrew()[i].getW())
                        <<new QStandardItem(mon->getCrew()[i].getI())
                        <<new QStandardItem(mon->getCrew()[i].getA())
                        <<new QStandardItem(mon->getCrew()[i].getLd())
                        <<new QStandardItem(mon->getCrew()[i].getSvg())
                        <<new QStandardItem(mon->getCrew()[i].getSvgInv());
                crew->appendRow(newCrew);
            }
            ui->textEdit->append(mon->getSpecialRules());
            switch(mon->getType())
            {
            case BASE:
                ui->radioBase->setChecked(true);
                break;
            case SPECIAL:
                ui->radioSpecial->setChecked(true);
                break;
            case RARE:
                ui->radioRare->setChecked(true);
                break;
            default:
                QLog_Error(LOG_ID_ERR, "fillUI : can't find a valid type.");
                break;
            }
        }
        else
            QLog_Error(LOG_ID_ERR, "FillUI : DYNAMIC_CAST ERROR : Can't cast to ModelMonster.");
    }
    else if(type == WARMACHINE_STRING)
    {
        ModelWarMachine* war = dynamic_cast<ModelWarMachine*>(m);
        if (war)
        {
            for(int i = 0 ; i < war->getCrew().size() ; i++)

            {
                QList<QStandardItem *> newCrew;
                newCrew<<new QStandardItem(war->getCrew()[i].getName())
                        <<new QStandardItem(QString::number(war->getCrew()[i].getPoints()))
                        <<new QStandardItem(war->getCrew()[i].getM())
                        <<new QStandardItem(war->getCrew()[i].getWs())
                        <<new QStandardItem(war->getCrew()[i].getBs())
                        <<new QStandardItem(war->getCrew()[i].getS())
                        <<new QStandardItem(war->getCrew()[i].getT())
                        <<new QStandardItem(war->getCrew()[i].getW())
                        <<new QStandardItem(war->getCrew()[i].getI())
                        <<new QStandardItem(war->getCrew()[i].getA())
                        <<new QStandardItem(war->getCrew()[i].getLd())
                        <<new QStandardItem(war->getCrew()[i].getSvg())
                        <<new QStandardItem(war->getCrew()[i].getSvgInv());
                crew->appendRow(newCrew);
            }
            ui->textEdit->append(war->getSpecialRules());
            switch(war->getType())
            {
            case BASE:
                ui->radioBase->setChecked(true);
                break;
            case SPECIAL:
                ui->radioSpecial->setChecked(true);
                break;
            case RARE:
                ui->radioRare->setChecked(true);
                break;
            default:
                QLog_Error(LOG_ID_ERR, "fillUI : can't find a valid type.");
                break;
            }
        }
        else
            QLog_Error(LOG_ID_ERR, "FillUI : DYNAMIC_CAST ERROR : Can't cast to ModelWarMachine.");
    }
}

void ModelWindow::setModelProperties(ParamsfromUImodel *p)
{
    StatsModel s(ui->lineEditName->text(), ui->lineEditM->text(),ui->lineEditCC->text(),
                 ui->lineEditCT->text(), ui->lineEditF->text(),ui->lineEditE->text(),
                 ui->lineEditPV->text(), ui->lineEditI->text(), ui->lineEditA->text(),
                 ui->lineEditCdt->text(), ui->lineEditSvg->text(), ui->lineEditSvgInv->text(),
                 ui->spinPoints->value());
    p->setStats(s);
    p->setWidthBase(ui->spinWidth->value());
    p->setLengthBase(ui->spinLength->value());
    p->setUnitP(ui->spinPU->value());
    p->setUrlImage(ui->lineEditImage->text());

    QList<OptionModel> optionList;
    // adding moodel options
    for(int i = 0; i< options->rowCount(); i++)
    {
        OptionModel o;
        for(int j = 0; j < options->columnCount(); j++)
        {
            QStandardItem* item = options->item(i,j);
            switch(j)
            {
                case 0:
                    o.setName(item->text());
                    break;
                case 1:
                    o.setNbPoints(item->text().toUInt());
                    break;
                case 2:
                    o.setSpecialRules(item->text());
                    break;
                default:
                    break;
            }
            o.setActivated(false);
            o.setRegimentOptions(false);
        }
        optionList.append(o);
    }
    // adding regiment options
    for(int i = 0; i< regOptions->rowCount(); i++)
    {
        OptionModel o;
        for(int j = 0; j < regOptions->columnCount(); j++)
        {
            QStandardItem* item = regOptions->item(i,j);
            switch(j)
            {
                case 0:
                    o.setName(item->text());
                    break;
                case 1:
                    o.setNbPoints(item->text().toUInt());
                    break;
                case 2:
                    o.setSpecialRules(item->text());
                    break;
                default:
                    break;
            }
            o.setActivated(false);
            o.setRegimentOptions(true);
        }
        optionList.append(o);
    }
    p->setOptions(optionList);

    p->setBannerPoints(ui->spinBannerPoints->value());
    p->setMusicianPoints(ui->spinMusicianPoints->value());
    StatsModel sc("champion", ui->lineEditMChamp->text(),ui->lineEditCCChamp->text(),
                 ui->lineEditCTChamp->text(), ui->lineEditFChamp->text(),ui->lineEditEChamp->text(),
                 ui->lineEditPVChamp->text(), ui->lineEditIChamp->text(), ui->lineEditAChamp->text(),
                 ui->lineEditCdtChamp->text(), ui->lineEditSvgChamp->text(), ui->lineEditSvgInvChamp->text(),
                 ui->spinPointsChamp->value());
    p->setChampionStats(sc);
    p->setBanner(false);
    p->setMusician(false);
    p->setChampion(false);
}

void ModelWindow::save(QString path)
{
    QLog_Info(LOG_ID_INFO, "save() : saving model with path : " + path);
    ParamsfromUImodel* params = new ParamsfromUImodel();
    if(ui->radioBase->isChecked())
    {
        params->setType(BASE);
    }
    else if(ui->radioSpecial->isChecked())
    {
        params->setType(SPECIAL);
    }
    else if(ui->radioRare->isChecked())
    {
        params->setType(RARE);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "save : Can't find type parameter.");
    }

    params->setSpecRules(ui->textEdit->toPlainText());
    setModelProperties(params);

    if(crew->rowCount() > 0)
    {
        QList<StatsModel> mOrCList;
        for(int i = 0; i< crew->rowCount(); i++)
        {
            StatsModel s;
            for(int j = 0; j < crew->columnCount(); j++)
            {

                QStandardItem* item = crew->item(i,j);
                switch(j)
                {
                    case 0:
                        s.setName(item->text());
                        break;
                    case 1:
                        s.setPoints(item->text().toUInt());
                        break;
                    case 2:
                        s.setM(item->text());
                        break;
                    case 3:
                        s.setWs(item->text());
                        break;
                    case 4:
                        s.setBs(item->text());
                        break;
                    case 5:
                        s.setS(item->text());
                        break;
                    case 6:
                        s.setT(item->text());
                        break;
                    case 7:
                        s.setW(item->text());
                        break;
                    case 8:
                        s.setI(item->text());
                        break;
                    case 9:
                        s.setA(item->text());
                        break;
                    case 10:
                        s.setLd(item->text());
                        break;
                    case 11:
                        s.setSvg(item->text());
                        break;
                    case 12:
                        s.setSvgInv(item->text());
                        break;
                    default:
                        break;
                }
            }
            mOrCList.append(s);
        }
        params->setMorC(mOrCList);
    }

    //TODO : check that this work even if hero was not selected
    params->setLord(ui->checkLord->isChecked());
    params->setMage(ui->checkMage->isChecked());
    params->setMounted(ui->checkMounted->isChecked());
    params->setGeneral(ui->checkGeneral->isChecked());
    params->setHasGB(ui->checkGB->isChecked());

    // save in class with factory + save in file
    poupik = fac.createFromUI(ui->comboUnitType->currentText(), params);
    QLog_Info(LOG_ID_INFO, "save() : model saved : " + poupik->displayStringInfo());
    poupik->save(path);
}

void ModelWindow::load(QString path)
{
    if(!path.isEmpty())
    {
        QLogger::QLog_Info(LOG_ID_INFO, "Loading model with path : " + path);
        //if(poupik))delete poupik;
        poupik = fac.createFromFile(path);
        QLog_Info(LOG_ID_INFO, "load() : model loaded : " + poupik->displayStringInfo());
        fillUI(poupik, path);
    }
}

void ModelWindow::on_pushButtonLoad_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir Model"),
            "./models", tr("Fichiers de Models (*.unit)"));

    //clean all ui
    ui->comboRace->setCurrentIndex(0);
    ui->comboUnitType->setCurrentIndex(0);

    ui->lineEditA->clear();
    ui->lineEditCC->clear();
    ui->lineEditCdt->clear();
    ui->lineEditCT->clear();
    ui->lineEditE->clear();
    ui->lineEditF->clear();
    ui->lineEditSvgInv->clear();
    ui->lineEditSvg->clear();
    ui->lineEditPV->clear();
    ui->lineEditName->clear();
    ui->lineEditM->clear();
    ui->lineEditImage->clear();
    ui->lineEditI->clear();
    ui->textEdit->clear();
    ui->spinPoints->clear();
    ui->spinPU->clear();

    ui->lineEditAChamp->clear();
    ui->lineEditCCChamp->clear();
    ui->lineEditCdtChamp->clear();
    ui->lineEditCTChamp->clear();
    ui->lineEditEChamp->clear();
    ui->lineEditFChamp->clear();
    ui->lineEditFChamp->clear();
    ui->lineEditIChamp->clear();
    ui->lineEditPVChamp->clear();
    ui->lineEditSvgInvChamp->clear();
    ui->lineEditSvgChamp->clear();
    ui->lineEditMChamp->clear();
    ui->spinPointsChamp->clear();

    ui->spinBannerPoints->clear();
    ui->spinMusicianPoints->clear();

    options->clear();
    regOptions->clear();
    crew->clear();

    //load the file
    load(fileName);
}

void ModelWindow::on_pushButtonAdd_clicked()
{
    bool ok;
    ui->lineEditPts2->text().toUInt(&ok);
    if(ui->comboUnitType->itemText(ui->comboUnitType->currentIndex()) == CAVALERY_STRING ||
       ui->comboUnitType->itemText(ui->comboUnitType->currentIndex()) == CHARACTER_STRING)
    {
        if(crew->rowCount()!=0)
        {
            int rep = QMessageBox::question(this,tr("Monture"),
                    tr("Le personnage, ou le cavalier ne peut avoir qu'une seule monture. Voulez-vous remplacer la monture actuelle ?"),
                    QMessageBox::Yes | QMessageBox::No);
            if (rep == QMessageBox::No)
            {
                ok = false;
            }
            else if(rep == QMessageBox::Yes)
            {
                crew->clear();
            }
        }
    }
    if(ok)
    {
        // If monted isn't checked, then check it automatically
        ui->checkMounted->setChecked(true);
        QList<QStandardItem *> newStat;

        newStat<<new QStandardItem(ui->lineEditName2->text())
                <<new QStandardItem(ui->lineEditPts2->text())
                <<new QStandardItem(ui->lineEditM2->text())
                <<new QStandardItem(ui->lineEditCC2->text())
                <<new QStandardItem(ui->lineEditCT2->text())
                <<new QStandardItem(ui->lineEditF2->text())
                <<new QStandardItem(ui->lineEditE2->text())
                <<new QStandardItem(ui->lineEditPV2->text())
                <<new QStandardItem(ui->lineEditI2->text())
                <<new QStandardItem(ui->lineEditA2->text())
                <<new QStandardItem(ui->lineEditCdt2->text())
                <<new QStandardItem(ui->lineEditSvg2->text())
                <<new QStandardItem(ui->lineEditSvgInv2->text());

        crew->appendRow(newStat);

        ui->lineEditName2->clear();
        ui->lineEditPts2->clear();
        ui->lineEditM2->clear();
        ui->lineEditCC2->clear();
        ui->lineEditCT2->clear();
        ui->lineEditF2->clear();
        ui->lineEditE2->clear();
        ui->lineEditPV2->clear();
        ui->lineEditI2->clear();
        ui->lineEditA2->clear();
        ui->lineEditCdt2->clear();
        ui->lineEditSvg2->clear();
        ui->lineEditSvgInv2->clear();
    }
    else QMessageBox::warning(this, tr("Erreur"), tr("Le nombre de point doit être un nombre entier."));
}

void ModelWindow::on_pushButtonRmv_clicked()
{
    QItemSelectionModel *selection = ui->viewModelCrew->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    crew->removeRow(indexElementSelectionne.row());
}
