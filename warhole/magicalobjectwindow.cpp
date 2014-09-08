#include "magicalobjectwindow.h"
#include "ui_magicalobjectwindow.h"

using namespace QLogger;

const QString MagicalObjectWindow::LOG_ID_INFO = "MagicalObjectWindow_info";
const QString MagicalObjectWindow::LOG_ID_TRACE = "MagicalObjectWindow_trace";
const QString MagicalObjectWindow::LOG_ID_WARN = "MagicalObjectWindow_warm";
const QString MagicalObjectWindow::LOG_ID_ERR = "MagicalObjectWindow_err";

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
}

MagicalObjectWindow::~MagicalObjectWindow()
{
    delete model;
    delete ui;
}

void MagicalObjectWindow::on_comboRace_currentTextChanged(const QString &raceDir)
{
    // get list of existing models to verify if some exist
    QDir* modelDir = new QDir(MAGICAL_OBJECT_PATH + "/" + raceDir);
    QStringList existingObjects;
    if (modelDir->exists())
    {
        existingObjects = modelDir->entryList();
    }
    if(existingObjects.isEmpty())
    {
        QLog_Info(LOG_ID_INFO, "on_comboBoxRace_currentIndexChanged() : No magical object found in race : " + raceDir);
    }

    // set the root path of the tree view
    ui->treeViewExistingObjects->setModel(model);
    ui->treeViewExistingObjects->setRootIndex(model->setRootPath(MAGICAL_OBJECT_PATH + "/" + raceDir));
    // hide size, type and date collumns
    ui->treeViewExistingObjects->hideColumn(1);
    ui->treeViewExistingObjects->hideColumn(2);
    ui->treeViewExistingObjects->hideColumn(3);
}
