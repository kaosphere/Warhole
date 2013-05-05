#ifndef MODELCHARRIOT_H
#define MODELCHARRIOT_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelabstract.h"
#include "modelanimal.h"
#include "modelinfantery.h"

class ModelCharriot : public ModelAbstract
{
public:
    ModelCharriot();

    ModelCharriot(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                  const QString &strength, const QString &toughness, const QString &wounds,
                  const QString &init, const QString &attacks, const QString &leadership,
                  const QString &save, const QString &invSave, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                  const QString& specRules);


    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);


    QList<ModelAnimal *> getMount() const;
    void setMount(const QList<ModelAnimal *> &value);
    void addMount(ModelAnimal* m);
    void removeMount(ModelAnimal* m);

    QList<ModelInfantery *> getCrew() const;
    void setCrew(const QList<ModelInfantery *> &value);
    void addCrew(ModelInfantery* c);
    void removeCrew(ModelInfantery* c);

private:
    QString specialRules;
    QList<ModelAnimal *> mounts;
    QList<ModelInfantery *> crew;
};

#endif // MODELCHARRIOT_H
