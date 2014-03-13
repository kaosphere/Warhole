#include "regimentabstract.h"

using namespace QLogger;

const QString RegimentAbstract::LOG_ID_INFO = "RegimentAbstract_info";
const QString RegimentAbstract::LOG_ID_TRACE = "RegimentAbstract_trace";
const QString RegimentAbstract::LOG_ID_WARN = "RegimentAbstract_warn";
const QString RegimentAbstract::LOG_ID_ERR = "RegimentAbstract_err";

RegimentAbstract::RegimentAbstract()
{
    QLoggerManager *manager = QLoggerManager::getInstance();
	manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

	
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
                                   const int &bp,
                                   const StatsModel& st,
                                   const QList<RecruitsGroup> g,
                                   const int& p,
                                   const int& sc)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
	manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

	
    name = n;
    musician = m;
    musicianPoints = mp;
    skirmishers = s;
    champion = c;
    banner = b;
    bannerPoints = bp;
    championStats = st;
    groups = g;
    points = p;
    startingCount = sc;
}

RegimentAbstract::RegimentAbstract(const RegimentAbstract &u)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
	manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

	
    name = u.name;
    musician = u.musician;
    musicianPoints = u.musicianPoints;
    skirmishers = u.skirmishers;
    champion = u.champion;
    banner = u.banner;
    bannerPoints = u.bannerPoints;
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

QList<RecruitsGroup> RegimentAbstract::getGroups() const
{
    return groups;
}

void RegimentAbstract::setGroups(const QList<RecruitsGroup> &value)
{
    groups = value;
}

void RegimentAbstract::addGroup(const RecruitsGroup& r)
{
	//TODO : Check if there is already a group with the same model before inserting it
	groups.append(r);
}

void RegimentAbstract::removeGroup(const RecruitsGroup& r)
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

void RegimentAbstract::setPoints(const int& value)
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

int RegimentAbstract::getBannerPoints() const
{
	return bannerPoints;
}

void RegimentAbstract::setBannerPoints(const int& value)
{
	bannerPoints = value;
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
    QList<RecruitsGroup>::const_iterator i = groups.constBegin();
    while (i != groups.constEnd()) {
        points += i->computePoints();
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
	if(banner)
	{
		points += bannerPoints;
	}
    return points;
}

QString RegimentAbstract::displayInfo() const
{
    QString s;
    QTextStream info(&s);
    info << "********************************************************" << endl;
    info << "******                  Regiment                  ******" << endl;
    info << "********************************************************" << endl;
    info << "Name : " << name << endl;
    if(musician)
    {
        info << "Has a musician for " << musicianPoints << " points." << endl;
	}
	else info << "Has no musician." << endl;
    if(banner)
    {
		info << "Has a banner for " << bannerPoints << " points." << endl;
	}
	else info << "Has no banner." << endl;
	if(champion)
    {
		info << "Has a champion : " << endl;
		info << championStats.displayString();
	}
	else info << "Has no musician." << endl;
    info << "Contains " << groups.size() << " groups : " << endl;
    for(int i = 0; i < groups.size() ; ++i)
	{
        info << "*******************************************************" << endl;
        info << groups[i].getNb() << " Number of models in the group :" << endl;
        info << groups[i].getModel()->displayStringInfo() << endl;
        info << groups[i].getPath() << endl;
    }
    info << "********************************************************" << endl;
    info << "********************************************************" << endl;
    return s;
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

    for(int i = 0; i < obj.groups.size() ; ++i)
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

bool RegimentAbstract::operator==(const RegimentAbstract& obj)
{
	if(name == obj.name &&
		musician == obj.musician &&
        musicianPoints == obj.musicianPoints &&
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
