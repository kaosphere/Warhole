#ifndef MODELANIMAL_H
#define MODELANIMAL_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>
#include <QVariant>

#include "modelabstract.h"

class ModelAnimal : public ModelAbstract
{
public:
    ModelAnimal();
    ModelAnimal(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                  const QString &strength, const QString &toughness, const QString &wounds,
                  const QString &init, const QString &attacks, const QString &leadership,
                  const QString &save, const QString &invSave, const int points, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                  const QString& specRules);
    ModelAnimal(const ModelAnimal & Copy);
    ~ModelAnimal();
    static void initModelAnimalSystem ();

    void load(QString path);
    void save(QString path);

    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

protected:
    QString specialRules;

    friend QDataStream & operator << (QDataStream &, const ModelAnimal &);
    friend QDataStream & operator >> (QDataStream &, ModelAnimal &);
};

Q_DECLARE_METATYPE(ModelAnimal)
QDataStream & operator << (QDataStream & out, const ModelAnimal &);
QDataStream & operator >> (QDataStream & in, ModelAnimal &);

#endif // MODELANIMAL_H
