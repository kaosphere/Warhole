#include "optionmodel.h"

OptionModel::OptionModel()
{
}

OptionModel::OptionModel(const QString &n, const int &pts, const bool &act, const QString &specRules)
{
    name = n;
    nbPoints = pts;
    activated = act;
    specialRules = specRules;
}

bool OptionModel::operator ==(const OptionModel &o)
{
    if(name == o.name && nbPoints == o.nbPoints && activated == o.activated && specialRules == o.specialRules)
        return true;
    else return false;
}

QString OptionModel::getName() const
{
    return name;
}

void OptionModel::setName(const QString &value)
{
    name = value;
}

bool OptionModel::isActivated() const
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
