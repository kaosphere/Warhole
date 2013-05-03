#ifndef MODELINFANTERY_H
#define MODELINFANTERY_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelabstract.h"

class ModelInfantery : protected ModelAbstract
{
    Q_OBJECT
public:
    ModelInfantery();

    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

private:
    QString specialRules;

};

#endif // MODELINFANTERY_H
