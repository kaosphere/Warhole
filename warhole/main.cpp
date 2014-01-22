#include "mainwindow.h"
#include <QApplication>
#include <QDebug>


#include <model/modelcavalry.h>
#include <model/modelcharacter.h>
#include <model/modelcharriot.h>
#include <model/modelinfantery.h>
#include <model/modelmonster.h>
#include <model/modelwarmachine.h>
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
