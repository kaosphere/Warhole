#include "modelmonster.h"

ModelMonster::ModelMonster():
    ModelAbstract()
{
}

ModelMonster::ModelMonster(const QString &n, const QString &move, const QString &weaponS,
                                 const QString &balisticS, const QString &strength, const QString &toughness,
                                 const QString &wounds, const QString &init, const QString &attacks,
                                 const QString &leadership, const QString &save, const QString &invSave,
                                 const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
                                 bool figSup, const QString &specRules, bool hasCrew) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, widthBase, lengthBase, unitP, urlImage, figSup)
{
    specialRules = specRules;
    hasACrew = hasCrew;
}

QString ModelMonster::getSpecialRules() const
{
    return specialRules;
}

void ModelMonster::setSpecialRules(const QString &value)
{
    specialRules = value;
}

QList<ModelInfantery *> ModelMonster::getCrew() const
{
    return crew;
}

void ModelMonster::setCrew(const QList<ModelInfantery *> &value)
{
    crew = value;
}

void ModelMonster::addCrewMember(ModelInfantery *c)
{
    crew<<c;
}

void ModelMonster::removeCrewMember(ModelInfantery *c)
{
    crew.removeOne(c);
}


bool ModelMonster::getHasACrew() const
{
    return hasACrew;
}

void ModelMonster::setHasACrew(bool value)
{
    hasACrew = value;
}
