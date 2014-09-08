#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QObject>

#include <warlibinitializer.h>
#include <Utilities/QLogger/QLogger.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialization of the warlib
    WarlibInit::initWarlib();

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8") );

    MainWindow w;

    w.show();
    
    return a.exec();
}
