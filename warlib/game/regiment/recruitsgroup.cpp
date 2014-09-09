#include "recruitsgroup.h"

using namespace QLogger;

const QString RecruitsGroup::LOG_ID_INFO = "RecruitsGroup_info";
const QString RecruitsGroup::LOG_ID_TRACE = "RecruitsGroup_trace";
const QString RecruitsGroup::LOG_ID_WARN = "RecruitsGroup_warm";
const QString RecruitsGroup::LOG_ID_ERR = "RecruitsGroup_err";

RecruitsGroup::RecruitsGroup(QObject *parent) : QObject(parent)
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

RecruitsGroup::RecruitsGroup(const int &n, const int &c, const QString& p, QObject *parent) : QObject(parent)
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

RecruitsGroup::RecruitsGroup(const RecruitsGroup& copy) : QObject(copy.parent())
{
    casualties = copy.casualties;
    nb = copy.nb;
    path = copy.path;
    model = copy.model->clone();
    objects = copy.objects;

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
    out << SAVE_VERSION
        << obj.nb
        << obj.casualties
        << obj.path;
    obj.model->serializeOut(out);

    out << obj.objects.size();
    for(int i = 0; i< obj.objects.size(); ++i)
    {
        out << obj.objects[i];
    }

    return out;
}

QDataStream & operator >>(QDataStream& in, RecruitsGroup& obj)
{
    ModelFactory fac;
    int version = 0;
    int  objectCount = 0;

    // Same comment that for other stream operator
    in >> version;
    in >> obj.nb;
    in >> obj.casualties;
    in >> obj.path;

    obj.model = fac.createEmptyModel(obj.path.section('/',-2,-2));

    obj.model->serializeIn(in);

    in >> objectCount;

    for(int i = 0; i< objectCount; ++i)
    {
        MagicalObject m;
        in >> m;
        obj.addMagicalObject(m);
    }

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

void RecruitsGroup::addMagicalObject(const MagicalObject &m)
{
    objects.append(m);
}

void RecruitsGroup::removeMagicalObject(const MagicalObject &m)
{
    objects.removeOne(m);
}

void RecruitsGroup::clearMagicalObjects()
{
    objects.clear();
}

QList<MagicalObject> RecruitsGroup::getObjects() const
{
    return objects;
}

void RecruitsGroup::setObjects(const QList<MagicalObject> &value)
{
    objects = value;
}


bool RecruitsGroup::operator==(const RecruitsGroup& obj) const
{
    if(nb == obj.nb &&
       casualties == obj.casualties &&
       path == obj.path &&
       objects == obj.objects)
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
    objects = copy.objects;

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
        for(int i = 0; i< objects.size(); ++i)
        {
            points += objects[i].getPoints();
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
