#ifndef MODELFACTORY_H
#define MODELFACTORY_H

#include <QMap>
#include <QString>
#include "modelabstract.h"

#include<QDebug>

class ModelFactory
{
public:
    ModelFactory();
    static void associateKeyToClass(const QString &key, ModelAbstract* mod);
    ModelAbstract* create(const QString& key, const QString path) const;

public:
    static QMap<QString,ModelAbstract*> factory_model_map;

};

#endif // MODELFACTORY_H
