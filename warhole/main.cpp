#include "mainwindow.h"
#include <QApplication>

#include"model/modelanimal.h"
#include"model/modelcavalry.h"
#include"model/modelcharacter.h"
#include"model/modelcharriot.h"
#include"model/modelinfantery.h"
#include"model/modelmonster.h"
#include"model/modelwarmachine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ModelCavalry::initModelCavalrySystem();
    ModelCharacter::initModelCharacterSystem();
    ModelCharriot::initModelCharriotSystem();
    ModelInfantery::initModelInfanterySystem();
    ModelMonster::initModelMonsterSystem();
    ModelWarMachine::initModelWarMachine();


    MainWindow w;
    w.show();
    
    return a.exec();
}
