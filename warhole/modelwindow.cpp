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

    loadAnimalWidget();
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

    ui->viewOptions->setModel(options);
    ui->viewOptions->header()->hide();

    loadAnimalWidget();

    poupik.load(f);

    ui->lineEditName->setText(poupik.getStats().getName());
    ui->lineEditM->setText(poupik.getStats().getM());
    ui->lineEditCC->setText(poupik.getStats().getWs());
    ui->lineEditCT->setText(poupik.getStats().getBs());
    ui->lineEditF->setText(poupik.getStats().getS());
    ui->lineEditE->setText(poupik.getStats().getT());
    ui->lineEditPV->setText(poupik.getStats().getW());
    ui->lineEditI->setText(poupik.getStats().getI());
    ui->lineEditA->setText(poupik.getStats().getA());
    ui->lineEditCdt->setText(poupik.getStats().getLd());
    ui->lineEditSvg->setText(poupik.getStats().getSvg());
    ui->lineEditSvgInv->setText(poupik.getStats().getSvgInv());
    ui->spinWidth->setValue(poupik.getSquareBaseW());
    ui->spinLength->setValue(poupik.getSquareBaseL());
    ui->spinPU->setValue(poupik.getUnitPower());
    //ui->lineEditName->setText(poupik.getFigSupInd());
    ui->lineEditImage->setText(poupik.getUrlImage());
    ui->textEdit->append(poupik.getSpecialRules());

    if(image->load(poupik.getUrlImage())) scene->addPixmap(*image);
    else  QMessageBox::warning(this, "Info", "URL de l'image non valide");
}

ModelWindow::~ModelWindow()
{
    delete ui;
}

void ModelWindow::loadWidgets(bool l)
{
    ui->viewModelCrew->setEnabled(l);

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

    ui->pushButtonAdd->setVisible(l);


}

void ModelWindow::loadAnimalWidget()
{
    ui->spinWidth->setValue(25);
    ui->spinLength->setValue(50);

    //hide character checkboxes
    ui->checkGB->setEnabled(false);
    ui->checkGeneral->setEnabled(false);
    ui->checkLord->setEnabled(false);
    ui->checkMage->setEnabled(false);
    ui->checkMounted->setEnabled(false);

    loadWidgets(false);
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
            loadAnimalWidget();
            break;
        case 2:
            loadCavaleryWidget();
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
        case 7:
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
    QList<QStandardItem *> newOption;

    newOption<<new QStandardItem(ui->lineOptionName->text())
            <<new QStandardItem(ui->lineEditOptionPts->text())
           <<new QStandardItem(ui->lineEditOptionSpec->text());

    options->appendRow(newOption);

    ui->lineOptionName->clear();
    ui->lineEditOptionPts->clear();
    ui->lineEditOptionSpec->clear();
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
    ModelAnimal poupik(ui->lineEditName->text(), ui->lineEditM->text(),ui->lineEditCC->text(),
                                          ui->lineEditCT->text(), ui->lineEditF->text(),ui->lineEditE->text(),
                                          ui->lineEditPV->text(), ui->lineEditI->text(), ui->lineEditA->text(),
                                          ui->lineEditCdt->text(), ui->lineEditSvg->text(), ui->lineEditSvgInv->text(),
                                          ui->spinWidth->value(), ui->spinLength->value(),ui->spinPU->value(), ui->lineEditImage->text(),
                                          false, ui->textEdit->toPlainText());

    QString path = "models/" + ui->comboRace->itemText(ui->comboRace->currentIndex()) + "/" + ui->comboUnitType->itemText(ui->comboUnitType->currentIndex()) + "/" + ui->lineEditName->text() +".unit";
    QFile f;
    f.setFileName(path);

    if(f.exists())
    {
        int rep = QMessageBox::question(this,"Ecraser", "La figurine existe déjà, voulez vous l'écraser?", QMessageBox::Yes | QMessageBox::No);
        if (rep == QMessageBox::Yes)
        {
            poupik.save(path);
            QMessageBox::information(this, "Info", "Figurine sauvegardée avec succès.");
        }
        else if (rep == QMessageBox::No)
        {
            QMessageBox::critical(this, "Annulation", "Sauvegarde annulée");
        }
    }
    this->close();
    this->deleteLater();

}

void ModelWindow::on_pushButtonLoad_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Model"), "./models", tr("Model files (*.unit)"));

    poupik.load(fileName);

    ui->lineEditName->setText(poupik.getStats().getName());
    ui->lineEditM->setText(poupik.getStats().getM());
    ui->lineEditCC->setText(poupik.getStats().getWs());
    ui->lineEditCT->setText(poupik.getStats().getBs());
    ui->lineEditF->setText(poupik.getStats().getS());
    ui->lineEditE->setText(poupik.getStats().getT());
    ui->lineEditPV->setText(poupik.getStats().getW());
    ui->lineEditI->setText(poupik.getStats().getI());
    ui->lineEditA->setText(poupik.getStats().getA());
    ui->lineEditCdt->setText(poupik.getStats().getLd());
    ui->lineEditSvg->setText(poupik.getStats().getSvg());
    ui->lineEditSvgInv->setText(poupik.getStats().getSvgInv());
    ui->spinWidth->setValue(poupik.getSquareBaseW());
    ui->spinLength->setValue(poupik.getSquareBaseL());
    ui->spinPU->setValue(poupik.getUnitPower());
    //ui->lineEditName->setText(poupik.getFigSupInd());
    ui->lineEditImage->setText(poupik.getUrlImage());
    ui->textEdit->append(poupik.getSpecialRules());

    if(image->load(poupik.getUrlImage())) scene->addPixmap(*image);
    else  QMessageBox::warning(this, "Info", "URL de l'image non valide");

    QMessageBox::information(this, "Info", "Figurine chargée : " + poupik.getStats().getName());

}

void ModelWindow::on_pushButtonAdd_clicked()
{
    QList<QStandardItem *> newStat;

    newStat<<new QStandardItem(ui->lineEditName2->text())
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

void ModelWindow::on_pushButtonAdd_2_clicked()
{
    QItemSelectionModel *selection = ui->viewModelCrew->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    crew->removeRow(indexElementSelectionne.row());
}
