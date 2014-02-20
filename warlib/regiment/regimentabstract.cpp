#include "regimentabstract.h"

RegimentAbstract::RegimentAbstract()
{
    name = "";
    musician = false;
    musicianPoints = 0;
    champion = false;
    skirmishers = false;
    banner = false;
    points = 0;
    startingCount = 0;
}

RegimentAbstract::RegimentAbstract(const QString &n,
                                   const bool &m,
                                   const int & mp,
                                   const bool &s,
                                   const bool &c,
                                   const bool &b,
                                   const StatsModel& st,
                                   const QMap<RecruitsGroup> g,
                                   const int& p,
                                   const int& sc)
{
    name = n;
    musician = m;
    musicianPoints = mp;
    skirmishers = s;
    champion = c;
    banner = b;
    championStats = st;
    groups = g;
    points = p;
    startingCount = sc;
}

RegimentAbstract::RegimentAbstract(const RegimentAbstract &u)
{
    name = u.name;
    musician = u.musician;
    musicianPoints = u.musiciantPoints;
    skirmishers = u.skirmishers;
    champion = u.champion;
    banner = u.banner;
    championStats = u.championStats;
    groups = u.groups;
    points = u.points;
    startingCount = u.startingCount;
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

QMap<QString, RecruitsGroup> RegimentAbstract::getGroups() const
{
    return groups;
}

void RegimentAbstract::setGroups(const QMap<QString, RecruitsGroup> &value)
{
    groups = value;
}

void RegimentAbstract::addGroup(const RecruitsGroup& r)
{
	groups.insert(r.getModel()->getStats().getName(), r);
}

void RegimentAbstract::removeGroup(const RecruitsGroup& r)
{
    groups.remove(r.getModel()->getStats().getName());
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

int RegimentAbstract::getMusicianPoints() const
{
	return musicianPoints;
}

void RegimentAbstract::setMusicianPoints(const int& value)
{
	musicianPoints = value;
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
    QMap<QString, RecruitsGroup>::const_iterator i = map.constBegin();
	while (i != map.constEnd()) {
		points += i.value().computePoints();
		++i;
	}
	if(musician)
	{
		points += musicianPoints;
	}
	if(champion)
	{
		points += championStats.getPoints();
	}
	return points;
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

    QMap<QString, RecruitsGroup>::const_iterator i = map.constBegin();
	while (i != map.constEnd()) {
		out << i.value();
		++i;
	}
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

bool RegimentAbstract::operator==(const RegimentAbstract& obj)
{
	if(name == obj.name &&
		musician == obj.musician &&
		musicianPoints == obj.musiciantPoints &&
		skirmishers == obj.skirmishers &&
		champion == obj.champion &&
		banner == obj.banner &&
		championStats == obj.championStats &&
		groups == obj.groups &&
		points == obj.points &&
		startingCount == obj.startingCount)
	{
		return true;
	}
	else return false;
}
