#include "regimentabstract.h"

using namespace QLogger;

const QString RegimentAbstract::LOG_ID_INFO = "RegimentAbstract_info";
const QString RegimentAbstract::LOG_ID_TRACE = "RegimentAbstract_trace";
const QString RegimentAbstract::LOG_ID_WARN = "RegimentAbstract_warn";
const QString RegimentAbstract::LOG_ID_ERR = "RegimentAbstract_err";

RegimentAbstract::RegimentAbstract(QObject *parent) : QObject(parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
	manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

	
    name = "";
    skirmishers = false;
    startingCount = 0;
}

RegimentAbstract::RegimentAbstract(const QString &n,
                                   const bool &s,
                                   const QList<RecruitsGroup> g,
                                   const int& sc, QObject *parent) : QObject(parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
	manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

	
    name = n;
    skirmishers = s;
    groups = g;
    startingCount = sc;
}

RegimentAbstract::RegimentAbstract(const RegimentAbstract &u) : QObject(u.parent())
{
    QLoggerManager *manager = QLoggerManager::getInstance();
	manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

	
    name = u.name;
    skirmishers = u.skirmishers;
    groups = u.groups;
    startingCount = u.startingCount;
}

RegimentAbstract::~RegimentAbstract()
{
}

bool RegimentAbstract::getSkirmishers() const
{
    return skirmishers;
}

void RegimentAbstract::setSkirmishers(bool value)
{
    skirmishers = value;
}

QString RegimentAbstract::getName() const
{
    return name;
}

void RegimentAbstract::setName(const QString &value)
{
    name = value;
}

QList<RecruitsGroup>& RegimentAbstract::getGroups()
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
    return points;
}

int RegimentAbstract::computeTotalNb()
{
	int nb = 0;
	QList<RecruitsGroup>::const_iterator i = groups.constBegin();
	while (i != groups.constEnd()) {
		nb += i->getNb();
		++i;
	}
	return nb;
}


QString RegimentAbstract::displayShortInfo() const
{
    QString s;
    QTextStream info(&s);
    info << "********************************************************" << endl;
    info << "******                  Regiment                  ******" << endl;
    info << "********************************************************" << endl;
    info << "Name : " << name << endl;

    info << "Contains " << groups.size() << " groups : " << endl;
    for(int i = 0; i < groups.size() ; ++i)
	{
        info << "*******************************************************" << endl;
        info << groups[i].getNb() << " Number of models in the group :" << endl;
        info << groups[i].getModel()->getStats().getName() << endl;
        info << groups[i].getPath() << endl;
    }
    info << "********************************************************" << endl;
    info << "********************************************************" << endl;
    return s;
}

QString RegimentAbstract::getHtml()
{
    QString html("<table width=100% cols=11 border=1 cellpadding=10>\n");

    html += QString("<tr>\n");
	html += "<td width=17%>\n";
    html += QString("%1")
            .arg(name);
	html += "</td>\n";
    for(int i = 0; i < groups.size() ; ++i)
    {
        html += "<td width=75%>\n";
        html += QString("<h2>%1 %2")
        		.arg(QString::number(groups[i].getNb()))
        		.arg(groups[i].getModel()->getHtml());
        if(groups[i].getModel()->getMusician())
        {
            html += QString("<li>Musicien (%1 pts)</li>\n")
                    .arg(groups[i].getModel()->getMusicianPoints());
        }
        if(groups[i].getModel()->getBanner())
        {
            html += QString("<li>Porte étendard (%1 pts)</li>\n")
                    .arg(groups[i].getModel()->getBannerPoints());
        }
        if(groups[i].getModel()->getChampion())
        {
            html += QString("<li>Champion (%1 pts)</li>\n")
                    .arg(groups[i].getModel()->getChampionStats().getPoints());
        }
        int s = groups[i].getObjects().size();
        if(s)
        {
            for(int k = 0; k<s; ++k)
            {
                html += groups[i].getObjects()[k].getHtml();
            }
        }
        html += "</td>\n";
    }
    html += "<td width=8%>\n";
    html += QString("%1 Points").arg(computePoints());
    html += "</td>\n";
    html += "</tr>\n";
    html += QString("</table>\n");

    return html;
}

QString RegimentAbstract::displayInfo() const
{
    QString s;
    QTextStream info(&s);
    info << "********************************************************" << endl;
    info << "******                  Regiment                  ******" << endl;
    info << "********************************************************" << endl;
    info << "Name : " << name << endl;
    info << "Contains " << groups.size() << " groups : " << endl;
    for(int i = 0; i < groups.size() ; ++i)
	{
        info << "*******************************************************" << endl;
        info << groups[i].getNb() << " Number of models in the group :" << endl;
        info << groups[i].getModel()->displayStringInfo() << endl;
        info << groups[i].getPath() << endl;
        int s = groups[i].getObjects().size();
        if(s)
        {
            for(int k = 0; k<s; ++k)
            {
                info << groups[i].getObjects()[k].displayString();
            }
        }
    }
    info << "********************************************************" << endl;
    info << "********************************************************" << endl;
    return s;
}

QDataStream &operator <<(QDataStream & out, const RegimentAbstract & obj)
{
    out << SAVE_VERSION
        << obj.name
        << obj.skirmishers
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
    int version = 0;

    in >> version;
    in >> obj.name;
    in >> obj.skirmishers;
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
		skirmishers == obj.skirmishers &&
		groups == obj.groups &&
		startingCount == obj.startingCount)
	{
		return true;
	}
    else return false;
}

RegimentAbstract &RegimentAbstract::operator =(const RegimentAbstract &obj)
{
    name = obj.name;
    skirmishers = obj.skirmishers;
    groups = obj.groups;
    startingCount = obj.startingCount;

    return *this;
}
