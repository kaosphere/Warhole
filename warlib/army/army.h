#ifndef Army_H
#define Army_H

#include "regiment/regimentabstract.h"
#include <QString>
#include <QList>

class Army
{
public:
    Army();

	static void initArmySystem();

    QString getName() const;
    void setName(const QString &value);

    QList<RegimentAbstract> &getUnits();
    void setUnits(const QList<RegimentAbstract> &value);
    void addUnit(const RegimentAbstract& u);
    void removeUnit(const RegimentAbstract& u);
    
    void save(const QString& path);
    void load(const QString& path);

    unsigned int getPoints() const;
    void setPoints(unsigned int value);

    friend QDataStream & operator << (QDataStream &, const Army &);
    friend QDataStream & operator >> (QDataStream &, Army &);
    
    QString displayInfo() const;
    QString displayShortInfo() const;

    QString &getHtml();

    int computePoints();

private:
    QString name;
    QList<RegimentAbstract> units;
    
    friend QDataStream & operator << (QDataStream &, const Army &);
    friend QDataStream & operator >> (QDataStream &, Army &);
};

Q_DECLARE_METATYPE(Army)
QDataStream & operator << (QDataStream & out, const Army &);
QDataStream & operator >> (QDataStream & in, Army &);

#endif // Army_H
