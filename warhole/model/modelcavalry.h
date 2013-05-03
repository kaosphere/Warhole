#ifndef MODELCAVALRY_H
#define MODELCAVALRY_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelabstract.h"

class ModelCavalry : public ModelAbstract
{
    Q_OBJECT
public:
    ModelCavalry(QObject *parent = 0);

    ModelCavalry(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                  const QString &strength, const QString &toughness, const QString &wounds,
                  const QString &init, const QString &attacks, const QString &leadership,
                  const QString &save, const QString &invSave, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                  const QString& specRules, QObject *parent = 0);


    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

    //monture du cavalier
    ModelAbstract *getMount() const;
    void setMount(ModelAbstract *value);

private:
    QString specialRules;
    ModelAbstract* mount;
};

#endif // MODELCAVALRY_H
