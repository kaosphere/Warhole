#include "modelcharriot.h"


ModelCharriot::ModelCharriot():
    ModelAbstract()
{
}

ModelCharriot::ModelCharriot(const QString &n, const QString &move, const QString &weaponS,
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

QString ModelCharriot::getSpecialRules() const
{
    return specialRules;
}

void ModelCharriot::setSpecialRules(const QString &value)
{
    specialRules = value;
}

QList<ModelAnimal *> ModelCharriot::getMount() const
{
    return mounts;
}

void ModelCharriot::setMount(const QList<ModelAnimal *> &value)
{
    mounts = value;
}

void ModelCharriot::addMount(ModelAnimal *m)
{
    mounts<<m;
}

void ModelCharriot::removeMount(ModelAnimal *m)
{
    mounts.removeOne(m);
}

QList<ModelInfantery *> ModelCharriot::getCrew() const
{
    return crew;
}

void ModelCharriot::setCrew(const QList<ModelInfantery *> &value)
{
    crew = value;
}

void ModelCharriot::addCrew(ModelInfantery *c)
{
    crew<<c;
}

void ModelCharriot::removeCrew(ModelInfantery *c)
{
    crew.removeOne(c);
}
