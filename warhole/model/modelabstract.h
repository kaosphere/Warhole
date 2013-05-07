#ifndef MODELABSTRACT_H
#define MODELABSTRACT_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "option/optionmodel.h"
#include "stats/statsmodel.h"

class ModelAbstract
{
public:
    explicit ModelAbstract();

    ModelAbstract(const StatsModel& stat, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& url, bool figSup);

    ModelAbstract(const QString &n, const QString &move, const QString &weaponS,
                  const QString &balisticS, const QString &strength, const QString &toughness,
                  const QString &wounds, const QString &init, const QString &attacks,
                  const QString &leadership, const QString &save, const QString &invSave, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& url, bool figSup);

    ModelAbstract(const ModelAbstract &Copy);

    ~ModelAbstract();

    StatsModel getStats() const;
    void setStats(const StatsModel &value);

    int getSquareBaseW() const;
    void setSquareBaseW(int value);

    int getSquareBaseL() const;
    void setSquareBaseL(int value);

    int getUnitPower() const;
    void setUnitPower(int value);

    QPixmap *getImage() const;
    void setImage(QPixmap *value);

    bool getFigSupInd() const;
    void setFigSupInd(bool value);

    QList<OptionModel> getOptions() const;
    void setOptions(const QList<OptionModel> &value);
    void addOption(OptionModel opt);
    void removeOption(OptionModel opt);

    QString getUrlImage() const;
    void setUrlImage(const QString &value);

    QDataStream & streamOut() const;
    void streamIn(QDataStream &in);


protected:

    StatsModel stats;
    //QList<ModelAbstract *> champion; //list of possible champion

    int squareBaseW;    //width of the square base
    int squareBaseL;    //length of the square base

    int unitPower;      //unit power of the model

    bool figSupInd;     //independant models (for charriots, war machines and monsters)

    QPixmap *image;     //sprite of the model to be used in the graphics
    QString urlImage;

    QList<OptionModel> options;   //list of options possible for model

    
public slots:

signals:
    
};

#endif // MODELABSTRACT_H
