#include "mainwindow.h"
#include <QApplication>

#include"model/modelanimal.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ModelAnimal::initModelAnimalSystem();



    MainWindow w;
    w.show();
    
    return a.exec();
}
