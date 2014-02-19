#include "modelfactory.h"

using namespace std;
using namespace QLogger;

const QString ModelFactory::LOG_ID_INFO = "ModelFactory_info";
const QString ModelFactory::LOG_ID_TRACE = "ModelFactory_trace";
const QString ModelFactory::LOG_ID_WARN = "ModelFactory_warm";
const QString ModelFactory::LOG_ID_ERR = "ModelFactory_err";

ModelFactory::ModelFactory()
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);
}

QMap<QString, ModelAbstract*> ModelFactory::factory_model_map = QMap<QString, ModelAbstract*>();

void ModelFactory::associateKeyToClass(const QString &key, ModelAbstract *mod)
{
    if(factory_model_map.find(key) == factory_model_map.end()) // key is not already in map
    {
        factory_model_map[key] = mod; // add key - mod association in map
    }
}

//create the corresponding model type depending on the path
ModelAbstract *ModelFactory::createFromFile(const QString& path) const
{
	ModelAbstract* tmp = 0;
	//extracting type directly in the path
    QString s = path.section('/',-2,-2);        
    QMap<QString, ModelAbstract*>::const_iterator it = factory_model_map.find(s);

    if(it != factory_model_map.end()) // key was found in map
    {
        tmp = *it;
        tmp = tmp->setFromFile(path);

        QLog_Info(LOG_ID_INFO, "Key found in map : " + s);
    }
    else
        QLog_Error(LOG_ID_ERR, "Can't find key in path : " + path);

    return tmp;
}

ModelAbstract* ModelFactory::createFromUI(const QString &key, const ParamsfromUImodel* params) const
{
    ModelAbstract* tmp = 0;
    QMap<QString, ModelAbstract*>::const_iterator it = factory_model_map.find(key);
    if(it != factory_model_map.end()) // key was found in map
    {
        tmp = *it;
        qDebug() << "hi from modelfactory createfromUI !";
        tmp = tmp->setFromUI(params);
    }

    return tmp;
}






