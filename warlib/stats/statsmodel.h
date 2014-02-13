#ifndef STATSMODEL_H
#define STATSMODEL_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

class StatsModel
{
public:
    StatsModel();
    StatsModel(const StatsModel&);
    StatsModel(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
               const QString &strength, const QString &toughness, const QString &wounds,
               const QString &init, const QString &attacks, const QString &leadership,
               const QString &save, const QString &invSave, int p);

    ~StatsModel();

    StatsModel& operator=(const StatsModel&);

	QString displayStats();

    QString getName() const;
    void setName(const QString &value);

    QString getM() const;
    void setM(const QString &value);

    QString getWs() const;
    void setWs(const QString &value);

    QString getBs() const;
    void setBs(const QString &value);

    QString getS() const;
    void setS(const QString &value);

    QString getT() const;
    void setT(const QString &value);

    QString getW() const;
    void setW(const QString &value);

    QString getI() const;
    void setI(const QString &value);

    QString getA() const;
    void setA(const QString &value);

    QString getLd() const;
    void setLd(const QString &value);

    QString getSvg() const;
    void setSvg(const QString &value);

    QString getSvgInv() const;
    void setSvgInv(const QString &value);

    int getPoints() const;
    void setPoints(int value);

protected:
    QString name;
    QString m;      //movement
    QString ws;     //weapon skill
    QString bs;     //balistic skill
    QString s;      //strength
    QString t;      //toughtness
    QString w;      //wounds
    QString i;      //initiative
    QString a;      //attacks
    QString ld;     //leadership
    QString svg;    //armor save
    QString svgInv; //invulnerable armor save

    int points;     //points of the model

    friend QDataStream & operator << (QDataStream &, const StatsModel &);
    friend QDataStream & operator >> (QDataStream &, StatsModel &);

};

#endif // STATSMODEL_H
