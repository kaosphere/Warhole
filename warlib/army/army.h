#ifndef Army_H
#define Army_H

#include "regiment/regimentabstract.h"
#include <QString>
#include <QList>

class Army
{
public:
    Army();

    QString getName() const;
    void setName(const QString &value);

    QList<RegimentAbstract> getUnits() const;
    void setUnits(const QList<RegimentAbstract> &value);
    void addUnit(const RegimentAbstract& u);
    void removeUnit(const RegimentAbstract& u);

    unsigned int getPoints() const;
    void setPoints(unsigned int value);

    friend QDataStream & operator << (QDataStream &, const Army &);
    friend QDataStream & operator >> (QDataStream &, Army &);

private:
    QString name;
    QList<RegimentAbstract> units;
    unsigned int points;
};

#endif // Army_H
