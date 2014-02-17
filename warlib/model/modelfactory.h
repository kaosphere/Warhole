#ifndef MODELFACTORY_H
#define MODELFACTORY_H

#include <QMap>
#include <QString>
#include "modelabstract.h"
#include "paramsfromUI/paramsfromuimodel.h"

#include<QDebug>

class ModelFactory
{
public:
    ModelFactory();
    static void associateKeyToClass(const QString &key, ModelAbstract* mod);
    ModelAbstract* createFromFile(const QString& path) const;
    ModelAbstract* createFromUI(const QString& key, const ParamsfromUImodel *params) const;
	

public:
    static QMap<QString,ModelAbstract*> factory_model_map;
    
};

#endif // MODELFACTORY_H
