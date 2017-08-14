#include "armywindowevolved.h"
#include "ui_armywindowevolved.h"
#include <Utilities/QLogger/QLogger.h>
#include <QMessageBox>
#include "defines.h"

#include "version.h"

#include <QDir>

using namespace QLogger;

const QString ArmyWindowEvolved::LOG_ID_INFO = "ArmyWindowEvolved_info";
const QString ArmyWindowEvolved::LOG_ID_TRACE = "ArmyWindowEvolved_trace";
const QString ArmyWindowEvolved::LOG_ID_WARN = "ArmyWindowEvolved_warm";
const QString ArmyWindowEvolved::LOG_ID_ERR = "ArmyWindowEvolved_err";

const QStringList ArmyWindowEvolved::OPTION_HEADER = QStringList()
                            << QObject::tr("Regiment")
                            << QObject::tr("Nombre")
                            << QObject::tr("Pts")
                            << QObject::tr("Options")
                            << QObject::tr("#");


ArmyWindowEvolved::ArmyWindowEvolved(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmyWindowEvolved)
{
    initArmyWindow();
}

ArmyWindowEvolved::~ArmyWindowEvolved()
{
    delete ui;
}

void ArmyWindowEvolved::initArmyWindow()
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    ui->setupUi(this);

    QLog_Trace(LOG_ID_TRACE, "Opening Army window Evolved");

    setWindowTitle("Warhole " +
                   WARHOLE_VERSION_STRING +
                   tr(" - Création d'armée (evolved)"));

    // get list of existing races
    QDir* modelDir = new QDir(MODEL_PATH);
    QStringList existingRaces;

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

    // Setting up army display panel
    armyModel = new QStandardItemModel();
    ui->treeView->setModel(armyModel);
    armyModel->setHorizontalHeaderLabels(OPTION_HEADER);

    baseItem = new QStandardItem(tr("Base"));
    specialItem = new QStandardItem(tr("Special"));
    rareItem = new QStandardItem(tr("Rare"));
    characterItem = new QStandardItem(tr("Personnage"));

    QFont f = baseItem->font();
    f.setItalic(true);

    // Put Base, Special and Rare italic
    baseItem->setFont(f);
    specialItem->setFont(f);
    rareItem->setFont(f);
    characterItem->setFont(f);

    armyModel->appendRow(baseItem);
    armyModel->appendRow(specialItem);
    armyModel->appendRow(rareItem);
    armyModel->appendRow(characterItem);

    // We want to hide the Id collumn
    ui->treeView->hideColumn(ITEM_ID_COLUMN);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    deleteRegimentAction = new QAction(tr("Supprimer"), this);
    connect(deleteRegimentAction, SIGNAL(triggered()), this, SLOT(deleteRegiment()));
    duplicateRegimentAction = new QAction(tr("Dupliquer"), this);
    connect(duplicateRegimentAction, SIGNAL(triggered()), this, SLOT(duplicateRegiment()));
    editRegimentAction = new QAction(tr("Editer"), this);
    connect(editRegimentAction, SIGNAL(triggered()), this, SLOT(editRegiment()));

    updateGlobalArmyPoints();
}

/**
 * @brief ArmyWindowEvolved::appendRegimentToTreeViewCategory Appends a regiment item in the tree view
 * @param id ID corresponding to the place in the army's regiment list. ID is used to find the regiment in the army if needed
 *        for duplication, deletion or modification
 * @param r Regiment to be appended
 * @param category Either Base, Special or Rare item
 */
