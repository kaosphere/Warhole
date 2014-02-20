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


QList<RegimentAbstract> Army::getUnits() const
{
    return units;
}

void Army::setUnits(const QList<RegimentAbstract> &value)
{
    units = value;
}


void Army::addUnit(const RegimentAbstract &u)
{
    units.append(u);
}

void Army::removeUnit(const RegimentAbstract &u)
{
	// Since Army will not be used as a game descriptor, we don't care 
	// removing one or the other if two regiments are identical
    units.removeOne(u);
}


QDataStream &operator <<(QDataStream & out, const Army & obj)
{
    out << obj.name
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
    in >> nb;

    for(int i = 0 ; i < nb ; i++)
    {
        RegimentAbstract u;
        in >> u;
        obj.addUnit(u);
    }

    return in;
}
