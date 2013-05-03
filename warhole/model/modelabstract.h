#ifndef MODELABSTRACT_H
#define MODELABSTRACT_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

class ModelAbstract : public QObject
{
    Q_OBJECT
public:
    explicit ModelAbstract(QObject *parent = 0);

    ModelAbstract(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                  const QString &strength, const QString &toughness, const QString &wounds,
                  const QString &init, const QString &attacks, const QString &leadership,
                  const QString &save, const QString &invSave, const QList<ModelAbstract *> &champ, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& urlImage, QObject *parent = 0);

    //private attributes accessors
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

    int getSquareBaseW() const;
    void setSquareBaseW(int value);

    int getSquareBaseL() const;
    void setSquareBaseL(int value);

    int getUnitPower() const;
    void setUnitPower(int value);

    QPixmap *getImage() const;
    void setImage(QPixmap *value);

    QList<ModelAbstract *> getChampion() const;
    void setChampion(QList<ModelAbstract *> value);

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

    QList<ModelAbstract *> champion; //list of possible champion

    int squareBaseW;    //width of the square base
    int squareBaseL;    //length of the square base

    int unitPower;      //unit power of the model

    QPixmap *image;     //sprite of the model to be used in the graphics

    
public slots:

signals:
    
};

#endif // MODELABSTRACT_H
