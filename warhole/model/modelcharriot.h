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
                  const QString &save, const QString &invSave, const int points, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                  const QString& specRules);
    ~ModelCharriot();

    static void initModelCharriotSystem();
    void load(QString path);
    void save(QString path);

    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

private:
    QString specialRules;
    QList<ModelAnimal *> mounts;
    QList<ModelInfantery *> crew;

    friend QDataStream & operator << (QDataStream &, const ModelCharriot &);
    friend QDataStream & operator >> (QDataStream &, ModelCharriot &);
};

Q_DECLARE_METATYPE(ModelCharriot)
QDataStream & operator << (QDataStream & out, const  ModelCharriot &);
QDataStream & operator >> (QDataStream & in,  ModelCharriot &);

#endif // MODELCHARRIOT_H
