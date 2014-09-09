#ifndef RECRUITSGROUP_H
#define RECRUITSGROUP_H

#include "defines.h"
#include <game/option/optionmodel.h>
#include <game/model/modelabstract.h>
#include <game/model/modelfactory.h>
#include <QString>
#include <QDataStream>
#include <Utilities/QLogger/QLogger.h>
#include "game/magicalObject/magicalobject.h"

// The RecruitsGroup represents a group of same type models inside a regiment
// The class prevents to have to instanciate several exact same models for
// a regiment. To handle that, a number stores how many models are in the group
// and how many casualties the group has. The path is the direct link to a .unit
// file.

class RecruitsGroup : public QObject
{
public:
    RecruitsGroup(QObject* parent = 0);
    RecruitsGroup(const int &n, const int &c, const QString& p, QObject* parent = 0);
    RecruitsGroup(const RecruitsGroup &copy);
    ~RecruitsGroup();

    ModelAbstract *getModel() const;
    void setModel(ModelAbstract *value);

    int getNb() const;
    void setNb(int value);

    int getCasualties() const;
    void setCasualties(int value);

    QString getPath() const;
    void setPath(const QString &value);

    bool operator==(const RecruitsGroup& obj) const;
    RecruitsGroup& operator=(const RecruitsGroup& copy);
    
    int computePoints() const;

    friend QDataStream & operator << (QDataStream &, const RecruitsGroup &);
    friend QDataStream & operator >> (QDataStream &, RecruitsGroup &);

    void loadPath();

    void addMagicalObject(const MagicalObject& m);
    void removeMagicalObject(const MagicalObject& m);
    void clearMagicalObjects();
    QList<MagicalObject> getObjects() const;
    void setObjects(const QList<MagicalObject> &value);

private:
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    ModelAbstract* model;
    int nb;
    int casualties;
    QString path;
    QList<MagicalObject> objects;
};

#endif // RECRUITSGROUP_H
