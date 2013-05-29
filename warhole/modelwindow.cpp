#include "modelwindow.h"
#include "ui_modelwindow.h"

ModelWindow::ModelWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelWindow)
{
    ui->setupUi(this);
    image = new QPixmap();
    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);

    options = new QStandardItemModel();
    crew = new QStandardItemModel();

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
    ui->setupUi(this);
    image = new QPixmap();

    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);

    options = new QStandardItemModel();
    crew = new QStandardItemModel();

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
        case 1:
            loadCavaleryWidget();
            break;
        case 2:
            loadCharriotWidget();
            break;
        case 3:
            loadInfanteryWidget();
            break;
        case 4:
            loadMonsterWidget();
            break;
        case 5:
            loadWarMachineWidget();
            break;
        case 6:
            loadCharacterWidget();
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

    if(image->load(fileName)) scene->addPixmap(*image);
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

    if(image->load(m->getUrlImage())) scene->addPixmap(*image);
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

void ModelWindow::setModelProperties(ModelAbstract* m)
{
    StatsModel s(ui->lineEditName->text(), ui->lineEditM->text(),ui->lineEditCC->text(),
                 ui->lineEditCT->text(), ui->lineEditF->text(),ui->lineEditE->text(),
                 ui->lineEditPV->text(), ui->lineEditI->text(), ui->lineEditA->text(),
                 ui->lineEditCdt->text(), ui->lineEditSvg->text(), ui->lineEditSvgInv->text(),ui->spinPoints->value());
    m->setStats(s);
    m->setSquareBaseW(ui->spinWidth->value());
    m->setSquareBaseL(ui->spinLength->value());
    m->setUnitPower(ui->spinPU->value());
    m->setUrlImage(ui->lineEditImage->text());

    //opTions
    //remove options not to make doubles
    m->clearOptions();
    //then fill options again
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
        m->addOption(o);
    }
}

void ModelWindow::save(QString path)
{
    switch(ui->comboUnitType->currentIndex())
    {
    case 1:
        setModelProperties(static_cast<ModelAbstract*>(cav));
        cav->setSpecialRules(ui->textEdit->toPlainText());
        //fill stats if its a cav, charriot or character
        cav->clearMount();
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
            cav->addMount(s);
        }
        cav->save(path);
        break;
    case 2:
        setModelProperties(static_cast<ModelAbstract*>(charriot));
        charriot->setSpecialRules(ui->textEdit->toPlainText());
        //fill stats if its a cav, charriot or character
        charriot->clearCrew();
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
            charriot->addCrew(s);
        }
        charriot->save(path);
        break;
    case 3:
        setModelProperties(static_cast<ModelAbstract*>(inf));
        inf->setSpecialRules(ui->textEdit->toPlainText());
        inf->save(path);
        break;
    case 4:
        setModelProperties(static_cast<ModelAbstract*>(machine));
        machine->setSpecialRules(ui->textEdit->toPlainText());
        machine->save(path);
        break;
    case 5:
        setModelProperties(static_cast<ModelAbstract*>(monster));
        monster->setSpecialRules(ui->textEdit->toPlainText());
        monster->save(path);
        break;
    case 6:
        setModelProperties(static_cast<ModelAbstract*>(hero));
        hero->setSpecialRules(ui->textEdit->toPlainText());
        hero->setIsALord(ui->checkLord->isChecked());
        hero->setIsAMage(ui->checkMage->isChecked());
        hero->setIsMounted(ui->checkMounted->isChecked());
        hero->setIsTheGeneral(ui->checkGeneral->isChecked());
        hero->save(path);
        break;
    default:
        break;
    }
}

void ModelWindow::load(QString path)
{
    QString s = path.section('/',-2,-2);
    QStringList l;
    l << "Cavalerie" << "Char" << "Infanterie" << "Personnage" << "Machine de guerre" << "Monstre";

    switch(l.indexOf(s))
    {
    case 0:
        //delete object first to prevent options to stack
        delete cav;
        cav = new ModelCavalry();
        //load
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
        break;
    case 1:
        //delete object first to prevent options to stack
        delete charriot;
        charriot = new ModelCharriot();
        //load
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
        //load
        inf->load(path);
        fillUI(static_cast<ModelAbstract*>(inf), path);
        ui->textEdit->append(inf->getSpecialRules());
        break;
    case 3:
        //delete object first to prevent options to stack
        delete hero;
        hero = new ModelCharacter();
        //load
        hero->load(path);
        fillUI(static_cast<ModelAbstract*>(hero), path);
        ui->textEdit->append(hero->getSpecialRules());
        ui->checkLord->setChecked(hero->getIsALord());
        ui->checkMage->setChecked(hero->getIsAMage());
        ui->checkGeneral->setChecked(hero->getIsTheGeneral());
        ui->checkMounted->setChecked(hero->getIsMounted());
        break;
    case 4:
        //delete object first to prevent options to stack
        delete machine;
        machine = new ModelWarMachine();
        //load
        machine->load(path);
        fillUI(static_cast<ModelAbstract*>(machine), path);
        ui->textEdit->append(machine->getSpecialRules());
        break;
    case 5:
        //delete object first to prevent options to stack
        delete monster;
        monster = new ModelMonster();
        //load
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

void ModelWindow::on_pushButtonAdd_2_clicked()
{
    QItemSelectionModel *selection = ui->viewModelCrew->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    crew->removeRow(indexElementSelectionne.row());
}
