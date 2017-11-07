/*! ********************************************************************
* magicalobject.h
* MagicalObject class
*
* AUTEUR: Alexandre Jumeline
* DATE: 03-04-2014
*************************************************************************/

#ifndef MAGICALOBJECT_H
#define MAGICALOBJECT_H

#include <QObject>
#include <QtCore>
#include "defines.h"
#include "Utilities/QLogger/QLogger.h"

class MagicalObject : public QObject
{
    Q_OBJECT
public:
    explicit MagicalObject(QObject *parent = 0);
    MagicalObject(QString n,
                  int p,
                  bool c,
                  QString s,
                  QObject* parent = 0);
    MagicalObject(const MagicalObject& copy);
    ~MagicalObject();

    QString getName() const;
    void setName(const QString &value);

    int getPoints() const;
    void setPoints(int value);

    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

    bool getCabalistic() const;
    void setCabalistic(bool value);

    bool operator==(const MagicalObject& other);
    MagicalObject& operator=(const MagicalObject& other);

    QString displayString() const;

    QString getHtml();

    friend QDataStream & operator << (QDataStream &out, const MagicalObject &obj);
    friend QDataStream & operator >> (QDataStream &in, MagicalObject &obj);

    void load(QString path);
    void save(QString path);
    static void initMagicalObjectSystem();
private:
    QString name;
    int points;
    QString specialRules;
    bool cabalistic;

    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

signals:

public slots:

};

Q_DECLARE_METATYPE(MagicalObject)

#endif // MAGICALOBJECT_H
