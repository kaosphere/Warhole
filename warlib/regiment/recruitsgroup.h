#ifndef RECRUITSGROUP_H
#define RECRUITSGROUP_H

#include "defines.h"
#include <option/optionmodel.h>
#include <model/modelcavalry.h>
#include <model/modelcharacter.h>
#include <model/modelcharriot.h>
#include <model/modelinfantery.h>
#include <model/modelmonster.h>
#include <model/modelwarmachine.h>
#include <model/modelfactory.h>
#include <QString>
#include <QDataStream>

// The RecruitsGroup represents a group of same type models inside a regiment
// The class prevents to have to instanciate several exact same models for
// a regiment. To handle that, a number stores how many models are in the group
// and how many casualties the group has. The path is the direct link to a .unit
// file.

class RecruitsGroup
{
public:
    RecruitsGroup();
    RecruitsGroup(const int &n, const int &c, const QString& p);
    ~RecruitsGroup();

    ModelAbstract *getModel() const;
    void setModel(ModelAbstract *value);

    int getNb() const;
    void setNb(int value);

    int getCasualties() const;
    void setCasualties(int value);

    QString getPath() const;
    void setPath(const QString &value);

    bool operator==(const RecruitsGroup&);

    int computePoints();

    friend QDataStream & operator << (QDataStream &, const RecruitsGroup &);
    friend QDataStream & operator >> (QDataStream &, RecruitsGroup &);

private:
    ModelAbstract* model;
    int nb;
    int casualties;
    QString path;
};

#endif // RECRUITSGROUP_H
