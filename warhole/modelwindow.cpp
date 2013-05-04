#include "modelwindow.h"
#include "ui_modelwindow.h"

ModelWindow::ModelWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);

    ui->spinWidth->setValue(25);
    ui->spinLength->setValue(50);

    options = new QStandardItemModel(1,4);

    ui->viewOptions->setModel(options);
    ui->viewOptions->header()->hide();
}

ModelWindow::~ModelWindow()
{
    delete ui;
}

void ModelWindow::loadAnimalWidget()
{
    ui->spinWidth->setValue(25);
    ui->spinLength->setValue(50);
}

void ModelWindow::loadCavaleryWidget()
{
    ui->spinWidth->setValue(25);
    ui->spinLength->setValue(50);
}

void ModelWindow::loadCharacterWidget()
{
    ui->spinWidth->setValue(25);
    ui->spinLength->setValue(25);
}

void ModelWindow::loadCharriotWidget()
{
    ui->spinWidth->setValue(50);
    ui->spinLength->setValue(100);
}

void ModelWindow::loadInfanteryWidget()
{
    ui->spinWidth->setValue(25);
    ui->spinLength->setValue(25);
}

void ModelWindow::loadMonsterWidget()
{
    ui->spinWidth->setValue(50);
    ui->spinLength->setValue(50);
}

void ModelWindow::loadWarMachineWidget()
{
    ui->spinWidth->setValue(25);
    ui->spinLength->setValue(25);
}

void ModelWindow::on_comboUnitType_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
            loadAnimalWidget();
            break;
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
    QPixmap image;

    fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "C:", tr("Image Files (*.png *.jpg *.bmp)"));
    ui->lineEditImage->setText(fileName);

    image.load(fileName);

    scene->addPixmap(image);

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
