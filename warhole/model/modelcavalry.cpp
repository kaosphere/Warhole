#include "modelcavalry.h"

ModelCavalry::ModelCavalry(QObject *parent):
    ModelAbstract(parent)
{
}

ModelCavalry::ModelCavalry(const QString &n, const QString &move, const QString &weaponS,
                           const QString &balisticS, const QString &strength, const QString &toughness,
                           const QString &wounds, const QString &init, const QString &attacks,
                           const QString &leadership, const QString &save, const QString &invSave,
                           const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
                           bool figSup, const QString &specRules, QObject *parent) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, widthBase, lengthBase, unitP, urlImage, figSup, parent)
{
    specialRules = specRules;
}

QString ModelCavalry::getSpecialRules() const
{
    return specialRules;
}

void ModelCavalry::setSpecialRules(const QString &value)
{
    specialRules = value;
}

ModelAbstract *ModelCavalry::getMount() const
{
    return mount;
}

void ModelCavalry::setMount(ModelAbstract *value)
{
    mount = value;
}



