#ifndef MODELANIMAL_H
#define MODELANIMAL_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelabstract.h"

class ModelAnimal : public ModelAbstract
{
    Q_OBJECT
public:
    ModelAnimal(QObject *parent = 0);

    ModelAnimal(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                  const QString &strength, const QString &toughness, const QString &wounds,
                  const QString &init, const QString &attacks, const QString &leadership,
                  const QString &save, const QString &invSave, const QList<ModelAbstract *> &champ, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                  const QString& specRules, QObject *parent = 0);


    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

private:
    QString specialRules;
};

#endif // MODELANIMAL_H
