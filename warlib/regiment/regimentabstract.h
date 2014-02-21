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
                     const bool& m, const int& mp,
                     const bool& s,
                     const bool& c, const bool& b,
                     const StatsModel& st,
                     const QMap<QString, RecruitsGroup> g,
                     const int& p,
                     const int& sc);
    RegimentAbstract(const RegimentAbstract& u);

    bool getMusician() const;
    void setMusician(bool value);

    bool getBanner() const;
    void setBanner(bool value);

    QMap<QString, RecruitsGroup> getGroups() const;
    void setGroups(const QMap<QString, RecruitsGroup> &value);
    void addGroup(const RecruitsGroup& r);
    void removeGroup(const RecruitsGroup& r);

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
    
    bool operator==(const RegimentAbstract&);

    void loadAllModels();

    int getPoints() const;
    void setPoints(const int& value);
    
    int getMusicianPoints() const;
    void setMusicianPoints(const int& value);

    int getStartingCount() const;
    void setStartingCount(int value);

    int computePoints();

    QString displayInfo() const;

private:
    QString name;
    QMap<QString, RecruitsGroup> groups; //using a map permits not to have doubles
    bool banner;
    bool musician;
    int musicianPoints;
    bool champion;
    bool skirmishers;
    StatsModel championStats;
    int points;
    int startingCount;
};

#endif // REGIMENTABSTRACT_H
