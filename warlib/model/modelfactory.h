#ifndef MODELFACTORY_H
#define MODELFACTORY_H

#include <QMap>
#include <QString>
#include "modelabstract.h"
#include "paramsfromUI/paramsfromuimodel.h"
#include "Utilities/QLogger/QLogger.h"

#include<QDebug>

class ModelFactory
{
public:
    ModelFactory();
    static void associateKeyToClass(const QString &key, ModelAbstract* mod);
    ModelAbstract* createEmptyModel(const QString& key);
    ModelAbstract* createFromFile(const QString& path) const;
    ModelAbstract* createFromUI(const QString& key, const ParamsfromUImodel *params) const;
	

public:
    static QMap<QString,ModelAbstract*> factory_model_map;

private:
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;
};

#endif // MODELFACTORY_H
