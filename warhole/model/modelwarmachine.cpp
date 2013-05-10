#include "modelwarmachine.h"

ModelWarMachine::ModelWarMachine():
    ModelAbstract()
{
}

ModelWarMachine::ModelWarMachine(const QString &n, const QString &move, const QString &weaponS,
                                 const QString &balisticS, const QString &strength, const QString &toughness,
                                 const QString &wounds, const QString &init, const QString &attacks,
                                 const QString &leadership, const QString &save, const QString &invSave, const int points,
                                 const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
                                 bool figSup, const QString &specRules) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, points, widthBase, lengthBase, unitP, urlImage, figSup)
{
    specialRules = specRules;
}

QString ModelWarMachine::getSpecialRules() const
{
    return specialRules;
}

void ModelWarMachine::setSpecialRules(const QString &value)
{
    specialRules = value;
}

QList<ModelInfantery *> ModelWarMachine::getCrew() const
{
    return crew;
}

void ModelWarMachine::setCrew(const QList<ModelInfantery *> &value)
{
    crew = value;
}

void ModelWarMachine::addCrewMember(ModelInfantery *c)
{
    crew<<c;
}

void ModelWarMachine::removeCrewMember(ModelInfantery *c)
{
    crew.removeOne(c);
}
