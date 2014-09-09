#include "warlibinitializer.h"


WarlibInit::WarlibInit()
{

}

void WarlibInit::initWarlib()
{
    qDebug() << "Initialization of the warlib";
    // remove log file of previous rum
    QFile logFile("logs/lastrun.log");
    if(logFile.exists())
    {
        qDebug() << "removing previous log file";
        logFile.remove();
    }
    else
        qDebug() << "No logFile not found !";

    initModelSerialization();
    initModelFactory();
    DiceRoller::initDiceRoller();
    PdfExporter::initPdfExporter();
}

void WarlibInit::initModelSerialization()
{
    ModelCavalry::initModelCavalrySystem();
    ModelCharacter::initModelCharacterSystem();
    ModelCharriot::initModelCharriotSystem();
    ModelInfantery::initModelInfanterySystem();
    ModelMonster::initModelMonsterSystem();
    ModelWarMachine::initModelWarMachine();
    Army::initArmySystem();
    MagicalObject::initMagicalObjectSystem();
}

void WarlibInit::initModelFactory()
{
    ModelFactory::associateKeyToClass(CAVALERY_STRING,new ModelCavalry);
    ModelFactory::associateKeyToClass(CHARACTER_STRING,new ModelCharacter);
    ModelFactory::associateKeyToClass(CHARRIOT_STRING,new ModelCharriot);
    ModelFactory::associateKeyToClass(INFANTERY_STRING,new ModelInfantery);
    ModelFactory::associateKeyToClass(MONSTER_STRING,new ModelMonster);
    ModelFactory::associateKeyToClass(WARMACHINE_STRING,new ModelWarMachine);
}
