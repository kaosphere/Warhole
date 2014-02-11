#include "modelfactory.h"

using namespace std;

ModelFactory::ModelFactory()
{

}

QMap<QString, ModelAbstract*> ModelFactory::factory_model_map = QMap<QString, ModelAbstract*>();

void ModelFactory::associateKeyToClass(const QString &key, ModelAbstract *mod)
{
    if(factory_model_map.find(key) == factory_model_map.end()) // key is not already in map
    {
        factory_model_map[key] = mod; // add key - mod association in map
    }
}

ModelAbstract *ModelFactory::createFromFile(const QString &key, const QString path) const
{
    ModelAbstract* tmp = 0;
    QMap<QString, ModelAbstract*>::const_iterator it = factory_model_map.find(key);

    if(it != factory_model_map.end()) // key was found in map
    {
        tmp = *it;
        tmp = tmp->setFromFile(path);

        qDebug() << "key found in map " << key;
        qDebug() << "name " << tmp->getStats().getName();
    }

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






