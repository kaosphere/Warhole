#ifndef UNITABSTRACT_H
#define UNITABSTRACT_H

#include "model/modelabstract.h"
#include "stats/statsmodel.h"
#include "option/optionmodel.h"

#include <QString>
#include <QList>

class UnitAbstract
{
public:
    UnitAbstract();

    bool getMusician() const;
    void setMusician(bool value);

    bool getBanner() const;
    void setBanner(bool value);

    QList<ModelAbstract *> getModels() const;
    void setModels(const QList<ModelAbstract *> &value);
    void addModel(const ModelAbstract& m);
    void removeModel(const ModelAbstract& m);

    QString getName() const;
    void setName(const QString &value);

    bool getChampion() const;
    void setChampion(bool value);

    bool getSkirmishers() const;
    void setSkirmishers(bool value);

private:
    QString name;
    QList<ModelAbstract *> models;
    bool banner;
    bool musician;
    bool champion;
    bool skirmishers;
};

#endif // UNITABSTRACT_H