void ArmyWindowEvolved::appendRegimentToTreeViewCategory(int id, RegimentAbstract r, QStandardItem* category)
{
    QList<QStandardItem*> itemList;
    QStandardItem* item;
    QString options;
    bool firstOption = true;
    item = new QStandardItem(r.getName());
    itemList.append(item);
    item = new QStandardItem(QString::number(r.computeTotalNb()));
    itemList.append(item);
    item = new QStandardItem(QString::number(r.computePoints()));
    itemList.append(item);

    // Fill options
    if(r.getGroups().first().getModel()->getMusician())
    {
        options += tr("Musicien");
        firstOption = false;
    }
    if(r.getGroups().first().getModel()->getBanner())
    {
        if(!firstOption)
            options += ", ";
        options += tr("Bannière");
        firstOption = false;
    }
    if(r.getGroups().first().getModel()->getChampion())
    {
        if(!firstOption)
            options += ", ";
        options += tr("Champion");
        firstOption = false;
    }
    for(int i = 0; i < r.getGroups().first().getModel()->getOptions().size(); ++i)
    {
        if(r.getGroups().first().getModel()->getOptions().at(i).isActivated())
        {
            if(!firstOption)
                options += ", ";
            options += r.getGroups().first().getModel()->getOptions().at(i).getName();
            firstOption = false;
        }
    }
    for(int i = 0; i < r.getGroups().first().getObjects().length(); ++i)
    {
        if(!firstOption)
            options += ", ";
        options += r.getGroups().first().getObjects().at(i).getName();
    }
    item = new QStandardItem(options);
    itemList.append(item);
    item = new QStandardItem(QString::number(id));
    itemList.append(item);
    category->appendRow(itemList);
}

void ArmyWindowEvolved::on_toolButtonAdd_clicked()
{
    // More that the "<none>" selection item in the combo box
    if(ui->comboBoxRace->count() > 1)
    {
        RegimentAbstract *newRegiment = new RegimentAbstract();
        regDialog = new AddRegimentDialog(ui->comboBoxRace->itemText(ui->comboBoxRace->currentIndex()), newRegiment, false);
        regDialog->setModal(true);

        if(regDialog->exec() == QDialog::Accepted)
        {
            QLog_Info(LOG_ID_INFO, "Added Regiment : " + newRegiment->displayInfo());

            currentArmy.addUnit(*newRegiment);
            refreshArmyList();
        }
        newRegiment->deleteLater();
    }
    else
    {
        QMessageBox::warning(this, tr("Races"), tr("Aucune race existente. Veuillez créer des figurines pour pouvoir constituer une armée."));
    }
}

/**
 * @brief ArmyWindowEvolved::on_toolButtonPdf_clicked Slot called when the pdf button is clicked
 */
void ArmyWindowEvolved::on_toolButtonPdf_clicked()
{
    currentArmy.setName(ui->lineEditArmyName->text());
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

/**
 * @brief ArmyWindowEvolved::updateGlobalArmyPoints Sets the army points label with the total army points
 */
void ArmyWindowEvolved::updateGlobalArmyPoints()
{
    ui->labelPts->setText(QString::number(currentArmy.computePoints()));
}

/**
 * @brief ArmyWindowEvolved::refreshArmyList This function gets all the regiments from the Army object and put them
 *        inside the tab view
 */
void ArmyWindowEvolved::refreshArmyList()
{
    clearAllCategories();
    for(int i = 0; i < currentArmy.getUnits().size(); ++i)
    {
        RegimentAbstract reg = currentArmy.getUnits().at(i);
        switch(reg.getGroups().first().getModel()->getType())
        {
        case BASE:
            appendRegimentToTreeViewCategory(i, reg, baseItem);
            break;
        case SPECIAL:
            appendRegimentToTreeViewCategory(i, reg, specialItem);
            break;
        case RARE:
            appendRegimentToTreeViewCategory(i, reg, rareItem);
            break;
        case CHARACTER:
            appendRegimentToTreeViewCategory(i, reg, characterItem);
            break;
        default:
            break;
        }
    }
    updateGlobalArmyPoints();
}

/**
 * @brief ArmyWindowEvolved::clearAllCategories Clears all regiments in each category
 */
void ArmyWindowEvolved::clearAllCategories()
{
    baseItem->removeRows(0, baseItem->rowCount());
    specialItem->removeRows(0, specialItem->rowCount());
    rareItem->removeRows(0, rareItem->rowCount());
    characterItem->removeRows(0, characterItem->rowCount());
}

/**
 * @brief ArmyWindowEvolved::on_treeView_customContextMenuRequested Slot requesting the context menu
 * @param pos mouse position
 */
void ArmyWindowEvolved::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index =ui->treeView->indexAt(pos);

    // Check that index is valid and that index is not "base", "special" or "rare"
    if(index.isValid() && armyModel->itemFromIndex(index)->parent() != NULL)
    {
        // Get the id from the row
        currentSelectedRegimentId = armyModel->index(index.row(), ITEM_ID_COLUMN, index.parent()).data().toInt();
        QLog_Trace(LOG_ID_TRACE, "Context menu opened for id : " + QString::number(currentSelectedRegimentId));

        QMenu *menu=new QMenu(this);
        menu->addAction(deleteRegimentAction);
        menu->addAction(duplicateRegimentAction);
        menu->addAction(editRegimentAction);
        menu->popup(ui->treeView->viewport()->mapToGlobal(pos));
    }
}

