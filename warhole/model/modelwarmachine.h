#ifndef MODELWARMACHINE_H
#define MODELWARMACHINE_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelabstract.h"
#include "modelinfantery.h"

class ModelWarMachine : public ModelAbstract
{
    Q_OBJECT
public:
    ModelWarMachine(QObject *parent = 0);

    ModelWarMachine(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                  const QString &strength, const QString &toughness, const QString &wounds,
                  const QString &init, const QString &attacks, const QString &leadership,
                  const QString &save, const QString &invSave, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                  const QString& specRules, QObject *parent = 0);


    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

    QList<ModelInfantery *> getCrew() const;
    void setCrew(const QList<ModelInfantery *> &value);
    void addCrewMember(ModelInfantery* c);
    void removeCrewMember(ModelInfantery* c);

private:
    QString specialRules;
    QList<ModelInfantery *> crew;
};

#endif // MODELWARMACHINE_H
