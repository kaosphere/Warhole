#include "modelanimal.h"

ModelAnimal::ModelAnimal(QObject *parent):
    ModelAbstract(parent)
{
}

ModelAnimal::ModelAnimal(const QString &n, const QString &move, const QString &weaponS,
                              const QString &balisticS, const QString &strength, const QString &toughness,
                              const QString &wounds, const QString &init, const QString &attacks,
                              const QString &leadership, const QString &save, const QString &invSave, const int &widthBase,
                              const int &lengthBase, const int &unitP, const QString &urlImage, bool figSup,
                              const QString &specRules, QObject *parent) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, widthBase, lengthBase, unitP, urlImage, figSup, parent)
{
    specialRules = specRules;
}

QString ModelAnimal::getSpecialRules() const
{
    return specialRules;
}

void ModelAnimal::setSpecialRules(const QString &value)
{
    specialRules = value;
}

