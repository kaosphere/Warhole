#include "optionmodel.h"

OptionModel::OptionModel(QObject *parent) : QObject(parent)
{
}

OptionModel::OptionModel(const QString &n, const int &pts, const bool &act, const QString &specRules, const bool& ro, QObject *parent) : QObject(parent)
{
    name = n;
    nbPoints = pts;
    activated = act;
    specialRules = specRules;
    regimentOptions = ro;
}

OptionModel::OptionModel(const OptionModel &obj) : QObject(obj.parent())
{
    name = obj.name;
    nbPoints = obj.nbPoints;
    activated = obj.activated;
    specialRules = obj.specialRules;
    regimentOptions = obj.regimentOptions;
}

OptionModel::~OptionModel()
{
}

bool OptionModel::operator ==(const OptionModel &o)
{
    if(name == o.name &&
       nbPoints == o.nbPoints &&
       specialRules == o.specialRules &&
       activated == o.activated &&
       regimentOptions == o.regimentOptions)
        return true;
    else return false;
}

OptionModel &OptionModel::operator =(const OptionModel & obj)
{
    name = obj.name;
    nbPoints = obj.nbPoints;
    activated = obj.activated;
    specialRules = obj.specialRules;
    regimentOptions = obj.regimentOptions;

    return *this;
}

QString OptionModel::displayString()
{
    QString s;
    QTextStream info(&s);
    info << name << " (" << nbPoints << " points";
    if(regimentOptions) info << tr(", régiment)") << endl;
    else info << ")" << endl;

    return s;
}

QString OptionModel::getHtml()
{
    QString html;
    html += QString("%1 (%3 pts)")
            .arg(name)
            .arg(QString::number(nbPoints));
    return html;
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

bool OptionModel::isRegimentOptions() const
{
    return regimentOptions;
}

void OptionModel::setRegimentOptions(bool value)
{
    regimentOptions = value;
}

QDataStream & operator <<(QDataStream & out, const OptionModel & obj)
{
    out << SAVE_VERSION
        << obj.name
        << obj.nbPoints
        << obj.activated
        << obj.specialRules
        << obj.regimentOptions;

    return out;
}

QDataStream & operator >>(QDataStream & in, OptionModel & obj)
{
    int version = 0;
    in >> version;
    in >> obj.name;
    in >> obj.nbPoints;
    in >> obj.activated;
    in >> obj.specialRules;
    in >> obj.regimentOptions;

    return in;
}
