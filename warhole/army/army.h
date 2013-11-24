#ifndef Army_H
#define Army_H

#include "unit/unitabstract.h"
#include <QString>
#include <QList>

class Army
{
public:
    Army();

    QString getName() const;
    void setName(const QString &value);

    QList<UnitAbstract> getUnits() const;
    void setUnits(const QList<UnitAbstract> &value);
    void addUnit(const UnitAbstract& u);
    void removeUnit(const UnitAbstract& u);

    unsigned int getPoints() const;
    void setPoints(unsigned int value);

    friend QDataStream & operator << (QDataStream &, const Army &);
    friend QDataStream & operator >> (QDataStream &, Army &);


private:
    QString name;
    QList<UnitAbstract> units;
    unsigned int points;
};

#endif // Army_H
