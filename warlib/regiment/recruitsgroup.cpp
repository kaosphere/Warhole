#include "recruitsgroup.h"

RecruitsGroup::RecruitsGroup()
{
    model = new ModelAbstract();
    casualties = 0;
    nb = 0;
    path = "";
}

RecruitsGroup::RecruitsGroup(const int &n, const int &c, const QString& p)
{
    casualties = c;
    nb = n;
    path = p;
    model = fac.createFromFile(path);
}

RecruitsGroup::~RecruitsGroup()
{
    delete model;
}

QDataStream & operator <<(QDataStream& out, const RecruitsGroup& obj)
{
    // Model is not in the serialization because we want the regiment to be bound with
    // a .unit file which is susceptible to change over time
    out << obj.nb
        << obj.casualties
        << obj.path;

    return out;
}

QDataStream & operator >>(QDataStream& in, RecruitsGroup& obj)
{
    // Same comment that for other stream operator
    in >> obj.nb;
    in >> obj.casualties;
    in >> obj.path;

    return in;
}

ModelAbstract *RecruitsGroup::getModel() const
{
    return model;
}

void RecruitsGroup::setModel(ModelAbstract *value)
{
    model = value;
}

QString RecruitsGroup::getPath() const
{
    return path;
}

void RecruitsGroup::setPath(const QString &value)
{
    path = value;
}

bool RecruitsGroup::operator==(const RecruitsGroup &obj)
{
    if(nb == obj.nb &&
       casualties == obj.casualties &&
       path == obj.path)
    {
        return true;
    }
    else return false;
}

int RecruitsGroup::computePoints()
{

}

int RecruitsGroup::getCasualties() const
{
    return casualties;
}

void RecruitsGroup::setCasualties(int value)
{
    casualties = value;
}

int RecruitsGroup::getNb() const
{
    return nb;
}

void RecruitsGroup::setNb(int value)
{
    nb = value;
}
