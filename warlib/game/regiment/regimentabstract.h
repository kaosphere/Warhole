#ifndef REGIMENTABSTRACT_H
#define REGIMENTABSTRACT_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "game/model/modelabstract.h"
#include "game/stats/statsmodel.h"
#include "game/option/optionmodel.h"
#include "recruitsgroup.h"
#include "Utilities/QLogger/QLogger.h"



class RegimentAbstract
{
public:
    RegimentAbstract();
    RegimentAbstract(const QString& n,
                     const bool& s,
                     const QList<RecruitsGroup> g,
                     const int& sc);
    RegimentAbstract(const RegimentAbstract& u);

    QList<RecruitsGroup> &getGroups();
    void setGroups(const QList<RecruitsGroup> &value);
    void addGroup(const RecruitsGroup& r);
    void removeGroup(const RecruitsGroup& r);

    QString getName() const;
    void setName(const QString &value);

    bool getSkirmishers() const;
    void setSkirmishers(bool value);

    friend QDataStream & operator << (QDataStream &, const RegimentAbstract &);
    friend QDataStream & operator >> (QDataStream &, RegimentAbstract &);
    
    bool operator==(const RegimentAbstract&);

    void loadAllModels();
	
    int getStartingCount() const;
    void setStartingCount(int value);

    int computePoints();
    int computeTotalNb();

    QString displayInfo() const;
    QString displayShortInfo() const;

    QString getHtml();

private:
	static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    QString name;
    QList<RecruitsGroup> groups; //using a map permits not to have doubles
    bool skirmishers;
    int startingCount;
};

#endif // REGIMENTABSTRACT_H
