#include "optionmodel.h"

OptionModel::OptionModel(QObject *parent) :
    QObject(parent)
{
}

OptionModel::OptionModel(const QString &n, const int &pts, const bool &act, const QString &specRules,
                         QObject *parent) :
    QObject(parent)
{
    name = n;
    nbPoints = pts;
    activated = act;
    specialRules = specRules;
}

QString OptionModel::getName() const
{
    return name;
}

void OptionModel::setName(const QString &value)
{
    name = value;
}

bool OptionModel::getActivated() const
{
    return activated;
}

void OptionModel::setActivated(bool value)
{
    activated = value;
}

int OptionModel::getNbPoints() const
{
    return nbPoints;
}

void OptionModel::setNbPoints(int value)
{
    nbPoints = value;
}

QString OptionModel::getSpecialRules() const
{
    return specialRules;
}

void OptionModel::setSpecialRules(const QString &value)
{
    specialRules = value;
}
