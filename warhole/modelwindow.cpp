#include "modelwindow.h"
#include "ui_modelwindow.h"

using namespace QLogger;

ModelWindow::ModelWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelWindow)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID), QLogger::WarnLevel);

    ui->setupUi(this);
    image = new QPixmap();
    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);

    options = new QStandardItemModel();
    crew = new QStandardItemModel();

    QStringList modelList;
    modelList << CAVALERY_STRING << CHARACTER_STRING << CHARRIOT_STRING << INFANTERY_STRING << MONSTER_STRING << WARMACHINE_STRING;
    ui->comboUnitType->addItems(modelList);

    ui->viewOptions->setModel(options);
    ui->viewOptions->header()->hide();

    ui->viewModelCrew->setModel(crew);
    ui->viewModelCrew->header()->hide();


    cav = new ModelCavalry();
    hero = new ModelCharacter();
    charriot = new ModelCharriot();
    inf = new ModelInfantery();
    monster = new ModelMonster();
    machine = new ModelWarMachine();

    loadInfanteryWidget();
}

ModelWindow::ModelWindow(QString f, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelWindow)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID), QLogger::WarnLevel);

    ui->setupUi(this);
    image = new QPixmap();

    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);

    options = new QStandardItemModel();
    crew = new QStandardItemModel();

    QStringList modelList;
    modelList << CAVALERY_STRING << CHARACTER_STRING << CHARRIOT_STRING << INFANTERY_STRING << MONSTER_STRING << WARMACHINE_STRING;
    ui->comboUnitType->addItems(modelList);

    ui->viewOptions->setModel(options);
    ui->viewOptions->header()->hide();

    ui->viewModelCrew->setModel(crew);
    ui->viewModelCrew->header()->hide();

    cav = new ModelCavalry();
    hero = new ModelCharacter();
    charriot = new ModelCharriot();
    inf = new ModelInfantery();
    monster = new ModelMonster();
    machine = new ModelWarMachine();

    loadInfanteryWidget();

    load(f);
}

ModelWindow::~ModelWindow()
{
    delete cav;
    delete hero;
    delete charriot;
    delete inf;
    delete monster;
    delete machine;

    delete crew;
    delete options;
    delete scene;

    delete ui;
}

void ModelWindow::loadWidgets(bool l)
{
    ui->lineEditA2->setVisible(l);
    ui->lineEditCC2->setVisible(l);
    ui->lineEditCdt2->setVisible(l);
    ui->lineEditCT2->setVisible(l);
    ui->lineEditE2->setVisible(l);
    ui->lineEditF2->setVisible(l);
    ui->lineEditF2->setVisible(l);
    ui->lineEditI2->setVisible(l);
    ui->lineEditPV2->setVisible(l);
    ui->lineEditSvgInv2->setVisible(l);
    ui->lineEditSvg2->setVisible(l);
    ui->lineEditM2->setVisible(l);
    ui->lineEditName2->setVisible(l);
    ui->lineEditPts2->setVisible(l);

    ui->label_28->setVisible(l);
    ui->label_54->setVisible(l);
    ui->label_55->setVisible(l);
    ui->label_56->setVisible(l);
    ui->label_57->setVisible(l);
    ui->label_58->setVisible(l);
    ui->label_59->setVisible(l);
    ui->label_60->setVisible(l);
    ui->label_61->setVisible(l);
    ui->label_62->setVisible(l);
    ui->label_63->setVisible(l);
    ui->label_64->setVisible(l);
    ui->label_65->setVisible(l);
    ui->label_66->setVisible(l);
    ui->label_67->setVisible(l);

    ui->pushButtonAdd->setVisible(l);
    ui->pushButtonRmv->setVisible(l);

    ui->viewModelCrew->setVisible(l);
}

void ModelWindow::loadCavaleryWidget()
{
    //hide character checkboxes
    ui->checkGB->setEnabled(false);
    ui->checkGeneral->setEnabled(false);
    ui->checkLord->setEnabled(false);
    ui->checkMage->setEnabled(false);
    ui->checkMounted->setEnabled(false);

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

    fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp)"));
    ui->lineEditImage->setText(fileName);

    if(image->load(fileName))
    {
    	scene->clear();
    	scene->addPixmap(*image);
    }
    else  QMessageBox::warning(this, "Info", "URL de l'image non valide");

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
        QMessageBox::warning(this, "Erreur", "Le nombre de point doit être un nombre entier.");
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

    if(ui->lineEditName->text().isEmpty() || ui->lineEditImage->text().isEmpty() || ui->comboRace->currentIndex() == 0 || ui->comboUnitType->currentIndex() == 0 )
    {
        QMessageBox::warning(this, "Info", "Vous devez obligatoirement choisir une race, un type d'unité et remplir un nom et une image.");
        return;
    }

    QString path = "models/" + ui->comboRace->itemText(ui->comboRace->currentIndex()) + "/" + ui->comboUnitType->itemText(ui->comboUnitType->currentIndex()) + "/" + ui->lineEditName->text() +".unit";
    QFile f;
    f.setFileName(path);

    if(f.exists())
    {
        int rep = QMessageBox::question(this,"Ecraser", "La figurine existe déjà, voulez vous l'écraser?", QMessageBox::Yes | QMessageBox::No);
        if (rep == QMessageBox::Yes)
        {
            save(path);
            QMessageBox::information(this, "Info", "Figurine sauvegardée avec succès.");
        }
        else if (rep == QMessageBox::No)
        {
            QMessageBox::critical(this, "Annulation", "Sauvegarde annulée");
        }
    }
    else{
        save(path);
        QMessageBox::information(this, "Info", "Figurine sauvegardée avec succès.");
    }
    this->close();
    this->deleteLater();

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
    else  QMessageBox::warning(this, "Info", "URL de l'image non valide");

    for(int i = 0 ; i < m->getOptions().length() ; i++)
    {
        QList<QStandardItem *> newOption;

        newOption<<new QStandardItem(m->getOptions()[i].getName())
                <<new QStandardItem(QString::number(m->getOptions()[i].getNbPoints()))
               <<new QStandardItem(m->getOptions()[i].getSpecialRules());

        options->appendRow(newOption);
    }
}

