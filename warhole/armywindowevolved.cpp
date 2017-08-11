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
                            << QObject::tr("Options");


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

    QFont f = baseItem->font();
    f.setItalic(true);

    // Put Base, Special and Rare italic
    baseItem->setFont(f);
    specialItem->setFont(f);
    rareItem->setFont(f);

    armyModel->appendRow(baseItem);
    armyModel->appendRow(specialItem);
    armyModel->appendRow(rareItem);

    updateGlobalArmyPoints();
}

/**
 * @brief ArmyWindowEvolved::appendRegimentToTreeViewCategory Appends a regiment item in the tree view
 * @param r Regiment to be appended
 * @param category Either Base, Special or Rare item
 */
void ArmyWindowEvolved::appendRegimentToTreeViewCategory(RegimentAbstract* r, QStandardItem* category)
{
    QList<QStandardItem*> itemList;
    QStandardItem* item;
    QString options;
    bool firstOption = true;

    item = new QStandardItem(r->getName());
    itemList.append(item);
    item = new QStandardItem(QString::number(r->computeTotalNb()));
    itemList.append(item);
    item = new QStandardItem(QString::number(r->computePoints()));
    itemList.append(item);

    // Fill options
    if(r->getGroups().first().getModel()->getMusician())
    {
        options += tr("Musicien");
        firstOption = false;
    }
    if(r->getGroups().first().getModel()->getBanner())
    {
        if(!firstOption)
            options += ", ";
        options += tr("Bannière");
        firstOption = false;
    }
    if(r->getGroups().first().getModel()->getChampion())
    {
        if(!firstOption)
            options += ", ";
        options += tr("Champion");
        firstOption = false;
    }
    for(int i = 0; i < r->getGroups().first().getModel()->getOptions().size(); ++i)
    {
        if(r->getGroups().first().getModel()->getOptions().at(i).isActivated())
        {
            if(!firstOption)
                options += ", ";
            options += r->getGroups().first().getModel()->getOptions().at(i).getName();
            firstOption = false;
        }
    }
    for(int i = 0; i < r->getGroups().first().getObjects().length(); ++i)
    {
        if(!firstOption)
            options += ", ";
        options += r->getGroups().first().getObjects().at(i).getName();
    }
    item = new QStandardItem(options);
    itemList.append(item);
    category->appendRow(itemList);
}

void ArmyWindowEvolved::on_toolButtonAdd_clicked()
{
    // More that the "<none>" selection item in the combo box
    if(ui->comboBoxRace->count() > 1)
    {
        RegimentAbstract *newRegiment = new RegimentAbstract();
        regDialog = new AddRegimentDialog(ui->comboBoxRace->itemText(ui->comboBoxRace->currentIndex()), newRegiment);
        regDialog->setModal(true);

        if(regDialog->exec() == QDialog::Accepted)
        {
            QLog_Info(LOG_ID_INFO, "Added Regiment : " + newRegiment->displayInfo());

            switch(newRegiment->getGroups().first().getModel()->getType())
            {
            case BASE:
                appendRegimentToTreeViewCategory(newRegiment, baseItem);
                break;
            case SPECIAL:
                appendRegimentToTreeViewCategory(newRegiment, specialItem);
                break;
            case RARE:
                appendRegimentToTreeViewCategory(newRegiment, rareItem);
                break;
            default:
                break;
            }
            currentArmy.addUnit(*newRegiment);
            updateGlobalArmyPoints();
        }
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
