#include "armywindowevolved.h"
#include "ui_armywindowevolved.h"
#include "Utilities/QLogger/QLogger.h"

#include "version.h"

using namespace QLogger;

const QString ArmyWindowEvolved::LOG_ID_INFO = "ArmyWindow_info";
const QString ArmyWindowEvolved::LOG_ID_TRACE = "ArmyWindow_trace";
const QString ArmyWindowEvolved::LOG_ID_WARN = "ArmyWindow_warm";
const QString ArmyWindowEvolved::LOG_ID_ERR = "ArmyWindow_err";


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

    setWindowTitle("Warhole " +
                   WARHOLE_VERSION_STRING +
                   tr(" - Création d'armée (evolved)"));


}
