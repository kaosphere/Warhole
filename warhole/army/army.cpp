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

QDataStream &operator <<(QDataStream & out, const Army & obj)
{
    out << obj.name
        << obj.points
        << obj.units.size();
    for(int i = 0; i < obj.units.size(); i++)
    {
        out << obj.units[i];
    }

    return out;
}

QDataStream &operator >>(QDataStream & in, Army & obj)
{
    int nb;

    in >> obj.name;
    in >> obj.points;
    in >> nb;

    for(int i = 0 ; i < nb ; i++)
    {
        UnitAbstract u;
        in >> u;
        obj.addUnit(u);
    }

    return in;
}
