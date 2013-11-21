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
    UnitAbstract(const QString& n, const QList<ModelAbstract*> & l, const QString& t,
                 const bool& m, const bool& s, const bool& c, const bool& b, const StatsModel& st);
    UnitAbstract(const UnitAbstract& u);

    bool operator==(const UnitAbstract&);

    bool getMusician() const;
    void setMusician(bool value);

    bool getBanner() const;
    void setBanner(bool value);

    QList<ModelAbstract *> getModels() const;
    void setModels(const QList<ModelAbstract *> &value);
    void addModel(ModelAbstract *m);
    void removeModel(ModelAbstract * m);

    QString getName() const;
    void setName(const QString &value);

    bool getChampion() const;
    void setChampion(bool value);

    bool getSkirmishers() const;
    void setSkirmishers(bool value);

    QString getType() const;
    void setType(const QString &value);

    StatsModel getChampionStats() const;
    void setChampionStats(const StatsModel &value);

private:
    QString name;
    QList<ModelAbstract *> models;
    QString type;
    bool banner;
    bool musician;
    bool champion;
    bool skirmishers;
    StatsModel championStats;
};

#endif // UNITABSTRACT_H
