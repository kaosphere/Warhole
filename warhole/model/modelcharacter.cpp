#include "modelcharacter.h"


ModelCharacter::ModelCharacter():
    ModelAbstract()
{
}

ModelCharacter::ModelCharacter(const QString &n, const QString &move, const QString &weaponS,
                               const QString &balisticS, const QString &strength, const QString &toughness,
                               const QString &wounds, const QString &init, const QString &attacks,
                               const QString &leadership, const QString &save, const QString &invSave,
                               const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
                               bool figSup, const QString &specRules, bool lord, bool general, bool mage,
                               bool mounted) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, widthBase, lengthBase, unitP, urlImage, figSup)
{
    specialRules = specRules;
    isALord = lord;
    isTheGeneral = general;
    isAMage = mage;
    isMounted = mounted;
}

ModelCharacter::ModelCharacter(const ModelCharacter &copy) : ModelAbstract(copy)
{
    specialRules = copy.specialRules;
    isALord = copy.isALord;
    isTheGeneral = copy.isTheGeneral;
    isAMage = copy.isAMage;
    isMounted = copy.isMounted;
}

QString ModelCharacter::getSpecialRules() const
{
    return specialRules;
}

void ModelCharacter::setSpecialRules(const QString &value)
{
    specialRules = value;
}


bool ModelCharacter::getIsALord() const
{
    return isALord;
}

void ModelCharacter::setIsALord(bool value)
{
    isALord = value;
}

bool ModelCharacter::getIsTheGeneral() const
{
    return isTheGeneral;
}

void ModelCharacter::setIsTheGeneral(bool value)
{
    isTheGeneral = value;
}
bool ModelCharacter::getIsAMage() const
{
    return isAMage;
}

void ModelCharacter::setIsAMage(bool value)
{
    isAMage = value;
}

bool ModelCharacter::getIsMounted() const
{
    return isMounted;
}

void ModelCharacter::setIsMounted(bool value)
{
    isMounted = value;
}
