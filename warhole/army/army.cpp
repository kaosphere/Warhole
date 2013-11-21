#include "army.h"

Army::Army()
{
}

QString Army::getName() const
{
    return name;
}

void Army::setName(const QString &value)
{
    name = value;
}


QList<UnitAbstract> Army::getUnits() const
{
    return units;
}

void Army::setUnits(const QList<UnitAbstract> &value)
{
    units = value;
}


void Army::addUnit(const UnitAbstract &u)
{
    units.append(u);
}

void Army::removeUnit(const UnitAbstract &u)
{
    units.removeOne(u);
}

unsigned int Army::getPoints() const
{
    return points;
}

void Army::setPoints(unsigned int value)
{
    points = value;
}
