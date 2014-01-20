#include "mainwindow.h"
#include <QApplication>

#include"model/modelanimal.h"
#include"model/modelcavalry.h"
#include"model/modelcharacter.h"
#include"model/modelcharriot.h"
#include"model/modelinfantery.h"
#include"model/modelmonster.h"
#include"model/modelwarmachine.h"
#include"model/modelfactory.h"
#include"defines.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ModelCavalry::initModelCavalrySystem();
    ModelCharacter::initModelCharacterSystem();
    ModelCharriot::initModelCharriotSystem();
    ModelInfantery::initModelInfanterySystem();
    ModelMonster::initModelMonsterSystem();
    ModelWarMachine::initModelWarMachine();

    ModelFactory::associateKeyToClass(CAVALERY_STRING,new ModelCavalry);
    ModelFactory::associateKeyToClass(CHARACTER_STRING,new ModelCharacter);
    ModelFactory::associateKeyToClass(CHARRIOT_STRING,new ModelCharriot);
    ModelFactory::associateKeyToClass(INFANTERY_STRING,new ModelInfantery);
    ModelFactory::associateKeyToClass(MONSTER_STRING,new ModelMonster);
    ModelFactory::associateKeyToClass(WARMACHINE_STRING,new ModelWarMachine);

    MainWindow w;
    w.show();
    
    return a.exec();
}
