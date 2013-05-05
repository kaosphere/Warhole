#ifndef MODELINFANTERY_H
#define MODELINFANTERY_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelabstract.h"

class ModelInfantery : protected ModelAbstract
{
public:
    ModelInfantery();

    ModelInfantery(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                  const QString &strength, const QString &toughness, const QString &wounds,
                  const QString &init, const QString &attacks, const QString &leadership,
                  const QString &save, const QString &invSave, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                  const QString& specRules);


    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

private:
    QString specialRules;

};

#endif // MODELINFANTERY_H
