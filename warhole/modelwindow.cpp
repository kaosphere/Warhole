#include "modelwindow.h"
#include "ui_modelwindow.h"

using namespace QLogger;

const QString ModelWindow::LOG_ID_INFO = "ModelWindow_info";
const QString ModelWindow::LOG_ID_TRACE = "ModelWindow_trace";
const QString ModelWindow::LOG_ID_WARN = "ModelWindow_warm";
const QString ModelWindow::LOG_ID_ERR = "ModelWindow_err";

ModelWindow::ModelWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelWindow)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    ui->setupUi(this);
    image = new QPixmap();
    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);

    options = new QStandardItemModel();
    crew = new QStandardItemModel();

    QStringList modelList;
    modelList << CAVALERY_STRING << CHARACTER_STRING << CHARRIOT_STRING <<
    		     INFANTERY_STRING << MONSTER_STRING << WARMACHINE_STRING;
    ui->comboUnitType->addItems(modelList);

    ui->viewOptions->setModel(options);
    ui->viewOptions->header()->hide();

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

    ui->setupUi(this);
    image = new QPixmap();

    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);

    options = new QStandardItemModel();
    crew = new QStandardItemModel();

    QStringList modelList;
    modelList << CAVALERY_STRING << CHARACTER_STRING << CHARRIOT_STRING <<
    		     INFANTERY_STRING << MONSTER_STRING << WARMACHINE_STRING;
    ui->comboUnitType->addItems(modelList);

    ui->viewOptions->setModel(options);
    ui->viewOptions->header()->hide();

    ui->viewModelCrew->setModel(crew);
    ui->viewModelCrew->header()->hide();

    loadInfanteryWidget();

    load(f);
}

ModelWindow::~ModelWindow()
{
    delete poupik;

    delete crew;
    delete options;
    delete scene;

    delete ui;
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
    ui->label_55->setEnabled(l);
    ui->label_56->setEnabled(l);
    ui->label_57->setEnabled(l);
    ui->label_58->setEnabled(l);
    ui->label_59->setEnabled(l);
    ui->label_60->setEnabled(l);
    ui->label_61->setEnabled(l);
    ui->label_62->setEnabled(l);
    ui->label_63->setEnabled(l);
    ui->label_64->setEnabled(l);
    ui->label_65->setEnabled(l);
    ui->label_66->setEnabled(l);
    ui->label_67->setEnabled(l);

    ui->pushButtonAdd->setEnabled(l);
    ui->pushButtonRmv->setEnabled(l);

    ui->viewModelCrew->setEnabled(l);
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

    loadWidgets(false);
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

    loadWidgets(false);
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
    else  QMessageBox::warning(this, tr("Info"), tr("URL de l'image non valide"));

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
    }
}

void ModelWindow::on_deleteOption_clicked()
{
    QItemSelectionModel *selection = ui->viewOptions->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    options->removeRow(indexElementSelectionne.row());
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
    //ui->lineEditName->setText(poupik.getFigSupInd());
    ui->lineEditImage->setText(m->getUrlImage());
    //ui->textEdit->append(poupik->getSpecialRules());

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
        }
        else
            QLog_Error(LOG_ID_ERR, "FillUI : DYNAMIC_CAST ERROR : Can't cast to ModelInfantery.");
    }
    else if(type == MONSTER_STRING)
    {
        ModelMonster* mon = dynamic_cast<ModelMonster*>(m);
        if (mon)
        {
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
        }
        optionList.append(o);
    }
    p->setOptions(optionList);
}

void ModelWindow::save(QString path)
{
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
    poupik->save(path);
}

void ModelWindow::load(QString path)
{
    if(!path.isEmpty())
    {
        QLogger::QLog_Info(LOG_ID_INFO, "Loading model with path : " + path);
        delete poupik;
        poupik = fac.createFromFile(path);
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

    options->clear();
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
