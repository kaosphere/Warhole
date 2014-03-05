#include "warlibinitializer.h"


WarlibInit::WarlibInit()
{
}

void WarlibInit::initWarlib()
{
    initModelSerialization();
    initModelFactory();
    DiceRoller::initDiceRoller();
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
