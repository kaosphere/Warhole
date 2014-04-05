#include "recruitsgroup.h"

using namespace QLogger;

const QString RecruitsGroup::LOG_ID_INFO = "RecruitsGroup_info";
const QString RecruitsGroup::LOG_ID_TRACE = "RecruitsGroup_trace";
const QString RecruitsGroup::LOG_ID_WARN = "RecruitsGroup_warm";
const QString RecruitsGroup::LOG_ID_ERR = "RecruitsGroup_err";

RecruitsGroup::RecruitsGroup()
{
    model = new ModelAbstract();
    casualties = 0;
    nb = 0;
    path = "";
    model = NULL;

    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);
}

RecruitsGroup::RecruitsGroup(const int &n, const int &c, const QString& p)
{
    casualties = c;
    nb = n;
    path = p;
    model = fac.createFromFile(path);

    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    QLog_Info(LOG_ID_INFO, "RecruitsGroup(n,c,p) : RecruitsGroup created with following model : ");
    QLog_Info(LOG_ID_INFO, model->displayStringInfo());
}

RecruitsGroup::RecruitsGroup(const RecruitsGroup& copy)
{
    casualties = copy.casualties;
    nb = copy.nb;
    path = copy.path;
    model = fac.createFromFile(copy.path);
}

RecruitsGroup::~RecruitsGroup()
{
    if(model) delete model;
}

QDataStream & operator <<(QDataStream& out, const RecruitsGroup& obj)
{
    // Model is not in the serialization because we want the regiment to be bound with
    // a .unit file which is susceptible to change over time
    out << obj.nb
        << obj.casualties
        << obj.path;
        obj.model->serializeOut(out);

    return out;
}

QDataStream & operator >>(QDataStream& in, RecruitsGroup& obj)
{
    // Same comment that for other stream operator
    in >> obj.nb;
    in >> obj.casualties;
    in >> obj.path;

    obj.model = obj.fac.createEmptyModel(obj.path.section('/',-2,-2));

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

int RecruitsGroup::computePoints() const
{
	if(model)
	{
		return (nb * model->computePoints());
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
