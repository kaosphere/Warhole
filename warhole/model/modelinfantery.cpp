#include "modelinfantery.h"

ModelInfantery::ModelInfantery():
    ModelAbstract()
{
}

ModelInfantery::ModelInfantery(const QString &n, const QString &move, const QString &weaponS,
                              const QString &balisticS, const QString &strength, const QString &toughness,
                              const QString &wounds, const QString &init, const QString &attacks,
                              const QString &leadership, const QString &save, const QString &invSave,
                              const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
                              bool figSup, const QString &specRules) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, widthBase, lengthBase, unitP, urlImage, figSup)
{
    specialRules = specRules;
}

ModelInfantery::ModelInfantery(const ModelInfantery &copy) : ModelAbstract(copy)
{
    specialRules = copy.specialRules;
}

QString ModelInfantery::getSpecialRules() const
{
    return specialRules;
}

void ModelInfantery::setSpecialRules(const QString &value)
{
    specialRules = value;
}

