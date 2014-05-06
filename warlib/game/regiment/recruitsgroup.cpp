#include "recruitsgroup.h"

using namespace QLogger;

const QString RecruitsGroup::LOG_ID_INFO = "RecruitsGroup_info";
const QString RecruitsGroup::LOG_ID_TRACE = "RecruitsGroup_trace";
const QString RecruitsGroup::LOG_ID_WARN = "RecruitsGroup_warm";
const QString RecruitsGroup::LOG_ID_ERR = "RecruitsGroup_err";

RecruitsGroup::RecruitsGroup()
{
    casualties = 0;
    nb = 0;
    path = "";

    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);
}

RecruitsGroup::RecruitsGroup(const int &n, const int &c, const QString& p)
{
    ModelFactory fac;
    casualties = c;
    nb = n;
    path = p;
    model = fac.createFromFile(path);

    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);
}

RecruitsGroup::RecruitsGroup(const RecruitsGroup& copy)
{
    casualties = copy.casualties;
    nb = copy.nb;
    path = copy.path;
    model = copy.model->clone();

    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);
}

RecruitsGroup::~RecruitsGroup()
{
    if(model) delete model;
}

QDataStream & operator <<(QDataStream& out, const RecruitsGroup& obj)
{
    // Model is not in the serialization because we want the regiment to be bound with
    // a .unit file which is susceptible to change over time
    out << SAVE_VERSION
        << obj.nb
        << obj.casualties
        << obj.path;
    obj.model->serializeOut(out);

    return out;
}

QDataStream & operator >>(QDataStream& in, RecruitsGroup& obj)
{
    ModelFactory fac;
    int version = 0;
    // Same comment that for other stream operator
    in >> version;
    in >> obj.nb;
    in >> obj.casualties;
    in >> obj.path;

    obj.model = fac.createEmptyModel(obj.path.section('/',-2,-2));

    obj.model->serializeIn(in);

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

void RecruitsGroup::loadPath()
{
    ModelFactory fac;

    if(!path.isEmpty())
        model = fac.createFromFile(path);
    else
        QLog_Error(LOG_ID_ERR, "loadPath() - Path is Empty.");
}

bool RecruitsGroup::operator==(const RecruitsGroup& obj) const
{
    if(nb == obj.nb &&
       casualties == obj.casualties &&
       path == obj.path)
    {
        return true;
    }
    else return false;
}

RecruitsGroup &RecruitsGroup::operator =(const RecruitsGroup &copy)
{
    casualties = copy.casualties;
    nb = copy.nb;
    path = copy.path;
    model = copy.model->clone();

    return *this;
}

int RecruitsGroup::computePoints() const
{
    int points = 0;
	if(model)
	{
        points += (nb * model->computePoints());
        points += model->getRegimentPoints();
        if(model->getMusician())
        {
            points += model->getMusicianPoints();
        }
        if(model->getChampion())
        {
            points += model->getChampionStats().getPoints();
        }
        if(model->getBanner())
        {
            points += model->getBannerPoints();
        }
        return points;
	}
	else
	{
        QLog_Error(LOG_ID_ERR, "Model is not instanciated, can't compute points.");
		return 0;
	}
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