void ModelWindow::setModelProperties(ParamsfromUImodel *p)
{
    qDebug() << "enter setModelProperty in modelwindow";
    StatsModel s(ui->lineEditName->text(), ui->lineEditM->text(),ui->lineEditCC->text(),
                 ui->lineEditCT->text(), ui->lineEditF->text(),ui->lineEditE->text(),
                 ui->lineEditPV->text(), ui->lineEditI->text(), ui->lineEditA->text(),
                 ui->lineEditCdt->text(), ui->lineEditSvg->text(), ui->lineEditSvgInv->text(),ui->spinPoints->value());
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
            //QMessageBox::information(this, "Info", item->text());

            switch(j)
            {
                case 0:
                    o.setName(item->text());
                    break;
                case 1:
                    o.setNbPoints(item->text().toUInt());
                    //QMessageBox::information(this, "Info", o.getNbPoints());
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
    qDebug() << "option 1 name : " << p->getOptions().first().getName();
    qDebug() << "exit setModelProperty in modelwindow";

}

void ModelWindow::save(QString path)
{
    qDebug() << "enter modelwindow save";
    ParamsfromUImodel* params = new ParamsfromUImodel();
    params->setSpecRules(ui->textEdit->toPlainText());
    setModelProperties(params);

    qDebug() << "begin creating statsmodel list";
    qDebug() << "crew object name : " << crew->objectName();
    qDebug() << "crew row count : " << crew->rowCount();

    if(crew->rowCount() > 0)
    {

        QList<StatsModel> mOrCList;
        for(int i = 0; i< crew->rowCount(); i++)
        {
            StatsModel s;
            for(int j = 0; j < crew->columnCount(); j++)
            {

                QStandardItem* item = crew->item(i,j);
                //QMessageBox::information(this, "Info", item->text());

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
        qDebug() << "stat 1 (MorC) name" << params->getMorC().first().getName();
    }

    qDebug() << "end creating statsmodel list";


    //TODO : check that this work even if hero was not selected
    params->setLord(ui->checkLord->isChecked());
    params->setMage(ui->checkMage->isChecked());
    params->setMounted(ui->checkMounted->isChecked());
    params->setGeneral(ui->checkGeneral->isChecked());
    qDebug() << "mage : " << params->getMage();
    qDebug() << "Name : " << params->getStats().getName();
    qDebug() << "end set lord/mage etc";

    // save in class with factory + save in file
    poupik = fac.createFromUI(ui->comboUnitType->currentText(), params);
    qDebug() << "from modWin save, poupik name : " << poupik->getStats().getName();
    poupik->save(path);
}

void ModelWindow::load(QString path)
{
    QString s = path.section('/',-2,-2);
    QStringList l;
    l << CAVALERY_STRING << CHARRIOT_STRING << INFANTERY_STRING << CHARACTER_STRING << WARMACHINE_STRING << MONSTER_STRING;

    QLogger::QLog_Info(LOG_ID, "Loading model with path : " + path);

    switch(l.indexOf(s))
    {
    case 0:
        //delete object first to prevent options to stack
        delete cav;
        cav = new ModelCavalry();
        cav->load(path);
        fillUI(static_cast<ModelAbstract*>(cav), path);

        for(int i = 0 ; i < cav->getMount().size() ; i++)
        {
            QList<QStandardItem *> newCrew;

            newCrew<<new QStandardItem(cav->getMount()[i].getName())
                    <<new QStandardItem(QString::number(cav->getMount()[i].getPoints()))
                    <<new QStandardItem(cav->getMount()[i].getM())
                    <<new QStandardItem(cav->getMount()[i].getWs())
                    <<new QStandardItem(cav->getMount()[i].getBs())
                    <<new QStandardItem(cav->getMount()[i].getS())
                    <<new QStandardItem(cav->getMount()[i].getT())
                    <<new QStandardItem(cav->getMount()[i].getW())
                    <<new QStandardItem(cav->getMount()[i].getI())
                    <<new QStandardItem(cav->getMount()[i].getA())
                    <<new QStandardItem(cav->getMount()[i].getLd())
                    <<new QStandardItem(cav->getMount()[i].getSvg())
                    <<new QStandardItem(cav->getMount()[i].getSvgInv());

            crew->appendRow(newCrew);
        }
        ui->textEdit->append(cav->getSpecialRules());
        QLogger::QLog_Info(LOG_ID, "Model loaded : \n");
        QLogger::QLog_Info(LOG_ID, cav->displayStringInfo());
        QLogger::QLog_Error(LOG_ID, "test pour l'erreur");
        QLogger::QLog_Error(LOG_ID, "test 2 pour l'erreur");
        break;
    case 1:
        //delete object first to prevent options to stack
        delete charriot;
        charriot = new ModelCharriot();
        charriot->load(path);
        fillUI(static_cast<ModelAbstract*>(charriot), path);
        for(int i = 0 ; i < charriot->getCrew().size() ; i++)
        {
            QList<QStandardItem *> newCrew;

            newCrew<<new QStandardItem(charriot->getCrew()[i].getName())
                    <<new QStandardItem(QString::number(charriot->getCrew()[i].getPoints()))
                    <<new QStandardItem(charriot->getCrew()[i].getM())
                    <<new QStandardItem(charriot->getCrew()[i].getWs())
                    <<new QStandardItem(charriot->getCrew()[i].getBs())
                    <<new QStandardItem(charriot->getCrew()[i].getS())
                    <<new QStandardItem(charriot->getCrew()[i].getT())
                    <<new QStandardItem(charriot->getCrew()[i].getW())
                    <<new QStandardItem(charriot->getCrew()[i].getI())
                    <<new QStandardItem(charriot->getCrew()[i].getA())
                    <<new QStandardItem(charriot->getCrew()[i].getLd())
                    <<new QStandardItem(charriot->getCrew()[i].getSvg())
                    <<new QStandardItem(charriot->getCrew()[i].getSvgInv());

            crew->appendRow(newCrew);
        }
        ui->textEdit->append(charriot->getSpecialRules());
        break;
    case 2:
        //delete object first to prevent options to stack
        delete inf;
        inf = new ModelInfantery();
        inf->load(path);
        fillUI(static_cast<ModelAbstract*>(inf), path);
        ui->textEdit->append(inf->getSpecialRules());
        break;
    case 3:
        //delete object first to prevent options to stack
        delete hero;
        hero = new ModelCharacter();
        hero->load(path);
        fillUI(static_cast<ModelAbstract*>(hero), path);
        ui->textEdit->append(hero->getSpecialRules());
        ui->checkLord->setChecked(hero->getIsALord());
        ui->checkMage->setChecked(hero->getIsAMage());
        ui->checkGeneral->setChecked(hero->getIsTheGeneral());
        ui->checkMounted->setChecked(hero->getIsMounted());
        for(int i = 0 ; i < hero->getMount().size() ; i++)
        {
            QList<QStandardItem *> newCrew;

            newCrew<<new QStandardItem(hero->getMount()[i].getName())
                    <<new QStandardItem(QString::number(hero->getMount()[i].getPoints()))
                    <<new QStandardItem(hero->getMount()[i].getM())
                    <<new QStandardItem(hero->getMount()[i].getWs())
                    <<new QStandardItem(hero->getMount()[i].getBs())
                    <<new QStandardItem(hero->getMount()[i].getS())
                    <<new QStandardItem(hero->getMount()[i].getT())
                    <<new QStandardItem(hero->getMount()[i].getW())
                    <<new QStandardItem(hero->getMount()[i].getI())
                    <<new QStandardItem(hero->getMount()[i].getA())
                    <<new QStandardItem(hero->getMount()[i].getLd())
                    <<new QStandardItem(hero->getMount()[i].getSvg())
                    <<new QStandardItem(hero->getMount()[i].getSvgInv());

            crew->appendRow(newCrew);
        }
        break;
    case 4:
        //delete object first to prevent options to stack
        delete machine;
        machine = new ModelWarMachine();
        machine->load(path);
        fillUI(static_cast<ModelAbstract*>(machine), path);
        ui->textEdit->append(machine->getSpecialRules());
        break;
    case 5:
        //delete object first to prevent options to stack
        delete monster;
        monster = new ModelMonster();
        monster->load(path);
        fillUI(static_cast<ModelAbstract*>(monster), path);
        ui->textEdit->append(monster->getSpecialRules());
        break;
    default:
        break;
    }
}

void ModelWindow::on_pushButtonLoad_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Model"), "./models", tr("Model files (*.unit)"));

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

    if(ok)
    {
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
    else QMessageBox::warning(this, "Erreur", "Le nombre de point doit être un nombre entier.");
}

void ModelWindow::on_pushButtonRmv_clicked()
{
    QItemSelectionModel *selection = ui->viewModelCrew->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    crew->removeRow(indexElementSelectionne.row());
}
