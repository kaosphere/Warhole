#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include <warlibinitializer.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialization of the warlib
    WarlibInit::initWarlib();

    MainWindow w;
    w.show();
    
    return a.exec();
}
