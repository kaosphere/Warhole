#include "magicalobject.h"

MagicalObject::MagicalObject(QObject *parent) :
    QObject(parent)
{
    name = "";
    points = 0;
    specialRules = "";
    cabalistic = false;
}

MagicalObject::MagicalObject(QString n, int p, bool c, QString s, QObject *parent) : QObject(parent)
{
    name = n;
    points = p;
    cabalistic = c;
    specialRules = s;
}

MagicalObject::MagicalObject(const MagicalObject &copy) : QObject(copy.parent())
{
    name = copy.name;
    points = copy.points;
    cabalistic = copy.cabalistic;
    specialRules = copy.specialRules;
}

MagicalObject::~MagicalObject()
{

}
QString MagicalObject::getName() const
{
    return name;
}

void MagicalObject::setName(const QString &value)
{
    name = value;
}
int MagicalObject::getPoints() const
{
    return points;
}

void MagicalObject::setPoints(int value)
{
    points = value;
}
QString MagicalObject::getSpecialRules() const
{
    return specialRules;
}

void MagicalObject::setSpecialRules(const QString &value)
{
    specialRules = value;
}
bool MagicalObject::getCabalistic() const
{
    return cabalistic;
}

void MagicalObject::setCabalistic(bool value)
{
    cabalistic = value;
}

bool MagicalObject::operator==(const MagicalObject &other)
{
    if(name == other.name &&
       points == other.points &&
       specialRules == other.specialRules &&
       cabalistic == other.cabalistic)
    {
        return true;
    }
    else return false;
}

MagicalObject &MagicalObject::operator=(const MagicalObject &other)
{
    name = other.name;
    points = other.points;
    specialRules = other.specialRules;
    cabalistic = other.cabalistic;

    return *this;
}

QString MagicalObject::displayString()
{
    QString s;
    QTextStream info(&s);
    info << name << endl;
    if(cabalistic) info << "Cabalistic object";
    info << "Points :                   " << points << endl;
    info << "Rules :                    " << specialRules << endl;
    return s;
}

QString MagicalObject::getHtml()
{
    QString html;
    html += QString("%1 (%3 pts)<tr>\n")
            .arg(name)
            .arg(QString::number(points));
    if(cabalistic) html += QString("Cabalistic : %1\n")
            .arg(specialRules);
    return html;
}

QDataStream &operator <<(QDataStream & out, const MagicalObject & obj)
{
    out << SAVE_VERSION
        << obj.name
        << obj.points
        << obj.specialRules
        << obj.cabalistic;

    return out;
}

QDataStream &operator >>(QDataStream &in, MagicalObject &obj)
{
    int version = 0;

    in >> version;
    in >> obj.name;
    in >> obj.points;
    in >> obj.specialRules;
    in >> obj.cabalistic;

    return in;
}




