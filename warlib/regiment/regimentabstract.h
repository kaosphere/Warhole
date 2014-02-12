#ifndef REGIMENTABSTRACT_H
#define REGIMENTABSTRACT_H

#include "model/modelabstract.h"
#include "model/modelcavalry.h"
#include "model/modelcharacter.h"
#include "model/modelcharriot.h"
#include "model/modelinfantery.h"
#include "model/modelmonster.h"
#include "model/modelwarmachine.h"
#include "stats/statsmodel.h"
#include "option/optionmodel.h"
#include "recruitsgroup.h"

#include <QString>
#include <QList>


class RegimentAbstract
{
public:
    RegimentAbstract();
    RegimentAbstract(const QString& n,
                     const bool& m, const bool& s,
                     const bool& c, const bool& b,
                     const StatsModel& st, const QList<RecruitsGroup> g);
    RegimentAbstract(const RegimentAbstract& u);

    bool getMusician() const;
    void setMusician(bool value);

    bool getBanner() const;
    void setBanner(bool value);

    QList<RecruitsGroup> getGroups() const;
    void setGroups(const QList<RecruitsGroup> &value);
    void addGroup(RecruitsGroup r);
    void removeGroup(RecruitsGroup r);

    QString getName() const;
    void setName(const QString &value);

    bool getChampion() const;
    void setChampion(bool value);

    bool getSkirmishers() const;
    void setSkirmishers(bool value);

    StatsModel getChampionStats() const;
    void setChampionStats(const StatsModel &value);

    friend QDataStream & operator << (QDataStream &, const RegimentAbstract &);
    friend QDataStream & operator >> (QDataStream &, RegimentAbstract &);

    void loadAllModels();

    int getPoints() const;
    void setPoints(int value);

    int getStartingCount() const;
    void setStartingCount(int value);

    int computePoints();

private:
    QString name;
    QList<RecruitsGroup> groups;
    bool banner;
    bool musician;
    bool champion;
    bool skirmishers;
    StatsModel championStats;
    int points;
    int startingCount;
};

#endif // REGIMENTABSTRACT_H
