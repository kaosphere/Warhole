#ifndef MODELWARMACHINE_H
#define MODELWARMACHINE_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelabstract.h"
#include "modelinfantery.h"

class ModelWarMachine : public ModelAbstract
{

public:
    ModelWarMachine();

    ModelWarMachine(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                  const QString &strength, const QString &toughness, const QString &wounds,
                  const QString &init, const QString &attacks, const QString &leadership,
                  const QString &save, const QString &invSave, const int points, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                  const QString& specRules);
    virtual ~ModelWarMachine();

    static void initModelWarMachine();
    virtual ModelWarMachine* setFromFile(QString path);
    virtual ModelWarMachine* setFromUI(const ParamsfromUImodel *params);
    virtual void load(QString path);
    virtual void save(QString path);
    
    virtual QString displayStringInfo();

    virtual int computePoints();

    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

private:
    QString specialRules;
    //TODO : remove this crew shit
    QList<ModelInfantery *> crew;

    friend QDataStream & operator << (QDataStream &, const ModelWarMachine &);
    friend QDataStream & operator >> (QDataStream &, ModelWarMachine &);
};

Q_DECLARE_METATYPE(ModelWarMachine)
QDataStream & operator << (QDataStream & out, const  ModelWarMachine &);
QDataStream & operator >> (QDataStream & in,  ModelWarMachine &);

#endif // MODELWARMACHINE_H
