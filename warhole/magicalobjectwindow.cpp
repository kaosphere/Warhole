#include "magicalobjectwindow.h"
#include "ui_magicalobjectwindow.h"

using namespace QLogger;

const QString MagicalObjectWindow::LOG_ID_INFO = "MagicalObjectWindow_info";
const QString MagicalObjectWindow::LOG_ID_TRACE = "MagicalObjectWindow_trace";
const QString MagicalObjectWindow::LOG_ID_WARN = "MagicalObjectWindow_warm";
const QString MagicalObjectWindow::LOG_ID_ERR = "MagicalObjectWindow_err";

const QStringList MagicalObjectWindow::OBJECT_HEADER = QStringList()
                            << QObject::tr("Nom")
                            << QObject::tr("Pts")
                            << QObject::tr("Règles");

MagicalObjectWindow::MagicalObjectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MagicalObjectWindow)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    ui->setupUi(this);

    model = new QFileSystemModel(this);

    objects = new QStandardItemModel();
    ui->treeViewExistingObjects->setModel(objects);
}

MagicalObjectWindow::~MagicalObjectWindow()
{
    delete model;
    delete ui;
}

void MagicalObjectWindow::on_comboRace_currentTextChanged(const QString &raceDir)
{
    updateTreeView(raceDir);
}


void MagicalObjectWindow::updateTreeView(QString raceDir)
{
    // get list of existing models to verify if some exist
    QDir* modelDir = new QDir(MAGICAL_OBJECT_PATH + "/" + raceDir);
    QStringList existingObjects;
    MagicalObject obj;
    objectList.clear();

    if (modelDir->exists())
    {
        existingObjects = modelDir->entryList();
        for(int i = 0; i <existingObjects.size(); ++i)
        {
            QStringList pieces = existingObjects[i].split(".");
            if(pieces.last() == "om")
            {
                obj.load(MAGICAL_OBJECT_PATH + "/" + raceDir + "/" + existingObjects[i]);
                objectList.append(obj);
            }
        }
    }
    if(existingObjects.isEmpty())
    {
        QLog_Info(LOG_ID_INFO, "on_comboBoxRace_currentIndexChanged() : No magical object found in race : " + raceDir);
    }

    objects->clear();
    for(int i = 0 ; i < objectList.size() ; i++)
    {
        QList<QStandardItem *> newObject;

        newObject<<new QStandardItem(objectList[i].getName())
                <<new QStandardItem(QString::number(objectList[i].getPoints()))
                <<new QStandardItem(objectList[i].getSpecialRules());
        objects->appendRow(newObject);
    }
    objects->setHorizontalHeaderLabels(OBJECT_HEADER);
}

void MagicalObjectWindow::clearWindow()
{
    ui->lineEditName->clear();
    ui->checkBox->setChecked(false);
    ui->textEdit->clear();
    ui->spinBox->clear();
}

void MagicalObjectWindow::on_addButton_clicked()
{
    MagicalObject obj;


    if(ui->comboRace->currentIndex() != 0 && !ui->lineEditName->text().isEmpty())
    {
        obj.setName(ui->lineEditName->text());
        obj.setPoints(ui->spinBox->value());
        obj.setSpecialRules(ui->textEdit->toPlainText());
        obj.setCabalistic(ui->checkBox->isChecked());

        QLog_Info(LOG_ID_INFO, "Magical Object saved : " + obj.displayString());

        obj.save(MAGICAL_OBJECT_PATH + '/' + ui->comboRace->currentText() + "/" + ui->lineEditName->text() + ".om");

        updateTreeView(ui->comboRace->currentText());
        clearWindow();
    }
    else
        QMessageBox::warning(this, tr("Warning"), tr("Veuillez choisir une race pour laquelle sauver l'objet, ainsi que donner un nom a l'objet."));

}


void MagicalObjectWindow::on_removeButton_clicked()
{
    QItemSelectionModel *selection = ui->treeViewExistingObjects->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(indexElementSelectionne.isValid())
    {
        int rep = QMessageBox::question(this,tr("Effacer"),
                                        tr("Voulez-vous vraiment effacer cet object magique ?"),
                                        QMessageBox::Yes | QMessageBox::No);
        if (rep == QMessageBox::Yes)
        {
            QFile f;
            f.setFileName(MAGICAL_OBJECT_PATH + "/" + ui->comboRace->currentText() + "/" + objects->item(indexElementSelectionne.row(), 0)->text() + ".om");
            f.remove();
            updateTreeView(ui->comboRace->currentText());
        }
        else if (rep == QMessageBox::No)
        {
            QMessageBox::critical(this, tr("Annulation"), tr("Opération annulée"));
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Info"), tr("Veuillez sélectionner un régiment a dupliquer."));
    }
}

void MagicalObjectWindow::on_editButton_clicked()
{
    QItemSelectionModel *selection = ui->treeViewExistingObjects->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    MagicalObject obj;

    if(indexElementSelectionne.isValid())
    {
        clearWindow();

        obj.load(MAGICAL_OBJECT_PATH + "/" + ui->comboRace->currentText() + "/" + objects->item(indexElementSelectionne.row(),0)->text() + ".om");
        ui->lineEditName->setText(obj.getName());
        ui->spinBox->setValue(obj.getPoints());
        ui->checkBox->setChecked(obj.getCabalistic());
        ui->textEdit->append(obj.getSpecialRules());
    }
    else
    {
        QMessageBox::warning(this, tr("Info"), tr("Veuillez sélectionner un régiment a dupliquer."));
    }
}
