#ifndef Army_H
#define Army_H

#include "game/regiment/regimentabstract.h"
#include <QtCore>
#include <QString>
#include <QList>
#include "Utilities/QLogger/QLogger.h"
#include "core/warlibexception.h"

class Army : public QObject
{
    Q_OBJECT
public:
    Army(QObject* parent = 0);
    Army(const Army& copy);

    virtual ~Army();

	static void initArmySystem();

    QString getName() const;
    void setName(const QString &value);

    QList<RegimentAbstract> &getUnits();
    void setUnits(const QList<RegimentAbstract> &value);
    void addUnit(const RegimentAbstract& u);
    void removeUnit(const RegimentAbstract& u);
    
    void save(const QString& path);
    void load(const QString& path);

    friend QDataStream & operator << (QDataStream &, const Army &);
    friend QDataStream & operator >> (QDataStream &, Army &);

    bool operator==(const Army& obj);
    Army& operator=(const Army& obj);
    
    QString displayInfo() const;
    QString displayShortInfo() const;

    QString getHtml();

    int computePoints();

private:
    QString name;
    QList<RegimentAbstract> units;

    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

};

Q_DECLARE_METATYPE(Army)

#endif // Army_H
