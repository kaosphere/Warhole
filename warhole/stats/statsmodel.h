#ifndef STATSMODEL_H
#define STATSMODEL_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

class StatsModel
{
public:
    StatsModel();



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

};

#endif // STATSMODEL_H
