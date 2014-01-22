#ifndef UNITABSTRACT_H
#define UNITABSTRACT_H

#include "model/modelabstract.h"
#include "model/modelcavalry.h"
#include "model/modelcharacter.h"
#include "model/modelcharriot.h"
#include "model/modelinfantery.h"
#include "model/modelmonster.h"
#include "model/modelwarmachine.h"
#include "stats/statsmodel.h"
#include "option/optionmodel.h"

#include <QString>
#include <QList>

#define INFANTERY_TYPE 0
#define CAVALERY_TYPE 1
#define CHARACTER_TYPE 2
#define CHARRIOT_TYPE 3
#define MONSTER_TYPE 4
#define WARMACHINE_TYPE 5
#define UNKNOWN 99

class UnitAbstract
{
public:
    UnitAbstract();
    UnitAbstract(const QString& n, const QString &p, const QList<ModelAbstract *> &l, const int &t,
                 const bool& m, const bool& s, const bool& c, const bool& b, const StatsModel& st, const int &nb);
    UnitAbstract(const UnitAbstract& u);

    bool operator==(const UnitAbstract&);

    bool getMusician() const;
    void setMusician(bool value);

    bool getBanner() const;
    void setBanner(bool value);

    QList<ModelAbstract*> getModels() const;
    void setModels(const QList<ModelAbstract*> &value);
    void addModel(ModelAbstract* m);
    void removeModel(ModelAbstract* m);

    QString getName() const;
    void setName(const QString &value);

    bool getChampion() const;
    void setChampion(bool value);

    bool getSkirmishers() const;
    void setSkirmishers(bool value);

    int getType() const;
    void setType(const int &value);

    StatsModel getChampionStats() const;
    void setChampionStats(const StatsModel &value);

    QString getPath() const;
    void setPath(const QString &value);

    friend QDataStream & operator << (QDataStream &, const UnitAbstract &);
    friend QDataStream & operator >> (QDataStream &, UnitAbstract &);

    void loadAllModels();

    void updateNbModels();

private:
    QString name;
    QList<ModelAbstract*> models;
    int type;
    bool banner;
    bool musician;
    bool champion;
    bool skirmishers;
    StatsModel championStats;
    QString path;
    int nbModels;
};

#endif // UNITABSTRACT_H