/**
 * @brief ArmyWindowEvolved::deleteRegiment This is called when the "delete" context menu is activated
 *        This means that an item id is selected. We delete this id from the army.
 */
void ArmyWindowEvolved::deleteRegiment()
{
    currentArmy.removeUnit(currentArmy.getUnits().at(currentSelectedRegimentId));
    refreshArmyList();
}

void ArmyWindowEvolved::duplicateRegiment()
{
    currentArmy.addUnit(currentArmy.getUnits().at(currentSelectedRegimentId));
    refreshArmyList();
}

void ArmyWindowEvolved::editRegiment()
{
    RegimentAbstract *newRegiment = new RegimentAbstract(currentArmy.getUnits().at(currentSelectedRegimentId));
    regDialog = new AddRegimentDialog(ui->comboBoxRace->itemText(ui->comboBoxRace->currentIndex()), newRegiment, true);
    regDialog->setModal(true);

    if(regDialog->exec() == QDialog::Accepted)
    {
        QLog_Info(LOG_ID_INFO, "Edited Regiment : " + newRegiment->displayInfo());

        // Remove previous one
        currentArmy.removeUnit(currentArmy.getUnits().at(currentSelectedRegimentId));
        // Add edited one
        currentArmy.addUnit(*newRegiment);
        refreshArmyList();
    }
    newRegiment->deleteLater();
}

void ArmyWindowEvolved::on_toolButtonSave_clicked()
{
    if(ui->lineEditArmyName->text().isEmpty() ||
       currentArmy.getUnits().size() == 0)
    {
        QMessageBox::warning(this, tr("Info"),
                tr("Vous devez donner un nom à l'armée et y ajouter des régiments."));
        return;
    }

    currentArmy.setName(ui->lineEditArmyName->text());

    QString path = ARMY_PATH + "/" + ui->comboBoxRace->itemText(ui->comboBoxRace->currentIndex()) +
            "/" + ui->lineEditArmyName->text() +".army";

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

void ArmyWindowEvolved::on_toolButton_Load_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Model"),
            "./armies", tr("Model files (*.army)"));

    load(fileName);
}

/**
 * @brief ArmyWindowEvolved::load Loads the army file at the specified path
 * @param path Army file path
 */
void ArmyWindowEvolved::load(QString path)
{
    QLog_Info(LOG_ID_INFO, "load() : Loading army : " + path);
    if(!path.isEmpty())
    {
        currentArmy.load(path);
        QLog_Info(LOG_ID_INFO, "Army loaded : ");
        QLog_Info(LOG_ID_INFO, currentArmy.displayInfo());
        refreshArmyList();

        // Get the race from the path to load it in the combo box
        QString s = path.section('/',-2,-2);
        ui->comboBoxRace->setCurrentText(s);
        ui->lineEditArmyName->setText(currentArmy.getName());
    }
    else
    {
        QLog_Error(LOG_ID_INFO, "load() : The path is empyty");
    }
}
