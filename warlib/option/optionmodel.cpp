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

OptionModel::OptionModel(const OptionModel &obj)
{
    name = obj.name;
    nbPoints = obj.nbPoints;
    activated = obj.activated;
    specialRules = obj.specialRules;
}

OptionModel::~OptionModel()
{
}

bool OptionModel::operator ==(const OptionModel &o)
{
    if(name == o.name && nbPoints == o.nbPoints && activated == o.activated && specialRules == o.specialRules)
        return true;
    else return false;
}

OptionModel &OptionModel::operator =(const OptionModel & obj)
{
    name = obj.name;
    nbPoints = obj.nbPoints;
    activated = obj.activated;
    specialRules = obj.specialRules;
}

QString OptionModel::displayString()
{
    QString s;
    QTextStream info(&s);
    info << name << endl;
    info << "Points :                   " << nbPoints << endl;
    info << "Rules :                    " << specialRules << endl;
    info << "Selected :                 " << activated << endl;
    return s;
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

QDataStream & operator <<(QDataStream & out, const OptionModel & obj)
{
    out << obj.name
        << obj.nbPoints
        << obj.activated
        << obj.specialRules;

    return out;
}

QDataStream & operator >>(QDataStream & in, OptionModel & obj)
{
    in >> obj.name;
    in >> obj.nbPoints;
    in >> obj.activated;
    in >> obj.specialRules;

    return in;
}
