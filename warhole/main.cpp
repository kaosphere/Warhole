#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include <warlibinitializer.h>
#include <Utilities/QLogger/QLogger.h>

using namespace QLogger;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialization of the warlib
    WarlibInit::initWarlib();

    // Start The logger
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList("General"), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList("Info"), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList("Warnings"), QLogger::WarnLevel);
    manager->addDestination("./logs/lastrun.log", QStringList("Errors"), QLogger::ErrorLevel);
    manager->addDestination("./logs/errors.log", QStringList("Errors2"), QLogger::ErrorLevel);

    MainWindow w;
    w.show();
    
    return a.exec();
}
