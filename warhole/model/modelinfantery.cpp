#include "modelinfantery.h"

ModelInfantery::ModelInfantery()
{
}

QString ModelInfantery::getSpecialRules() const
{
    return specialRules;
}

void ModelInfantery::setSpecialRules(const QString &value)
{
    specialRules = value;
}

