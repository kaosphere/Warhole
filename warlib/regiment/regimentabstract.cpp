#include "regimentabstract.h"

RegimentAbstract::RegimentAbstract()
{
    name = "";
    musician = false;
    champion = false;
    skirmishers = false;
    banner = false;
}

RegimentAbstract::RegimentAbstract(const QString &n,
                                   const bool &m,
                                   const bool &s,
                                   const bool &c,
                                   const bool &b,
                                   const StatsModel& st,
                                   const QList<RecruitsGroup> g)
{
    name = n;
    musician = m;
    skirmishers = s;
    champion = c;
    banner = b;
    championStats = st;
    groups = g;
}

RegimentAbstract::RegimentAbstract(const RegimentAbstract &u)
{
    name = u.name;
    musician = u.musician;
    skirmishers = u.skirmishers;
    champion = u.champion;
    banner = u.banner;
    championStats = u.championStats;
    groups = u.groups;
}


bool RegimentAbstract::getMusician() const
{
    return musician;
}

void RegimentAbstract::setMusician(bool value)
{
    musician = value;
}

bool RegimentAbstract::getSkirmishers() const
{
    return skirmishers;
}

void RegimentAbstract::setSkirmishers(bool value)
{
    skirmishers = value;
}

bool RegimentAbstract::getChampion() const
{
    return champion;
}

void RegimentAbstract::setChampion(bool value)
{
    champion = value;
}

QString RegimentAbstract::getName() const
{
    return name;
}

void RegimentAbstract::setName(const QString &value)
{
    name = value;
}

QList<RecruitsGroup> RegimentAbstract::getGroups() const
{
    return groups;
}

void RegimentAbstract::setGroups(const QList<RecruitsGroup> &value)
{
    groups = value;
}

void RegimentAbstract::addGroup(RecruitsGroup r)
{
    groups.append(r);
}

void RegimentAbstract::removeGroup(RecruitsGroup r)
{
    groups.removeOne(r);
}

bool RegimentAbstract::getBanner() const
{
    return banner;
}

void RegimentAbstract::setBanner(bool value)
{
    banner = value;
}

StatsModel RegimentAbstract::getChampionStats() const
{
    return championStats;
}

void RegimentAbstract::setChampionStats(const StatsModel &value)
{
    championStats = value;
}

int RegimentAbstract::getPoints() const
{
    return points;
}

void RegimentAbstract::setPoints(int value)
{
    points = value;
}

int RegimentAbstract::getStartingCount() const
{
    return startingCount;
}

void RegimentAbstract::setStartingCount(int value)
{
    startingCount = value;
}

int RegimentAbstract::computePoints()
{
    int points = 0;
    QList<RecruitsGroup>::Iterator i;
    for(i=groups.begin();i<groups.end();++i)
    {
        points += (i->getNb() * i->getModel()->computePoints());
    }
}

QDataStream &operator <<(QDataStream & out, const RegimentAbstract & obj)
{
    out << obj.name
        << obj.banner
        << obj.musician
        << obj.champion
        << obj.skirmishers
        << obj.championStats
        << obj.points
        << obj.startingCount
        << obj.groups.size();

    for(int i; i<obj.groups.size();++i)
    {
        out << obj.groups[i];
    }

    return out;
}

QDataStream &operator >>(QDataStream & in, RegimentAbstract & obj)
{
    int size;

    in >> obj.name;
    in >> obj.banner;
    in >> obj.musician;
    in >> obj.champion;
    in >> obj.skirmishers;
    in >> obj.championStats;
    in >> obj.points;
    in >> obj.startingCount;
    in >> size;

    for(int i = 0; i < size; ++i)
    {
        RecruitsGroup r;
        in >> r;
        obj.addGroup(r);
    }

    return in;
}
